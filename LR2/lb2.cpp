#include <iostream>
#include <fstream>
#include <vector>
#include "RailwayField.h"
#include "Stations.h"
#include "Trains.h"
#include "Routes.h"
#include "TimeManager.h"
#include "Preloading.h"
#include "interface.h"

int main(int argc, char* argv[])
{
	/*char ch;
	InProgramTime timer;
	timer.ShowTime();
	float tick = 12.75f;
	timer = timer + tick;
	timer.ShowTime();

	Train obj;
	RailwayField rf;
	TrainInTimeManipulator manipulator;

	rf.SetStationsInfo();
	rf.CreatingRoute();
	rf.ShowRoutes();

	obj.SetNum();
	obj.PutLocomotive();
	obj.PutCarrieges();
	rf.SetTrainRoute(obj);
	obj.ShowDetailedTrainInfo();

	while (true)
	{
		
		system("cls");

		obj.ShowDetailedTrainInfo();
		std::cout << "Press q button to skip 15 minutes" << std::endl; std::cin >> ch;
		if (ch == 'q' || ch == 'Q')
			manipulator.ChangingConditionsOfTheTrain(&obj);
		else
			break;
	}

	PassengerStation st1;

	st1.Loading(&obj);

	obj.ShowDetailedTrainInfo();*/

	std::vector<Train*> trainPark;
	RailwayField rf;
	ProgramPreloading preloader;
	InProgramTime programTime;
	TrainInTimeManipulator manipulator;
	preloader.MapPreloading(rf, argv[1]);
	preloader.StationsLoading(rf, argv[2]);
	preloader.RoutePreloading(rf, argv[3]);
	preloader.TrainsPreloading(rf, trainPark, argv[4]);

	while (true)
	{
		MainMenu(trainPark, rf, programTime, manipulator);
	}
	
	/*manipulator.ChangingConditionsOfTheTrain(&trainPark[0]);*/
	return 0;
}