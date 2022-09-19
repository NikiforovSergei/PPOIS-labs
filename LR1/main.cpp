
#include "game.h"

/// \file main.cpp
/// \brief главный файл

/// \brief содержит меню игры
int main() {

    Game Game;

    std::cout<<"1. New game\n2. Exit\n";
    std::cout<<"Choose an option: ";
    int choice = Game.CheckInputNumber();

    while (choice!=2){
        while (choice>2 || choice<1){
            std::cout<<"Oops, that input is invalid.  Please try again!\n";
            choice = Game.CheckInputNumber();
        }
        if(choice==2){
            break;
        }
        Game.PlayProcess();

        std::cout<<"1. New game\n2. Exit\n";
        std::cout<<"Choose an option: ";
        choice = Game.CheckInputNumber();
    }

    return 0;

}