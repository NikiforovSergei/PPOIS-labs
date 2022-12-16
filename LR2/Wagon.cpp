#include "Wagon.h"

TYPE Wagon::getType()
{
    return UNKNOWN;
}

int Wagon::getAmount() {
    return amount;
}

int Wagon::getCapacity() {
	return capacity;
}

int Wagon::missing() {
	return getCapacity() - getAmount();
}

void Wagon::setAmount(int set) {
	set = set < 0 ? 0 : set;
	set = set > getCapacity() ? getCapacity() : set;
	amount = set;
}

void Wagon::adjustAmount(int delta) {
	setAmount(getAmount() + delta);
}
