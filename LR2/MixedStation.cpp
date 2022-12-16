#include "MixedStation.h"
#include <stdio.h>

TYPE MixedStation::getType() {
	return MIXED;
}

int MixedStation::getCapacity(TYPE type) {
	switch (type)
	{
	case PASSENGER:
		return capacity;
	case CARGO:
		return capacityCargo;
	case MIXED:
		return capacityCargo + capacity;
	case UNKNOWN:
		return 0;
	}
}

int MixedStation::getAmount(TYPE type) {
	switch (type)
	{
	case PASSENGER:
		return amount;
	case CARGO:
		return amountCargo;
	case MIXED:
		return amount + amountCargo;
	case UNKNOWN:
		return 0;
	}
}

int MixedStation::adjustAmount(TYPE type, int delta) {
	return setAmount(type, getAmount(type) + delta);
}

int MixedStation::setAmount(TYPE type, int set) {
	int old = getAmount(type);
	set = set < 0 ? 0 : set;
	set = set > getCapacity(type) ? getCapacity(type) : set;
	switch (type)
	{
	case PASSENGER: {
		amount = set;
		break;
	}
	case CARGO: {
		amountCargo = set;
		break;
	}
	case MIXED: {
		amount = set;
		amountCargo = set;
	}
	}
	return set - old;
}

int MixedStation::setAmount(int set) {
	return setAmount(MIXED, set);
}

int MixedStation::adjustAmount(int adjust) {
	return adjustAmount(MIXED, adjust);
}

bool MixedStation::canUnload(int amount, Wagon& wagon) {
	return 1;
		wagon.getType() != UNKNOWN &&
		getAmount(wagon.getType()) >= amount;
}

bool MixedStation::canLoad(int amount, Wagon& wagon) {
	return 1;
		wagon.getType() != UNKNOWN &&
		(getAmount(wagon.getType()) + amount) <= getCapacity(wagon.getType());
}

void MixedStation::load(Wagon& wagon) {
	int toLoad = wagon.missing();
	//printf("%i, %s, %i, %i\n", toLoad, canLoad(toLoad, wagon) ? "TRUE" : "FALSE", wagon.getType(), getType());
	if (canLoad(toLoad, wagon)) {
		wagon.adjustAmount(toLoad);
		adjustAmount(wagon.getType(), -toLoad);
		const char* typeStr = toString(wagon.getType());
		if (toLoad != 0)
			printf("Loaded [%i] resource points of type [%s] into wagon, wagon resources [%i], [%s] station resources [%i]\n", toLoad, typeStr, wagon.getAmount(), typeStr, getAmount(wagon.getType()));
	}
}

int MixedStation::missing(TYPE type) {
	return getCapacity(type) - getAmount(type);
}

void MixedStation::unload(Wagon& wagon) {
	int toUnload = missing(wagon.getType());
	if (canUnload(toUnload, wagon)) {
		wagon.adjustAmount(-toUnload);
		adjustAmount(wagon.getType(), toUnload);
		const char* typeStr = toString(wagon.getType());
		if (toUnload != 0)
			printf("Unloaded [%i] resource points of type [%s] from wagon, wagon resources [%i], [%s] station resources [%i]\n", toUnload, typeStr, wagon.getAmount(), typeStr, getAmount(wagon.getType()));
	}
}