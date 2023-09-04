cmake_minimum_required(VERSION 3.16)
project(test DESCRIPTION "test opencv")
# project(test)

# 编译选项
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC ${COMPILER_WARNINGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_WARNINGS} -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=deprecated-declarations -Wno-deprecated-declarations")

# 开关
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# 查找库
find_package(OpenCV 4.5.4 REQUIRED)

set(TEST_LIB myopencv)
set(_LINK_LIBS ${OpenCV_LIBS})
# ouput dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 包含头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${OpenCV_INLCUDE_DIRS}
        
)
file(GLOB_RECURSE _SRC_FILE ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${TEST_LIB} STATIC ${_SRC_FILE})
target_link_libraries(${TEST_LIB} ${_LINK_LIBS})

# add_executable(test ${PROJECT_SOURCE_DIR}/test/test_main.cpp)
# target_link_libraries(test ${TEST_LIB}) # 链接库

# add_executable(fast_detect ${PROJECT_SOURCE_DIR}/test/fast_detect.cpp)
# target_link_libraries(fast_detect ${_LINK_LIBS})

# add_executable(feature_detect ${PROJECT_SOURCE_DIR}/test/feature_detect.cpp)
# target_link_libraries(feature_detect ${_LINK_LIBS})

# add_executable(test_resize ${PROJECT_SOURCE_DIR}/test/test_resize.cpp)
# target_link_libraries(test_resize ${_LINK_LIBS}) # 链接库

# add_executable(test_orb ${PROJECT_SOURCE_DIR}/test/test_orb.cpp)
# target_link_libraries(test_orb ${TEST_LIB} ${_LINK_LIBS}) # 链接库

add_executable(test ${PROJECT_SOURCE_DIR}/src/pyramid/test.cpp)
target_link_libraries(test ${TEST_LIB} ${_LINK_LIBS}) # 链接库