//
// Created by konstantin on 29.09.22.
//

#include "ocean.h"
#include <iostream>


living* ocean::fill_field(const std::string& name, const std::string& type, int temp[]) {

    try {
        if(type == "shark"){
            return new class shark(name, temp);

        }else if(type == "salmon"){
            return new  class salmon(name, temp);

        }else if(type == "puffer"){
            return new  class puffer(name, temp);

        }else if(type == "clown"){
            return new  class clown(name, temp);

        }else if(type == "anchovys"){
            return new  class anchovys(name, temp);

        }else if(type == "corals"){
            return new  class corals(temp);

        }else if(type == "seaweed"){
            return new  class seaweed(temp);

        }else if(type == "kril"){
            return new class kril(temp);
        }else{
            throw Exception("Something, went wrong");
        }

    } catch (std::exception &exception) {
        std::cout << exception.what() << std::endl;
        std::cout << "Please, check you data from file!" << std::endl;
        sleep(5);
        return nullptr;
    }

}
void ocean::delete_ocean() {

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            for(auto & alive: ocean_field.at(i).at(j)){
                delete alive;
            }
        }
    }

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            ocean_field.at(i).at(j).clear();
        }
    }

    for(int i = 0; i < ocean_field.size(); i++){
        ocean_field.at(i).clear();
    }

    ocean_field.clear();}

