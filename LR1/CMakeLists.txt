cmake_minimum_required(VERSION 3.23)
project(LabPPOIS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
set(SOURCE_FILES main.cpp Tests.cpp)
add_executable(LabPPOIS ${SOURCE_FILES})
target_link_libraries(LabPPOIS gtest gtest_main)
