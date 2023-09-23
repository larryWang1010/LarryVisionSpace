cmake_minimum_required(VERSION 3.16)

project(txt2pcd)

find_package(PCL REQUIRED)
# 设置PCL点云库依赖
find_package(PCL)
message(STATUS "Pcl version: " ${PCL_VERSION})
include_directories(
    ${PCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    )
# list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")#不加这个会报错,必须在下面这行之前
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(txt2pcd txt2pcd.cpp)
target_link_libraries(txt2pcd ${PCL_LIBRARIES})