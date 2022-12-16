#pragma once

#include"Wagon.h"
#include"Railroad.h"

enum ACTION {UNLOAD, LOAD, WAIT, SKIP};

using std::pair;
using std::vector;
using std::iterator;
using std::string;

class Train {
private:
	const int locomotivePower;
	const string name;
	vector<Wagon*> wagons;
	vector<pair<int, ACTION>> path;
	vector<pair<int, ACTION>>::iterator current;
	int travelTimer;
	int waitTimer;
	bool done;
	
	Railroad* railroad;
public:
	Train(string nameIn, Railroad* road, int power) : name(nameIn), railroad(road), locomotivePower(power) {
		current = end(path);
		//travelTimer = (int)(railroad->getPathLength(getCurrentStation(), getNextStation()) * getTravelTimeModifier());
	};
	Train(string nameIn, Railroad* road) : Train(nameIn, road, 4) {};

	double getTravelTimeModifier();
	bool traverse();
	void tick();
	bool isWaiting();
	void wait();
	ACTION getStationAction(int);
	ACTION getCurrentAction();
	int getCurrentStation();
	int getNextStation();
	bool tryLoop();

	void pushWagon(Wagon*);
	void pushPath(int, ACTION);
};

