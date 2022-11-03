cmake_minimum_required(VERSION 3.16.3)
project(ppvis_lab2)

set(CMAKE_CXX_STANDARD 17)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTests tests/tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
