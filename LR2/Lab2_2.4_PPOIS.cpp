#include <iostream>
#include "Menu.h"
#include "ModelMapUtility.h"
int main()
{
	std::string path;
	std::cout << "Input path: ";
	std::cin >> path;
	ModelMap obj(path);
	ModelMapUtility m(obj);
	std::cout << "Start modelling?\n1.Yes.\n2.No\n";
	std::cin >> path;
	if (path == "1")
		m.fieldModelling();
	else
		return 0;
	//D:\\university\\Lab2_2.4_PPOIS\\Sources\\test.txt
}