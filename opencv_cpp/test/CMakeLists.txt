find_package(GTest REQUIRED)
include_directories(
  ${PROJECT_SOURCE_DIR}/include  
  ${GTEST_INCLUDE_DIRS}
)

set(gtest_submodules
  # calib3d
  core
  feature2d
  imgproc
)
foreach(module ${gtest_submodules})
    file(GLOB_RECURSE tmp ${PROJECT_SOURCE_DIR}/src/${module}/unit_test*.cpp)
    list(APPEND UNIT_SRC_FILES ${tmp})
endforeach()
message(STATUS "Unit test samples: " ${UNIT_SRC_FILES})
add_executable(opencv_unit_test ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp ${UNIT_SRC_FILES})

message(STATUS "Test var: " ${EXECUTABLE_OUTPUT_PATH})
target_link_libraries(opencv_unit_test ${_LINK_LIBS} ${GTEST_LIBRARIES})
