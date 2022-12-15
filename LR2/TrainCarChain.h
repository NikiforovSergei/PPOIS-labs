#pragma once
#include <vector>
#include "TrainCar.h"
class TrainCarChain
{
private:
	std::vector<TrainCar*> trainCarChain;
	std::vector<TrainCar*> passengerTrainCar;
	std::vector<TrainCar*> goodsTrainCar;
	int trainChainType = 0;
	void trainCarPartition();
	void setTrainCarChainType(int type);
public:
	TrainCarChain(std::vector<TrainCar*> trCarChain);
	int getTrainCarValueByType(bool type);
	int getTrainCarChainType();
	std::vector<TrainCar*> getTrainCarList(bool type);
	std::vector<TrainCar*> getFullTrainCarList();
	int getTrainChainOccupancyLimit(bool type);
	int getTrainCarChainCurrentOccupancy(bool type);
};

