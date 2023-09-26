#include <Eigen/Dense>
#include <iostream>

#include "gtest/gtest.h"
TEST(EIGEN, Foundation) {
    Eigen::Vector3d ptd(1.0, 1.0, 1.0);
    int a = 10;

    std::cout << ptd(0) * a << std::endl;
}