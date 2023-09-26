#include <gtest/gtest.h>
#include <stdio.h>

#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

TEST(IMGPROC, Drawing) {
    Mat img = Mat::zeros(Size(800, 600), CV_8UC3);
    img.setTo(255);
    Point p1(100, 100);
    Point p2(758, 50);
    line(img, p1, p2, Scalar(0, 0, 255), 2);
    line(img, Point(300, 300), Point(758, 400), Scalar(0, 255, 255), 3);

    Point p(20, 20);  //初始化点坐标为(20,20)
    circle(img, p, 2, Scalar(0, 255, 0), -1);

    Point p4;
    p4.x = 600;
    p4.y = 600;
    circle(img, p4, 100, Scalar(120, 120, 120), -1);

    int thickness = 3;
    int lineType = 8;
    double angle = 30;  //椭圆旋转角度
    ellipse(img, Point(100, 100), Size(90, 60), angle, 0, 360, Scalar(255, 255, 0), thickness, lineType);

    Rect r(250, 250, 120, 200);
    rectangle(img, r, Scalar(0, 255, 255), 3);
    imshow("大杂烩", img);

    waitKey();
}
