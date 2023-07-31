#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#define VERSION "1"
#define VERSION1 1

// int main() {
//   std::string info = "version is " VERSION;
//   std::cout << info << std::endl;
//   return 0;
// }

int main() {
    // * double -> string 使用 stringstream
    double d = 3.1415926;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << d;  // 控制小数位数为3
    std::string str = ss.str();
    std::cout << str << std::endl;  // 输出：3.142

    // * string(char) -> double
    std::string str2 = "123.4567";
    float num_float = std::stof(str2);    // convert string to float
    double num_double = std::stod(str2);  // convert string to double

    std::cout << "num_float = " << num_float << std::endl;
    std::cout << "num_double = " << num_double << std::endl;

    char chr[] = "123.4567";
    std::string str1(chr);
    double num_double1 = std::atof(chr);   // char -> double
    double num_double2 = std::stod(str1);  // char -> string -> double
    std::cout << "num_double = " << num_double1 << " " << num_double2 << std::endl;

    return 0;
}

// 参考
// https://www.cnblogs.com/chorulex/p/7660187.html
// https://www.programiz.com/cpp-programming/string-float-conversion