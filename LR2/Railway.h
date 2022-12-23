//
// Created by fasolinger on 22.12.22.
//

#ifndef PPOIS_2_RAILWAY_H
#define PPOIS_2_RAILWAY_H


#include <vector>
#include <queue>
#include "Station.h"
#include "Train.h"

using namespace std;

class Railway {
private:
    queue<Station> stations;
    Train train;
public:
    Railway(queue<Station> stations, Train train) : stations(stations), train(train) {}
    
    void startTrain(){
        int size = stations.size();
        for (int i = 0; i < size; ++i) {
            if (i== size-1){
                Station currentStation = stations.front();
                train.processStation(currentStation, true);
                stations.pop();
            }else {
                Station currentStation = stations.front();
                train.processStation(currentStation );
                stations.pop();
            }
        }

    }
};

#endif //PPOIS_2_RAILWAY_H
