#include <iostream>
#include <memory>
#include <vector>

#include "feature/feature_detect.h"
#include "pose_estimation/RobustMatcher.h"
using namespace my_test;
int main() {
    std::cout << "============= start ============= " << std::endl;
    std::string dectector = "orb";
    cv::Mat image = cv::imread("./data/lena.png");
    FeatureDetectPtr feature_detect = std::make_shared<FeatureDetect>(dectector);
    feature_detect->orb_detect(image);

    RobustMatcher matcher;
    std::vector<cv::KeyPoint> keypoints;
    matcher.computeKeyPoints(image, keypoints);
    cv::Mat img_keypoints;
    cv::drawKeypoints(image, keypoints, img_keypoints);  // Draw keypoints
    cv::imshow("RobustMatcher", img_keypoints);          // Show detected (drawn) keypoints
    cv::waitKey();
    return 1;
}