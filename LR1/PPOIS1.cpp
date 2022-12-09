/// \file PPOIS1.cpp
/// \brief главный файл
///
/// \authors DominikFurs
/// \date 29.10.2022

#include <iostream>
#include <windows.h>
#include "game.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Menu mn;
	do
	{
		system("cls");
		mn.start();

		Puzzle game;
		while (!game.checker())
		{
			cout << game;
			game.move();
			system("cls");
		}
		cout << game;
		mn.end();
	} while (true);

}