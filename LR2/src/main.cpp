#include "gameEngine/gameEngine.hpp"
#include "entityInterface/animal.hpp"
#include "entityInterface/grassEater.hpp"
#include "entityInterface/abstractEntity.hpp"
#include "entityInterface/plant.hpp"

#include <iostream>

int main(int argc, char **args)
{
    gameEngine::engine *tmp = new gameEngine::engine;
    tmp->init("Test start");
    tmp->start();
    tmp->cleanup();
    tmp->quit();

    return 0;
}