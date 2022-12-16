#include<iostream>
#include<conio.h>
#include<thread>
#include<chrono>
#include"Railroad.h"
#include"Train.h"
#include"PassengerWagon.h"
#include"Utils.h"
#include"Errors.h"
#include"exception"

using std::runtime_error;
using std::cin;
using std::this_thread::sleep_for;

constexpr int TICK_TIME = 2000;

int main(int argc, char** argv) {

	bool manual = false;

	try {
		if (argc > 2)
			if (string(argv[2])._Equal("-manual"))
				manual = true;
			else
				throw runtime_error(INV_ARGS);

		Railroad* road = createRailroadFromFile(argv[1]);
		Train* t = new Train("Bob", road, 4);
		int days = 1;

		vector<Train*> trains = createTrainsFromFile(argv[1], road);

		while (true) {
			printf("Day [%i]\n---\n", days);
			for (Train* t : trains)
				t->tick();
			road->tick();
			days++;
			printf("---\n\n");
			if (manual) {
				printf("Waiting for user input to continue...\n");
				cin.get();
			} else sleep_for(std::chrono::milliseconds(TICK_TIME));
		}
	}
	catch (std::exception& e) {
		printf("Caught exception: %s\n", e.what());
	}
}