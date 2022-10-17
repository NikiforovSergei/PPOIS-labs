#include "Cut.h"
#include <iostream>
void Cut::cut(string& str) {
	string func_name;
	func_name = str;
	func_name.erase(func_name.begin(), func_name.begin() + func_name.find(' ') + 1);
	str = func_name;
}