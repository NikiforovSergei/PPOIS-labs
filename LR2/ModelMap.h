#pragma once
#include <vector>
#include <tuple>
#include "InputUtility.h"
#include "Train.h"
#include "RailwayStation.h"
class ModelMap
{
private:
	std::vector<Train*> trains;
	std::vector<RailwayStation*> stations;
	std::vector<std::vector<int>> graph;
public:
	ModelMap(std::string path);
	void buildModel(std::string path);
	void createTrains(std::vector<std::vector<int>> &trainsInfo);
	void createStations(std::vector<std::vector<int>> &stationsInfo);
	void setGraph(std::vector<std::vector<int>> &parsedGraph);
	RailwayStation* getObjRailwayStation(int RSNumber);
	Train* createObjectTypeTrain(TrainCarChain &chain, Locomotive &currentLoc,std::vector<int> &trainRoute);
	Locomotive* createObjectTypeLocomotive(int number,int lifetime, int tractiveForce);
	TrainCar* createObjectTypeTrainCar(int limit,bool type);
	TrainCarChain* createObjectTypeTrainCarChain(std::vector<TrainCar*> &chain);
	GoodsRailwayStation* createObjectTypeGoodsRailwayStation(int number, int transpotableResource);
	PassengerRailwayStation* createObjectTypePassengerRailwayStation(int number, int transpotableResource);
	MultiRailwayStation* createObjectTypeMultiRailwayStation(int number,int transpotableResource1, int transpotableResource2);
	std::vector<Train*> getTrains();
	std::vector<RailwayStation*> getStations();
	std::vector<std::vector<int>> getGraph();
	void deleteObjTrain(int index);

};

