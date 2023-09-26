find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)
include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIRS}
)
add_executable(eigen_unit_test test_main.cpp unit_test.cpp)
target_link_libraries(eigen_unit_test ${EIGEN3_LIBS} ${GTEST_LIBRARIES})