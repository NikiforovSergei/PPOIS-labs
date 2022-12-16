#include "Game.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

Game::Game() {
	generate(cells[0], cells[0] + 16, [n = 0]() mutable { return n++; });
	while(!solvable())
		shuffle(cells[0], cells[0] + 16, mt19937(chrono::steady_clock::now().time_since_epoch().count()));
}

Game::Game(const Game& obj) {
	memcpy(cells, obj.cells, 16 * sizeof(int));
}

void Game::draw() {
	string linebuf, cellbuf;
	for (int j = 0; j < 13; j++)
		cout << '\xDB';
	cout << '\n';
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cellbuf = cells[i][j] != 0 ? to_string(cells[i][j]) : " ";
			linebuf += (cellbuf.length() == 2 ? "\xDB" : "\xDB ") + cellbuf;
			if (j == 3)
				linebuf += '\xDB';
		}
		cout << linebuf;
		linebuf = "";
		cout << '\n';
		for (int j = 0; j < 13; j++)
			cout << '\xDB';
		cout << '\n';
	}
}

int& Game::operator[](int val) {
	int* copy_arr = new int[16];
	copy(cells[0], cells[0] + 16, copy_arr);
	return copy_arr[val];
}

bool Game::operator==(Game& rhs) {
	return equal(cells[0], cells[0] + 16, rhs.cells[0]);
}

ostream& operator<<(ostream& os, Game& obj) {
	for (int i = 0; i < 16; i++) {
		os << obj[i];
		if (i != 15) os << ' ';
	}
	return os;
}

istream& operator>>(istream& is, Game& x) {
	string in;
	int ind;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			is >> in;
			try { ind = stoi(in); }
			catch (...) { ind = 0; };
			x.cells[i][j] = ind;
		}
	return is;
}

bool Game::solved() {
	for (int i = 0; i < 15; i++)
		if (operator[](i) != (i + 1)) {
			cout << operator[](i) << " " << i << endl;
			return false;
		}
	return true;
}

bool Game::move(int x, int y, Direction dir) {
	switch (dir)
	{
	case UP:
		if (!cells[y - 1][x]) {
			swap(cells[y - 1][x], cells[y][x]); return true; }
	case RIGHT:
		if (!cells[y][x + 1]) {
			swap(cells[y][x + 1], cells[y][x]); return true; }
	case DOWN:
		if (!cells[y + 1][x]) {
			swap(cells[y + 1][x], cells[y][x]); return true; }
	case LEFT:
		if (!cells[y][x - 1]) {
			swap(cells[y][x - 1], cells[y][x]); return true; }
	default:
		/**@throws Throws the exception if the passed direction is incorrect.*/
		throw "Wrong direction argument!\n";
	}
	return false;
}

int Game::get_invertions() {
	int inv_count = 0;
	for (int i = 0; i < 15; i++)
		for (int j = i + 1; j < 16; j++)
			if (operator[](j) && operator[](i) && operator[](i) > operator[](j))
				inv_count++;
	return inv_count;
}

int Game::blank_line()
{
	for (int i = 3; i >= 0; i--)
		for (int j = 3; j >= 0; j--)
			if (cells[i][j] == 0)
				return 4 - i;
}

bool Game::solvable()
{
	int invCount = get_invertions();

	int pos = blank_line();
	if (pos & 1)
		return !(invCount & 1);
	else
		return invCount & 1;
}

bool Game::move(int val, Direction dir) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (cells[i][j] == val)
				return move(j, i, dir);
}

Direction Game::ctod(char ch) {
	switch (ch)
	{
	case 'U':
		return UP;
	case 'R':
		return RIGHT;
	case 'D':
		return DOWN;
	case 'L':
		return LEFT;
	}
}