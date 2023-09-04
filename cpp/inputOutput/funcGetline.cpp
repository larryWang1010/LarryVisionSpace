#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // * istream getline
    // char name[256], wolds[256];
    // cout << "Input your name: ";
    // cin.getline(name, 256);
    // cout << name << endl;
    // cout << "Input your wolds: ";
    // cin.getline(wolds, 256, ',');
    // cout << wolds << endl;
    // cin.getline(wolds, 256, ',');
    // cout << wolds << endl;
    // * string getline
    // string line;
    // std::cout << "Please, enter your name: ";
    // while (std::getline(cin, line)) {
    //     cout << "Hello, " << line << "!" << endl;
    // }

    // ifstream file("./../data.txt");
    // if (file.is_open()) {
    //     while (std::getline(file, line)) {
    //         std::cout << line << std::endl;
    //     }
    // } else {
    //     std::cerr << "error" << std::endl;
    // }

    // return 0;
    // test.cpp

    // cout << "hello world---cout" << endl;
    // cerr << "hello world---cerr" << endl;
    // return 0;

    // string str;
    // cout << "Input: ";
    // getline(cin, str, 'A');
    // cout << "The string we have gotten is :" << str << '.' << endl;
    // getline(cin, str, 'B');
    // cout << "The string we have gotten is :" << str << '.' << endl;

    std::string str11 = "4 6 7 234 6";
    std::stringstream ss;
    ss << str11;
    int pid;
    ss >> pid;
    std::cout << ss.str() << " \n" << pid << std::endl;
}