/*
 * @Author: jiajunwang 18035173529@163.com
 * @Date: 2023-07-13 11:47:37
 * @LastEditors: jiajunwang 18035173529@163.com
 * @LastEditTime: 2023-07-13 16:00:01
 * @FilePath: /testOpencv/test/test_orb.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

#include "orb_slam2/ORBextractor.h"
using namespace my_test;
int main(int argc, char** argv) {
    std::cout << "Start!" << std::endl;
    std::string image_path;
    std::string file_path;

    if (argc < 2) {
        std::cout << "Usage: test orb -d dataset_path" << std::endl
                  << "Input Parameter: " << std::endl
                  << "required:" << std::endl
                  << "\t-d: the following parameter should be the path of EuRoC dataset" << std::endl
                  << "\t-f: config file path" << std::endl;
        return -1;
    }
    for (int i = 1; i < argc; ++i) {
        std::string option = argv[i];
        if (!option.compare("-d")) {
            if (i + 1 <= argc) {
                image_path = argv[i + 1];
            }
        } else if (!option.compare("-f")) {
            if (i + 1 <= argc) {
                file_path = argv[i + 1];
            }
        } else {
            // std::cout << "Successfully load parameters!" << std::endl;
        }
    }

    cv::Mat image = cv::imread(image_path);

    std::cout << "Image info: " << image.type() << " " << image.channels() << std::endl;
    if (image.empty()) {
        return 0;
    } else if (image.type() == CV_8UC1) {
        std::cout << "image type wrong!" << std::endl;
        return 0;
    } else {
        std::cout << "Successfully load images!" << std::endl;
    }

    // load parameters from yaml file

    cv::FileStorage fSettings(file_path, cv::FileStorage::READ);
    if (!fSettings.isOpened()) {
        std::cerr << "Failed to open settings file at: " << file_path << std::endl;
        exit(-1);
    }
    float fx = fSettings["Camera.fx"];
    float fy = fSettings["Camera.fy"];
    float cx = fSettings["Camera.cx"];
    float cy = fSettings["Camera.cy"];
    int nFeatures = fSettings["ORBextractor.nFeatures"];
    float fScaleFactor = fSettings["ORBextractor.scaleFactor"];
    int nLevels = fSettings["ORBextractor.nLevels"];
    int fIniThFAST = fSettings["ORBextractor.iniThFAST"];
    int fMinThFAST = fSettings["ORBextractor.minThFAST"];

    std::cout << "ORB Extractor Parameters: " << std::endl
              << "- Camera Intrinsics: "
              << "[" << fx << " " << fy << " " << cx << " " << cy << "]" << std::endl
              << "- Number of Features: " << nFeatures << std::endl
              << "- Scale Levels: " << nLevels << std::endl
              << "- Scale Factor: " << fScaleFactor << std::endl
              << "- Initial Fast Threshold: " << fIniThFAST << std::endl
              << "- Minimum Fast Threshold: " << fMinThFAST << std::endl;

    std::vector<cv::KeyPoint> kps;
    cv::Mat dps;
    std::shared_ptr<ORBextractor> mpORBextractorLeft;
    mpORBextractorLeft = std::make_shared<ORBextractor>(nFeatures, fScaleFactor, nLevels, fIniThFAST, fMinThFAST);
    (*mpORBextractorLeft)(image, cv::Mat(), kps, dps);

    cv::Mat image_kp;
    cv::drawKeypoints(image, kps, image_kp);  // Draw keypoints
    cv::imshow("orb_slam2", image_kp);
    cv::waitKey();
    return 0;
}