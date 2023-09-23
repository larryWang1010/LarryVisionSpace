#include <iostream>
int add(int a, int b);
int main() {
    // int e;
    // e = add(num, 1);
    // // std::cout << "num is: " << c << std::endl;
    // int d;
    // d = add(num, 10);
    // std::cout << "num is: " << c << " " << d << std::endl;
    // for (int i = 0; i < 5; ++i) {
    //     static int num = 10;
    //     num = num + 2;
    //     std::cout << "num is: " << num << std::endl;
    // }
    double a = 5.333f;
    std::cout << "a is: " << a << std::endl;
}

int add(int a, int b) {
    static int c = 5;
    return a + b;
}