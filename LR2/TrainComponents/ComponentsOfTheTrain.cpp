#include "ComponentsOfTheTrain.h"

ComponentOfTrain::ComponentOfTrain()
{
	number = rand() % 90000 + 10000;
}

Locomotive::Locomotive()
{
	type = "Locomotive";
	normalVelocity = 80.0;
	serviceTime = 25;
	weight = 40;
}
Locomotive::~Locomotive() {};
void Locomotive::SetData() 
{
	system("cls");
	std::cout << "Enter number "; std::cin >> number;
	std::cout << "Enter weight of locomotive "; std::cin >> weight;
	std::cout << "Enter normal velocity "; std::cin >> normalVelocity;
	std::cout << "Enter service time "; std::cin >> serviceTime;
}
void Locomotive::GetData()
{
	std::cout << "Type: " << type << std::endl;
	std::cout << "Number: " << number << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Normal velocity: " << normalVelocity << std::endl;
	std::cout << "Service time: " << serviceTime << std::endl << std::endl;
}

float Locomotive::GetWeight()
{
	return weight;
}

float Locomotive::GetNormalVelocity()
{
	return normalVelocity;
}

const char* Locomotive::GetType() 
{
	return type;
}

void Carriege::SetData() 
{
	system("cls");
	std::cout << "Enter number "; std::cin >> number;
	std::cout << "Enter weight of carriege "; std::cin >> weight;
}
void Carriege::GetData() 
{
	std::cout << "Type: " << GetType() << std::endl;
	std::cout << "Number: " << number << std::endl;
	std::cout << "Weight of carriege: " << weight << std::endl;
}

const char* Carriege::GetType()
{
	return type;
}

PassengerCarriege::PassengerCarriege()
{
	weight = 30;
	type = "Passenger carriege";
	passengersCount = 0;
}
void PassengerCarriege::SetData() 
{
	Carriege::SetData();
	std::cout << "Enter number of passengers "; std::cin >> passengersCount;
}
float PassengerCarriege::GetWeight() 
{
	return ComponentOfTrain::weight + 0.08f * passengersCount;
}
void PassengerCarriege::GetData() 
{
	Carriege::GetData();
	std::cout << "Number of passengers: " << GetPassengers() << std::endl;
	std::cout << "Weight with passengers: " << GetWeight() << std::endl << std::endl;
}

short int PassengerCarriege::GetPassengers()
{
	return passengersCount;
}

void PassengerCarriege::SetPasengers(short int passengersCount)
{
	this->passengersCount = passengersCount;
}

void PassengerCarriege::ChangeNumberOfPassengers(short int passengersCount)
{
	if (this->passengersCount + passengersCount >= MaxPassengersCount)
	{
		this->passengersCount = 35;
	}
	else if (this->passengersCount + passengersCount < 0)
	{
		this->passengersCount = 0;
	}
	else
		this->passengersCount += passengersCount;
	/*bool correct_input = false;
	do {
		if (this->passengersCount + passengersCount < max_number && this->passengersCount + passengersCount > 0)
		{
			this->passengersCount += passengersCount;
			correct_input = true;
		}
		else
			std::cout << "Max passengers count is 35" << std::endl;
	} while (correct_input = false);*/
}

const char* PassengerCarriege::GetType()
{
	return type;
}

FreightCarriege::FreightCarriege()
{
	weight = 22.0;
	type = "Freight carriege";
	occupancy = 0.0;
}

float FreightCarriege::GetWeight() 
{
	return ComponentOfTrain::weight + 0.3f * occupancy;
}

float FreightCarriege::GetOccupancy()
{
	return occupancy;
}

void FreightCarriege::SetOccupancy(float occupancy)
{
	this->occupancy = occupancy;
}

void FreightCarriege::SetData() 
{
	Carriege::SetData();
	std::cout << "Enter occupancy of carriege "; std::cin >> occupancy;
}

void FreightCarriege::GetData() 
{
	Carriege::GetData();
	std::cout << "Occupancy: " << GetOccupancy() << " %" << std::endl;
	std::cout << "Weight with cargo: " << GetWeight() << std::endl << std::endl;
}
