cmake_minimum_required(VERSION 3.16)
project(sophus)


find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${Sophus_INCLUDE_DIRS}
)
# 源文件


add_executable(sophus useSophus2.cpp)