cmake_minimum_required(VERSION 3.24)
project(LR2)

find_package(Crow)
target_link_libraries(Crow::Crow)
add_compile_options(-pthread)

set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
SET(CMAKE_CXX_FLAGS " -pthread")

add_executable(LR2 main.cpp field/field.h field/field.cpp field/square.h field/square.cpp dwellers/dweller.h dwellers/dweller.cpp dwellers/plant.h dwellers/plant.cpp dwellers/herbivore.h dwellers/herbivore.cpp dwellers/animal.h dwellers/animal.cpp dwellers/carnivore.h dwellers/carnivore.cpp)
