#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Stations.h"
#include "RailwayField.h"

class ProgramPreloading
{
public:
	void MapPreloading(RailwayField&, char* str);
	void StationsLoading(RailwayField&, char* str);
	void RoutePreloading(RailwayField&, char* str);
	bool IsRouteExist(std::vector<std::vector<float>>, std::vector<int>);
	void FindDistancesBetweenStations(std::vector<std::vector<float>>, std::vector<int>, std::vector<float>&);
	void TrainsPreloading(RailwayField& , std::vector<Train*>&, char* str);
};