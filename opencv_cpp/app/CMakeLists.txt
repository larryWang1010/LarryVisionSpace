add_executable(disparity_filtering disparity_filtering.cpp)
target_link_libraries(disparity_filtering ${CV_TEST_LIB}) # 链接库

add_executable(image_pyramid image_pyramid.cpp)
target_link_libraries(image_pyramid ${CV_TEST_LIB}) # 链接库

add_executable(copy_make_border copy_make_border.cpp)
target_link_libraries(copy_make_border ${CV_TEST_LIB}) # 链接库