
#include "game.h"

/// \file game_field.cpp
/// \brief содержит методы игрвого поля

/** @defgroup game_field game_field.cpp
 * Игровой поле
 * @{
 */


void Game::CreateField() {

    srand(time(NULL));
    std::cout<<"Please, enter the margin side size: ";
    size_of_field = CheckInputNumber();
    while(size_of_field<2 || size_of_field > 10){
        std::cout<<"Oops, that input is invalid.  Please try again!\n";
        size_of_field = CheckInputNumber();
    }
    system("./cls.sh");
    pattern_of_winners_set.resize(size_of_field);
    field.resize(size_of_field);
    int counter=1;

    for(int i = 0; i < size_of_field; i++){
        for(int j = 0; j < size_of_field; j++){
            pattern_of_winners_set.at(i).push_back(counter);
            counter++;
        }
    }
    pattern_of_winners_set.at(size_of_field-1).at(size_of_field-1)=0;

    int CheckExistValue=rand()% (size_of_field*size_of_field-1)+1;
    for(int i = 0; i < size_of_field; i++){
        for(int j = 0; j < size_of_field; j++){
            while(!CheckCellOnRepetition(CheckExistValue)){
                CheckExistValue = rand()% (size_of_field*size_of_field);
            }
                if(CheckExistValue == 0){
                    points_of_empty.first = i;
                    points_of_empty.second = j;
                }
                Cell cell;
                cell.number = CheckExistValue;
                cell.points.first=i;
                cell.points.second = j;
                field.at(i).push_back(cell);
        }
    }

}

bool Game::CheckCellOnRepetition(int number) {

    for(int i = 0; i <= size_of_field; i++){
        for(int j = 0; j < size_of_field; j++){
            if(field.at(i).empty() || field.at(i).size()-1<j){
                return true;
            }
            if(field.at(i).at(j).number==number){
                return false;
            }
        }
    }
    return true;

}

void Game::ShowField() {

    for(int i = 0; i < size_of_field; i++){
        for(int k = 0; k < size_of_field; k++){
            std::cout<<"\t"<<" "<<"\t"<<"|";
        }
        std::cout<<std::endl;
        for(int j = 0; j < size_of_field; j++){
            std::cout<<"\t"<<field.at(i).at(j).number<<"\t"<<"|";
        }
        std::cout<<std::endl;
        for(int k = 0; k < size_of_field; k++){
            std::cout<<"\t"<<" "<<"\t"<<"|";
        }
        std::cout<<std::endl;
        for(int k = 0; k < size_of_field; k++){
            std::cout<<"----------------";
        }
        std::cout<<std::endl;
    }

}


int Game::CheckInputNumber() {

    int choice;
    std::cin>>choice;

    do{
        try{
            if(choice==0){
                throw std::exception();
            }
            else{
                return choice;
            }
        }catch (std::exception& exception){
            std::cin.clear();
            std::cin.ignore(255,'\n');
            std::cout<<"Oops, that input is invalid.  Please try again!\n";
            std::cin>>choice;
        }
    } while (true);

}


void Game::DeleteField() {

    for(int i = 0; i < size_of_field; i++){
        field.at(i).clear();
        pattern_of_winners_set.at(i).clear();
    }
    field.clear();
    pattern_of_winners_set.clear();

    counter_of_move = 0;

}


bool Game::CheckUnpossibleWin() {
    if(size_of_field != 2){
        return false;
    }else{
        if(field.at(0).at(0).number==1 && field.at(1).at(0).number==2 && field.at(1).at(1).number==3){
            std::cout<<"This combination cannot be solved.Start a new game!\n";
            return true;
        }else if(field.at(0).at(1).number==3 && field.at(1).at(0).number==1 && field.at(1).at(1).number==2){
            std::cout<<"This combination cannot be solved.Start a new game!\n";
            return true;
        }else if(field.at(1).at(1).number==1 && field.at(0).at(1).number==2 && field.at(0).at(0).number==3){
            std::cout<<"This combination cannot be solved.Start a new game!\n";
            return true;
        }else if(field.at(1).at(0).number==3 && field.at(0).at(1).number==1 && field.at(0).at(0).number==2){
            std::cout<<"This combination cannot be solved.Start a new game!\n";
            return true;
        }
    }
    return false;
}
/** @} */