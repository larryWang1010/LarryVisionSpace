include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIRS}
)
add_executable(unit_test_eigen 
    test_main.cpp 
    unit_test_eigen.cpp
)
target_link_libraries(unit_test_eigen ${EIGEN3_LIBS} ${GTEST_LIBRARIES})