//
// Created by konstantin on 30.09.22.
//

#ifndef OCEAN_FILE_H
#define OCEAN_FILE_H

#include "ocean_system.h"

class file : public ocean_system {
public:

    file(std::fstream& file){
        std::string strtemp, strname, strtype;
        int temp[6],counter=0;
        char check;

        while (!file.eof()){
            file>>strtemp;
            if(ocean_field.empty()){
                ocean_field.resize(std::stoi(strtemp));
                file>>strtemp;
                for(int i = 0; i < ocean_field.size(); i++){
                    ocean_field.at(i).resize(std::stoi(strtemp));
                }
                continue;
            }

            if(isdigit(strtemp[0])){
                temp[counter] = std::stoi(strtemp);
            }else if (counter == 2){
                strtype = strtemp;
                continue;
            }else {
                strname = strtemp;
                counter=-1;
            }
            counter++;

            if(counter == 3){
                if(file.eof()){
                    counter = 0;
                }else{
                    file.get(check);
                    if(check == 10){
                        temp[counter]='\0';
                        counter = 0;
                    }
                }
            }

            if(counter==0){
                ocean_field.at(temp[0]).at(temp[1]).
                        push_back(fill_field(strname,strtype,temp));
            }
        }
        for(int i = 0; i < ocean_field.size(); i++){
            for(int j = 0; j < ocean_field.at(i).size(); j++){
                while(ocean_field.at(i).at(j).size() < 4){
                    ocean_field.at(i).at(j).push_back(nullptr);
                }
            }
        }
    }

};
#endif //OCEAN_FILE_H
