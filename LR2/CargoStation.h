#pragma once

#include "Station.h"

class CargoStation : public Station {
public:
	CargoStation(int capacity) : Station(capacity) {};
	TYPE getType() override;
};
