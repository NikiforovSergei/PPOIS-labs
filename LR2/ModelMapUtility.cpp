#include "ModelMapUtility.h"

ModelMapUtility::ModelMapUtility(ModelMap& obj) : currentMap(obj)
{
	this->findStartPoints();
	this->findRouteDistance();
};

ModelMap ModelMapUtility::getModel()
{
	return currentMap;
}

void ModelMapUtility::findRouteDistance()
{
	std::vector<std::vector<int>> tmpRoutes;
	for (int i = 0; i < currentMap.getTrains().size(); ++i)
		tmpRoutes.push_back(currentMap.getTrains()[i]->getRoute());
	for (int i = 0; i < tmpRoutes.size(); ++i)
		this->findRoutePointToPointDistance(tmpRoutes[i]);
	for (int i = 0; i < tmpRoutes.size(); ++i)
		tmpRoutes[i].erase(tmpRoutes[i].begin());
	routes = tmpRoutes;
}

void ModelMapUtility::findRoutePointToPointDistance(std::vector<int> &tmpRoute)
{
	std::vector<int> tempRoute;
	for (int i1 = 0; i1 < tmpRoute.size() - 1; ++i1)
		for (int h = 0; h < currentMap.getGraph().size(); ++h)
			for (int h1 = 0; h1 < currentMap.getGraph()[h].size() - 2; ++h1)
				if (tmpRoute[i1] == currentMap.getGraph()[h][h1])
					if (tmpRoute[i1 + 1] == currentMap.getGraph()[h][h1 + 1])
						tempRoute.push_back(currentMap.getGraph()[h][2]);
	routePointToPointDistance.push_back(tempRoute);

}

void ModelMapUtility::findStartPoints()
{
	positionTracking.resize(currentMap.getTrains().size());
	for (int i = 0; i < currentMap.getTrains().size(); ++i)
	{
		positionTracking[i] = currentMap.getTrains()[i]->getRoute()[0];
		currentMap.getTrains()[i]->setCurrentPosition(positionTracking[i]);
	}
}

void ModelMapUtility::createNewRoutes()
{
	for (int i = 0; i < currentMap.getTrains().size(); ++i)
	{
		int length = 0;
		int temp=0;
		std::vector<int> route;
		this->showGraph();
		this->showObjTrainInfo(i);
		cout << "Input route length: ";
		std::cin >> length;
		for (int j = 0; j < length; ++j)
		{
			std::cin >> temp;
			route.push_back(temp);
		}
		currentMap.getTrains()[i]->setRoute(route);
		this->showObjTrainInfo(i);
		route.clear();
	}
	this->findStartPoints();
	this->findRouteDistance();
	return;
}

void ModelMapUtility::showGraph()
{
	for (int i = 0; i < this->getModel().getGraph().size(); ++i)
	{
		for (int j = 0; j < this->getModel().getGraph()[i].size(); ++j)
			cout << this->getModel().getGraph()[i][j] << "  ";
		cout << '\n';
	}
}

void ModelMapUtility::showTrainsInfo()
{
	for (int i = 0; i < currentMap.getTrains().size(); ++i)
	{
		this->showObjTrainInfo(i);
	}
}

void ModelMapUtility::showObjTrainInfo(int TrainIndex)
{
	cout << "\t\t\tTrain #" << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getLocomotiveNumber() << "\n";
	cout << "{\n";
	if (currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarChainType() == 1)
		cout << "Train type: goods\n";
	else if (currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarChainType() == 2)
		cout << "Train type: passenger\n";
	else
		cout << "Train type: multi\n";
	cout << "Locomotive:\n" <<"\t{\n" 
		<< "\t\tTractiveForce: " << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getTractiveForce() << "\n";
	cout << "\t\tLifeTime: " << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getLifeTime() << "\n";
	cout << "\t}\n";
	cout << "CurrentPosition: " << currentMap.getTrains()[TrainIndex]->getCurrentPosition() << "\n";
	cout << "CurrentWeight: " << currentMap.getTrains()[TrainIndex]->getCurrentWeight() << "\n";
	cout << "CurrentSpeed: " << currentMap.getTrains()[TrainIndex]->getTrainSpeed() << "\n";
	cout << "Route: ";
	for (int j = 0; j < currentMap.getTrains()[TrainIndex]->getRoute().size(); ++j)
		if (j == currentMap.getTrains()[TrainIndex]->getRoute().size() - 1)
			cout << currentMap.getTrains()[TrainIndex]->getRoute()[j];
		else
			cout << currentMap.getTrains()[TrainIndex]->getRoute()[j] << " -> ";
	cout << "\n}";
	cout << "\n";
}

void ModelMapUtility::showTrainChainsInfo()
{
	cout <<"\n" << "TrainCarChainStatus:\n";
	
	for (int i = 0; i < currentMap.getTrains().size(); ++i)
	{
		this->showObjTrainChainInfo(i);
	}
}

void ModelMapUtility::showObjTrainChainInfo(int TrainIndex)
{
	if (currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarChainType() == 3) {

			cout << "\t\t\tTrain #" << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getLocomotiveNumber() << "\n";
			cout << "Passenger traincars: " << "\n";
			for (int j = 0; j < currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1).size(); ++j)
			{
				cout << j + 1 << ". " << "Current passenger occupancy: " << currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1)[j]->getCurrentOccupancy() << " Limit: "
					<< currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1)[j]->getOccupancyLimit() << "\n";
			}
			cout << "Goods traincars:\n";
			for (int j = 0; j < currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0).size(); ++j)
			{
				cout << j + 1 << ". " << "Current goods occupancy: " << currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0)[j]->getCurrentOccupancy() << " Limit: "
					<< currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0)[j]->getOccupancyLimit() << "\n";
			}
		}
		else if (currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarChainType() == 2)
		{
			cout << "\t\t\tTrain #" << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getLocomotiveNumber() << "\n";
			cout << "Passenger traincars: " << "\n";
			for (int j = 0; j < currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1).size(); ++j)
			{
				cout << j + 1 << ". " << "Current passenger occupancy: " << currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1)[j]->getCurrentOccupancy() << " Limit: "
					<< currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(1)[j]->getOccupancyLimit() << "\n";
			}

		}
		else
		{
			cout << "\t\t\tTrain #" << currentMap.getTrains()[TrainIndex]->getCurrentLocomotive().getLocomotiveNumber() << "\n";
			cout << "Goods traincars:\n";
			for (int j = 0; j < currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0).size(); ++j)
			{
				cout << j + 1 << ". " << "Current goods occupancy: " << currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0)[j]->getCurrentOccupancy() << " Limit: "
					<< currentMap.getTrains()[TrainIndex]->getCurrentChain().getTrainCarList(0)[j]->getOccupancyLimit() << "\n";
			}
		}
}

void ModelMapUtility::showRailwayStationInfo(int RSNumber)
{
	for (int i = 0; i < currentMap.getStations().size(); ++i)
	{
		if (currentMap.getStations()[i]->getRailwayStationNumber() == RSNumber)
		{
			cout << "\t\tRailwayStation #" << RSNumber << "\n";
			switch (currentMap.getStations()[i]->getRailwayStationType())
			{
			case 1:
			{
				cout << "RSType: goods" << "\n";
				cout << "Transpotable resource: " << currentMap.getStations()[i]->getTranspotableResource(0) << "\n";
				cout << "Offloaded resource: " << currentMap.getStations()[i]->getOffloadedResource(0) << "\n";
				break;
			}
			case 2:
			{
				cout << "RSType: passenger" << "\n";
				cout << "Passenger resource: " << currentMap.getStations()[i]->getTranspotableResource(0) << "\n";
				cout << "Offloaded passenger resource: " << currentMap.getStations()[i]->getOffloadedResource(0) << "\n";
				break;
			}
			case 3: 
			{
				cout << "RSType: multi" << "\n";
				cout << "Transpotable resource: " << currentMap.getStations()[i]->getTranspotableResource(0) << "  Passenger resource: "
					<< currentMap.getStations()[i]->getTranspotableResource(1) << "\n";
				cout << "Offloaded goods resource: " << currentMap.getStations()[i]->getOffloadedResource(0) << "  Offloaded passenger resource: " 
					<< currentMap.getStations()[i]->getOffloadedResource(1) << "\n";
				break;
			}
			default:
				break;
			}
			break;
		}
	}
}

void ModelMapUtility::fieldModelling()
{
	int tick = 1;
	this->showTrainsInfo();
	while (true)
	{
		if (routes.empty())
		{
			for (int i = 0; i < currentMap.getTrains().size(); ++i)
			{
				currentMap.getTrains()[i]->reduceLifeTime(1);
				if (currentMap.getTrains()[i]->getCurrentLocomotive().getLifeTime() == 0)
				{
					cout << "Train #" << currentMap.getTrains()[i]->getCurrentLocomotive().getLocomotiveNumber() <<
						" is decommissioned\n\n";
					currentMap.deleteObjTrain(i);
				}
			}
			this->showTrainsInfo();
			cout << "All routes is completed\nDo you want to set new routes?\n1.Yes.\n2.No.\n";
			int choice = false;
			std::cin >> choice;
			if (choice==1)
			{
				routes.clear();
				positionTracking.clear();
				routePointToPointDistance.clear();
				this->createNewRoutes();
			}
			else
				return;

		}
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tCurrent tick: " << tick << "\n\n";
		for (int i = 0; i < routePointToPointDistance.size(); ++i)
		{
			routePointToPointDistance[i][0] -= currentMap.getTrains()[i]->getTrainSpeed();
			if (routePointToPointDistance[i][0] < 0)
			{
				routePointToPointDistance[i].erase(routePointToPointDistance[i].begin());
				positionTracking[i] = routes[i][0];
				routes[i].erase(routes[i].begin());
				currentMap.getTrains()[i]->setRoute(routes[i]);
				currentMap.getTrains()[i]->setCurrentPosition(positionTracking[i]);
				cout << "\t\t\tTrain #" << currentMap.getTrains()[i]->getCurrentLocomotive().getLocomotiveNumber()
					<< " is arrived";
				this->showRailwayStationInfo(positionTracking[i]);
				cout << "\nChoose action:\n"
					<< "1.LoadTrain\n2.OffloadTrain\n3.Transit\n4.TemporaryStop\n";
				int choice = 0;
				std::cin >> choice;
				switch (choice)
				{
				case 1:
				{
					if (currentMap.getObjRailwayStation(positionTracking[i])->getRailwayStationType() == 1)
					{
						while (true)
						{
							cout << "Input necessary cargo: ";
							std::cin >> choice;
							if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, 0) == 3)
								break;
							else if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, 0) == 2)
								cout << "Station doesn't have so much resource\n";
							else
								cout << "TrainCarChain limit is too low for this weight\n";
						}
					}
					else if (currentMap.getObjRailwayStation(positionTracking[i])->getRailwayStationType() == 2)
					{
						while (true)
						{
							cout << "Input necessary cargo: ";
							std::cin >> choice;
							if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, 1) == 3)
								break;
							else if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, 1) == 2)
								cout << "Station doesn't have so much resource\n";
							else
								cout << "TrainCarChain limit is too low for this passenger value\n";
						}
					}
					else
					{
						bool flag = false;
						cout << "Choose loadType(0-goods,1-passenger): ";
						std::cin >> flag;
						while (true)
						{
							if (flag)
								cout << "Input necessary passenger value: ";
							else
								cout << "Input necessary cargo: ";
							std::cin >> choice;
							if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, flag) == 3)
								break;
							else if (currentMap.getObjRailwayStation(positionTracking[i])->loadTrain(*currentMap.getTrains()[i],
								choice, flag) == 2)
								cout << "Station doesn't have so much resource\n";
							else
								cout << "TrainCarChain limit is too low for this weight\n";
						}
					}
					break;
				}
				case 2:
				{
				if (currentMap.getObjRailwayStation(positionTracking[i])->getRailwayStationType() == 1)
				{
					while (true)
					{
						cout << "Input necessary goods offload percent value: ";
						std::cin >> choice;
						if (choice < 0 || choice >100)
							cout << "Incorrect offload percentage\n";
						else
						{
							currentMap.getObjRailwayStation(positionTracking[i])->offloadTrain(*currentMap.getTrains()[i],
								choice, 0);
							break;
						}
					}
				}
				else if (currentMap.getObjRailwayStation(positionTracking[i])->getRailwayStationType() == 2)
				{
					while (true)
					{
						cout << "Input necessary passenger offload percent value: ";
						std::cin >> choice;
						if (choice < 0 || choice > 100)
							cout << "Incorrect offload percentage\n";
						else
						{
							currentMap.getObjRailwayStation(positionTracking[i])->offloadTrain(*currentMap.getTrains()[i],
								choice, 0);
							break;
						}
					}
				}
				else
				{
					bool flag = false;
					cout << "Choose offLoadType(0-goods,1-passenger): ";
					std::cin >> flag;
					while (true)
					{
						if (flag)
							cout << "Input necessary goods offload percent value: ";
						else
							cout << "Input necessary passenger offload percent value: ";
						std::cin >> choice;
						if (choice < 0 || choice >100)
							cout << "Incorrect offload percentage\n";
						else
						{
							currentMap.getObjRailwayStation(positionTracking[i])->offloadTrain(*currentMap.getTrains()[i],
								choice, flag);
							break;
						}
					}
				}
					break;
				}
				case 3:
					break;
				case 4:
				{
					routes[i].insert(routes[i].begin(),positionTracking[i]);
					routePointToPointDistance[i].insert(routePointToPointDistance[i].begin(), currentMap.getTrains()[i]->getTrainSpeed());
					continue;
					break;
				}
				default:
					break;
				}
				cout << "\n";
				this->showObjTrainInfo(i);
				this->showObjTrainChainInfo(i);
				cout << "\n";
				this->showRailwayStationInfo(positionTracking[i]);
				cout << "\n";
				if (routes[i].empty())
					routes.erase(routes.begin() + i);
				if (routePointToPointDistance[i].empty())
					routePointToPointDistance.erase(routePointToPointDistance.begin() + i);		
			}
		}
		tick++;
		}
}