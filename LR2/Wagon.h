#pragma once

#include"Types.h"

class Wagon {
private:
	const int capacity;
	int amount;
public:
	Wagon(int capacityMax) : capacity(capacityMax) { 
		amount = 0; 
	};
	virtual TYPE getType();
	int getAmount();
	int getCapacity();
	int missing();
	void setAmount(int);
	void adjustAmount(int);
};