cmake_minimum_required(VERSION 3.23)
project(MatrixLib)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(tests/googletest)
include_directories(tests/googletest/googletest/include)
#add_custom_target(copy_assets
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/test/assets ${CMAKE_CURRENT_BINARY_DIR}/test/assets
#)
#include_directories(mytarget copy_assets)

add_executable(MatrixLib matrix.h numeric_matrix.h tests/main.cpp)
target_link_libraries(MatrixLib gtest_main)