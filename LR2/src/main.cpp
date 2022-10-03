#include "gameEngine/gameEngine.hpp"

int main()
{
    gameEngine::engine* tmp = new gameEngine::engine;

    tmp->init("Test start");
    tmp->start();

    tmp->cleanup();
    tmp->quit();
    
    return 0;
}