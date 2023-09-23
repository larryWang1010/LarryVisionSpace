/*
 * Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <vpi/Array.h>
#include <vpi/Image.h>
#include <vpi/Pyramid.h>
#include <vpi/Status.h>
#include <vpi/Stream.h>
#include <vpi/algo/ConvertImageFormat.h>
#include <vpi/algo/GaussianPyramid.h>
#include <vpi/algo/ImageFlip.h>
#include <vpi/algo/ORB.h>

#include <bitset>
#include <cstdio>
#include <cstring>  // for memset
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <vpi/OpenCVInterop.hpp>

#define CHECK_STATUS(STMT)                                    \
    do {                                                      \
        VPIStatus status = (STMT);                            \
        if (status != VPI_SUCCESS) {                          \
            char buffer[VPI_MAX_STATUS_MESSAGE_LENGTH];       \
            vpiGetLastStatusMessage(buffer, sizeof(buffer));  \
            std::ostringstream ss;                            \
            ss << vpiStatusGetName(status) << ": " << buffer; \
            throw std::runtime_error(ss.str());               \
        }                                                     \
    } while (0);

static cv::Mat DrawKeypoints(cv::Mat img, VPIKeypointF32* kpts, int numKeypoints) {
    cv::Mat out;
    img.convertTo(out, CV_8UC1);
    cvtColor(out, out, cv::COLOR_GRAY2BGR);

    if (numKeypoints == 0) {
        return out;
    }

    // prepare our colormap
    cv::Mat cmap(1, 256, CV_8UC3);
    {
        cv::Mat gray(1, 256, CV_8UC1);
        for (int i = 0; i < 256; ++i) {
            gray.at<unsigned char>(0, i) = i;
        }
        applyColorMap(gray, cmap, cv::COLORMAP_HOT);
    }

    for (int i = 0; i < numKeypoints; ++i) {
        cv::Vec3b color = cmap.at<cv::Vec3b>(rand() % 255);
        circle(out, cv::Point(kpts[i].x, kpts[i].y), 3, cv::Scalar(color[0], color[1], color[2]), -1);
    }

    return out;
}

int main(int argc, char* argv[]) {
    // OpenCV image that will be wrapped by a VPIImage.
    // Define it here so that it's destroyed *after* wrapper is destroyed
    cv::Mat cvImage;

    // VPI objects that will be used
    VPIImage imgInput = NULL;
    VPIImage imgGrayScale = NULL;

    VPIPyramid pyrInput = NULL;
    VPIArray keypoints = NULL;
    VPIArray descriptors = NULL;
    VPIPayload orbPayload = NULL;
    VPIStream stream = NULL;

    int retval = 0;

    try {
        // =============================
        // Parse command line parameters

        if (argc != 3) {
            throw std::runtime_error(std::string("Usage: ") + argv[0] + " <cpu|cuda> <input image>");
        }

        std::string strBackend = argv[1];
        std::string strInputFileName = argv[2];

        // Now parse the backend
        VPIBackend backend;

        if (strBackend == "cpu") {
            backend = VPI_BACKEND_CPU;
        } else if (strBackend == "cuda") {
            backend = VPI_BACKEND_CUDA;
        } else {
            throw std::runtime_error("Backend '" + strBackend + "' not recognized, it must be either cpu or cuda.");
        }

        // =====================
        // Load the input image

        cvImage = cv::imread(strInputFileName);
        if (cvImage.empty()) {
            throw std::runtime_error("Can't open first image: '" + strInputFileName + "'");
        }

        // =================================
        // Allocate all VPI resources needed

        // Create the stream where processing will happen
        CHECK_STATUS(vpiStreamCreate(0, &stream));

        // Define the algorithm parameters. We'll use defaults.
        VPIORBParams orbParams;
        CHECK_STATUS(vpiInitORBParams(&orbParams));

        // We now wrap the loaded image into a VPIImage object to be used by VPI.
        // VPI won't make a copy of it, so the original
        // image must be in scope at all times.
        CHECK_STATUS(vpiImageCreateWrapperOpenCVMat(cvImage, 0, &imgInput));

        CHECK_STATUS(vpiImageCreate(cvImage.cols, cvImage.rows, VPI_IMAGE_FORMAT_U8, 0, &imgGrayScale));

        // Create the output keypoint array.
        CHECK_STATUS(
            vpiArrayCreate(orbParams.maxFeatures, VPI_ARRAY_TYPE_KEYPOINT_F32, backend | VPI_BACKEND_CPU, &keypoints));

        // Create the output descriptors array.
        CHECK_STATUS(vpiArrayCreate(orbParams.maxFeatures, VPI_ARRAY_TYPE_BRIEF_DESCRIPTOR, backend | VPI_BACKEND_CPU,
                                    &descriptors));

        // Create the payload for ORB Feature Detector algorithm
        CHECK_STATUS(vpiCreateORBFeatureDetector(backend, 20000, &orbPayload));

        // Create our OpenCV Counterparts
        std::vector<cv::KeyPoint> keypointsOne;
        std::vector<cv::KeyPoint> keypointsTwo;
        cv::Mat descriptorsOne(orbParams.maxFeatures, VPI_BRIEF_DESCRIPTOR_ARRAY_LENGTH, CV_8U);
        cv::Mat descriptorsTwo(orbParams.maxFeatures, VPI_BRIEF_DESCRIPTOR_ARRAY_LENGTH, CV_8U);

        // ================
        // Processing stage

        // First convert input to grayscale
        CHECK_STATUS(vpiSubmitConvertImageFormat(stream, backend, imgInput, imgGrayScale, NULL));

        // Then, create the Gaussian Pyramid for the image and wait for the execution to finish
        CHECK_STATUS(vpiPyramidCreate(cvImage.cols, cvImage.rows, VPI_IMAGE_FORMAT_U8, orbParams.pyramidLevels, 0.5,
                                      backend, &pyrInput));
        CHECK_STATUS(vpiSubmitGaussianPyramidGenerator(stream, backend, imgGrayScale, pyrInput, VPI_BORDER_ZERO));

        // Then get ORB features and wait for the execution to finish
        CHECK_STATUS(vpiSubmitORBFeatureDetector(stream, backend, orbPayload, pyrInput, keypoints, descriptors,
                                                 &orbParams, VPI_BORDER_ZERO));

        CHECK_STATUS(vpiStreamSync(stream));

        // =======================================
        // Output processing and saving it to disk

        // Lock output keypoints and scores to retrieve its data on cpu memory
        VPIArrayData outKeypointsData;
        VPIImageData imgData;
        CHECK_STATUS(vpiArrayLockData(keypoints, VPI_LOCK_READ, VPI_ARRAY_BUFFER_HOST_AOS, &outKeypointsData));
        CHECK_STATUS(vpiImageLockData(imgGrayScale, VPI_LOCK_READ, VPI_IMAGE_BUFFER_HOST_PITCH_LINEAR, &imgData));

        VPIKeypointF32* outKeypoints = (VPIKeypointF32*)outKeypointsData.buffer.aos.data;

        printf("\n%d keypoints found\n", *outKeypointsData.buffer.aos.sizePointer);

        cv::Mat img;
        CHECK_STATUS(vpiImageDataExportOpenCVMat(imgData, &img));

        cv::Mat outImage = DrawKeypoints(img, outKeypoints, *outKeypointsData.buffer.aos.sizePointer);

        imwrite("orb_feature_detector_" + strBackend + ".png", outImage);

        // Done handling outputs, don't forget to unlock them.
        CHECK_STATUS(vpiImageUnlock(imgGrayScale));
        CHECK_STATUS(vpiArrayUnlock(keypoints));

        cv::imwrite("orb_feature_detector_" + strBackend + ".png", outImage);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        retval = 1;
    }

    // ========
    // Clean up

    // Make sure stream is synchronized before destroying the objects
    // that might still be in use.
    vpiStreamSync(stream);

    vpiImageDestroy(imgInput);
    vpiImageDestroy(imgGrayScale);
    vpiArrayDestroy(keypoints);
    vpiArrayDestroy(descriptors);
    vpiPayloadDestroy(orbPayload);
    vpiStreamDestroy(stream);

    return retval;
}
