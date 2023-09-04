cmake_minimum_required(VERSION 3.16)
project(cmake_test)
option(FLAG "compile flag" OFF)
message(STATUS "FLAG1: ${FLAG}")
if (NOT CMAKE_BUILD_TYPE)
  # if build type is not specific, setting default type to Release
  set(CMAKE_BUILD_TYPE CACHE STRING Release)
endif()
message(STATUS "Project build type : ${CMAKE_BUILD_TYPE}")
# 第一次赋值之后，再修改是不起作用的，原因：变量已经缓存在CMakeCache.txt文件中，无法在txt中修改但可以通过-D选项修改
option(FLAG "compile flag" OFF) # 已经被设置成ON，后续在使用option()不起作用
message(STATUS "FLAG2: ${FLAG}")

if(FLAG)
    add_definitions(-DUSE_MARCO)
endif()


add_executable(test test.cpp)

message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_ROOT = ${CMAKE_ROOT}")



message(STATUS "父目录 CMakeLists.txt 文件")
 
set(MY_VAL "666")
 
message(STATUS "第一次在父目录 MY_VAL=${MY_VAL}")
 
add_subdirectory(src)
 
message(STATUS "第二次在父目录 MY_VAL=${MY_VAL}")