/// \file game.cpp
/// \brief реализация методов классов Puzzle и Menu

#include "game.h"
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <algorithm>

Puzzle::Puzzle()
{
	list_filling();
	do
	{
		random_sort();
	} while (!solve());
	board_filling();
	coordinate();
}

void Puzzle::random_sort()
{
	random_shuffle(begin(list), end(list));
}

bool Puzzle::solve()
{
	int e;
	int res = 0;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i] == 0)
			e = i / board_size + 1;
	}
	for (int i = 0; i < list_size - 1; i++)
	{
		for (int j = i + 1; j < list_size; j++)
		{
			if (list[j] < list[i] && list[j] != 0)
				res++;
		}
	}
	res += e;
	return (res % 2 == 0) ? true : false;
}

bool Puzzle::checker()
{
	return (board == solution) ? true : false;
}

void Puzzle::list_filling()
{
	for (int i = 0; i < list_size; i++)
	{
		list.push_back(i);
	}
}

void Puzzle::board_filling()
{
	int k = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			board[i][j] = list[k];
			k++;
		}
	}
}


void Puzzle::coordinate()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] == 0)
			{
				X = i; Y = j;
			}
		}
	}
}

void Puzzle::move()
{
	char ch = 0;
	ch = _getch();
	switch (ch)
	{
	case 'W':
	case 'w':
		if (X != 3)
		{
			swap(board[X][Y], board[X + 1][Y]);
			X += 1;
		}
		break;
	case 'A':
	case 'a':
		if (X != 3)
		{
			swap(board[X][Y], board[X][Y + 1]);
			Y += 1;
		}
		break;
	case 's':
	case 'S':
		if (X != 0)
		{
			swap(board[X][Y], board[X - 1][Y]);
			X -= 1;
		}
		break;
	case 'D':
	case 'd':
		if (Y != 0)
		{
			swap(board[X][Y], board[X][Y - 1]);
			Y -= 1;
		}
		break;
	}
}


ostream& operator << (ostream& s, Puzzle& p) {

	for (int i = 0; i < p.board_size; i++)
	{
		for (int j = 0; j < p.board_size; j++)
		{
			if (p.board[i][j] == 0)
				s << " " << '\t';
			else
				s << p.board[i][j] << '\t';
		}
		s << '\v';
	}
	return s;
}

int& Puzzle::operator[](const int n)
{
	if (n < 0 || n >= list_size)
		throw exception();
	return list[n];
}

void Menu::end()
{
	cout << "Поздравляем, вы собрали головоломку!!!" << endl << endl << endl << endl;
	cout << " Нажмите любую клавишу, чтобы выйти в меню" << endl << "e - выход" << endl;
	int x = _getch();
	if (x == 'e')
		exit(0);
}

Puzzle::~Puzzle() {}

void Menu::set_choice(int ch)
{
	this->ch = ch;
}

void Menu::start()
{
	int ch;
	cout << "1. Запустить." << endl
		<< "2. Условия игры." << endl
		<< "3. Выйти." << endl;
	cin >> ch;
	set_choice(ch);
	switch (ch)
	{
	case 1:
		system("cls");
		break;
	case 2:
		system("cls");
		conditions();
		break;
	case 3:
		system("cls");
		exit(0);
	default:
		break;
	}
}

void Menu::conditions()
{
	cout << "Популярная головоломка пятнашка была придумана еще в конце 19 века." << endl <<
		"Классическое игровое поле представляет собой матрицу 4х4 клеток, на котором по порядку (слева - направо и сверху - вниз) располагаются цифры от 1 до 15." << endl <<
		"Последняя клетка – пустая. Клетки перемешиваются определенным образом, и задача игрока состоит в том, чтобы восстановить их первоначальное правильное расположение." << endl << 
		"Делать это можно лишь путем перемещения на пустую клетку другой, соседней с ней клетки (расположенной слева, справа, сверху или снизу от пустой)."<< endl << endl << endl;
	cout << "Нажмите любую клавишу, чтобы выйти в меню" << endl;
	int x = _getch();
	system("cls");
	start();
}