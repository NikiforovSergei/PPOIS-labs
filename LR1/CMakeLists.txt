cmake_minimum_required(VERSION 3.23)
project(PPOISLab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(run_project main.cpp)
include_directories(rectangle_lib)

add_subdirectory(rectangle_lib)
add_subdirectory(rectangle_tests)

target_link_libraries(run_project rectangle_lib)