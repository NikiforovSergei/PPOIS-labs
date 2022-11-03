#pragma once
#include "Trains.h"
#include "Stations.h"
#include "RailwayField.h"

const float tickTime = 0.25;

class InProgramTime
{
private:
	unsigned short int hours;
	unsigned short int minutes;
public:
	InProgramTime();
	void ShowTime();
	InProgramTime operator+(float tickTime);
};

class TrainInTimeManipulator
{
public:
	void ChangingConditionsOfTheTrain(Train* train);
};
