cmake_minimum_required(VERSION 3.12)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

add_library(Graph src/Graph.cpp src/Edge.cpp )

add_executable(GraphExec src/Graph.cpp src/Edge.cpp tests/main.cpp)


