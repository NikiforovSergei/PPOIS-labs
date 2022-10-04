#include "Game.h"

Game::Game()
{	
	signs = 0;				//set signs on the field
	player = true;			//set player - X

	std::cout << "Write the sqare of your game field ";
	std::cin >> cell;
	field = new char* [cell];

	for (int rows = 0; rows < cell; rows++)
	{
		field[rows] = new char[cell];
		for (int cols = 0; cols < cell; cols++)
		{
			field[rows][cols] = ' ';
		}
	}
}

Game::~Game()
{
	for (int row = 0; row < cell; row++)
	{
		delete[] field[row];
	}
	delete[] field;
}

bool Game::GetPlayer()
{
	return player;
}

void Game::SetPlayer(bool player)
{
	this->player = player;
}

void Game::show()
{
	for (int rows = 0; rows < cell; rows++)
	{
		for (int cols = 0; cols < 16 * cell; cols++)
		{
			std::cout << '_';
		}
		std::cout << std::endl << std::endl;

		for (int j = 0; j < cell; j++)
		{
			std::cout << '\t' << field[rows][j] << '\t' << '|';
		}
		std::cout << std::endl;
	}
}

bool Game::check()
{
	for (int rows = 0; rows < cell; rows++)
	{
		for (int cols = 0; cols < cell; cols++)
		{
			if (cols != 0 && cols + 1 != cell)			//check horizont
			{
				if ('x' == field[rows][cols - 1] && 'x' == field[rows][cols] && 'x' == field[rows][cols + 1])
				{
					return true;
				}
				if ('o' == field[rows][cols - 1] && 'o' == field[rows][cols] && 'o' == field[rows][cols + 1])
				{
					return true;
				}
			}
			if (rows != 0 && rows + 1 != cell)			//check vertical
			{
				if ('x' == field[rows - 1][cols] && 'x' == field[rows][cols] && 'x' == field[rows + 1][cols])
				{
					return true;
				}
				if ('o' == field[rows - 1][cols] && 'o' == field[rows][cols] && 'o' == field[rows + 1][cols])
				{
					return true;
				}
			}
			if (rows != 0 && cols != 0 && rows + 1 != cell && cols + 1 != cell)				//check diogonal
			{
				if ('x' == field[rows - 1][cols - 1] && 'x' == field[rows][cols] && 'x' == field[rows + 1][cols + 1])
				{
					return true;
				}
				else if ('x' == field[rows - 1][cols + 1] && 'x' == field[rows][cols] && 'x' == field[rows + 1][cols - 1])
				{
					return true;
				}

				if ('o' == field[rows - 1][cols - 1] && 'o' == field[rows][cols] && 'o' == field[rows + 1][cols + 1])
				{
					return true;
				}
				else if ('o' == field[rows - 1][cols + 1] && 'o' == field[rows][cols] && 'o' == field[rows + 1][cols - 1])
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Game::PutASign(int row, int collumn)
{
	if (GetField()[row][collumn] != 'x' && GetField()[row][collumn] != 'o')
	{
		if (GetPlayer())
		{
			GetField()[row][collumn] = 'x';
			signs++;
		}
		else
		{
			GetField()[row][collumn] = 'o';
			signs++;
		}
		SetPlayer(!GetPlayer());		//changes player sign
	}
}

void Game::move_X(int row, int collumn)		//shift and bold X on the game field
{
	if (field[row][collumn] != 'x' && field[row][collumn] != 'o')
	{
		shift_X(row, collumn);
	}
	else
	{
		if (field[row][collumn] == 'x')
		{
			bold_X(row, collumn);
		}
		else
		{
			bold_O(row, collumn);
		}
	}
}

void Game::move_O(int row, int collumn)		//shift and bold O on the game field
{
	if (field[row][collumn] != 'x' && field[row][collumn] != 'o')
	{
		shift_O(row, collumn);
	}
	else
	{
		if (field[row][collumn] == 'o')
		{
			bold_O(row, collumn);
		}
		else
		{
			bold_X(row, collumn);
		}
	}
}

int Game::GetCells()
{
	return cell;
}

int Game::GetSigns()
{
	return signs;
}

char** Game::GetField()
{
	return field;
}

char*& Game::operator [](const int& index) const  // overloading operator []
{
	return  field[index];
}

void Game::shift_X(int row, int collumn)
{
	system("cls");
	field[row][collumn] = 'X';
	show();
	field[row][collumn] = ' ';
}

void Game::bold_X(int row, int collumn)
{
	system("cls");
	field[row][collumn] = 'X';
	show();
	field[row][collumn] = 'x';
}

void Game::shift_O(int row, int collumn)
{
	system("cls");
	field[row][collumn] = 'O';
	show();
	field[row][collumn] = ' ';
}

void Game::bold_O(int row, int collumn)
{
	system("cls");
	field[row][collumn] = 'O';
	show();
	field[row][collumn] = 'o';
}