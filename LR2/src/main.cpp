#include "gameEngine/gameEngine.hpp"
#include "gameCycle/mainCycle.hpp"
#include "gameField/fieldAndCell.hpp"
#include "gameState/introState.hpp"
#include "entityInterface/animal.hpp"

#include <iostream>

int main(int argc, char **args)
{
    gameField::cell _cell(4);
    animal panda("panda", 100, 20, MALE, 1, "../assets/panda.png");
    gameField::field *_field = new gameField::field(8, 5, _cell);
    _field->getCell(1, 1)->put(new animal(panda));
    _field->getCell(1, 1)->put(new animal(panda));
    gameCycle::mainCycle _cycle;
    gameEngine::engine _game(_field, &_cycle);
    
    if (!_game.init("Test start", 800u, 500u));
    {
        _game.changeState(new introState());
        _game.start();
    }

    _game.cleanup();
    _game.quit();

    delete _field;
    return 0;
}