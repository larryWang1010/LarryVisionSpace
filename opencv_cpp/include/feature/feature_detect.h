/*
 * @Author: jiajunwang 18035173529@163.com
 * @Date: 2023-06-07 15:16:38
 * @LastEditors: jiajunwang 18035173529@163.com
 * @LastEditTime: 2023-07-13 13:39:13
 * @FilePath: /testOpencv/include/feature/feature_detect.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
namespace my_test {
class FeatureDetect {
   private:
    /* data */
    cv::Ptr<cv::FeatureDetector> detector_;
    cv::Ptr<cv::DescriptorExtractor> extractor_;

   public:
    FeatureDetect(/* args */);
    FeatureDetect(std::string type_detector);
    ~FeatureDetect();
    int orb_detect(cv::Mat& image);
};
using FeatureDetectPtr = std::shared_ptr<FeatureDetect>;

}  // namespace my_test