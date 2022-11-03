#pragma once
#include "Stations.h"
class Station;

class Route
{
private:
	std::vector<Station*> stationsInRoute;
	std::vector<float> distancesBetweenStations;
	Station* startStation;
	Station* terminus;
public:
	//Route(std::vector<Station*> stationsInroute, float routeDistance, std::vector<float> distancesBetweenStations)
	//{
	//	this->stationsInRoute = stationsInroute;
	//	startStation = stationsInRoute[0];
	//	terminus = stationsInRoute[stationsInRoute.size() - 1];
	//	this->routeDistance = routeDistance;
	//	this->distancesBetweenStations = distancesBetweenStations;
	//}


	void ShowRouteInfo();
	Station* GetStartStation();
	float GetRouteDistance();
	float GetDistanceToTheNextStation(int i);
	std::vector<Station*> GetStationsList();
	Station* GetTerminus();
	void SetStartStation(Station*);
	void SetTerminus(Station*);
	void SetStationsInTheRoute(std::vector<Station*>);
	void SetDistancesBetweenSatations(std::vector<float>);
	void ShowDetailedRouteInfo();
};