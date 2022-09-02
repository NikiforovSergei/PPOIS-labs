cmake_minimum_required(VERSION 3.22)

project(Matrix)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)
add_executable(matrix_run ${SOURCE_FILES})

include_directories(matrix)

add_subdirectory(matrix)
add_subdirectory(matrix_test)

target_link_libraries(matrix_run matrix)