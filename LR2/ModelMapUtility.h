#pragma once
#include "ModelMap.h"

using std::cout;

class ModelMapUtility
{
private:
	ModelMap currentMap;
	std::vector<int> positionTracking;
	std::vector<std::vector<int>> routes;
	std::vector<std::vector<int>> routePointToPointDistance;
public:
	ModelMapUtility(ModelMap &obj);
	ModelMap getModel();
	void findRouteDistance();
	void findRoutePointToPointDistance(std::vector<int> &tmpRoute);
	void findStartPoints();
	void createNewRoutes();
	void fieldModelling();
	void showTrainsInfo();
	void showObjTrainInfo(int TrainIndex);
	void showObjTrainChainInfo(int TrainIndex);
	void showTrainChainsInfo();
	void showRailwayStationInfo(int RSNumber);
	void showGraph();
};

