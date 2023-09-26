#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#define millisecond 1000000
#define DEBUG_PRINT(...) \
    printf(__VA_ARGS__); \
    printf("\n")
#define DEBUG_TIME(time_) auto time_ = std::chrono::high_resolution_clock::now()
#define RUN_TIME(time_) (double)(time_).count() / millisecond
using namespace std;

TEST(Core, resize) {
    std::string image_path = "./data/lena.png";
    cv::Mat image = cv::imread(image_path);
    cv::Mat image2X_INTER_NEAREST;
    cv::Mat image2X_INTER_LINEAR;
    cv::Mat image2X_INTER_AREA;
    cv::Mat image2X_INTER_CUBIC;
    double scale = 3.0;

    cv::Mat initMat;
    cv::resize(image, initMat, cv::Size(), scale, scale, cv::INTER_NEAREST);

    DEBUG_PRINT("image size[%d,%d],scale=%3.1f", image.rows, image.cols, scale);
    DEBUG_TIME(T0);
    cv::resize(image, image2X_INTER_NEAREST, cv::Size(), scale, scale, cv::INTER_NEAREST);  //最近邻插值
    DEBUG_TIME(T1);
    cv::resize(image, image2X_INTER_LINEAR, cv::Size(), scale, scale, cv::INTER_LINEAR);  //线性插值（默认）
    DEBUG_TIME(T2);
    cv::resize(image, image2X_INTER_AREA, cv::Size(), scale, scale,
               cv::INTER_AREA);  //区域插值,图像放大时类似于线性插值，图像缩小时可以避免波纹出现。
    DEBUG_TIME(T3);
    cv::resize(image, image2X_INTER_CUBIC, cv::Size(), scale, scale, cv::INTER_CUBIC);  //三次样条插值
    DEBUG_TIME(T4);

    DEBUG_PRINT("INTER_NEAREST:%3.3fms", RUN_TIME(T1 - T0));
    DEBUG_PRINT("INTER_LINEAR :%3.3fms", RUN_TIME(T2 - T1));
    DEBUG_PRINT("INTER_AREA   :%3.3fms", RUN_TIME(T3 - T2));
    DEBUG_PRINT("INTER_CUBIC  :%3.3fms", RUN_TIME(T4 - T3));
}
TEST(Core, ColorMap) {
    // We need an input image. (can be grayscale or color)
    std::string image_path = "./data/lena.png";
    cv::Mat img_in = cv::imread(image_path);
    if (img_in.empty())
        std::cerr << "Sample image (" << image_path
                  << ") is empty. Please adjust your path, so it points to a valid input image!" << std::endl;

    // Holds the colormap version of the image:
    cv::Mat img_color;
    // Apply the colormap:
    cv::applyColorMap(img_in, img_color, cv::COLORMAP_TURBO);
    // Show the result:
    cv::imshow("ColorMap", img_color);
}