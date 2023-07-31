#include "feature/feature_detect.h"

namespace my_test {
FeatureDetect::FeatureDetect(/* args */) {}
FeatureDetect::FeatureDetect(std::string type_detector) {
    if (type_detector == "orb") {
        detector_ = cv::ORB::create(1000, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
        extractor_ = detector_;
    }
}

FeatureDetect::~FeatureDetect() {}

int FeatureDetect::orb_detect(cv::Mat& image) {
    if (image.empty()) {
        std::cout << "ERROR: fail to load image " << std::endl;
        return 0;
    }

    std::vector<cv::KeyPoint> keypoints;
    detector_->detect(image, keypoints);

    cv::Mat descriptors;
    extractor_->compute(image, keypoints, descriptors);

    printf("ORB detect %lu cv orb keypoints \n", keypoints.size());

    cv::Mat img_keypoints;
    cv::drawKeypoints(image, keypoints, img_keypoints);  // Draw keypoints
    cv::imshow("CV ORB Keypoints", img_keypoints);       // Show detected (drawn) keypoints
    cv::waitKey();
    return 1;
}
}  // namespace my_test
