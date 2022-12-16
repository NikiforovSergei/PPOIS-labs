#include "Station.h"
#include <stdio.h>

TYPE Station::getType() {
	return UNKNOWN;
}

int Station::getAmount() {
	return amount;
}

int Station::setAmount(int set) {
	int old = getAmount();
	set = set < 0 ? 0 : set;
	set = set > getCapacity() ? getCapacity() : set;
	amount = set;
	return set - old;
}

int Station::adjustAmount(int delta) {
	return setAmount(getAmount() + delta);
}

int Station::getCapacity() {
	return capacity;
}

bool Station::canLoad(int amount, Wagon& wagon) {
	return
		getType() != UNKNOWN &&
		wagon.getType() != UNKNOWN &&
		getAmount() >= amount &&
		wagon.getType() == getType();
}

bool Station::canUnload(int amount, Wagon& wagon) {
	return
		getType() != UNKNOWN &&
		wagon.getType() != UNKNOWN &&
		(getAmount() + amount) <= getCapacity() &&
		wagon.getType() == getType();
}

void Station::load(Wagon& wagon) {
	int toLoad = wagon.missing();
	//printf("%i, %s, %i, %i\n", toLoad, canLoad(toLoad, wagon) ? "TRUE" : "FALSE", wagon.getType(), getType());
	if (canLoad(toLoad, wagon)) {
		wagon.adjustAmount(toLoad);
		adjustAmount(-toLoad);
		if(toLoad != 0)
			printf("Loaded [%i] resource points into wagon, wagon resources [%i], station resources [%i]\n", toLoad, wagon.getAmount(), getAmount());
	}
}

int Station::missing() {
	return getCapacity() - getAmount();
}

void Station::unload(Wagon& wagon) {
	int toUnload = missing();
	if (canUnload(toUnload, wagon)) {
		wagon.adjustAmount(-toUnload);
		adjustAmount(toUnload);
		if (toUnload != 0)
			printf("Unloaded [%i] resource points from wagon, wagon resources [%i], station resources [%i]\n", toUnload, wagon.getAmount(), getAmount());
	}
}