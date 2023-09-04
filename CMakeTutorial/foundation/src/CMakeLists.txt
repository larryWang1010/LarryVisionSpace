cmake_minimum_required(VERSION 3.10)
 
message(STATUS "进入子目录 src/CMakeLists.txt 文件")
set(MY_VAL "777" PARENT_SCOPE)
message(STATUS "在子目录 MY_VAL=${MY_VAL}")
 
message(STATUS "退出子目录")