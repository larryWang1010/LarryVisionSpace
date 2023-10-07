find_package(PCL REQUIRED)
message(STATUS "Pcl version: " ${PCL_VERSION})
include_directories(
    ${PCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")#不加这个会报错,必须在下面这行之前
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})



# unit test
option(ENABLE_UNIT_TEST "Enable unit test" ON)
include_directories( 
  ${GTEST_INCLUDE_DIRS}
)
if(ENABLE_UNIT_TEST)
    add_executable(unit_test_cpp 
        unit_test/test_main.cpp
        unit_test/unit_test_converter.cpp
    )
    target_link_libraries(unit_test_cpp ${GTEST_LIBRARIES})
endif()


# app
add_executable(txt2pcd app/txt2pcd.cpp)
target_link_libraries(txt2pcd ${PCL_LIBRARIES})
add_executable(tmp app/tmp.cpp)
target_link_libraries(tmp)