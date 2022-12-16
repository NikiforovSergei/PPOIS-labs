#pragma once

#include<vector>
#include<utility>
#include<string>
#include<time.h>
#include"Station.h"

using std::vector;
using std::pair;

class Railroad {
private:
	vector<vector<pair<int,int>>> graph;
	vector<Station*> stationsMap;
public:
	Railroad();
	vector<vector<pair<int, int>>> getGraph() const;
	void pushRaw(vector<pair<int, int>>);
	void addEdge(int u, int v, int w);
	void addStation(Station*);
	Station* getStation(int);
	int countStations();
	bool pathExists(int, int);
	int getPathLength(int, int);
	void tick();
};

