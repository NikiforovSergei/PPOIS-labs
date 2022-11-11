#include "Train.h"

Train::Train(Locomotive &trLocomotive, TrainCarChain &trCarChain) : trainLocomotive(trLocomotive), trainCarChain(trCarChain)
{
	this->calculateWeight();
	this->calculateSpeed();;
}

int Train::getCurrentWeight()
{
	return currentWeight;
}

int Train::getTrainSpeed()
{
	return trainSpeed;
}

int Train::getCurrentPosition()
{
	return currentPosition;
}

void Train::reduceLifeTime(int lifeTime)
{
	trainLocomotive.setLifeTime(trainLocomotive.getLifeTime()-lifeTime);
}

Locomotive Train::getCurrentLocomotive()
{
	return trainLocomotive;
}

std::vector<int> Train::getRoute()
{
	return route;
}

TrainCarChain Train::getCurrentChain()
{
	return trainCarChain;
}

void Train::calculateWeight()
{
	double weight = 0;
	for (int i = 0; i < trainCarChain.getFullTrainCarList().size(); ++i)
		if (trainCarChain.getFullTrainCarList()[i]->getTrainCarType())
			weight += (trainCarChain.getFullTrainCarList()[i]->getCurrentOccupancy() * 80) * 0.001 + 45;
		else
			weight += trainCarChain.getFullTrainCarList()[i]->getCurrentOccupancy()+45;
	weight += 80; //вес локомотива(80)
	this->setCurrentWeight(round(weight));
}

void Train::calculateSpeed()
{
	int speed=0;
	speed = round(trainLocomotive.getTractiveForce() / this->getCurrentWeight()) * 10;
	if (speed > 90 && trainCarChain.getTrainCarChainType() != 2)
		speed = 90;
	else if (speed < 20)
		speed = 25; // минимально-допустимая скорость = 25
	this->setTrainSpeed(speed);
}

void Train::setTrainSpeed(int speed)
{
	trainSpeed = speed;
}

void Train::setCurrentWeight(int weight)
{
	currentWeight = weight;
}

void Train::setCurrentPosition(int position)
{
	currentPosition = position;
}

void Train::setRoute(std::vector<int> &trainRoute)
{
	route = trainRoute;
}

