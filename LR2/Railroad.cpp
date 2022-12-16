#include"Railroad.h"
#include"MixedStation.h"

Railroad::Railroad() {}

vector<vector<pair<int, int>>> Railroad::getGraph() const {
	return this->graph;
}

void Railroad::addEdge(int u, int v, int w) {
	this->graph[u].push_back(pair<int, int>(v, w));
	this->graph[v].push_back(pair<int, int>(u, w));
}

void Railroad::pushRaw(vector<pair<int, int>> vec) {
	this->graph.push_back(vec);
}

void Railroad::addStation(Station* station) {
	this->stationsMap.push_back(station);
}

Station* Railroad::getStation(int index) {
	return stationsMap[index];
}

int Railroad::countStations() {
	return stationsMap.size();
}

bool Railroad::pathExists(int u, int v) {
	return getPathLength(u, v) != -1;
}

int Railroad::getPathLength(int u, int v) {
	auto res = find_if(begin(graph[u]), end(graph[u]), [v](pair<int, int> p) {return p.first == v; });
	return res == end(graph[u]) ? -1 : (*res).second;
}

void Railroad::tick() {
	srand(time(NULL));
	for (int i = 0; i < stationsMap.size(); i++) {
		Station* st = stationsMap[i];
		if (st->getAmount() < st->getCapacity()) {
			if (st->getType() != MIXED) {
				int refill = (int)st->getCapacity() * 0.075 + (rand() % 75 / 100.);
				int adjusted = st->adjustAmount(refill);
				printf("Station [%i] refilled by [%i] resource points, current amount [%i]\n", i + 1, adjusted, st->getAmount());
			}
			else {
				MixedStation* mst = (MixedStation*)st;
				int refillCargo = (int)mst->getCapacity(CARGO) * 0.075 + (rand() % 75 / 100.);
				int refillPassenger = (int)mst->getCapacity(PASSENGER) * 0.075 + (rand() % 75 / 100.);
				int adjustedCargo = mst->adjustAmount(CARGO, refillCargo);
				int adjustedPassenger = mst->adjustAmount(PASSENGER, refillPassenger);
				printf("Station [%i] refilled by [%i] resource points, current amount [%i] = Cargo [%i] + Passenger[%i]\n",
					i + 1,
					refillCargo + refillPassenger,
					mst->getAmount(MIXED),
					mst->getAmount(CARGO),
					mst->getAmount(PASSENGER)
				);
			}
		}
	}
}

