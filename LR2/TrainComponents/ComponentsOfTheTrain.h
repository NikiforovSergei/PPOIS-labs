#pragma once
#include <ctime>
#include <iostream>

class ComponentOfTrain
{
protected:
	const char* type;
	float weight;
	int number;
public:
	ComponentOfTrain();
	~ComponentOfTrain() {};
	virtual void SetData() = 0;
	virtual void GetData() = 0;
	virtual const char* GetType() = 0;

};

class Locomotive : public ComponentOfTrain
{
protected:
	float normalVelocity;
	short int serviceTime;
public:
	Locomotive();
	~Locomotive();
	void SetData() override;
	void GetData() override;
	float GetWeight();
	float GetNormalVelocity();
	const char* GetType() override;
};

class Carriege : public ComponentOfTrain
{
public:
	virtual float GetWeight() = 0;
	void SetData() override;
	void GetData() override;
	const char* GetType();
};

class PassengerCarriege : public Carriege
{
protected:
	short int passengersCount;
	const short int MaxPassengersCount = 35;
public:
	PassengerCarriege();
	void SetData() override;
	float GetWeight() override;
	void GetData() override;
	short int GetPassengers();
	void SetPasengers(short int passengersCount);
	void ChangeNumberOfPassengers(short int passengersCount);
	const char* GetType();
};

class FreightCarriege : public Carriege
{
protected:
	float occupancy;
	float max_occupancy = 100;
public:

	FreightCarriege();

	float GetWeight() override;
	float GetOccupancy();
	void SetOccupancy(float occupancy);
	void SetData() override;
	void GetData() override;
};