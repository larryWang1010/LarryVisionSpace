#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
// csv data
struct csvData {
  float xyz[3];
  float q[4];  // w x y z
  float v[3];
  float w[3];
  float a[3];
};
void readCsv(const std::string &strPathGtInfo,
             std::map<std::string, csvData> &out_csv_data);
struct ExampleParam {
  std::string path_csv_file;
  int parseParameter(int argc, char **argv) {
    if (argc < 2) {
      std::cout << "Usge load csv file: -d file_path" << std::endl;
      return -1;
    }
    for (int i = 0; i < argc; ++i) {
      std::string str(argv[i]);
      if (!str.compare("-d")) {
        this->path_csv_file = std::string(argv[i + 1]);
        if (str[this->path_csv_file.size() - 1] != '/') {
          this->path_csv_file.push_back('/');
        }
      }
    }
    return 0;
  }
};

int main(int argc, char **argv) {
  ExampleParam load_file;
  if (load_file.parseParameter(argc, argv)) {
    return -1;
  }
  std::string csv_file(load_file.path_csv_file + "data.csv");
  std::map<std::string, csvData> csv_data;
  readCsv(csv_file, csv_data);
  return 0;
}

void readCsv(const std::string &strPathGtInfo,
             std::map<std::string, csvData> &out_csv_data) {
  // 打开CSV文件
  std::ifstream file(strPathGtInfo);
  std::string line;
  std::getline(file, line);
  // std::cout << line << " " << std::endl;
  // 读取每一行数据
  size_t counter = 0;
  while (std::getline(file, line)) {
    counter++;
    // 将读取的每一行数据转换为字符串流
    std::stringstream ss(line);
    std::string cell;
    csvData data;
    // 读取每一列数据
    // std::cout << line << " " << std::endl;
    std::vector<std::string> oneLine;
    while (std::getline(ss, cell, ',')) {
      // std::cout << cell << " ";
      oneLine.push_back(cell);
    }
    for (int i = 1; i < 4; ++i) {
      data.xyz[i - 1] = std::stof(oneLine[i]);
    }
    for (int i = 4; i < 8; ++i) {
      data.q[i - 4] = std::stof(oneLine[i]);
    }
    // std::cout << "q :" << oneLine[0] << " " << data.q[0] << " " << data.q[1]
    // << " " << data.q[2] << " " << data.q[3] << std::endl;
    out_csv_data.insert(std::pair<std::string, csvData>(oneLine[0], data));
    std::map<std::string, csvData>::iterator it = out_csv_data.begin();
    std::map<std::string, csvData>::iterator itEnd = out_csv_data.end();
    while (it != itEnd) {
      std::cout << it->first << " " << it->second.q[0] << " " << it->second.q[1]
                << " " << it->second.q[2] << " "
                << " " << it->second.q[3] << "!" << std::endl;
      it++;
    }
  }
  std::cout << "All groundtruth pose: " << counter << std::endl;

  // 关闭文件
  file.close();
}
