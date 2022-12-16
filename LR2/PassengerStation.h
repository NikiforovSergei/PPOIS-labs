#pragma once

#include "Station.h"

class PassengerStation : public Station {
public:
	PassengerStation(int capacity) : Station(capacity) {};
	TYPE getType() override;
};
