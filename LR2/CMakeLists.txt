cmake_minimum_required(VERSION 3.22)

project(xml_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(xml_lib)
#include_directories(tests)

add_subdirectory(xml_lib)
#add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} xml_lib)