#include "gameEngine/gameEngine.hpp"
#include "gameCycle/mainCycle.hpp"
#include "gameField/fieldAndCell.hpp"
#include "gameState/introState.hpp"

#include <iostream>

int main(int argc, char **args)
{
    gameField::field* _field = new gameField::field(4, 3);
    gameCycle::mainCycle* _cycle = new gameCycle::mainCycle();
    gameEngine::engine *_game = new gameEngine::engine(_field, _cycle);
    _game->init("Test start");
    _game->changeState(new introState());
    _game->start();
    _game->cleanup();
    _game->quit();

    return 0;
}