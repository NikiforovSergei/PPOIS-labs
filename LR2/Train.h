#ifndef PPOIS_2_TRAIN_H
#define PPOIS_2_TRAIN_H

#include <iostream>
#include "Station.h"
#include "Randomazer.h"
#include <unistd.h>



using namespace std;

class Train {
private:
    static const int MAX_PASS_BY_CAR=50;
    static const int MAX_MASS_BY_CAR =68;
    constexpr static const double SPEED_LOST_BY_MASS = 0.005;
    constexpr static const double SPEED_LOST_BY_PASSENGERS = 0.001;
    double defaultTrainSpeed;
    int passCars;
    int freightCars;

    int actualPass=0;
    int actualMass=0;
    double actualTrainSpeed;

    void processPassengers(Station station){
        int passengersLeave = Randomazer::generateRandomValue(0,actualPass);
        cout<<"Train lose "<<passengersLeave<<" passengers"<<endl;
        actualPass-=passengersLeave;
        int passengersGet = Randomazer::generateRandomValue(0,(MAX_PASS_BY_CAR*passCars)-actualPass);
        cout<<"Train get "<<passengersGet<<" passengers"<<endl;
        actualPass+=passengersGet;
        cout<<"- In train now "<<actualPass<<" passengers"<<endl;
    }

    void processFreight(Station station) {
        int massLeave = Randomazer::generateRandomValue(0,actualMass);
        cout<<"Train lose "<<massLeave<<" tons"<<endl;
        actualMass-=massLeave;
        int massGet = Randomazer::generateRandomValue(0,(MAX_MASS_BY_CAR*freightCars)-actualMass);
        cout<<"Train get "<<massGet<<" tons"<<endl;
        actualMass+=massGet;
        cout<<"- In train now "<<actualMass<<" tons"<<endl;
    }

    void calculateSpeed(Station station) {
        actualTrainSpeed-= (actualMass*SPEED_LOST_BY_MASS)+(actualPass*SPEED_LOST_BY_PASSENGERS);
        cout<<"Now train is moving "<<actualTrainSpeed<<"km/h"<<endl;
        cout<<"Distance to the next station "<<station.getDistanceToNextStation()<<" kilometers"<<endl;
        double time = station.getDistanceToNextStation()/actualTrainSpeed;
        cout<<"Train will arrive to the next station after "<<time<<" hours"<<endl;
        sleep(time*10);
    }

public:

    Train (){
        int passCars, freightCars;
        double defaultTrainSpeed;
        cout<<"Default speed - "; cin>>defaultTrainSpeed;
        cout<<"Passengers cars - "; cin>>passCars;
        cout<<"Freight cars - "; cin>>freightCars;
        this->passCars = passCars;
        this->freightCars = freightCars;
        this->defaultTrainSpeed = defaultTrainSpeed;
        this->actualTrainSpeed = defaultTrainSpeed;
    }

    void processStation(Station station,bool isLast= false){
        cout<<"\t\tTrain arrive to "+ station.getStationName()<<endl;
        if (!isLast){
            switch (station.getStationType()) {
                case StationType::PASS_FREIGHT_STATION:{
                    processPassengers(station);
                    processFreight(station);
                    break;
                }
                case StationType::PASS_STATION: {
                    processPassengers(station);
                    break;
                }
                case StationType::FREIGHT_STATION: {
                    processFreight(station);
                    break;
                }
            }
            calculateSpeed(station);
        }else{
            cout<<"Train lose "<<actualPass<<" passengers"<<endl;
            actualPass-=actualPass;
            cout<<"Train get "<<0<<" passengers"<<endl;
            cout<<"- In train now "<<actualPass<<" passengers"<<endl;

            cout<<"Train lose "<<actualMass<<" tons"<<endl;
            actualMass-=actualMass;
            cout<<"Train get "<<0<<" tons"<<endl;
            cout<<"- In train now "<<actualMass<<" tons"<<endl;
            cout<<"\t\t\tTrain is STOPPED!!!"<<endl;
        }

        cout<<"==================================="<<endl;
    }
};


#endif //PPOIS_2_TRAIN_H
