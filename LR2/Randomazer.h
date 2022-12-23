//
// Created by fasolinger on 22.12.22.
//

#ifndef PPOIS_2_RANDOMAZER_H
#define PPOIS_2_RANDOMAZER_H

#include <ctime>
#include <iostream>
#include <queue>

using namespace std;

class Randomazer {
public:
    static int generateRandomValue(int min,int max){
        int num = min + rand() % (max - min + 1);
        return num;
    }

    static queue <Station> generateRandomStation(){
        queue <Station> stations;
        for(int i =0; i<10;i++){
            Station *s = new Station("Station_"+ to_string(i+1),StationType::PASS_FREIGHT_STATION,Randomazer::generateRandomValue(30,100));
            stations.push(*s);
        }
        return stations;
    }
private:
    Randomazer(){}
};


#endif //PPOIS_2_RANDOMAZER_H
