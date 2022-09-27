cmake_minimum_required(VERSION 3.23)
project(PostMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(PostMachine main.cpp Lib/postMachine.cpp Lib/postMachine.h)
