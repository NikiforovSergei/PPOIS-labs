#pragma once

#include "Wagon.h"

class PassengerWagon : public Wagon {
public:
	PassengerWagon(int capacity) : Wagon(capacity) {};
	TYPE getType() override;
};
