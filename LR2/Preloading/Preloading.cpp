
#include "Preloading.h"


void ProgramPreloading::MapPreloading(RailwayField& rf, char* str)
{
	std::ifstream file;
	try
	{
		int numberOfStations;
		std::vector<std::vector<float>> adjMatrix;
		std::vector<float> adjRow;
		file.open(str);
		file >> numberOfStations;;
		adjRow.resize(numberOfStations);
		for (int i = 0; i < numberOfStations; i++)
		{
			for (int j = 0; j < numberOfStations; j++)
			{
				file >> adjRow[j];
			}
			adjMatrix.push_back(adjRow);
		}
		rf.SetAdjMatrix(adjMatrix);
		rf.SetNumberOfStations(numberOfStations);
		file.close();
	}
	catch (std::exception)
	{
		std::cout << "There is a problem with railway map.txt file" << std::endl;
		exit(3);
	}
}

void ProgramPreloading::StationsLoading(RailwayField& rf, char* str)
{
	try
	{
		std::string stationName, stationType, stationTask;
		Station* station;
		std::vector<Station*> stationsVector;
		std::ifstream file;
		file.open(str);
		while (true)
		{
			file >> stationType >> stationName >> stationTask;
			station = rf.SetStationType(stationType);
			station->SetName(stationName);
			station->SetTaskFromFile(stationTask);
			stationsVector.push_back(station);
			if (file.eof())
				break;
		}
		rf.SetStationsVector(stationsVector);
		file.close();
	}
	catch (std::exception)
	{
		std::cout << "There is a problem with stations.txt file" << std::endl;
		exit(3);
	}
}

void ProgramPreloading::RoutePreloading(RailwayField& rf, char* str)
{

	std::ifstream file;
	std::vector<std::vector<float>> adjMatrix = rf.GetAdjMatrix();
	std::vector<float> distancesBetweenStations;
	std::vector<int> numbersOfStationsInRoute;
	std::vector<Route*> routes;
	std::vector<Station*> stationsInRoute, stationsVector = rf.GetStationsVector();
	int n;
	file.open(str);
	while (file >> n)
	{
		try {
			if (n > stationsVector.size() - 1)
			{
				throw std::exception("Exception was caused! File: routes.txt. The number of station is greater than awerall number of the stations");
			}
			stationsInRoute.push_back(stationsVector[n]);
			numbersOfStationsInRoute.push_back(n);
			if (file.peek() == '\n' || file.eof())
			{
				if (IsRouteExist(adjMatrix, numbersOfStationsInRoute))
				{
					FindDistancesBetweenStations(adjMatrix, numbersOfStationsInRoute, distancesBetweenStations);
					Route* route = new Route();
					route->SetDistancesBetweenSatations(distancesBetweenStations);
					route->SetStationsInTheRoute(stationsInRoute);
					route->SetStartStation(stationsInRoute[0]);
					route->SetTerminus(stationsInRoute[stationsInRoute.size() - 1]);
					routes.push_back(route);
				}
				stationsInRoute.clear();
				numbersOfStationsInRoute.clear();
				distancesBetweenStations.clear();
			}
		}
		catch (std::exception e)
		{
			std::cout << e.what();
			stationsInRoute.clear();
			numbersOfStationsInRoute.clear();
		}
	}
	rf.SetRoutes(routes);
	file.close();
}

bool ProgramPreloading::IsRouteExist(std::vector<std::vector<float>> adjMatrix, std::vector<int> numbersOfStationsInRoute)
{
	for (int i = 0; i < numbersOfStationsInRoute.size() - 1; i++)
	{
		if (adjMatrix[numbersOfStationsInRoute[i]][numbersOfStationsInRoute[i + 1]] == 0)
		{
			return false;
		}
	}
	return true;
}

void ProgramPreloading::FindDistancesBetweenStations(std::vector<std::vector<float>> adjMatrix, std::vector<int> numbersOfStationsInRoute, std::vector<float>& distancesBetweenStations)
{
	for (int i = 0; i < numbersOfStationsInRoute.size() - 1; i++)
	{

		distancesBetweenStations.push_back(adjMatrix[numbersOfStationsInRoute[i]][numbersOfStationsInRoute[i + 1]]);
	}
}

void ProgramPreloading::TrainsPreloading(RailwayField& rf, std::vector<Train*>& trainPark, char* str)
{
	std::ifstream file;
	int numberOfTheTrain, PassengersCarriegesCount, FreightCarriegesCount;
	std::vector<Carriege*> carry;
	Locomotive loco;
	TrainCreator creator;
	file.open(str);
	while (true)
	{
		Train* train = new Train;
		file >> numberOfTheTrain >> PassengersCarriegesCount >> FreightCarriegesCount;
		train->SetNumberOfTheTrain(numberOfTheTrain);
		train->SetCarriegesCount(PassengersCarriegesCount + FreightCarriegesCount);
		creator.LocoCreator();
		for (int i = 0; i < PassengersCarriegesCount; i++)
		{
			carry.push_back(creator.PassengerCarryCreator());
		}
		for (int i = 0; i < FreightCarriegesCount; i++)
		{
			carry.push_back(creator.FreightCarryCreator());
		}
		train->SetCarrieges(carry);
		train->SetLocomotive(loco);
		rf.SetTrainRoute(*train);
		carry.clear();
		trainPark.push_back(train);
		if (file.eof())
			break;
	}

	file.close();
}