#include "TrainCarChain.h"

TrainCarChain::TrainCarChain(std::vector<TrainCar*> trCarChain)
{
	trainCarChain = trCarChain;
	this->trainCarPartition();
	if (goodsTrainCar.size() == trainCarChain.size())
		this->setTrainCarChainType(1);
	else if (passengerTrainCar.size() == trainCarChain.size())
		this->setTrainCarChainType(2);
	else
		this->setTrainCarChainType(3);
}

void TrainCarChain::trainCarPartition()
{
	for (int i = 0; i < trainCarChain.size(); ++i)
	{
		if (trainCarChain[i]->getTrainCarType())
			passengerTrainCar.push_back(trainCarChain[i]);
		else
			goodsTrainCar.push_back(trainCarChain[i]);
	}
}

int TrainCarChain::getTrainCarValueByType(bool type)
{
	if (type)
		return passengerTrainCar.size();
	else
		return goodsTrainCar.size();
};

int TrainCarChain::getTrainCarChainType()
{
	return trainChainType;
}

std::vector<TrainCar*> TrainCarChain::getTrainCarList(bool type)
{
	if (type)
		return passengerTrainCar;
	else
		return goodsTrainCar;
}

std::vector<TrainCar*> TrainCarChain::getFullTrainCarList()
{
	return trainCarChain;
}

void TrainCarChain::setTrainCarChainType(int type)
{
	trainChainType = type;
}

int TrainCarChain::getTrainChainOccupancyLimit(bool type)
{
	if (type)
	{
		int limit = 0;
		for (int i = 0; i < this->getTrainCarList(1).size(); ++i)
			limit += this->getTrainCarList(1)[i]->getOccupancyLimit();
		return limit;
	}
	else
	{
		int limit = 0;
		for (int i = 0; i < this->getTrainCarList(0).size(); ++i)
			limit += this->getTrainCarList(0)[i]->getOccupancyLimit();
		return limit;
	}
}

int TrainCarChain::getTrainCarChainCurrentOccupancy(bool type)
{
	if (type)
	{
		int occupancy = 0;
		for (int i = 0; i < this->getTrainCarList(1).size(); ++i)
			occupancy += this->getTrainCarList(1)[i]->getCurrentOccupancy();
		return occupancy;
	}
	else
	{
		int occupancy = 0;
		for (int i = 0; i < this->getTrainCarList(0).size(); ++i)
			occupancy += this->getTrainCarList(0)[i]->getCurrentOccupancy();
		return occupancy;
	}
}