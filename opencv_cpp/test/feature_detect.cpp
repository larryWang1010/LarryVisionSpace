#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
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
    cv::waitKey();
    return 1;
}