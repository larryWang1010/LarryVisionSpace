#include <gtest/gtest.h>

#include <iostream>
#include <string>
TEST(Basic, Converter) {
    float a = 3.14;
    std::cout << "Converter: " << std::to_string(a) << std::endl;
}