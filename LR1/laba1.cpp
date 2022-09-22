/// \file main.cpp
/// \brief главный файл
///
/// \author ZayatsDmitry
/// \date 21.09.2022

#include <iostream>
#include <windows.h>
#include "mygame.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	Menu mn;
	do
	{
		system("cls");
		mn.start_menu();

		Puzzle game;
		while (!game.checker())
		{
			cout << game;
			game.move();
			system("cls");
		}
		cout << game;
		mn.end_of_the_game();
	} while (true);

}