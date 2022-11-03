#pragma once

#include <iostream>
#include <conio.h>
#include "TimeManager.h"

void ShowTrainsInfo(std::vector<Train*>&, RailwayField);
void ShowDetailedInfo(std::vector<Train*>&, RailwayField, int);
void CreateNewTrain(std::vector<Train*>&, RailwayField);
void ShowRoutesInfo(std::vector<Train*>&, RailwayField);
void ShowDetailedRouteInfo(std::vector<Train*>&, RailwayField, int, std::vector<Route*>);
void ShowStationsInfo(std::vector<Train*>&, RailwayField);

void MainMenu(std::vector<Train*>& trainPark, RailwayField& rf, InProgramTime& programTime, TrainInTimeManipulator& manipulator)
{
	char choise;
	system("cls");
	std::cout << "1. Show trains info\n2. Create new train\n3. Show routes info\n4. Show stations info\n5. Set route for free trains\n0. Exit\n\n\n\n\n";
	std::cout << "Local time : "; programTime.ShowTime();
	std::cout << "\nPress q to skip 15 minutes...\n";
	try
	{
		choise = _getch();
		switch (choise)
		{
		case '1':
			ShowTrainsInfo(trainPark, rf);
			break;
		case '2':
			CreateNewTrain(trainPark, rf);
			break;
		case '3':
			ShowRoutesInfo(trainPark, rf);
			break;
		case '4':
			ShowStationsInfo(trainPark, rf);
			break;
		case '5':
			for (auto train : trainPark)
			{
				if (train->GetStatus() == Free)
					rf.SetTrainRoute(*train);
			}
			break;
		case '0':
			exit(0);
			break;
		case 'q':
			for (auto train : trainPark)
			{
				manipulator.ChangingConditionsOfTheTrain(train);
			}
			programTime + 0.25;
			break;
		default:
			throw std::exception("Incorrect choice. There is no option with this number.");
			break;
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		_getch();
		return;
	}
}

void ShowTrainsInfo(std::vector<Train*>& trainPark, RailwayField rf)
{
	system("cls");
	int num = 1;
	int ch;
	for (auto train : trainPark)
	{
		std::cout << num << ". "; train->ShowBriefInfo();
		num++;
	}
	std::cout << "\nSelect train to check detailed information..." << std::endl;
	std::cout << "\n\n\n\nPress 0 to return to main menu..." << std::endl;;
	try
	{
		std::cin >> ch;
		if (ch == 0)
			return;
		if (ch <= 0 || ch >= num)
			throw std::exception("Incorrect input");
		ShowDetailedInfo(trainPark, rf, ch - 1);
	}
	catch (std::exception& e)
	{
		std::cout << "\n\n\n" << e.what() << std::endl;
		_getch();
		return;
	}
	
}

void ShowDetailedInfo(std::vector<Train*>& trainPark, RailwayField rf, int ch)
{
	system("cls");
	trainPark[ch]->ShowDetailedTrainInfo();
	trainPark[ch]->LocoAndCarryInfo();
	std::cout << "\n\n\n\nPress any button to return to main menu..." << std::endl;;
	_getch();
}

void CreateNewTrain(std::vector<Train*>& trainPark, RailwayField rf)
{
	system("cls");
	int number, carryCount;
	Train* train = new Train;
	std::cout << "Enter number of the train: "; std::cin >> number;
	train->SetNumberOfTheTrain(number);
	std::cout << "Enter count of carrieges: "; std::cin >> carryCount;
	train->SetCarriegesCount(carryCount);
	train->CreateLocomotive();
	train->CreateCarrieges();
	rf.SetTrainRoute(*train);
	trainPark.push_back(train);
}

void ShowRoutesInfo(std::vector<Train*>& trainPark, RailwayField rf)
{
	system("cls");
	int num = 1;
	int ch;
	std::vector<Route*> routes = rf.GetRoutes();
	for (auto route : routes)
	{
		std::cout << num << ". "; route->ShowRouteInfo();
		num++;
	}
	std::cout << "\nSelect route to check detailed information..." << std::endl;
	std::cout << "\n\n\n\nPress 0 to return to main menu..." << std::endl;;
	std::cin >> ch;
	/*try
	{*/

		if (ch == 0)
			return;
		ShowDetailedRouteInfo(trainPark, rf, ch - 1, routes);
	/*}
	catch (std::exception& e)
	{
		std::cout << "\n\n\n" << e.what() << std::endl;
		_getch();
		return;
	}*/

}

void ShowDetailedRouteInfo(std::vector<Train*>& trainPark, RailwayField rf, int ch, std::vector<Route*> routes)
{
	system("cls");
	routes[ch]->ShowDetailedRouteInfo();
	std::cout << "\n\n\n\nPress any button to return to main menu..." << std::endl;;
	_getch();
}

void ShowStationsInfo(std::vector<Train*>& trainPark, RailwayField rf)
{
	system("cls");
	char ch;
	std::vector<Station*> stations = rf.GetStationsVector();
	for(auto st : stations)
	{
		st->ShowStationInfo();
	}
	std::cout << "\n\n\n\nPress any button to return to main menu..." << std::endl;;
	_getch();
}