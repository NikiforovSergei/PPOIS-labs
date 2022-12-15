#include "RailwayStation.h"

int RailwayStation::getMapPostion()
{
	return railwayStationNumber;
}

int RailwayStation::getOffloadedResource(bool type)
{
	return offloadedResource;
}

int RailwayStation::getTranspotableResource(bool type)
{
	return transpotableResource;
}

int RailwayStation::getRailwayStationNumber()
{
	return railwayStationNumber;
}

int RailwayStation::getRailwayStationType()
{
	return railwayStationType;
}

int MultiRailwayStation::getTranspotableResource(bool type)
{
	if (!type)
		return RSPart1.getTranspotableResource(type);
	else
		return RSPart2.getTranspotableResource(type);
}

int MultiRailwayStation::getOffloadedResource(bool type)
{
	if (!type)
		return RSPart1.getOffloadedResource(type);
	else
		return RSPart2.getOffloadedResource(type);
}

bool RailwayStation::checkLoadPossibility(int necessaryCargo)
{
	if (transpotableResource - necessaryCargo >= 0)
		return true;
	else
		return false;
}

GoodsRailwayStation::GoodsRailwayStation(int number, int transpotableResource)
{
	this->setTranspotableResource(transpotableResource);
	this->setRailwayStationNumber(number);
	this->setRailwayStationType(1);
}

PassengerRailwayStation::PassengerRailwayStation(int number, int transpotableResource)
{
	this->setTranspotableResource(transpotableResource);
	this->setRailwayStationNumber(number);
	this->setRailwayStationType(2);
}

MultiRailwayStation::MultiRailwayStation(int number,GoodsRailwayStation &obj1,PassengerRailwayStation &obj2) : RSPart1(obj1), RSPart2(obj2)
{
	this->setRailwayStationNumber(number);
	RSPart1 = obj1;
	RSPart2 = obj2;
	this->setRailwayStationType(3);
}

int PassengerRailwayStation::loadTrain(Train& currentTrain, int necessaryCargo, bool type)
{
	if (currentTrain.getCurrentChain().getTrainChainOccupancyLimit(1) < necessaryCargo)
		return 1;
	if (!this->checkLoadPossibility(necessaryCargo))
		return 2;
	else
	{
		int loadPerTrainCar = round(necessaryCargo / currentTrain.getCurrentChain().getTrainCarList(1).size());
		for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(1).size(); ++i)
			currentTrain.getCurrentChain().getTrainCarList(1)[i]->setCurrentOccupancy(currentTrain.getCurrentChain().getTrainCarList(1)[i]->getCurrentOccupancy() + loadPerTrainCar);
		currentTrain.calculateWeight();
		currentTrain.calculateSpeed();
		this->setTranspotableResource(this->getTranspotableResource(1) - necessaryCargo);
		currentTrain.calculateWeight();
		currentTrain.calculateSpeed();
		return 3;
	}
}

void PassengerRailwayStation::offloadTrain(Train& currentTrain, double necessaryOffloadPercent, bool type)
{
	double offloadWeight = 0, offloadedResource = 0;
	for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(1).size(); ++i)
		offloadWeight += currentTrain.getCurrentChain().getTrainCarList(1)[i]->getCurrentOccupancy();
	offloadWeight = offloadWeight * (necessaryOffloadPercent / 100) / currentTrain.getCurrentChain().getTrainCarList(1).size();
	for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(1).size(); ++i)
	{
		currentTrain.getCurrentChain().getTrainCarList(1)[i]->setCurrentOccupancy(currentTrain.getCurrentChain().getTrainCarList(1)[i]->getCurrentOccupancy() - offloadWeight);
		offloadedResource += offloadWeight;
	}
	currentTrain.calculateWeight();
	currentTrain.calculateSpeed();
	this->setOffloadResource(offloadedResource);
}


int GoodsRailwayStation::loadTrain(Train &currentTrain, int necessaryCargo, bool type)
{	
	if (currentTrain.getCurrentChain().getTrainChainOccupancyLimit(0) < necessaryCargo)
		return 1;
	if (!this->checkLoadPossibility(necessaryCargo))
		return 2;
	else {
		int loadPerTrainCar = round(necessaryCargo / currentTrain.getCurrentChain().getTrainCarList(0).size());
		for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(0).size(); ++i)
			currentTrain.getCurrentChain().getTrainCarList(0)[i]->setCurrentOccupancy(currentTrain.getCurrentChain().getTrainCarList(0)[i]->getCurrentOccupancy() + loadPerTrainCar);
		currentTrain.calculateWeight();
		currentTrain.calculateSpeed();
		this->setTranspotableResource(this->getTranspotableResource(0) - necessaryCargo);
		currentTrain.calculateWeight();
		currentTrain.calculateSpeed();
		return 3;
	}
}

void GoodsRailwayStation::offloadTrain(Train &currentTrain, double necessaryOffloadPercent, bool type)
{
	double offloadWeight=0,offloadedResource=0;
	for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(0).size(); ++i)
		offloadWeight += currentTrain.getCurrentChain().getTrainCarList(0)[i]->getCurrentOccupancy();
	offloadWeight=offloadWeight*(necessaryOffloadPercent / 100) / currentTrain.getCurrentChain().getTrainCarList(type).size();
	for (int i = 0; i < currentTrain.getCurrentChain().getTrainCarList(0).size(); ++i)
	{
		currentTrain.getCurrentChain().getTrainCarList(0)[i]->setCurrentOccupancy(currentTrain.getCurrentChain().getTrainCarList(0)[i]->getCurrentOccupancy() - offloadWeight);
		offloadedResource += offloadWeight;
	}
	currentTrain.calculateWeight();
	currentTrain.calculateSpeed();
	this->setOffloadResource(offloadedResource);
}

void MultiRailwayStation::offloadTrain(Train& currentTrain, double necessaryOffloadPercent, bool type)
{
	if (!type)
		RSPart1.offloadTrain(currentTrain, necessaryOffloadPercent, type);
	else
		RSPart2.offloadTrain(currentTrain, necessaryOffloadPercent, type);
}

int MultiRailwayStation::loadTrain(Train &currentTrain, int necessaryCargo, bool type)
{
	if (!type)
		return RSPart1.loadTrain(currentTrain, necessaryCargo, type);
	else
		return RSPart2.loadTrain(currentTrain, necessaryCargo, type);
}

void RailwayStation::setOffloadResource(int resource)
{
	offloadedResource = resource;
}

void RailwayStation::setTranspotableResource(int resource)
{
	transpotableResource = resource;
}

void RailwayStation::setRailwayStationNumber(int RSNumber)
{
	railwayStationNumber = RSNumber;
}

void RailwayStation::setRailwayStationType(int type)
{
	railwayStationType = type;
}