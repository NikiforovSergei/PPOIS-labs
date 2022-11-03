#include "Routes.h";
#include "Stations.h"
#include "Trains.h"

void Route::ShowRouteInfo()
{
	std::cout << startStation->GetName() << " - " << terminus->GetName() << std::endl;
}

Station* Route::GetStartStation()
{
	return startStation;
}

Station* Route::GetTerminus()
{
	return terminus;
}

float Route::GetRouteDistance()
{
	float routeDistance = 0;
	for (auto el : distancesBetweenStations)
	{
		routeDistance += el;
	}
	return routeDistance;
}

float Route::GetDistanceToTheNextStation(int i)
{
	return distancesBetweenStations[i];
}

std::vector<Station*> Route::GetStationsList()
{
	return stationsInRoute;
}

void Route::SetStartStation(Station* startStation)
{
	this->startStation = startStation;
}

void Route::SetTerminus(Station* terminus)
{
	this->terminus = terminus;
}

void Route::SetStationsInTheRoute(std::vector<Station*> stationsInRoute)
{
	this->stationsInRoute = stationsInRoute;
}

void Route::SetDistancesBetweenSatations(std::vector<float> distancesBetweenStations)
{
	this->distancesBetweenStations = distancesBetweenStations;
}

void Route::ShowDetailedRouteInfo()
{
	for (auto st : stationsInRoute)
	{
		if (st == startStation)
		{
			std::cout << st->GetName() << " <--- Start Station " << std::endl;
		}
		else if (st == terminus)
		{
			std::cout << st->GetName() << " <--- Terminus " << std::endl << std::endl << std::endl;
		}
		else
		{
			std::cout << st->GetName() << std::endl;
		}
	}
	std::cout << "\n\n\nDistance: " << GetRouteDistance() << std::endl;
}