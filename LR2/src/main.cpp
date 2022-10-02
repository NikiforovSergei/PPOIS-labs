#include "gameEngine/gameEngine.hpp"
using namespace gameEngine;

int main()
{
    engine* game = new gameEngine::engine();

    game->init("Test game");
    game->start();

    game->quit();
    game->cleanup();

    return 0;
}