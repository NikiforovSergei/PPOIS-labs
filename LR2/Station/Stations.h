#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Trains.h"
//#include "RailwayField.h"

class Route;
class Train;

enum Task
{
	Loading = 1,
	Unloading,
	Transit,
	TemporaryStoping
};


class Station
{
protected:
	std::string name;
	std::string type;
	Task task;
	int temporaryStopingTime = 4;
public:
	Station(){}
	virtual void Loading(Train*) = 0;
	virtual void Unloading(Train*) = 0;
	virtual ~Station() {}
	void SetName(std::string name);
	std::string GetName();
	bool SpendTimeOnStation();
	std::string GetTask();
	void SetTask(Task task);
	void SetTaskFromFile(std::string);
	void FullUnloading(Train*);
	void ShowStationInfo();
	std::string GetType();
	void DoTask(Train*);
};

class FreightStation : virtual public Station
{
public:
	FreightStation();
	void Loading(Train* train) override;
	void Unloading(Train* train) override;
};

class PassengerStation : virtual public Station
{
private:
	int passengersCount;
public:
	PassengerStation();
	void Loading(Train* train) override;
	void Unloading(Train* train) override;
	void SetPassengersCount(int passengersCount);
	int GetPassengersCount();
	void IncreasePassengesCount(int value);
};

class MixedStation : public PassengerStation, public FreightStation
{
public:
	MixedStation();
	void Loading(Train* train);
	void Unloading(Train* train) override;
};