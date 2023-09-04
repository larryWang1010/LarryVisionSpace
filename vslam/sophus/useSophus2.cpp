#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>

#include "sophus/se3.hpp"
#include "sophus/so3.hpp"

using SO3Type = Sophus::SO3<double>;
using SE3Type = Sophus::SE3<double>;

using namespace std;
using namespace Eigen;

int main(int argc, char** argv) {
    // 沿z轴选装90°的旋转矩阵
    Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();

    // 转成四元数
    Quaterniond q(R);
    SO3Type SO3_R(R);  // 旋转矩阵转SO3
    SO3Type SO3_q(q);  // 四元数转SO3
    //
    cout << "SO(3) from atrix:\n" << SO3_R.matrix() << endl;
    cout << "SO(3) from quaternion:\n" << SO3_q.matrix() << endl;

    return 0;
}