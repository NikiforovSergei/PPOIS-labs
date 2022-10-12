//
// Created by konstantin on 29.09.22.
//

#include "ocean_system.h"
#include "iostream"
#include <iomanip>

void ocean_system::run() {

    std::string menu;
    bool exit = false;

    show_ocean();

    std::cout<<"Enter a symbol(n - next, e - exit, s - state of cell): ";
    menu = check_input_char();

    while (!exit) {
       if(menu == "s" || menu == "S"){
           std::cout << "Enter a points of cell:";
           cell_state(input(0, ocean_field.at(0).size()),
                      input(0, ocean_field.size()));
       }else if(menu == "e" || menu == "E"){
           delete_ocean();
           exit = true;
       }else if(menu == "n" || menu == "N"){
           next();
       }else{
           std::cout<<"Error"<<std::endl;
       }

        if(!exit){
            std::cout<<"Enter a symbol(n - next, e - exit, s - state of cell): ";
            menu = check_input_char();
        }
    }
}

void ocean_system::show_ocean() {
    int counter = 0, memory = 0, jmemory = 0;

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            jmemory = j;
            for(int k = 0; k < 32*ocean_field.at(i).size(); k++){
                std::cout<<"#";
            }
            std::cout<<std::endl;
            memory = 0;
            for(int i_1 = 0; i_1 < 4; i_1++){
                int ocean_size = 0;
                while(ocean_size <= ocean_field.at(i).at(j).size()){
                    if(i_1<ocean_field.at(i).at(j).size()){
                        for(living* alive : ocean_field.at(i).at(j)){
                            if(counter==memory){
                                if(alive == nullptr){
                                    std::cout<<"\t "<<"----- -----"<<std::setw(10)<<"\t|";
                                    break;
                                }
                                std::cout<<"\t"<<alive->who()<<std::setw(10)<<"\t|";
                                break;
                            }
                            counter++;
                        }
                    } else {
                        std::cout<<"\t "<<"----- -----"<<std::setw(10)<<"\t|";
                    }

                    j++;
                    counter=0;
                    if(ocean_field.at(i).size()<=j){
                        break;
                    }
                }
                counter=0;
                memory++;
                j = jmemory;
                std::cout<<std::endl;
            }
            break;
        }
    }
    for(int k = 0; k < 32*ocean_field.at(0).size(); k++){
        std::cout<<"#";
    }
    std::cout<<std::endl;

}

void ocean_system::cell_state(int index_2, int index_1) {
    for(int i = 0; i < 20; i++){
        std::cout<<"#";
    }

    std::cout<<"\tCell state( 0 - male, 1 - female):"<<std::endl;

    for(auto & alive : ocean_field.at(index_1).at(index_2)){
        if(alive == nullptr){
            continue;
        }
        std::cout<<alive->who()<<"\t"<<alive->getInfo()<<std::endl;
    }
    for(int i = 0; i < 20; i++){
        std::cout<<"#";
    }
    std::cout<<std::endl;
}

int ocean_system::input(int begin, int end){
    int user_input;
    std::cin>>user_input;

    while(user_input < (begin + 1)  || user_input >= (end + 1) ){
        std::cout<<"Oops, please, check if the input is correct!\n";
        std::cin.clear();
        std::cin.ignore(255,'\n');
        std::cin>>user_input;
    }
    return user_input - 1;
}

char ocean_system::check_input_char() {

    char temp;
    std::cin>>temp;

    while(temp != 69 && temp != 101 && temp != 78 &&
          temp != 110 && temp != 115  && temp != 83){
        std::cout<<"Something went wrong. Try again."<<std::endl;
        std::cin>>temp;

    }

    return  temp;

}

void ocean_system::next() {

    for(size_t i = 0; i < ocean_field.size(); i++){
        for(size_t j = 0; j < ocean_field.at(i).size(); j++){
            move(ocean_field.at(i).at(j));
        }
    }

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            for(auto & alive: ocean_field.at(i).at(j)) {
                if(alive == nullptr){
                    continue;
                }
                alive->setCheckStep();
            }
        }
    }
    show_ocean();

}

void ocean_system::move(std::vector<living*> &cell){
    std::pair<int,int> points;
    int temp[6];
    std::pair<int,int> previous;

    for(size_t i = 0; i < cell.size(); i++){

        if(cell.at(i) == nullptr){
            continue;
        }

        if(cell.at(i)->getType() == state::corals || cell.at(i)->getType() == state::seaweed){
            points = cell.at(i)->go(ocean_field);
            if(cell.at(i)->getAmouont() < 0){
                delete cell.at(i);
                cell.at(i) = nullptr;
                continue;
            }
            continue;
        }

        if(cell.at(i)->getCheckStep()){
            continue;
        }

        if(cell.at(i)->check_die()){
            delete cell.at(i);
            cell.at(i) = nullptr;
            continue;
        }
        previous.first = cell.at(i)->getPoint().first;
        previous.second = cell.at(i)->getPoint().second;

        points = cell.at(i)->go(ocean_field);
        if(cell.at(i)->die_from_other() != nullptr){
            for(size_t n = 0; n < ocean_field.at(points.first).at(points.second).size(); n++){
                if(ocean_field.at(points.first).at(points.second).at(n) == cell.at(i)->die_from_other()){
                    delete ocean_field.at(points.first).at(points.second).at(n);
                    ocean_field.at(points.first).at(points.second).at(n) = nullptr;
                    break;
                }
            }
            cell.at(i)->victim(nullptr);
            continue;
        }

        if(cell.at(i)->propagate() && cell.at(i)->getPropogate_state() && cell.at(i)->getType() != state::kril){
            temp[0] = points.first;
            temp[1] = points.second;
            temp[2] = 0;
            temp[3] = cell.at(i)->getSex();
            temp[4] = 1;
            temp[5] = 100;
            cell.at(i)->setPropogate();
            for(size_t n = 0; n < ocean_field.at(points.first).at(points.second).size(); n++){
                if(ocean_field.at(points.first).at(points.second).at(n) == nullptr){
                    if(cell.at(i)->getType() == 0){
                        ocean_field.at(points.first).at(points.second).at(n) = fill_field(cell.at(i)->getName(),"shark",temp);
                        std::cout<<"Was born "<< ocean_field.at(points.first).at(points.second).at(n)->getName()<<std::endl;
                        break;

                    }else if(cell.at(i)->getType() == 1){
                        ocean_field.at(points.first).at(points.second).at(n) = fill_field(cell.at(i)->getName(),"salmon",temp);
                        std::cout<<"Was born "<< ocean_field.at(points.first).at(points.second).at(n)->getName()<<std::endl;
                        break;

                    }else if(cell.at(i)->getType() == 3){
                        ocean_field.at(points.first).at(points.second).at(n) = fill_field(cell.at(i)->getName(),"puffer",temp);
                        std::cout<<"Was born "<< ocean_field.at(points.first).at(points.second).at(n)->getName()<<std::endl;
                        break;

                    }else if(cell.at(i)->getType() == 2){
                        ocean_field.at(points.first).at(points.second).at(n) = fill_field(cell.at(i)->getName(),"clown",temp);
                        std::cout<<"Was born "<< ocean_field.at(points.first).at(points.second).at(n)->getName()<<std::endl;
                        break;

                    }else if(cell.at(i)->getType() == 6) {
                        ocean_field.at(points.first).at(points.second).at(n) = fill_field(cell.at(i)->getName(),"anchovys",temp);
                        std::cout<<"Was born "<< ocean_field.at(points.first).at(points.second).at(n)->getName()<<std::endl;
                        break;
                    }
                }
            }
        }
        if(previous.first == points.first && previous.second == points.second) {

        }else{
            for(size_t n = 0; n < ocean_field.at(points.first).at(points.second).size(); n++){
                if(ocean_field.at(points.first).at(points.second).at(n) == nullptr){
                    ocean_field.at(points.first).at(points.second).at(n) = cell.at(i);
                    break;
                }
            }
            cell.at(i) = nullptr;
        }
    }
}
