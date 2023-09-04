#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// csv data
struct GtInfo {
    std::string timestamp;
    float xyz[3];
    float q[4];  // w x y z
    float v[3];
    float w[3];
    float a[3];
};
void LoadGtInfo(const std::string& strPath, std::vector<GtInfo>& poses);
size_t FindMatchTimestamp(const std::vector<GtInfo>& poses, const double& target);

int main() {
    double target = 1403636580.928565520;
    std::string path = "./data.csv";
    std::vector<GtInfo> poses;
    poses.reserve(50000);
    LoadGtInfo(path, poses);
    size_t idx = FindMatchTimestamp(poses, target);
    double res = std::stod(poses[idx].timestamp) / 1e9;
    printf("Find matched timestamp %ld:%s, delta %f \n", idx, poses[idx].timestamp.c_str(), res - target);
}

void LoadGtInfo(const std::string& strPath, std::vector<GtInfo>& poses) {
    std::ifstream file(strPath);
    std::string line;
    std::getline(file, line);  // ignore first line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string str;
        GtInfo info;
        std::vector<std::string> strSplit;
        while (std::getline(ss, str, ',')) {
            strSplit.push_back(str);
        }
        info.timestamp = strSplit[0];
        for (int i = 1; i < 4; ++i) {
            info.xyz[i - 1] = std::stof(strSplit[i]);
        }
        for (int i = 4; i < 8; ++i) {
            info.q[i - 4] = std::stof(strSplit[i]);
        }
        poses.emplace_back(info);
    }
    file.close();
}
// return index
size_t FindMatchTimestamp(const std::vector<GtInfo>& poses, const double& target) {
    if (poses.empty()) {
        std::cerr << "Error, no poses and open slam mode." << std::endl;
        return 0;
    }
    if (target < std::stod(poses[0].timestamp) / 1e9) {
        return -1;
    }
    size_t low = 0;
    size_t high = poses.size();
    // todo 还有点问题，有时会找到对应帧的后一帧
    while (low + 1 < high) {
        size_t midIndex = low + std::floor((high - low) / 2);
        double midTimestamp = std::stod(poses[midIndex].timestamp) / 1e9;
        printf("Debug low:mid:high %ld:%ld:%ld \n", low, midIndex, high);
        if (target < midTimestamp) {
            high = midIndex - 1;
        } else if (target > midTimestamp) {
            low = midIndex + 1;
        } else if (target == midTimestamp) {
            return midIndex;
        }
    }
    // debug
    std::cout << "Debug index " << low << ":" << high << " low:high " << poses[low].timestamp << " "
              << poses[high].timestamp << std::endl;

    return std::abs(std::stod(poses[low].timestamp) / 1e9 - target) <
                   std::abs(std::stod(poses[high].timestamp) / 1e9 - target)
               ? low
               : high;
}