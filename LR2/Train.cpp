#include "Train.h"

double Train::getTravelTimeModifier() {
	return wagons.size() * 0.1 - locomotivePower * 0.075 + 1.0;
}

bool Train::traverse() {
	if (current < (end(path)-1)) {
		current++;
		printf("[%s] arrived to station [%i]\n", name.c_str(), getCurrentStation() + 1);
		return true;
	}
	else {
		bool looped = tryLoop();
		printf("[%s] arrived to station [%i]\n", name.c_str(), getCurrentStation() + 1);
		return looped;
	}
}

void Train::tick() {

	if (current == end(path))
		return;

	if (isWaiting()) {
		wait();
		return;
	}

	if (travelTimer == 0) {
		if (getNextStation() == -1) {
			printf("[%s] stays at final destination, station [%i]\n", name.c_str(), getCurrentStation() + 1);
			return;
		}
		else traverse();

		if (!done) {
			switch (getCurrentAction())
			{
			case UNLOAD: {
				for (int i = 0; i < wagons.size(); i++) {
					if (railroad->getStation(getCurrentStation())->missing() > 0)

						printf("[%s] performs unload operation on station [%i], wagon [%i]:\n\t", name.c_str(), getCurrentStation() + 1, i + 1);
					railroad->getStation(getCurrentStation())->unload(*wagons[i]);
				}
				break;
			}
			case LOAD: {
				for (int i = 0; i < wagons.size(); i++) {
					if (wagons[i]->missing() > 0)
						printf("[%s] performs load operation on station [%i], wagon [%i]:\n\t", name.c_str(), getCurrentStation() + 1, i + 1);
					railroad->getStation(getCurrentStation())->load(*wagons[i]);
				}
				break;
			}
			case WAIT: {
				waitTimer = 4;
				break;
			}
			case SKIP:
			default:
				break;
			}
			done = true;
		}

		done = false;
		travelTimer = (int)(railroad->getPathLength(getCurrentStation(), getNextStation()) * getTravelTimeModifier());
		if(getNextStation() != -1)
			printf("[%s] forwading to station [%i]\n", name.c_str(), getNextStation() + 1);
	}
	else {
		printf("[%s] is in travel, [%i] days left until arrival...\n", name.c_str(), travelTimer);
		travelTimer--;
	}
}

bool Train::isWaiting() {
	return waitTimer > 0;
}

void Train::wait() {
	if (isWaiting()) {
		printf("[%s] is waiting on station [%i], [%i] days left to wait...\n", name.c_str(), getCurrentStation(), waitTimer);
		waitTimer--;
	}
}

ACTION Train::getStationAction(int station) {
	auto res = find_if(begin(path), end(path), [station](pair<int, ACTION> p) {return p.first == station; });
	return res == end(path) ? SKIP : (*res).second;
}

ACTION Train::getCurrentAction() {
	return (*current).second;
}

int Train::getCurrentStation() {
	return (*current).first;
}

int Train::getNextStation() {
	auto tryNext = find_if(begin(path), end(path), [this](pair<int, ACTION> p) {return p.first == getCurrentStation(); }) + 1;
	if (tryNext == end(path))
		return -1;

	if (current == (end(path) - 1)) {
		return (*tryNext).first;
	}
	return (*(current + 1)).first;
}

bool Train::tryLoop() {
	auto tryNext = find_if(begin(path), end(path), [this](pair<int, ACTION> p) {return p.first == getCurrentStation(); });
	if (tryNext < (end(path) - 1)) {
		current = tryNext+1;
		return true;
	}
	return false;
}

void Train::pushWagon(Wagon* wagon) {
	wagons.push_back(wagon);
}

void Train::pushPath(int station, ACTION action) {
	path.push_back(pair<int, ACTION>(station, action));
	current = begin(path);
}
