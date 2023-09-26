cmake_minimum_required(VERSION 3.16)
project(opencv_test 
    VERSION 1.0
    DESCRIPTION "test opencv"
    LANGUAGES CXX
)

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

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 开关选项
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_APP "Build app" ON)
option(BUILD_GTESTS "Build Gtest " ON)

# 查找库
find_package(OpenCV 4.5.4 REQUIRED)
message(STATUS "Found OpenCV ${OpenCV_VERSION} headers in: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Found OpenCV_LIBS: ${OpenCV_LIBS}")
# add_library(opencv_test::opencv INTERFACE IMPORTED)
# set_property(TARGET opencv_test::opencv PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OpenCV_INCLUDE_DIRS})
# set_property(TARGET opencv_test::opencv PROPERTY INTERFACE_LINK_LIBRARIES ${OpenCV_LIBS})

set(CV_TEST_LIB opencv)
file(GLOB_RECURSE _SRC_FILE ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${CV_TEST_LIB})
target_sources(${CV_TEST_LIB}
    PRIVATE ${_SRC_FILE}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# 包含头文件
target_include_directories( ${CV_TEST_LIB} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
 )
# 第三方库
target_link_libraries( ${CV_TEST_LIB} 
    PUBLIC 
        ${OpenCV_LIBS}
)
# add googletest
if(BUILD_GTESTS)
   add_subdirectory(Thirdparty/googletest)
   add_subdirectory(test)
endif()
# add app
if(BUILD_APP)
    add_subdirectory(app)
endif()