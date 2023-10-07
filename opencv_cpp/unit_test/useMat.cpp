#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
#define Win_Name2 "Audi 奥迪"
int main() {
    std::string imgPath = "./data/disparity.png";
    cv::Mat imgDisparity = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
    cv::Mat inImage1 = cv::imread(imgPath, -1);
    cv::Mat inImage2 = cv::imread(imgPath, 0);
    std::cout << "Image type: " << imgDisparity.type() << " " << inImage1.type() << " " << inImage2.type() << std::endl;

    for (int i = 0; i < imgDisparity.rows; i++) {
        for (int j = 0; j < imgDisparity.cols; j++) {
            // at<类型>(i,j)进行操作，对于灰度图
            imgDisparity.at<ushort>(i, j) = imgDisparity.at<ushort>(i, j) * 10;
            // std::cout << imgDisparity.at<ushort>(i, j) << " ";
        }
        // std::cout << std::endl;
    }
    // float a = 30;
    // std::cout << "tan " << tan(a * M_PI / 180) << std::endl;
    // visual
    cv::Mat cvDisparityColor;
    // imgDisparity.convertTo(imgDisparity, CV_8UC1, 255.0, 0);
    // applyColorMap(imgDisparity, cvDisparityColor, cv::COLORMAP_JET);  // only for CV_8UC1 and CV_8UC3
    // cv::imshow("Disparity image", cvDisparityColor);
    // cv::waitKey(0);

    // imgDisparity.convertTo(imgDisparity, CV_8UC1, 255.0, 0);
    // cv::imshow("Disparity image2: ", imgDisparity);
    // cv::waitKey();

    //绘制奥迪Audi车标
    Mat image2 = Mat::zeros(600, 850, CV_8UC3);  //生成一个850x600的窗口
    circle(image2, Point(200, 300), 100, Scalar(225, 0, 225), 7,
           8);  //绘制第一个圆，半径为100，圆心（200，300），颜色为紫色
    circle(image2, Point(350, 300), 100, Scalar(225, 0, 225), 7,
           8);  //绘制第一个圆，半径为100，圆心（350，300），线宽为7
    circle(image2, Point(500, 300), 100, Scalar(225, 0, 225), 7, 8);  //绘制第一个圆，半径为100，圆心（500，300）
    circle(image2, Point(650, 300), 100, Scalar(225, 0, 225), 7, 8);  //绘制第一个圆，半径为100，圆心（650，300）
    cv::Rect roi = cv::Rect(100, 100, 400, 250);
    cv::rectangle(image2, roi, cv::Scalar(10, 10, 255), 2);
    imshow(Win_Name2, image2);
    waitKey();
    return 0;
}