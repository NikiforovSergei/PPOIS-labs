#pragma once

#include<vector>
#include<utility>
#include"Railroad.h"
#include"Train.h"

using std::string;

void printGraph(vector<vector<pair<int, int>>>);
Railroad* createRailroadFromFile(string);
vector<Train*> createTrainsFromFile(string, Railroad*);
string beforeDelim(string const& str, string const& delim);
string afterDelim(string const& str, string const& delim);