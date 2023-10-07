# 开关选项
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_APP "Build app" ON)
option(BUILD_GTESTS "Build Gtest " OFF)


set(CV_TEST_LIB opencv)
file(GLOB_RECURSE _SRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

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
   add_subdirectory(test)
endif()
# add app
if(BUILD_APP)
    add_subdirectory(app)
endif()