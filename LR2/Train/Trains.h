#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include "ComponentsOfTheTrain.h"
#include "Routes.h"
//#include "RailwayField.h"
class Station;
class Route;

enum Status
{
	InTheWay = 0,
	OnTheStation,
	Free
};

class TrainCreator
{
public:
	Locomotive LocoCreator();
	Carriege* PassengerCarryCreator();
	Carriege* FreightCarryCreator();
};

class Train
{
private:
	const float alpha = 0.03f;
	TrainCreator creator;
protected:
	Status status;
	Station* location;
	Locomotive loco;
	std::vector<Carriege*> carry;
	Route* route;
	float timeToTheNextStation;
	unsigned short int carriegesCount;
	unsigned int numberOfTheTrain;
public:
	int numberOfCurrentStation = 0;
	Train();
	void CreateLocomotive();
	void CreateCarrieges();
	float GetWeight();
	float GetVelocity();
	float GetRouteTime();
	void SetCarriegesCount(int);
	short int GetCarriegesCount();
	std::vector<Carriege*> GetCarrieges();
	void SetCarrieges(std::vector<Carriege*>);
	void LocoAndCarryInfo();
	void SetRoute(Route* route);
	Route& GetRoute();
	std::string ShowStatus();
	void ShowDetailedTrainInfo();
	void ShowBriefInfo();
	void SetStatus(Status);
	Status GetStatus();
	void SetLocation(Station*);
	void SetTimeToTheNextStation(int);
	void ChangeTimeToTheNextStation(float);
	float GetTimeToNextStation();
	Station* GetLocation();
	void TimeFormating(float time);
	void SetNumberOfTheTrain(int);
	int GetNumberOfTheTrain();
	void SetLocomotive(Locomotive);
	//void UpdateTrainInfo();
	
};
