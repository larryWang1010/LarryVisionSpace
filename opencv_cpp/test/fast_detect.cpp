#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat src = imread("./data/lena.png");
    if (src.empty()) {
        cout << "could not load image..." << endl;
        return -1;
    }

    vector<KeyPoint> keypoints;
    int fast_threshold = 20;
    bool nonmaxSuppression = true;
    FAST(src, keypoints, fast_threshold, nonmaxSuppression);

    // compute responses
    vector<float> responses(keypoints.size());
    for (int i = 0; i < keypoints.size(); i++) responses[i] = keypoints[i].response;

    // find max response
    float max_response = *max_element(responses.begin(), responses.end());

    // compute radii
    vector<float> radii(keypoints.size());
    for (int i = 0; i < keypoints.size(); i++) radii[i] = INT_MAX;

    for (int i = 0; i < keypoints.size(); i++)
        for (int j = 0; j < keypoints.size(); j++)
            if (responses[j] > responses[i])
                radii[i] = min(radii[i], static_cast<float>(norm(keypoints[i].pt - keypoints[j].pt)));

    // find minimum radius that satisfies condition
    float min_radius = INT_MAX;
    for (int i = 0; i < keypoints.size(); i++)
        if (radii[i] > max_response / 2) min_radius = min(min_radius, radii[i]);

    // keep only keypoints with radius greater than min_radius
    vector<KeyPoint> filtered_keypoints;
    for (int i = 0; i < keypoints.size(); i++)
        if (radii[i] >= min_radius && filtered_keypoints.size() < 100)  // set desired number of keypoints here
            filtered_keypoints.push_back(keypoints[i]);

    cout << "number of FAST keypoints detected: " << filtered_keypoints.size() << endl;
    Mat img_keypoints;
    drawKeypoints(src, filtered_keypoints, img_keypoints);  // Draw keypoints
    imshow("CV fast Keypoints", img_keypoints);             // Show detected (drawn) keypoints
    waitKey();
    return 0;
}
