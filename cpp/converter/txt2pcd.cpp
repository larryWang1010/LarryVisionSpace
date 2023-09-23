#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "common.h"
int main(int argc, char** argv) {
    if (argc < 1) {
        std::cout << "Error, please input txt file!" << std::endl;
        exit;
    }
    std::string strInputFile(argv[1]);
    std::ifstream fs(strInputFile);
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointXYZ xyz;
    pcl::PCDWriter write2pcd;
    std::string line;
    std::string str;

    steady_time_t start = steady_clk_t::now();
    while (std::getline(fs, line)) {
        std::stringstream ss(line);
        std::vector<std::string> strSplit;  // 声明为static，strSplit为空
        while (std::getline(ss, str, ' ')) strSplit.push_back(str);
        xyz.x = std::stof(strSplit[1]);
        xyz.y = std::stof(strSplit[2]);
        xyz.z = std::stof(strSplit[3]);
        cloud.emplace_back(xyz);
    }
    steady_time_t end = steady_clk_t::now();
    double delta = std::chrono::duration_cast<dura_ms_t>(end - start).count();
    fs.close();
    std::string outFile = "./" + strInputFile.substr(0, 21) + ".pcd";
    write2pcd.write(outFile, cloud);
    return 0;
}