/*
 * @Description:数据类型转换 c和c++的方法
 * @Author: larry.wang
 * @Date: 2023-07-29 11:32:11
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
template <typename T>
string toString(const T& t);
int main() {
    // * use double
    // std::cout << "---------------use double---------------------" << std::endl;
    // double d1 = 1.9842947260153;
    // double d2 = 1423478946.367985433;
    // double d3 = 12344.12372;
    // double d4 = 7512.8;

    // std::cout << "cout default: " << d1 << " " << d2 << std::endl;  // 默认显示6位有效数字，大数采用科学计数法
    // std::cout << std::fixed << "big double: " << d3 << " " << d4 << std::endl;  // 大的整数，输出不使用科学技术法
    // std::cout << std::fixed << "small double: " << d1 << std::endl;             // 小的整数，cout损失精度
    // 小的浮点数转string，会损失精度，to_string只能精确到6位小数点
    // std::cout << "string: " << std::to_string(d4) << " ";
    // 可使用 stringstream 和 setprecision 支持最高15位的精度
    // std::stringstream ss;
    // ss << std::setprecision(14) << d1;  // 控制小数位数
    // std::cout << ss.str() << std::endl;
    // std::cout << "----------------------------------------------" << std::endl;
    // // * string -> double
    // long long int ref = 14036365797635555;
    // std::string str = "1403636582708555520";
    // long long int num1 = std::stoll(str) / 1e9;
    // long long int diff = num1 - ref;
    // std::cout << std::fixed << std::setprecision(0) << std::endl;
    // std::cout << "diff " << diff << std::endl;
    // std::cout << "num_double = " << std::fixed << std::setprecision(6) << std::stod(str) << std::endl;
    // std::cout << "num_float  = " << std::fixed << std::setprecision(0) << std::stof(str) << std::endl;

    // * char -> float
    // char chr[] = "1234.567";
    // std::string str1(chr);
    // std::cout << "num_double = " << std::atof(chr) << " chr " << chr << std::endl;     // char -> float
    // std::cout << "num_double = " << std::stof(str1) << " str1 " << str1 << std::endl;  // char -> string -> float

    // ostringstream对象用来进行格式化的输出，常用于将各种类型转换为string类型
    // ostringstream只支持<<操作符

    // cout << toString(14.22342342567) << endl;  //实型->string：输出14.2

    // cout << toString(12301) << endl;                //整型->string：输出12301
    // cout << toString(6748392716482657358) << endl;  //长整型->string：输出6748392716482657358
    // cout << toString(true) << endl;                 //布尔型->string：输出1

    return 0;
}

template <typename T>
string toString(const T& t) {
    ostringstream oss;  //创建一个格式化输出流
    oss << t;           //把值传递到流中
    return oss.str();
}

// 参考
// https://www.cnblogs.com/chorulex/p/7660187.html
// https://www.programiz.com/cpp-programming/string-float-conversion