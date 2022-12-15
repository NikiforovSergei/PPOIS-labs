#pragma once
#include "Train.h"

class RailwayStation
{
private:
	int railwayStationNumber=0;
	int railwayStationType = 0;
	int transpotableResource=0;
	int offloadedResource=0;
protected:
	bool checkLoadPossibility(int necessaryCargo);
public:
	int getMapPostion();
	int getRailwayStationNumber();
	int getRailwayStationType();
	void setRailwayStationNumber(int RSNumber);
	void setTranspotableResource(int resource);
	void setOffloadResource(int resource);
	void setRailwayStationType(int type);
	virtual int getOffloadedResource(bool type);
	virtual int getTranspotableResource(bool type);
	virtual int loadTrain(Train &currentTrain, int necessaryCargo, bool type) = 0;
	virtual void offloadTrain(Train &currnetTrain, double necessaryOffloadPercent, bool type) = 0;
	
};

class GoodsRailwayStation :public RailwayStation
{
public:
	GoodsRailwayStation(int number, int transpotableResource);
	int loadTrain(Train &currentTrain, int necessaryCargo, bool type) override;
	void offloadTrain(Train& currentTrain, double necessaryOffloadPercent, bool type) override;
};

class PassengerRailwayStation : public RailwayStation
{
public:
	PassengerRailwayStation(int number, int transpotableResource);
	int loadTrain(Train& currentTrain, int necessaryCargo, bool type) override;
	void offloadTrain(Train& currentTrain, double necessaryOffloadPercent,bool type) override;
};

class MultiRailwayStation : public RailwayStation
{
private:
	GoodsRailwayStation RSPart1;
	PassengerRailwayStation RSPart2;
public:
	MultiRailwayStation(int number,GoodsRailwayStation &obj1, PassengerRailwayStation &obj2);
	int loadTrain(Train &currentTrain, int necessaryCargo, bool type) override;
	void offloadTrain(Train &currentTrain, double necessaryOffloadPercent, bool type) override;
	int getTranspotableResource(bool type) override;
	int getOffloadedResource(bool type) override;
};

