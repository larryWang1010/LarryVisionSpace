#include <gtest/gtest.h>

#include <bitset>
#include <chrono>
#include <cstdio>
#include <cstring>  // for memset
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <vector>

// #include "ORBextractor.h"
using namespace cv;
using namespace std;
TEST(Feature, cv_orb) {
    cv::Ptr<cv::FeatureDetector> fd = cv::ORB::create(1000, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
    cv::Ptr<cv::DescriptorExtractor> de = fd;

    cv::Mat image = cv::imread("./data/lena.png");

    std::vector<cv::KeyPoint> keypoints;
    fd->detect(image, keypoints);

    cv::Mat descriptors;
    de->compute(image, keypoints, descriptors);

    printf("Detect %lu cv orb keypoints \n", keypoints.size());

    cv::Mat img_keypoints;
    cv::drawKeypoints(image, keypoints, img_keypoints);  // Draw keypoints
    cv::imshow("CV ORB Keypoints", img_keypoints);       // Show detected (drawn) keypoints
    cv::waitKey(5);
}
TEST(Feature, cv_fast) {
    std::string imgPath1 = "data/lena.png";
    Mat src = imread(imgPath1);
    if (src.empty()) cout << "Error, cannot load image..." << endl;

    vector<KeyPoint> keypoints;
    int fast_threshold = 20;
    bool nonmaxSuppression = true;
    FAST(src, keypoints, fast_threshold, nonmaxSuppression);

    // compute responses
    vector<float> responses(keypoints.size());
    for (size_t i = 0; i < keypoints.size(); i++) responses[i] = keypoints[i].response;

    // find max response
    float max_response = *max_element(responses.begin(), responses.end());

    // compute radii
    vector<float> radii(keypoints.size());
    for (size_t i = 0; i < keypoints.size(); i++) radii[i] = INT_MAX;

    for (size_t i = 0; i < keypoints.size(); i++)
        for (size_t j = 0; j < keypoints.size(); j++)
            if (responses[j] > responses[i])
                radii[i] = min(radii[i], static_cast<float>(norm(keypoints[i].pt - keypoints[j].pt)));

    // find minimum radius that satisfies condition
    float min_radius = INT_MAX;
    for (size_t i = 0; i < keypoints.size(); i++)
        if (radii[i] > max_response / 2) min_radius = min(min_radius, radii[i]);

    // keep only keypoints with radius greater than min_radius
    vector<KeyPoint> filtered_keypoints;
    for (size_t i = 0; i < keypoints.size(); i++)
        if (radii[i] >= min_radius && filtered_keypoints.size() < 100)  // set desired number of keypoints here
            filtered_keypoints.push_back(keypoints[i]);

    cout << "number of FAST keypoints detected: " << filtered_keypoints.size() << endl;
    Mat img_keypoints;
    drawKeypoints(src, filtered_keypoints, img_keypoints);  // Draw keypoints
    imshow("CV fast Keypoints", img_keypoints);             // Show detected (drawn) keypoints
    waitKey(5);
}

// #define CHECK_STATUS(STMT)                                    \
//     do {                                                      \
//         VPIStatus status = (STMT);                            \
//         if (status != VPI_SUCCESS) {                          \
//             char buffer[VPI_MAX_STATUS_MESSAGE_LENGTH];       \
//             vpiGetLastStatusMessage(buffer, sizeof(buffer));  \
//             std::ostringstream ss;                            \
//             ss << vpiStatusGetName(status) << ": " << buffer; \
//             throw std::runtime_error(ss.str());               \
//         }                                                     \
//     } while (0);

// static cv::Mat DrawKeypoints(cv::Mat img, VPIKeypointF32* kpts, int numKeypoints) {
//     cv::Mat out;
//     img.convertTo(out, CV_8UC1);
//     cvtColor(out, out, cv::COLOR_GRAY2BGR);

//     if (numKeypoints == 0) {
//         return out;
//     }

//     // prepare our colormap
//     cv::Mat cmap(1, 256, CV_8UC3);
//     {
//         cv::Mat gray(1, 256, CV_8UC1);
//         for (int i = 0; i < 256; ++i) {
//             gray.at<unsigned char>(0, i) = i;
//         }
//         applyColorMap(gray, cmap, cv::COLORMAP_HOT);
//     }

//     for (int i = 0; i < numKeypoints; ++i) {
//         cv::Vec3b color = cmap.at<cv::Vec3b>(rand() % 255);
//         circle(out, cv::Point(kpts[i].x, kpts[i].y), 3, cv::Scalar(color[0], color[1], color[2]), -1);
//     }

//     return out;
// }

// std::string imgPath = "./data/lena.png";

// TEST(Feature, CV_ORB) {
//     cv::Ptr<cv::FeatureDetector> fd = cv::ORB::create(1000, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
//     cv::Ptr<cv::DescriptorExtractor> de = fd;

//     cv::Mat image = cv::imread(imgPath);
//     ASSERT_FALSE(image.empty());

//     std::vector<cv::KeyPoint> keypoints;

//     std::chrono::steady_clock::time_point time_StartExtORB = std::chrono::steady_clock::now();
//     fd->detect(image, keypoints);
//     std::chrono::steady_clock::time_point time_EndExtORB = std::chrono::steady_clock::now();
//     double mTimeORB_Ext =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndExtORB - time_StartExtORB)
//             .count();

//     cv::Mat descriptors;
//     std::chrono::steady_clock::time_point time_StartCalcDesc = std::chrono::steady_clock::now();
//     de->compute(image, keypoints, descriptors);
//     std::chrono::steady_clock::time_point time_EndCalcDesc = std::chrono::steady_clock::now();
//     double mTimeDes_Calc =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndCalcDesc - time_StartCalcDesc)
//             .count();
//     printf("Detect %lu cv orb keypoints, cost %f %f ms \n", keypoints.size(), mTimeORB_Ext, mTimeDes_Calc);

//     // cv::Mat img_keypoints;
//     // cv::drawKeypoints(image, keypoints, img_keypoints);  // Draw keypoints
//     // cv::imshow("CV ORB Keypoints", img_keypoints);       // Show detected (drawn) keypoints
//     // cv::waitKey(10);

//     int roiViolations = 0;
//     for (std::vector<cv::KeyPoint>::const_iterator kp = keypoints.begin(); kp != keypoints.end(); ++kp) {
//         int x = cvRound(kp->pt.x);
//         int y = cvRound(kp->pt.y);

//         ASSERT_LE(0, x);
//         ASSERT_LE(0, y);
//         ASSERT_GT(image.cols, x);
//         ASSERT_GT(image.rows, y);
//     }

//     ASSERT_EQ(0, roiViolations);
// }

// TEST(Feature, VPI_ORB) {
//     // OpenCV image that will be wrapped by a VPIImage.
//     // Define it here so that it's destroyed *after* wrapper is destroyed
//     cv::Mat cvImage;

//     // VPI objects that will be used
//     VPIImage imgInput = NULL;
//     VPIImage imgGrayScale = NULL;

//     VPIPyramid pyrInput = NULL;
//     VPIArray keypoints = NULL;
//     VPIArray descriptors = NULL;
//     VPIPayload orbPayload = NULL;
//     VPIStream stream = NULL;

//     int retval = 0;

//     std::string strBackend = "cuda";                                // cpu or cuda
//     std::string strInputFileName = "./data/kodim08_grayscale.png";  //<input image>

//     // Now parse the backend
//     VPIBackend backend;

//     if (strBackend == "cpu") {
//         backend = VPI_BACKEND_CPU;
//     } else if (strBackend == "cuda") {
//         backend = VPI_BACKEND_CUDA;
//     } else {
//         throw std::runtime_error("Backend '" + strBackend + "' not recognized, it must be either cpu or cuda.");
//     }

//     cvImage = cv::imread(strInputFileName);
//     if (cvImage.empty()) {
//         throw std::runtime_error("Can't open first image: '" + strInputFileName + "'");
//     }

//     // =================================
//     // Allocate all VPI resources needed
//     // Create the stream where processing will happen
//     CHECK_STATUS(vpiStreamCreate(backend | VPI_BACKEND_CPU, &stream));

//     // Define the algorithm parameters. We'll use defaults.
//     VPIORBParams orbParams;
//     CHECK_STATUS(vpiInitORBParams(&orbParams));

//     // We now wrap the loaded image into a VPIImage object to be used by VPI.
//     // VPI won't make a copy of it, so the original
//     // image must be in scope at all times.

//     CHECK_STATUS(vpiImageCreateWrapperOpenCVMat(cvImage, backend | VPI_BACKEND_CPU, &imgInput));

//     CHECK_STATUS(
//         vpiImageCreate(cvImage.cols, cvImage.rows, VPI_IMAGE_FORMAT_U8, backend | VPI_BACKEND_CPU, &imgGrayScale));

//     // Create the output keypoint array.
//     CHECK_STATUS(
//         vpiArrayCreate(orbParams.maxFeatures, VPI_ARRAY_TYPE_KEYPOINT_F32, backend | VPI_BACKEND_CPU, &keypoints));

//     // Create the output descriptors array.
//     CHECK_STATUS(vpiArrayCreate(orbParams.maxFeatures, VPI_ARRAY_TYPE_BRIEF_DESCRIPTOR, backend | VPI_BACKEND_CPU,
//                                 &descriptors));

//     // Create the payload for ORB Feature Detector algorithm
//     CHECK_STATUS(vpiCreateORBFeatureDetector(backend, 20000, &orbPayload));

//     // Create our OpenCV Counterparts
//     std::vector<cv::KeyPoint> keypointsOne;
//     std::vector<cv::KeyPoint> keypointsTwo;
//     cv::Mat descriptorsOne(orbParams.maxFeatures, VPI_BRIEF_DESCRIPTOR_ARRAY_LENGTH, CV_8U);
//     cv::Mat descriptorsTwo(orbParams.maxFeatures, VPI_BRIEF_DESCRIPTOR_ARRAY_LENGTH, CV_8U);

//     // ================
//     // Processing stage

//     // First convert input to grayscale
//     CHECK_STATUS(vpiSubmitConvertImageFormat(stream, backend, imgInput, imgGrayScale, NULL));

//     // Then, create the Gaussian Pyramid for the image and wait for the execution to finish
//     CHECK_STATUS(vpiPyramidCreate(cvImage.cols, cvImage.rows, VPI_IMAGE_FORMAT_U8, orbParams.pyramidLevels, 0.5,
//                                   backend, &pyrInput));
//     CHECK_STATUS(vpiSubmitGaussianPyramidGenerator(stream, backend, imgGrayScale, pyrInput, VPI_BORDER_ZERO));

//     // Then get ORB features and wait for the execution to finish
//     steady_time_t time_StartExtVpiORB = steady_clk_t::now();
//     CHECK_STATUS(vpiSubmitORBFeatureDetector(stream, backend, orbPayload, pyrInput, keypoints, descriptors,
//     &orbParams,
//                                              VPI_BORDER_ZERO));
//     steady_time_t time_EndExtVpiORB = steady_clk_t::now();
//     double mTimeExtVpiORB =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndExtVpiORB -
//         time_StartExtVpiORB)
//             .count();
//     CHECK_STATUS(vpiStreamSync(stream));

//     // =======================================
//     // Output processing and saving it to disk

//     // Lock output keypoints and scores to retrieve its data on cpu memory
//     VPIArrayData outKeypointsData;
//     VPIImageData imgData;
//     CHECK_STATUS(vpiArrayLockData(keypoints, VPI_LOCK_READ, VPI_ARRAY_BUFFER_HOST_AOS, &outKeypointsData));
//     CHECK_STATUS(vpiImageLockData(imgGrayScale, VPI_LOCK_READ, VPI_IMAGE_BUFFER_HOST_PITCH_LINEAR, &imgData));

//     VPIKeypointF32* outKeypoints = (VPIKeypointF32*)outKeypointsData.buffer.aos.data;

//     printf("Detect %d vpi orb keypoints, cost %f ms \n", *outKeypointsData.buffer.aos.sizePointer, mTimeExtVpiORB);

//     cv::Mat img;
//     CHECK_STATUS(vpiImageDataExportOpenCVMat(imgData, &img));

//     // cv::Mat outImage = DrawKeypoints(img, outKeypoints, *outKeypointsData.buffer.aos.sizePointer);

//     // imwrite("orb_feature_detector_" + strBackend + ".png", outImage);

//     // Done handling outputs, don't forget to unlock them.
//     CHECK_STATUS(vpiImageUnlock(imgGrayScale));
//     CHECK_STATUS(vpiArrayUnlock(keypoints));

//     // cv::imwrite("orb_feature_detector_" + strBackend + ".png", outImage);
//     // ========
//     // Clean up

//     // Make sure stream is synchronized before destroying the objects
//     // that might still be in use.
//     vpiStreamSync(stream);

//     vpiImageDestroy(imgInput);
//     vpiImageDestroy(imgGrayScale);
//     vpiArrayDestroy(keypoints);
//     vpiArrayDestroy(descriptors);
//     vpiPayloadDestroy(orbPayload);
//     vpiStreamDestroy(stream);
// }

// TEST(Feature, SLAM_ORB) {
//     static constexpr int nFeatures = 1000;
//     static constexpr float fScaleFactor = 1.2;
//     static constexpr int nLevels = 8;
//     static constexpr int fIniThFAST = 20;
//     static constexpr int fMinThFAST = 7;

//     ORBextractor orb_extractor(nFeatures, fScaleFactor, nLevels, fIniThFAST, fMinThFAST);

//     cv::Mat image = cv::imread(imgPath);
//     ASSERT_FALSE(image.empty());

//     std::vector<cv::KeyPoint> keypoints;
//     cv::Mat descriptors;
//     std::vector<int> vLapping = {0, 1000};
//     std::chrono::steady_clock::time_point time_StartExtSlamORB = std::chrono::steady_clock::now();
//     orb_extractor(image, cv::Mat(), keypoints, descriptors, vLapping);
//     std::chrono::steady_clock::time_point time_EndExtSlamORB = std::chrono::steady_clock::now();
//     double mTimeSlamORB_Ext =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndExtSlamORB -
//         time_StartExtSlamORB)
//             .count();
//     printf("Detect %lu orb-slam orb keypoints, cost %f ms \n", keypoints.size(), mTimeSlamORB_Ext);
//     // visual
//     // cv::Mat img_keypoints;
//     // cv::drawKeypoints(image, keypoints, img_keypoints);  // Draw keypoints
//     // cv::imshow("ORBSLAM ORB Keypoints", img_keypoints);  // Show detected (drawn) keypoints
//     // cv::waitKey(10);

//     int roiViolations = 0;
//     for (std::vector<cv::KeyPoint>::const_iterator kp = keypoints.begin(); kp != keypoints.end(); ++kp) {
//         int x = cvRound(kp->pt.x);
//         int y = cvRound(kp->pt.y);

//         ASSERT_LE(0, x);
//         ASSERT_LE(0, y);
//         ASSERT_GT(image.cols, x);
//         ASSERT_GT(image.rows, y);
//     }

//     ASSERT_EQ(0, roiViolations);
// }

// TEST(Feature, CV_FAST) {
//     cv::Mat imgInput = cv::imread(imgPath);
//     std::vector<cv::KeyPoint> keypoints;
//     keypoints.reserve(1000);
//     if (imgInput.empty()) std::cerr << "Error, no Image input! " << std::endl;

//     cv::Ptr<cv::FeatureDetector> fast = cv::FastFeatureDetector::create(100);
//     steady_time_t time_StartExtCvFast = steady_clk_t::now();
//     fast->detect(imgInput, keypoints);
//     steady_time_t time_EndExtCvFast = steady_clk_t::now();
//     double mTimeExtCvFast =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndExtCvFast -
//         time_StartExtCvFast)
//             .count();
//     printf("Detect %ld cv fast keypoints, cost %f ms \n", keypoints.size(), mTimeExtCvFast);

//     // cv::Mat outImage;
//     // cv::drawKeypoints(imgInput, keypoints, outImage);
//     // cv::imwrite("cv_fast_feature_detector.png", outImage);
// }

// vpi smaple https://docs.nvidia.com/vpi/algo_fast_corners_detector.html
// TEST(Feature, VPI_FAST) {
//     cv::Mat cvImage;
//     int retval = 0;

//     std::string strBackend = "cuda";  // cpu or cuda
//     // std::string strInputFileName = "./data/lena.png";  //<input image>
//     std::string strInputFileName = "./data/kodim08_grayscale.png";

//     // Now parse the backend
//     VPIBackend backend;

//     if (strBackend == "cpu") {
//         backend = VPI_BACKEND_CPU;
//     } else if (strBackend == "cuda") {
//         backend = VPI_BACKEND_CUDA;
//     } else {
//         throw std::runtime_error("Backend '" + strBackend + "' not recognized, it must be either cpu or cuda.");
//     }

//     cvImage = cv::imread(strInputFileName);
//     if (cvImage.empty()) {
//         throw std::runtime_error("Can't open first image: '" + strInputFileName + "'");
//     }
//     VPIStream stream = NULL;
//     CHECK_STATUS(vpiStreamCreate(backend | VPI_BACKEND_CPU, &stream));

//     VPIImage imgInput = NULL;
//     CHECK_STATUS(vpiImageCreateWrapperOpenCVMat(cvImage, backend | VPI_BACKEND_CPU, &imgInput));

//     VPIImage imgGrayScale = NULL;
//     CHECK_STATUS(
//         vpiImageCreate(cvImage.cols, cvImage.rows, VPI_IMAGE_FORMAT_U8, backend | VPI_BACKEND_CPU, &imgGrayScale));

//     CHECK_STATUS(vpiSubmitConvertImageFormat(stream, backend, imgInput, imgGrayScale, NULL));

//     VPIArray keypoints = NULL;
//     CHECK_STATUS(vpiArrayCreate(1000, VPI_ARRAY_TYPE_KEYPOINT_F32, backend | VPI_BACKEND_CPU, &keypoints));

//     VPIFASTCornerDetectorParams params;
//     vpiInitFASTCornerDetectorParams(&params);
//     params.circleRadius = 3;
//     params.arcLength = 9;
//     params.intensityThreshold = 100;
//     params.nonMaxSuppression = 1;
//     steady_time_t time_StartExtVpiFast = steady_clk_t::now();
//     CHECK_STATUS(vpiSubmitFASTCornerDetector(stream, backend, imgGrayScale, keypoints, &params, VPI_BORDER_ZERO));
//     steady_time_t time_EndExtVpiFast = steady_clk_t::now();
//     double mTimeExtVpiFast =
//         std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(time_EndExtVpiFast -
//         time_StartExtVpiFast)
//             .count();
//     CHECK_STATUS(vpiStreamSync(stream));

//     // =======================================
//     // Output processing and saving it to disk
//     VPIArrayData outKeypointsData;
//     VPIImageData imgData;
//     CHECK_STATUS(vpiArrayLockData(keypoints, VPI_LOCK_READ, VPI_ARRAY_BUFFER_HOST_AOS, &outKeypointsData));
//     CHECK_STATUS(vpiImageLockData(imgGrayScale, VPI_LOCK_READ, VPI_IMAGE_BUFFER_HOST_PITCH_LINEAR, &imgData));

//     VPIKeypointF32* outKeypoints = (VPIKeypointF32*)outKeypointsData.buffer.aos.data;
//     printf("Detect %d vpi fast keypoints, cost %f ms \n", *outKeypointsData.buffer.aos.sizePointer, mTimeExtVpiFast);

//     // 转成 mat，保存
//     // cv::Mat img;
//     // CHECK_STATUS(vpiImageDataExportOpenCVMat(imgData, &img));
//     // cv::Mat outImage = DrawKeypoints(img, outKeypoints, *outKeypointsData.buffer.aos.sizePointer);
//     // cv::imwrite("orb_feature_detector_" + strBackend + ".png", outImage);

//     CHECK_STATUS(vpiArrayUnlock(keypoints))
//     CHECK_STATUS(vpiImageUnlock(imgGrayScale));
//     vpiStreamSync(stream);

//     vpiStreamDestroy(stream);
//     vpiImageDestroy(imgInput);
//     vpiImageDestroy(imgGrayScale);
//     vpiArrayDestroy(keypoints);
// }
