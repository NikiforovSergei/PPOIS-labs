#include "modelmap.h"
#include "railwaystation.h"

ModelMap::ModelMap(std::string path)
{	
	this->buildModel(path);
}

void ModelMap::deleteObjTrain(int index)
{
	trains.erase(trains.begin() + index);
}

Train* ModelMap::createObjectTypeTrain(TrainCarChain &chain, Locomotive &currentLoc, std::vector<int> &trainRoute)
{
	Train *obj = new Train (currentLoc,chain);
	obj->setRoute(trainRoute);
	return obj;
}

TrainCar* ModelMap::createObjectTypeTrainCar(int limit, bool type)
{
	if (type)
	{
		PassengerTrainCar* obj = new PassengerTrainCar(limit);
		return obj;
	}
	else
	{
		GoodsTrainCar* obj = new GoodsTrainCar(limit);
		return obj;
	}
}

TrainCarChain* ModelMap::createObjectTypeTrainCarChain(std::vector<TrainCar*> &chain)
{
	TrainCarChain* obj = new TrainCarChain(chain);
	return obj;
}

Locomotive* ModelMap::createObjectTypeLocomotive(int number, int lifetime, int tractiveForce)
{
	Locomotive* obj = new Locomotive(tractiveForce,lifetime,number);
	return obj;
}

GoodsRailwayStation* ModelMap::createObjectTypeGoodsRailwayStation(int number, int transpotableResource)
{
	GoodsRailwayStation* obj = new GoodsRailwayStation(number,transpotableResource);
	return obj;
}

PassengerRailwayStation* ModelMap::createObjectTypePassengerRailwayStation(int number, int transpotableResource)
{
	PassengerRailwayStation* obj = new PassengerRailwayStation(number, transpotableResource);
	return obj;
}

MultiRailwayStation* ModelMap::createObjectTypeMultiRailwayStation(int number, int transpotableResource1, int transpotableResource2)
{
	GoodsRailwayStation *obj1 = this->createObjectTypeGoodsRailwayStation(number,transpotableResource1);
	PassengerRailwayStation *obj2 = this->createObjectTypePassengerRailwayStation(number, transpotableResource2);
	MultiRailwayStation* obj = new MultiRailwayStation(number,*obj1,*obj2);
	obj->setRailwayStationNumber(number);
	return obj;
}

void ModelMap::setGraph(std::vector<std::vector<int>> &parsedGraph)
{
	graph = parsedGraph;
}

void ModelMap::createTrains(std::vector<std::vector<int>> &trainsInfo)
{	
	/*for (int i = 0; i < trainsInfo.size(); i++) {
		for (int j = 0; j < trainsInfo[i].size(); j++)
			std::cout << trainsInfo[i][j] << " ";
		std::cout << std::endl;
	}*/
	for (int i = 0; i < trainsInfo.size(); ++i)
	{
		std::vector<int> tmpRoute;
		std::vector<int> tmpComponents;
		std::vector<TrainCar*> tmpTrainCars;
		for (int j = 0; j < trainsInfo[i].size(); ++j)
		{
			if (trainsInfo[i][j] == -1) 
				tmpComponents.push_back(trainsInfo[i][j + 1]);
			if (trainsInfo[i][j] == -2)
				for (int z = 1; z < 3; ++z)
					tmpComponents.push_back(trainsInfo[i][j + z]);
			if (trainsInfo[i][j] == -3)
				for (int z = 1; z < 3; ++z)
					tmpComponents.push_back(trainsInfo[i][j + z]);
			if (trainsInfo[i][j] == -4)
			{
				for (int z = j+1; z < trainsInfo[i].size(); ++z)
					tmpRoute.push_back(trainsInfo[i][z]);
				break;
			}
		}
		for (int j = 0; j < tmpComponents[1]; ++j) {
			tmpTrainCars.push_back(this->createObjectTypeTrainCar(tmpComponents[2], 1));
		}
		for (int j = 0; j < tmpComponents[3]; ++j) 
			tmpTrainCars.push_back(this->createObjectTypeTrainCar(tmpComponents[4], 0));
			
		trains.push_back(this->createObjectTypeTrain(*(this->createObjectTypeTrainCarChain(tmpTrainCars)),*(this->createObjectTypeLocomotive(i+1,10,tmpComponents[0])),tmpRoute));
	}
}

void ModelMap::createStations(std::vector<std::vector<int>>&stationsInfo)
{
	for (int i = 0; i < stationsInfo.size(); ++i)
	{
		for (int j = 0; j < stationsInfo[i].size(); ++j)
		{
			if (stationsInfo[i][j] == -1)
			{
				stations.push_back(this->createObjectTypeGoodsRailwayStation(stationsInfo[i][j+1],stationsInfo[i][j+2]));
			}
			if (stationsInfo[i][j] == -2)
			{
				stations.push_back(this->createObjectTypePassengerRailwayStation(stationsInfo[i][j + 1], stationsInfo[i][j + 2]));
			}
			if (stationsInfo[i][j] == -3)
			{
				stations.push_back(this->createObjectTypeMultiRailwayStation(stationsInfo[i][j + 1], stationsInfo[i][j + 2],stationsInfo[i][j+3]));
			}
		}
	}
}

void ModelMap::buildModel(std::string path)
{	
	std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> inputValues = parseInfo(path);
	this->setGraph(std::get<0>(inputValues));
	this->createTrains(std::get<2>(inputValues));
	this->createStations(std::get<1>(inputValues));
}

std::vector<Train*> ModelMap::getTrains()
{
	return trains;
}

std::vector<RailwayStation*> ModelMap::getStations()
{
	return stations;
}

std::vector<std::vector<int>> ModelMap::getGraph()
{
	return graph;
}

RailwayStation* ModelMap::getObjRailwayStation(int RSNumber)
{
	for (int i = 0; i < stations.size(); ++i)
	{
		if (stations[i]->getRailwayStationNumber() == RSNumber)
		{
			return stations[i];
		}
	}
}