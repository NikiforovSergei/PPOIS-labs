#pragma once
#include<vector>
#include "TrainCarChain.h"
#include "Locomotive.h"

class Train
{
private:
	Locomotive trainLocomotive;
	int trainSpeed = 0;
	int currentWeight = 0;
	int currentPosition = 0;
	std::vector<int> route;
	bool isArrived = false;
	TrainCarChain trainCarChain;
public:
	Train(Locomotive &trLocomotive, TrainCarChain &trCarChain);
	int getCurrentWeight();
	int getTrainSpeed();
	TrainCarChain getCurrentChain();
	int getCurrentPosition();
	Locomotive getCurrentLocomotive();
	std::vector<int> getRoute();
	void calculateSpeed();
	void calculateWeight();
	void setRoute(std::vector<int> &trainRoute);
	void setCurrentPosition(int position);
	void setCurrentWeight(int weight);
	void setTrainSpeed(int speed);
	void reduceLifeTime(int lifeTime);
};

