/*
 * @Author: jiajunwang 18035173529@163.com
 * @Date: 2023-07-13 10:14:28
 * @LastEditors: jiajunwang 18035173529@163.com
 * @LastEditTime: 2023-07-13 10:22:50
 * @FilePath: /test/test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <chrono>
#include <opencv2/opencv.hpp>
#define millisecond 1000000
#define DEBUG_PRINT(...) \
    printf(__VA_ARGS__); \
    printf("\n")
#define DEBUG_TIME(time_) auto time_ = std::chrono::high_resolution_clock::now()
#define RUN_TIME(time_) (double)(time_).count() / millisecond
using namespace std;

int main() {
    string image_path = "./data/lena.png";
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

    return 0;
}