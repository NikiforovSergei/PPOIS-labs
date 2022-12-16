#pragma once

#include "Wagon.h"
#include "Types.h"

class Station {

private:
	int amount;
	const int capacity;
	Station(int maxCapacity) : capacity(maxCapacity) { amount = 0; };

public:
	virtual TYPE getType();
	virtual bool canUnload(int, Wagon&);
	virtual bool canLoad(int, Wagon&);
	virtual void load(Wagon&);
	virtual void unload(Wagon&);
	virtual int getAmount();
	virtual int getCapacity();
	virtual int setAmount(int);
	virtual int adjustAmount(int);
	virtual int missing();
	friend class CargoStation;
	friend class MixedStation;
	friend class PassengerStation;
};

