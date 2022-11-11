#pragma once
#include <iostream>

class TrainCar
{
private:
	bool trainCarType;
	int currentOccupancy;
	int occupancyLimit;
public:
	int getCurrentOccupancy();
	int getOccupancyLimit();
	bool getTrainCarType();
	void setCurrentOccupancy(int load);
	void setOccupancyLimit(int limit);
	void setTrainCarType(bool type);
};

class GoodsTrainCar :public TrainCar
{
public:
	GoodsTrainCar(int limit);
};

class PassengerTrainCar :public TrainCar
{
public:
	PassengerTrainCar(int limit);
};
