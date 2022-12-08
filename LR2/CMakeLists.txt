cmake_minimum_required(VERSION 3.23)
project(TESTlab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Testing2 main.cpp Entity/Animal.cpp Entity/Animal.h Entity/Herbivore.cpp Entity/Herbivore.h Entity/Plant.cpp Entity/Plant.h GameField/Cell.cpp GameField/Cell.h Entity/Entity.cpp Entity/Entity.h GameField/GameField.cpp GameField/GameField.h)
