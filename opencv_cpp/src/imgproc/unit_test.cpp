#include <gtest/gtest.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
std::string imgPath1 = "data/lena.png";
std::string imgPath2 = "data/disparity.png";
std::string imgPath3 = "data/left.png";

void multipleImage(std::vector<cv::Mat> imgVector, cv::Mat& dst, int imgCols) {
    const int MAX_PIXEL = 300;
    int imgNum = imgVector.size();
    //选择图片最大的一边 将最大的边按比例变为300像素
    cv::Size imgOriSize = imgVector[0].size();
    int imgMaxPixel = cv::max(imgOriSize.height, imgOriSize.width);
    //获取最大像素变为MAX_PIXEL的比例因子
    double prop = imgMaxPixel < MAX_PIXEL ? (double)imgMaxPixel / MAX_PIXEL : MAX_PIXEL / (double)imgMaxPixel;
    cv::Size imgStdSize(imgOriSize.width * prop, imgOriSize.height * prop);  //窗口显示的标准图像的Size

    cv::Mat imgStd;              //标准图片
    cv::Point2i location(0, 0);  //坐标点(从0,0开始)
    //构建窗口大小 通道与imageVector[0]的通道一样
    cv::Mat imgWindow(imgStdSize.height * ((imgNum - 1) / imgCols + 1), imgStdSize.width * imgCols,
                      imgVector[0].type());
    for (int i = 0; i < imgNum; i++) {
        location.x = (i % imgCols) * imgStdSize.width;
        location.y = (i / imgCols) * imgStdSize.height;
        resize(imgVector[i], imgStd, imgStdSize, prop, prop, cv::INTER_LINEAR);  //设置为标准大小
        imgStd.copyTo(imgWindow(cv::Rect(location, imgStdSize)));
    }
    dst = imgWindow;
}
int displayGrayPixcel(cv::Mat& img) {
    if (!(img.type() == 0 && img.channels() == 1)) return -1;
    for (int row = 0; row < img.rows; ++row)
        for (int col = 0; col < img.cols; ++col) std::cout << img.at<unsigned int>(row, col) << " ";
    // std::cout << std::endl;
}
void mask_depth(cv::Mat& image, cv::Mat& th, int throld = 1000) {
    int nr = image.rows;  // number of rows
    int nc = image.cols;  // number of columns
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (image.at<ushort>(i, j) > throld) th.at<ushort>(i, j) = 0;
        }
    }
}
TEST(IMGPROC, ImageFormat) {
    cv::Mat inImage = cv::imread(imgPath2, cv::IMREAD_ANYDEPTH);  // load CV_16U
    // cv::Mat inImage;
    // cv::ximgproc::readGT(imgPath, inImage); // load CV_16S
    if (inImage.empty()) std::cout << "Error, cannot load image!" << std::endl;
    cv::imshow("Image origin", inImage);
    // 1. convert to CV_32F
    cv::Mat disp_float;
    inImage.convertTo(disp_float, CV_32F, 1.0 / 64);
    cv::imshow("Image CV_32F", disp_float);
    // 2. convert to CV_8UC1
    cv::Mat cvDisparity;
    disp_float.convertTo(cvDisparity, CV_8UC1, 255.0 / (64), 0);
    cv::imshow("Gray image", cvDisparity);
    // 3. color mapping
    cv::Mat cvDisparityColor;
    cv::applyColorMap(cvDisparity, cvDisparityColor, cv::COLORMAP_JET);
    cv::imshow("Gray with jet color", cvDisparityColor);
}
TEST(IMGPROC, ObstacleDetection) {
    int thresh = 20;
    int max_thresh = 255;
    int area = 500;
    cv::Mat imgDisp;
    cv::Mat origin;
    origin = cv::imread("data/test.png");
    cv::imshow("Origin image", origin);
    imgDisp = cv::imread(imgPath2, cv::IMREAD_ANYDEPTH);
    if (imgDisp.empty()) printf("Error, cannot load image!");
    cv::Mat disp_float;
    imgDisp.convertTo(disp_float, CV_32F, 1.0 / 64);
    cv::Mat cvDisparity;
    disp_float.convertTo(cvDisparity, CV_8UC1, 255.0 / (64), 0);
    cv::imshow("Gray image", cvDisparity);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));  //核的大小可适当调整
    cv::Mat out;
    //进行开操作
    cv::morphologyEx(cvDisparity, out, cv::MORPH_OPEN, element);
    //显示效果图
    imshow("opencv", out);
    cv::Mat src_copy = cvDisparity.clone();
    cv::Mat threshold_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::RNG rng(12345);
    // 对图像进行二值化
    cv::threshold(cvDisparity, threshold_output, thresh, 255, cv::THRESH_BINARY);
    // mask_depth(src, threshold_output);
    // 寻找轮廓
    cv::findContours(threshold_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // 对每个轮廓计算其凸包
    std::vector<std::vector<cv::Point> > hull(contours.size());
    std::vector<std::vector<cv::Point> > result;
    for (size_t i = 0; i < contours.size(); i++) {
        cv::convexHull(cv::Mat(contours[i]), hull[i], false);
    }

    // 绘出轮廓及其凸包
    cv::Mat drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) < area)  //面积小于area的凸包，可忽略
            continue;
        result.push_back(hull[i]);
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::drawContours(drawing, contours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
        cv::drawContours(drawing, hull, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
    }
    cv::imshow("contours", drawing);
    cv::waitKey(5);
}
