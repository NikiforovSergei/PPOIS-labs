//
// Created by fasolinger on 22.12.22.
//

#ifndef PPOIS_2_STATION_H
#define PPOIS_2_STATION_H

#include <string>
using namespace std;

enum StationType{
    PASS_STATION,
    FREIGHT_STATION,
    PASS_FREIGHT_STATION
};
class Station {

private:
    string stationName;
    StationType stationType;
    double distanceToNextStation;

public:
    void setDistanceToNextStation(double distanceToNextStation) {
        Station::distanceToNextStation = distanceToNextStation;
    }

    Station(string stationName,StationType stationType,int distanceToNextStation):
            stationName(stationName),
            stationType(stationType),
            distanceToNextStation(distanceToNextStation)
            {}

    StationType getStationType() const {
        return stationType;
    }

    const string &getStationName() const {
        return stationName;
    }

    double getDistanceToNextStation() const {
        return distanceToNextStation;
    }
};


#endif //PPOIS_2_STATION_H
