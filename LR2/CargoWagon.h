#pragma once
#pragma once

#include "Wagon.h"

class CargoWagon : public Wagon {
public:
	CargoWagon(int capacity) : Wagon(capacity) {};
	TYPE getType() override;
};
