#include "Menu.h"
using namespace std;

void Menu::StartUpMenu()
{
	system("cls");
	PrintMenu();
	switch (GetPlayerChoice())
	{
	case 1:
		StartGame();
		break;
	case 2:
		return;
		break;
	default:
		StartUpMenu();
		break;
	}
}

int Menu::LevelChoice()
{
	int choice = 1;
	cout << "Choose a level:\n1-3\n";
	cin >> choice;
	if (choice < 0 || choice > 3)
		throw new exception("Choice out of range");
	return choice;
}

void Menu::PrintMenu() const
{
	cout << "WELCOME TO THE GAME OF TAGPUZZLE!!!!\n\n1-Start Game\n2-Quit\n";
}

void Menu::StartGame()
{
	puzzle = new Puzzle(LevelChoice());
	Congratulate();
}

void Menu::Congratulate() const
{
	cout << "\n\n\n\n\nCONGRATULATIONS!!!!! You did it!\n";
}

int Menu::GetPlayerChoice()
{
	int a;
	cin >> a;
	return a;
}
