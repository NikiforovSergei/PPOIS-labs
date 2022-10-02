cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

#include(CTest)
#enable_testing()

add_executable(
    main
    src/main.cpp
    src/entityInterface/abstractEntity.hpp
    src/entityInterface/abstractEntity.cpp
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

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
