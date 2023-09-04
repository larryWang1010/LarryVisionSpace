#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct GtInfo {
    std::string timestamp;
    float xyz[3];
    float q[4];  // w x y z
    float v[3];
    float w[3];
    float a[3];
};
void LoadGtInfo(const string& strPathGtInfo, std::vector<GtInfo> gtPoses);
int main() {
    string path = "/home/larry/ua-dataset/EuRoC/MH_01_easy/mav0/state_groundtruth_estimate0/data.csv";
    std::vector<GtInfo> gtPoses;
    LoadGtInfo(path, gtPoses);
    return 0;
}
void LoadGtInfo(const string& strPathGtInfo, std::vector<GtInfo> gtPoses) {
    std::ifstream file(strPathGtInfo);
    std::string line;
    std::getline(file, line);  // jump first line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string str;
        GtInfo info;
        std::vector<std::string> strSplit;
        while (std::getline(ss, str, ',')) strSplit.push_back(str);
        info.timestamp = strSplit[0];
        double ts = std::stod(info.timestamp);
        for (int i = 1; i < 4; ++i) info.xyz[i - 1] = std::stof(strSplit[i]);
        for (int i = 4; i < 8; ++i) info.q[i - 4] = std::stof(strSplit[i]);
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Info: " << info.timestamp << " " << info.xyz[0] << " " << info.xyz[1] << " " << info.xyz[2]
                  << std::endl;
        gtPoses.emplace_back(info);
    }
    file.close();
}
