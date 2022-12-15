#include "TrainCar.h"

int TrainCar::getCurrentOccupancy()
{
	return currentOccupancy;
}

int TrainCar::getOccupancyLimit()
{
	return occupancyLimit;
}

bool TrainCar::getTrainCarType()
{
	return trainCarType;
}

void TrainCar::setCurrentOccupancy(int load)
{
	currentOccupancy = load;
}

void TrainCar::setOccupancyLimit(int limit)
{
	occupancyLimit = limit;
}

void TrainCar::setTrainCarType(bool type)
{
	trainCarType = type;
}

GoodsTrainCar::GoodsTrainCar(int limit)
{
	this->setCurrentOccupancy(0);
	this->setOccupancyLimit(limit);
	this->setTrainCarType(0);
}

PassengerTrainCar::PassengerTrainCar(int limit)
{
	this->setCurrentOccupancy(0);
	this->setOccupancyLimit(limit);
	this->setTrainCarType(1);
}