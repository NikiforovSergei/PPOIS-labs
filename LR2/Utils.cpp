#include"Utils.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include"CargoStation.h"
#include"CargoWagon.h"
#include"PassengerStation.h"
#include"PassengerWagon.h"
#include"MixedStation.h"
#include"Errors.h"

constexpr char WEIGHT_DELIM = '^';
constexpr char NODE_DELIM = ';';
constexpr char PATH_DELIM = '-';
constexpr char WAGON_DELIM = ',';
const string SECTION_DELIM = "---\n";

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::runtime_error;

void printGraph(vector<vector<pair<int,int>>> graph) {
    cout << "Railroad graph structure: \n";
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++)
			printf("%i-[%i]->%i\n", i, graph[i][j].second, graph[i][j].first);
		printf("\n");
	}

}

Railroad* createRailroadFromFile(string file) {
	Railroad* instance = new Railroad();
	ifstream input(file);
	string line, temp;
	int lineIndex = 0, charIndex = 0;

	int capacity, adj, weight = 0;
	while (getline(input, line) && !line._Equal("---")) {
		stringstream lineStream(line);

		if (lineIndex == 0)
			while (getline(lineStream, temp, ';')) {

				try { capacity = stoi(temp.substr(1, temp.size())); }
				catch (...) { cerr << "Can't parse capacity on line 1, char " << (charIndex + 3); throw; }

				switch (temp[0]) {
				case '$': { instance->addStation(new CargoStation(capacity)); break; }
				case '@': { instance->addStation(new PassengerStation(capacity)); break; }
				case '&': { instance->addStation(new MixedStation(capacity, capacity)); break; }
				default: { throw runtime_error(U_SYMB); }
				}

				charIndex += temp.size();
			}
		else {
			vector<pair<int, int>> bufferVector;
			while (getline(lineStream, temp, NODE_DELIM)) {
				try {
					//cout << temp.substr(0, temp.find(',')) << endl << temp.substr(temp.find(',') + 1, temp.size()) << endl;
					adj = stoi(beforeDelim(temp, string(1, WEIGHT_DELIM)));
					weight = stoi(afterDelim(temp, string(1, WEIGHT_DELIM)));
				}
				catch (...) { 
					cerr << "Error parsing adjacency at line " << lineIndex << endl; 
					throw;
				}
				if ((lineIndex - 1 > instance->countStations()) || (adj >= instance->countStations())) {
					cerr << "Station index on line " << lineIndex << " is out of described stations bounds!" << endl;
					throw runtime_error(ST_OOB);
				}
				bufferVector.push_back(pair<int, int>(adj, weight));
			}
			//instance->addEdge(lineIndex - 1, adj, weight);
			//instance->graph.push_back(bufferVector);
			instance->pushRaw(bufferVector);
		}
		lineIndex++;
		charIndex = 0;
	}
	input.close();
	return instance;
}

vector<Train*> createTrainsFromFile(string file, Railroad* railroad) {
	ifstream input(file);
	string line, temp, temp1, name;
	stringstream t;
	t << input.rdbuf();
	stringstream trainsPartStream(afterDelim(t.str(), SECTION_DELIM));

	vector<Train*> res;
	while (getline(trainsPartStream, line)) {
		int nodeIndex = 0, capacity = 0, ind = -1, prevInd = -1;
		Train* trainInstance = NULL;
		stringstream lineStream(line);
		while (getline(lineStream, temp, NODE_DELIM)) {
			switch (nodeIndex) {
			case 0: {
				trainInstance = new Train(temp, railroad);
				break;
			}
			case 1: {
				stringstream pathStream(temp);
				while (getline(pathStream, temp1, PATH_DELIM)) {
					ind = stoi(temp1.substr(1, temp1.size()));
					if (ind != -1 && prevInd != -1) {
						if (!railroad->pathExists(prevInd, ind)) {
							cerr << "The path from " << prevInd << " to " << ind << " is not traversible or does not exist!" << endl;
							throw runtime_error(NOT_TRAV);
						}
						else if (ind > (railroad->countStations() - 1)) {
							cerr << "Station index " << ind << " is out of described stations bounds!" << endl;
							throw runtime_error(ST_OOB);
						}
					}
					switch (temp1[0]) {
					case '<': { trainInstance->pushPath(ind, LOAD); break; }
					case '>': { trainInstance->pushPath(ind, UNLOAD); break; }
					case '!': { trainInstance->pushPath(ind, WAIT); break; }
					case '#': { trainInstance->pushPath(ind, SKIP); break; }
					default: { throw runtime_error(U_SYMB); }
					}
					prevInd = ind;
				}
				break;
			}
			case 2: {
				stringstream pathStream(temp);
				while (getline(pathStream, temp1, WAGON_DELIM)) {
					capacity = stoi(temp1.substr(1, temp1.size()));
					switch (temp1[0]) {
					case '$': { trainInstance->pushWagon(new CargoWagon(capacity)); break; }
					case '@': { trainInstance->pushWagon(new PassengerWagon(capacity)); break; }
					default: { throw runtime_error(U_SYMB); }
					}
				}
				break;
			}
			}
			nodeIndex++;
		}
		//nodeIndex = 0;
		if(trainInstance != NULL)
			res.push_back(trainInstance);
	}
	return res;
}

string beforeDelim(string const& str, string const& delim)
{
	return str.substr(0, str.find(delim));
}

string afterDelim(string const& str, string const& delim)
{
	return str.substr(str.find(delim) + delim.size());
}
