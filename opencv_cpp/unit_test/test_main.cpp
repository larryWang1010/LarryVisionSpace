#include <gtest/gtest.h>

// #include "opencv2/opencv.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    srand((unsigned)time(NULL));
    int rt = RUN_ALL_TESTS();

    // cv::waitKey(0); // visual

    return rt;
}