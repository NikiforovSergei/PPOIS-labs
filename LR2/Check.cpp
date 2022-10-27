#include "Check.h"

void Check::check_two(string str) {
	if (str.find(" ") == str.rfind(" ")) {
		if (str.find(" ") <= str.size() - 2) {

		}
		else {
			throw "Wrong syntax!";
		}
	}
	else {
		throw "Wrong syntax!";
	}
}