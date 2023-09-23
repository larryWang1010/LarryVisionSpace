// #include <iostream>
// #include <opencv2/opencv.hpp>
// using namespace cv;
// using namespace std;
// void saveDisp(const char* filename, Mat mat);
// int main() {
//     char* filename = "../../data/disparity_value.txt";

//     Mat left = imread("../../data/1.png", cv::IMREAD_GRAYSCALE);
//     Mat right = imread("../../data/2.png", cv::IMREAD_GRAYSCALE);
//     double t = (double)getTickCount();
//     Mat disp;
//     StereoBM bm;
//     CvStereoBMState* BMState = cvCreateStereoBMState();
//     bm.state->SADWindowSize = 15;
//     bm.state->minDisparity = 0;
//     bm.state->numberOfDisparities = 80;
//     bm.state->textureThreshold = 10;
//     bm.state->uniquenessRatio = 8;
//     bm.state->speckleWindowSize = 10;
//     bm.state->speckleRange = 32;
//     bm.state->disp12MaxDiff = -1;
//     /*防止左侧黑边*/
//     copyMakeBorder(left, left, 0, 0, 80, 0, IPL_BORDER_REPLICATE);
//     copyMakeBorder(right, right, 0, 0, 80, 0, IPL_BORDER_REPLICATE);

//     bm.operator()(left, right, disp, CV_32F);
//     disp = disp.colRange(80, left.cols);

//     t = ((double)getTickCount() - t) / getTickFrequency();
//     std::cout << "time:" << t << std::endl;
//     cv::imshow("disp", disp);
//     // saveDisp(filename, disp);
//     cv::WaitKey(0);
//     return 0;
// }

// /**
// 将视差保存到txt,用于MATLAB读取
// **/
// void saveDisp(const char* filename, Mat mat) {
//     int ih = mat.type();
//     // float disp = mat.at<float>(0,0);
//     FILE* fp = fopen(filename, "wt");
//     fprintf(fp, "%02d\n", mat.rows);
//     fprintf(fp, "%02d\n", mat.cols);
//     for (int y = 0; y < mat.rows; y++) {
//         for (int x = 0; x < mat.cols; x++) {
//             float disp = mat.at<float>(y, x);  // 这里视差矩阵是CV_16S 格式的，故用 short 类型读取
//             fprintf(fp, "%f\n", disp);         // 若视差矩阵是 CV_32F 格式，则用 float 类型读取
//         }
//     }
//     fclose(fp);
// }