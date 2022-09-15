#include "TicTacToe.h"


TTT::TTT(int new_size)
{
	if (new_size > 2) {
		size = new_size;
		int grid_size = size * size;
		grid = new char[grid_size];
	}
	else {
		std::cout << "Enter a number greater than two" << std::endl;
		int greater_num = 0;
		while (greater_num < 3) {
			std::cin >> greater_num;
			size = greater_num;
			int grid_size = greater_num * greater_num;
			grid = new char[grid_size];
		}
	}

	first_move = true;
	is_game_over = false;

	
	for (int i = 0; i < size * size; i++) {
		grid[i] = '|';
	}
}

char & TTT::operator[](int position)
{
	if (position >= 0 && position < size * size) {
		return grid[position];
	}
	else {
		std::cout << "Invalid value 3" << std::endl;
	}
}

int TTT::GetSize() {
	return size;
}

void TTT::SetPosition(int position)
{
	if (is_game_over == false) {
		if (position >= 0 && position < size * size) {
			if (grid[position] != 'X' && grid[position] != 'O') {
				if (first_move == true) {
					grid[position] = 'X';
					prev_move = 'X';
					first_move = false;
				}
				else {
					if (prev_move == 'X') {
						grid[position] = 'O';
						prev_move = 'O';
					}
					else {
						grid[position] = 'X';
						prev_move = 'X';
					}
				}
			}
			else {
				std::cout << "Cell is not empty" << std::endl;
				std::cout << "Enter valid value 1" << std::endl;
				int new_position;
				std::cin >> new_position;
				SetPosition(new_position);
			}
		}
		else {
			std::cout << "Enter valid value 2" << std::endl;
			std::cout << "position " << position << std::endl;
			int new_position;
			std::cin >> new_position;
			SetPosition(new_position);
		}
		Winner();
	}
	else {
		std::cout << "The game is over" << std::endl;
		return;
	}

}

TTT::~TTT()
{
	delete[] grid;
}

void TTT::NewGame(int new_size)
{
	this->~TTT();

	if (new_size > 2) {
		size = new_size;
		int grid_size = size * size;
		grid = new char[grid_size];
	}
	else {
		std::cout << "Enter a number greater than two" << std::endl;
		int greater_num = 0;
		while (greater_num < 3) {
			std::cin >> greater_num;
			size = greater_num;
			int grid_size = greater_num * greater_num;
			grid = new char[grid_size];
		}
	}

	first_move = true;
	is_game_over = false;

	for (int i = 0; i < size * size; i++) {
		grid[i] = '|';
	}
}

void TTT::rows()
{
	int any_row = 0;

	for (int i = 0; i < size * size; i++) {
		if (grid[i] == 'X') {
			any_row++;
		}
		if (grid[i] == 'O') {
			any_row--;
		}
		if (abs(any_row) == size) {
			break;
		}
		if ((i + 1) % size == 0) {
			any_row = 0;
		}
	}

	if (any_row > 0 && abs(any_row) == size) {
		std::cout << "X is the winner 2" << std::endl;
		is_game_over = true;
		return;
	}
	if (any_row < 0 && abs(any_row) == size) {
		std::cout << "O is the winner 2" << std::endl;
		is_game_over = true;
		return;
	}
}

void TTT::columns()
{
	int any_column = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j / 3 < size; j = j + size) {
			if (grid[i + j] == 'X') {
				any_column++;
			}
			if (grid[i + j] == 'O') {
				any_column--;
			}
		}
		if (abs(any_column) == size) {
			break;
		}
		any_column = 0;
	}

	if (any_column > 0 && abs(any_column) == size) {
		std::cout << "X is the winner 1" << std::endl;
		is_game_over = true;
		return;
	}
	if (any_column < 0 && abs(any_column) == size) {
		std::cout << "O is the winner 1" << std::endl;
		is_game_over = true;
		return;
	}
}

void TTT::diagonal1()
{
	int dioganal1 = 0;

	for (int i = 0; i < size * size; i += size + 1) {
		if (grid[i] == 'X') {
			dioganal1++;
		}
		if (grid[i] == 'O') {
			dioganal1--;
		}
	}

	if (dioganal1 > 0 && abs(dioganal1) == size) {
		std::cout << "X is the winner 3" << std::endl;
		is_game_over = true;
		return;
	}
	if (dioganal1 < 0 && abs(dioganal1) == size) {
		std::cout << "O is the winner 3" << std::endl;
		is_game_over = true;
		return;
	}
}

void TTT::diagonal2()
{
	int dioganal2 = 0;

	for (int i = size - 1; i < size * size - 1; i += size - 1) {
		if (grid[i] == 'X') {
			dioganal2++;
		}
		if (grid[i] == 'O') {
			dioganal2--;
		}
		if (abs(dioganal2) == size) {
			break;
		}
	}

	if (dioganal2 > 0 && abs(dioganal2) == size) {
		std::cout << "X is the winner 4" << std::endl;
		is_game_over = true;
		return;
	}
	if (dioganal2 < 0 && abs(dioganal2) == size) {
		std::cout << "O is the winner 4" << std::endl;
		is_game_over = true;
		return;
	}
}

void TTT::Winner()
{
	if (is_game_over == false) {
		
		rows();
		columns();
		diagonal1();
		diagonal2();

	}
}

std::ostream& operator<<(std::ostream& os, TTT& game)
{
	int c = -1;

	for (int i = 0; i < game.GetSize() * game.GetSize(); i++) {
		c++;
		if (c == game.GetSize()) {
			c = 0;
			os << '\n';
		}
		os << game[i] << ' ';
	}
	os << std::endl;

	return os;
}

std::istream& operator>>(std::istream& os, TTT& game)
{
	for (int i = 0; i < game.GetSize() * game.GetSize(); i++) {
		os >> game[i];
	}

	return os;
}
