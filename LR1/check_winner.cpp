//
// Created by konstantin on 10.09.22.
//

#include "game.h"

///\file check_winner.cpp
/// \brief содержит метод проверки выиграша


/** @defgroup check_winner check_winner.cpp
 * Проверка на выигрыш
 * @{
 */

bool Game::CheckWinnerSet() {

    for(int i = 0; i < size_of_field; i++){
        for(int j = 0; j < size_of_field; j++){
            if(field.at(i).at(j).number != pattern_of_winners_set.at(i).at(j)){
                return false;
            }
        }
    }
    return true;

}
/** @} */