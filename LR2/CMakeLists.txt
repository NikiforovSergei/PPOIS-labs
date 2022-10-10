cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

add_executable(
    game
    src/main.cpp
    src/entityInterface/abstractEntity.hpp
    src/entityInterface/animal.hpp
    src/entityInterface/grassEater.hpp
    src/entityInterface/plant.hpp
    src/gameCycle/mainCycle.hpp
    src/gameCycle/mainCycle.cpp
    src/gameEngine/gameEngine.hpp
    src/gameEngine/gameEngine.cpp
    src/gameField/fieldAndCell.hpp
    src/gameField/fieldAndCell.cpp
    src/gameState/gameState.hpp
    src/gameState/introState.hpp
    src/gameState/introState.cpp
    src/gameState/moderateState.hpp
    src/gameState/moderateState.cpp
    src/gameState/autoState.hpp
    src/gameState/autoState.cpp
    )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

