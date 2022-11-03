#include "Trains.h"
#include "Stations.h"
#include "Routes.h"

Locomotive TrainCreator::LocoCreator()
{
	system("cls");
	char ch;
	Locomotive loco;
	std::cout << "Do you want to set parameters of locomotive?" << std::endl
		<< "In another way default parameters will be set." << std::endl
		<< "(weight = 45t, normal velocity = 80 MpH, service time = 25 years)" << std::endl
		<< "y/n" << std::endl;
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		loco.SetData();
	return loco;
}

Carriege* TrainCreator::PassengerCarryCreator()
{
	system("cls");
	char ch;
	Carriege* carry;
	carry = new PassengerCarriege();
	std::cout << "Do you want to set parameters of carriege?" << std::endl
		<< "In another way default parameters will be set." << std::endl
		<< "(weight of carriege = 30t, number of passengers = 0)" << std::endl
		<< "y/n" << std::endl;
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		carry->SetData();
	return carry;
}

Carriege* TrainCreator::FreightCarryCreator()
{
	system("cls");
	Carriege* carry;
	carry = new FreightCarriege();
	char ch;
	std::cout << "Do you want to set parameters of carriege?" << std::endl
		<< "In another way default parameters will be set." << std::endl
		<< "(weight of carriege = 22t, occupancy = 0%)" << std::endl
		<< "y/n" << std::endl;
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		carry->SetData();
	return carry;
}

Train::Train()
{
	status = Free;
	carriegesCount = 5;
	carry.resize(carriegesCount);
}

void Train:: CreateLocomotive()
{

	loco = creator.LocoCreator();
}

void Train::CreateCarrieges()
{
	int ch;
	for (int i = 0; i < carriegesCount; i++)
	{
		system("cls");
		std::cout << "Select the type of carriege:\n1. Passengers carriege.\n2. Freight carriege\n";
		std::cin >> ch;
		switch (ch)
		{
		case 1:
			carry[i] = creator.PassengerCarryCreator();
			break;
		case 2:
			carry[i] = creator.FreightCarryCreator();
			break;
		default:
			std::cout << "Wrong value\n";
			i--;
			break;
		}
	}
}

float Train::GetWeight()
{
	float weight = 0;
	for (int i = 0; i < carriegesCount; i++)
	{
		weight += carry[i]->GetWeight();
	}
	return weight + loco.GetWeight();
}

float Train::GetVelocity()
{
	return loco.GetNormalVelocity() - alpha * GetWeight();
}

void Train::SetCarriegesCount(int carriegesCount)
{
	this->carriegesCount = carriegesCount;
}

short int Train::GetCarriegesCount()
{
	return carriegesCount;
}

std::vector<Carriege*> Train::GetCarrieges()
{
	return carry;
}

void Train::SetCarrieges(std::vector<Carriege*> carry)
{
	this->carry = carry;
}

void Train::LocoAndCarryInfo()
{
	std::cout << "\n*********LOCOMOTIVE************\n\n";
	loco.GetData();
	std::cout << "*******************************\n\n";
	for (int i = 0; i < carriegesCount; i++)
	{
		std::cout << "*********CARRIEGE " << i + 1 << "**********\n\n";
		carry[i]->GetData();
		std::cout << "*******************************\n\n";
	}
}

Route& Train::GetRoute()
{
	return *route;
}

void Train::SetRoute(Route* route)
{
	this->route = route;
}

void Train::ShowBriefInfo()
{
	std::cout << "Train " << GetNumberOfTheTrain() << "   "; route->ShowRouteInfo();
}

void Train::ShowDetailedTrainInfo()
{

	if (status == Free)
	{
		system("cls");
		std::cout << "Status: " << ShowStatus() << std::endl;
		std::cout << "Last station: " << location->GetName() << std::endl;
		std::cout << "Number of carrieges: " << GetCarriegesCount() << std::endl;
		std::cout << "Weight: " << GetWeight() << std::endl;
		std::cout << "Time to the next station: -- : -- " << std::endl;
	}
	else {
		system("cls");
		std::cout << "Status: " << ShowStatus() << std::endl;
		std::cout << "Route: "; route->ShowRouteInfo();
		std::cout << "Route time: "; TimeFormating(GetRouteTime());
		std::cout << "Last station: " << location->GetName() << std::endl;
		std::cout << "Velocity: " << GetVelocity() << std::endl;
		std::cout << "Number of carrieges: " << GetCarriegesCount() << std::endl;
		std::cout << "Weight: " << GetWeight() << std::endl;
		std::cout << "Route distance: " << route->GetRouteDistance() << std::endl;
		std::cout << "Time to the next station: "; TimeFormating(timeToTheNextStation);
	}
}

void Train::SetStatus(Status status)
{
	this->status = status;
}

std::string Train::ShowStatus()
{
	switch (status)
	{
	case InTheWay:
		return "In the way";
		break;
	case OnTheStation:
		return "On the station";
		break;
	case Free:
		return "Free";
		break;
	default:
		break;
	}
}

Status Train::GetStatus()
{
	return status;
}

void Train::SetLocation(Station* location)
{
	this->location = location;
}

float Train::GetRouteTime()
{
	return route->GetRouteDistance()/GetVelocity();
}

void Train::SetTimeToTheNextStation(int i)
{
	this->timeToTheNextStation = route->GetDistanceToTheNextStation(i) / GetVelocity(); 
}

float Train::GetTimeToNextStation()
{
	return timeToTheNextStation;
}

void Train::ChangeTimeToTheNextStation(float time)
{
	this->timeToTheNextStation -= time;
}

Station* Train::GetLocation()
{
	return location;
}

void Train::TimeFormating(float time)
{
	if (int((time - (int)time) * 60) < 10)
		std::cout << (int)time << " : 0" << int((time - (int)time) * 60) << std::endl;
	else
		std::cout << (int)time << " : " << int((time - (int)time) * 60) << std::endl;
}

void Train::SetNumberOfTheTrain(int numberOfTheTrain)
{
	this->numberOfTheTrain = numberOfTheTrain;
}

int Train::GetNumberOfTheTrain()
{
	return numberOfTheTrain;
}

void Train::SetLocomotive(Locomotive loco)
{
	this->loco = loco;
}

//void Train::UpdateTrainInfo()
//{
//	
//}