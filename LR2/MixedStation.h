#pragma once

#include "Station.h"

class MixedStation : public Station {
private:
	const int capacityCargo;
	int amountCargo;
public:
	MixedStation(int capacityCivMax, int capacityCargoMax) : Station(capacityCivMax), capacityCargo(capacityCargoMax) {
		amountCargo = 0;
	};
	TYPE getType() override;
	int adjustAmount(TYPE, int);
	int adjustAmount(int) override;
	int setAmount(TYPE, int);
	int setAmount(int) override;
	int getCapacity(TYPE);
	int getAmount(TYPE);
	bool canLoad(int amount, Wagon& train) override;
	bool canUnload(int amount, Wagon& train) override;
	void load(Wagon&) override;
	void unload(Wagon&) override;
	int missing(TYPE);
};
