#include <iostream>
#include "Menu.h"
#include "ModelMapUtility.h"
int main()
{
	system("chcp 1251");
	system("cls");
	std::string path;
	/*std::cout << "Input path: ";
	std::cin >> path;*/
	path = "C:\\Lab2_2.4PPOIS\\test.txt";
	ModelMap obj(path);
	ModelMapUtility m(obj);
	std::cout << "Начать моделирование?\n1.Да.\n2.Нет\n";
	std::cin >> path;
	if (path == "1")
		m.fieldModelling();
	else
		return 0;
	//D:\\university\\Lab2_2.4_PPOIS\\Sources\\test.txt
}