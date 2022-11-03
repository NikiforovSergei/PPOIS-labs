#pragma once
#include <vector>
#include "Trains.h"
#include "Stations.h"
#include "string"
#include <conio.h>

class Station;
class Route;

class RailwayField
{
private:
	int numberOfStations;
	/*std::vector<std::vector<float>> adj_matrix = { {0, 178, 0, 0, 0, 205, 0, 109},
		{178, 0, 0, 0, 0, 0, 0, 80},
		{0, 200, 0, 230, 0, 0, 0, 50},
		{0, 0, 230, 0, 0, 0, 214, 0},
		{0, 0, 0, 155, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 98, 0},
		{0, 0, 0, 0, 175, 98, 0, 0},
		{109, 0, 50, 0, 0, 0, 66, 0} };*/
	//std::vector<std::vector<float>> adjMatrix = { {0,240,0,0}, {0,0,100,0}, {120,0,0,150}, {0,0,0,0} };
	std::vector<std::vector<float>> adjMatrix;
	std::vector<Station*> stationsVector;
	//std::vector<std::vector<Station*>> routes;
	std::vector<Route*> routes;
	float routeDistance;
	
public:
	RailwayField() {};
	//void setStationTask(int);
	//void SetStationsInfo();
	//void CreatingRoute();
	//int SelectingStartStation(std::vector<Station*>&);
	//void SelectingNextStations(int start, std::vector<Station*>& route, std::vector<float>&);
	void ShowRoutes();
	Route* SelectTrainRoute(int n);
	void SetTrainRoute(Train& tr);
	void SetAdjMatrix(std::vector<std::vector<float>>);
	void SetNumberOfStations(int);
	Station* SetStationType(std::string);
	void SetStationsVector(std::vector<Station*>);
	std::vector<Station*> GetStationsVector();
	void SetRoutes(std::vector<Route*>);
	std::vector<std::vector<float>> GetAdjMatrix();
	std::vector<Route*> GetRoutes();
};

class RideController
{
};

