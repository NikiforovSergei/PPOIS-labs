#include "Stations.h"
#include "Trains.h"
#include "Routes.h"



void Station::SetName(std::string name)
{
	this->name = name;
}

std::string Station::GetName()
{
	return name;
}

std::string Station::GetTask()
{
	switch (task)
	{
	case 1:
		return "Loadind";
		break;
	case 2:
		return "Unloading";
		break;
	case 3:
		return "Transit";
		break;
	case 4:
		return "Temporary Stopping";
		break;
	default:
		throw new std::exception("Problem with function GetTask");
	}
}

std::string Station::GetType()
{
	return type;
}

void Station::ShowStationInfo()
{
	std::cout << GetName() << '\t' << type << "\t\t" << GetTask() << std::endl;
}

void Station::FullUnloading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Passenger carriege")
		{
			((PassengerCarriege*)tmp[i])->SetPasengers(0);
		}
		else if (tmp[i]->GetType() == "Freight carriege")
		{
			((FreightCarriege*)tmp[i])->SetOccupancy(0);
		}

	}
	train->SetCarrieges(tmp);
}

bool Station::SpendTimeOnStation()
{
	if(temporaryStopingTime == 0)
	{
		temporaryStopingTime = 4;
		return true;
	}
	else
	{
		temporaryStopingTime--;
		return false;
	}
}

FreightStation::FreightStation() : Station()
{
	type = "Freight Station";
}
void FreightStation::Loading(Train* train) //loading
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Freight carriege")
		{
			std::cout << "Freight carriege loading..." << std::endl;
			((FreightCarriege*)tmp[i])->SetOccupancy(100);
		}
	}
	train->SetCarrieges(tmp);
}

void FreightStation::Unloading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Freight carriege")
		{
			std::cout << "Freight carriege unloading..." << std::endl;
			((FreightCarriege*)tmp[i])->SetOccupancy(0);
		}
	}
	train->SetCarrieges(tmp);
}

PassengerStation::PassengerStation() : Station()
{
	passengersCount = rand() % 7;
	type = "Passenger Station";
}

void PassengerStation::Loading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Passenger carriege")
		{
			std::cout << "Freight carriege loading..." << std::endl;
			((PassengerCarriege*)tmp[i])->ChangeNumberOfPassengers(7);
		}
	}
	train->SetCarrieges(tmp);
}

void PassengerStation::Unloading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Passenger carriege")
		{
			std::cout << "Freight carriege unloading..." << std::endl;
			((PassengerCarriege*)tmp[i])->ChangeNumberOfPassengers(-5);
		}
	}
	train->SetCarrieges(tmp);
}

void PassengerStation::SetPassengersCount(int passengersCount)
{
	this->passengersCount = passengersCount;
}

int PassengerStation::GetPassengersCount()
{
	return passengersCount;
}

void PassengerStation::IncreasePassengesCount(int value) 
{
	passengersCount += value;
}

MixedStation::MixedStation()
{
	type = "Mixed Station";
}

void MixedStation::Loading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Passenger carriege")
		{
			std::cout << "Passenger carriege loading..." << std::endl;
			((PassengerCarriege*)tmp[i])->ChangeNumberOfPassengers(5);
		}
		else if (tmp[i]->GetType() == "Freight carriege")
		{
			std::cout << "Freight carriege loading..." << std::endl;
			((FreightCarriege*)tmp[i])->SetOccupancy(100);
		}

	}
	train->SetCarrieges(tmp);
}

void MixedStation::Unloading(Train* train)
{
	std::vector<Carriege*> tmp = train->GetCarrieges();
	int size = train->GetCarriegesCount();
	for (int i = 0; i < size; i++)
	{
		if (tmp[i]->GetType() == "Passenger carriege")
		{
			std::cout << "Passenger carriege unloading..." << std::endl;
			((PassengerCarriege*)tmp[i])->ChangeNumberOfPassengers(-5);
		}
		else if (tmp[i]->GetType() == "Freight carriege")
		{
			std::cout << "Freight carriege unloading..." << std::endl;
			((FreightCarriege*)tmp[i])->SetOccupancy(0);
		}

	}
	train->SetCarrieges(tmp);
}

void Station::SetTask(Task task)
{
	this->task = task;
}

void Station::SetTaskFromFile(std::string task)
{
	if (task == "Loading")
	{
		SetTask(Task::Loading);
	}
	else if (task == "Unloading")
	{
		SetTask(Task::Unloading);
	}
	else if (task == "Transit")
	{
		SetTask(Task::Transit);
	}
	else if (task == "TemporaryStoping")
	{
		SetTask(Task::TemporaryStoping);
	}
	else
	{
		SetTask(Task::TemporaryStoping);
		std::cout << " Incorrect task has chosen. Default task: Temporary Stoping." << std::endl;
	}
}

void SetTypeOfStation(std::string type)
{
	
}

void Station::DoTask(Train* train)
{
	switch (task)
	{
	case 1:
		Loading(train);
		break;
	case 2:
		Unloading(train);
		break;
	case 3: 
		break;
	case 4: 
		break;
	}
}