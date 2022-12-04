cmake_minimum_required(VERSION 3.24)
project(LR2)
set(CMAKE_CXX_STANDARD 23)
add_executable(
        LR2
        stc/Tree/Tree.h
        stc/Tree/Tree.cpp
        stc/Parser/Parser.h
        stc/Parser/Parser.cpp
        stc/Exceptions/Exceptions.h main.cpp)

