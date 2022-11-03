#include "RailwayField.h"
#include "Trains.h"


//void RailwayField::setStationTask(int i)
//{
//	int task;
//	std::cout << "Enter station task: \n" <<
//		"1. Loading\n2. Unloadinng\n3. Transit\n4.Temporary stopping\n";
//	std::cin >> task;
//	switch (task)
//	{
//	case 1:
//		stations[i]->SetTask(Loading);
//		break;
//	case 2:
//		stations[i]->SetTask(Unloading);
//		break;
//	case 3:
//		stations[i]->SetTask(Transit);
//		break;
//	case 4:
//		stations[i]->SetTask(TemporaryStoping);
//		break;
//	default:
//		break;
//	}
//}
//
//void RailwayField::SetStationsInfo()
//{
//	system("cls");
//	std::string name;
//	char ch;
//	for (int i = 0; i < numberOfStations; i++)
//	{
//		system("cls");
//		std::cout << "Select type of stations: \n1. Passenger station.\n2. Freight station.\n3. Mixed station.\n";
//		std::cin >> ch;
//
//		switch (ch)
//		{
//		case '1':
//			stations[i] = new PassengerStation();
//			break;
//		case '2':
//			stations[i] = new FreightStation();
//			break;
//		case '3':
//			stations[i] = new MixedStation();
//			break;
//		default:
//			std::cout << "Wrong value\n"; i--;
//			continue;
//		}
//		system("cls");
//		std::cout << "Enter station name: \n";
//		std::cin >> name;
//		stations[i]->SetName(name);
//		system("cls");
//		setStationTask(i);
//	}
//}

Station* RailwayField::SetStationType(std::string type)
{
	Station* station;
	if (type == "Passenger")
	{
		station = new PassengerStation();
	}
	else if (type == "Freight")
	{
		station = new FreightStation();
	}
	else if (type == "Mixed")
	{
		station = new MixedStation();
	}
	else
	{
		std::cout << " Incorrect type has chosen. Default type: Passenger carriege." << std::endl;
		station = new PassengerStation();
	}
	return station;
}


//void RailwayField::CreatingRoute()
//{
//	while (true)
//	{
//		char choice;
//		std::vector<Station*> routeStations;
//		std::vector<float> distancesBetweenStations;
//		SelectingNextStations(SelectingStartStation(routeStations), routeStations, distancesBetweenStations);
//		Route* route = new Route(routeStations, routeDistance, distancesBetweenStations);
//		routes.push_back(route);
//		std::cout << "Do you want to create one more route?(y/n)" << std::endl; std::cin >> choice;
//		if (choice != 'y' && choice != 'Y')
//			break;
//	}
//}
//
//int RailwayField::SelectingStartStation(std::vector<Station*>&routeStations)
//{
//	int startStationNumber;
//	routeDistance = 0;
//	for (int i = 0; i < numberOfStations; i++)
//	{
//		std::cout << i + 1 << ". "; stationsVector[i]->ShowStationInfo();
//	}
//	std::cout << "Select the start station\n"; std::cin >> startStationNumber;
//	//routes[numberofroutes][0] = stations[startstationnumber-1];
//	routeStations.push_back(stationsVector[startStationNumber - 1]);
//	return startStationNumber - 1;
//}
//
//void RailwayField::SelectingNextStations(int start, std::vector<Station*>& routeStations, std::vector<float>& distancesBetweenStations)
//{
//	system("cls");
//	bool hasNeighbourStations = false;
//	int choice, adjList[20], counter = 0, stationNumber = 1;
//	for (int i = 0; i < numberOfStations; i++)
//	{
//		if (adjMatrix[start][i] != 0)
//		{
//			hasNeighbourStations = true;
//			std::cout << stationNumber++ << ". "; stationsVector[i]->ShowStationInfo();
//			adjList[counter++] = i;
//		}
//	}
//	if (hasNeighbourStations)
//	{
//		std::cout << "Select the next station or select '0' to make this station terminus\n";
//		std::cin >> choice;
//		if (choice == 0)
//			return;
//		//routes[numberOfRoutes][numberInRoute] = stations[choice - 1];
//		choice--;
//		routeDistance += adjMatrix[start][adjList[choice]];
//		distancesBetweenStations.push_back(adjMatrix[start][adjList[choice]]);
//		routeStations.push_back(stationsVector[adjList[choice]]);
//		SelectingNextStations(adjList[choice],  routeStations, distancesBetweenStations);
//	}
//	else
//	{
//		std::cout << "There are no neighbour stations" << std::endl;
//	}
//}

//std::vector<std::vector<float>> RailwayField::GetAdjMatrix()
//{
//	return adjMatrix;
//}

void RailwayField::ShowRoutes()
{
	int routeNumber = 1;
	for (auto st : routes)
	{
		std::cout << routeNumber << ". "; st->ShowRouteInfo();
		routeNumber++;
	}
}
// settrainroute -> selecttrainroute
Route* RailwayField::SelectTrainRoute(int n)
{
	return routes[n];
}

void RailwayField::SetTrainRoute(Train& train)
{
	if (train.GetStatus() == Free)
	{
		
			system("cls");
			int choice;
			std::cout << "Train " << train.GetNumberOfTheTrain() << " is free." << std::endl;
			std::cout << "Choice the train route:" << std::endl;
			ShowRoutes();
			std::cin >> choice;
			try 
			{
				if (choice < numberOfStations && choice > 0)
				{
					Route* trainRoute = SelectTrainRoute(choice - 1);
					train.SetRoute(trainRoute);
					train.SetLocation(trainRoute->GetStartStation());
					train.SetStatus(InTheWay);
					train.SetTimeToTheNextStation(0);
					train.GetLocation()->Loading(&train);
				}
				else
					throw std::exception("Select existent route.");
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
				_getch();
				return;
			}
		
	}
}

void RailwayField::SetAdjMatrix(std::vector<std::vector<float>> adjMatrix)
{
	this->adjMatrix = adjMatrix;
}

void RailwayField::SetNumberOfStations(int numberOfStations)
{
	this->numberOfStations = numberOfStations;
}

void RailwayField::SetStationsVector(std::vector<Station*> stationsVector)
{
	this->stationsVector = stationsVector;
}

std::vector<Station*> RailwayField::GetStationsVector()
{
	return stationsVector;
}

void RailwayField::SetRoutes(std::vector<Route*> routes)
{
	this->routes = routes;
}

std::vector<std::vector<float>> RailwayField::GetAdjMatrix()
{
	return adjMatrix;
}

std::vector<Route*> RailwayField::GetRoutes()
{
	return routes;
}