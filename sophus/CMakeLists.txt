# todo: sophus 由两个版本：非模板和模板，编译
find_package(Sophus REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIRS}
    ${Sophus_INCLUDE_DIRS}
)
add_executable(unit_test_sophus 
    test_main.cpp 
    unit_test_sophus.cpp
)
target_link_libraries(unit_test_sophus 
    ${EIGEN3_LIBS} 
    ${GTEST_LIBRARIES} 
    ${Sophus_LIBRARIES}
)