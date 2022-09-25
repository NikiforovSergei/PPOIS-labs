cmake_minimum_required(VERSION 3.23)
project(LR1)

set(CMAKE_CXX_STANDARD 20)

add_executable(LR1 main.cpp PostMachine/PostMachine.cpp PostMachine/PostMachine.h)
