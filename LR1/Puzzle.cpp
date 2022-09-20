#include "Puzzle.h"

#include <windows.h>
#include <ctime>
#include <chrono>
#include <thread>

Puzzle::Puzzle(int level)
{
	srand(static_cast<int>(time(0)));
	currentLevel = level;
	while (currentLevel <= 3)
	{
		SetLevel(currentLevel);
		Shuffle();
		while (true)
		{
			system("cls");
			PrintBoard();
			if (CheckWinCondition())
				break;
			AwaitPlayerInput();
		}
		currentLevel++;
	}
}

Tile Puzzle::operator[](int x)
{
	int y = 0;
	while (x >= size)
	{
		x -= size;
		y += 1;
	}
	return puzzleBoard[y][x];
}

void Puzzle::PrintBoard() const
{
	std::cout << "Controls:\nW - up\nS - down\nA - left\nD - right\nG - get tile's value\n\n\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << puzzleBoard[i][j].GetValue();
		}
		std::cout << '\n';
	}
}

void Puzzle::Shuffle()
{	
	for (int i = 0; i < 10000; i++)
	{
		Direction a = static_cast<Direction>(rand() % 4);
		Move(a);
	}
}

bool Puzzle::CheckWinCondition() const
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!puzzleBoard[i][j].CheckPlacement(i, j))
				return false;
		}
	}
	return true;
}

void Puzzle::Move(Direction dir)
{
	int xOffset = 0;
	int yOffset = 0;
	switch (dir)
	{
	case Direction::up:
		xOffset = 1;
		break;
	case Direction::down:
		xOffset = -1;
		break;
	case Direction::left:
		yOffset = 1;
		break;
	case Direction::right:
		yOffset = -1;
	}

	if (blankX + xOffset < size && blankY + yOffset < size &&
		blankX + xOffset >= 0 && blankY + yOffset >= 0)
	{
		Swap(puzzleBoard[blankX][blankY], puzzleBoard[blankX + xOffset][blankY + yOffset]);
		blankX += xOffset;
		blankY += yOffset;
	}
}

void Puzzle::Swap(Tile &one, Tile &two)
{
	Tile temp = one;
	one = two;
	two = temp;
}

void Puzzle::AwaitPlayerInput()
{
	Direction dir;
	switch (_getch())
	{
	case 'w':
		dir = Direction::up;
		break;
	case 's':
		dir = Direction::down;
		break;
	case 'a':
		dir = Direction::left;
		break;
	case 'd':
		dir = Direction::right;
		break;
	case 'g':
		std::cout << "Enter tile's number\n";
		int num;
		std::cin >> num;
		if (num >= 1 && num <= size * size)
		{
			std::cout << (*this)[num - 1].GetValue() << std::endl;
		}
		Sleep(3000);
	default:
		return;
	}
	Move(dir);
}

void Puzzle::SetLevel(int level)
{
	switch (level)
	{
	case 1:
		size = 3;
		puzzleBoard = new Tile * [3];
		for (int i = 0; i < 3; i++)
		{
			puzzleBoard[i] = new Tile[3]
			{
				level1[i][0], level1[i][1], level1[i][2]
			};
		}
		blankX = 2;
		blankY = 2;
		break;
	case 2:
		size = 4;
		puzzleBoard = new Tile * [4];
		for (int i = 0; i < 4; i++)
		{
			puzzleBoard[i] = new Tile[4]
			{
				level2[i][0], level2[i][1], level2[i][2], level2[i][3]
			};
		}
		blankX = 3;
		blankY = 3;
		break;
	case 3:
		size = 5;
		puzzleBoard = new Tile * [5];
		for (int i = 0; i < 5; i++)
		{
			puzzleBoard[i] = new Tile[5]
			{
				level3[i][0], level3[i][1], level3[i][2], level3[i][3], level3[i][4]
			};
		}
		blankX = 4;
		blankY = 4;
		break;
	default:
		break;
	}
}