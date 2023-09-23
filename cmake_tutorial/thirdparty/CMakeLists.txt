# CMakeLists.txt
project(tutorial)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)


# =============  boost  ===============
# set(BOOST_ROOT /usr/local/install/boost_1_71_0)

find_package(Boost COMPONENTS regex system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    add_executable(foo foo.cpp)
    target_link_libraries (foo ${Boost_LIBRARIES})
endif()