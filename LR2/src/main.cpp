#include "gameEngine/gameEngine.hpp"
#include "gameCycle/mainCycle.hpp"
#include "gameField/fieldAndCell.hpp"
#include "gameState/introState.hpp"
#include "entityInterface/animal.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char **args)
{
    gameField::field _field;
    std::fstream FILE("../field.txt");
    FILE >> _field;

    std::fstream out("../outField.txt");
    out << _field;

    //gameCycle::mainCycle _cycle;
    //gameEngine::engine _game(&_field, &_cycle);

    //if (!_game.init("Test start", 800u, 800u))
    //{
    //    _game.changeState(new introState());
    //    _game.start();
    //}

    //_game.cleanup();
    //_game.quit();

    return 0;
}
