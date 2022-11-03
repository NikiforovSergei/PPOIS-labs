#include "Header.h"

fox::fox(int c, int r, int health) {
	row = r;
	column = c;
	health = health;
}

state fox::who() {
	return FOX;
}

void fox::move(cell world[9][9], int randNumber, vector<fox*> vectorOfFoxes) {
	if (this->health == 0) { // Check health of zero
		int indexOfFoxZero;
		world[this->row][this->column].fox -= 1;
		for (int i = 0; i < vectorOfFoxes.size(); i++) { //find first zero element, it is our element
			if (vectorOfFoxes[i]->health == 0) {
				indexOfFoxZero = i;
				break;
			}
		}
		vectorOfFoxes.erase(vectorOfFoxes.begin() + indexOfFoxZero); // Delete first zero grass
		return;
	}
	if (this->age < 10) {
		this->age += 1;
	}
	else {
		int indexOfFoxZero;
		world[this->row][this->column].rabbit -= 1;
		for (int i = 0; i < vectorOfFoxes.size(); i++) { //find first zero element, it is our element
			if (vectorOfFoxes[i]->age == 10) {
				indexOfFoxZero = i;
				break;
			}
		}
		vectorOfFoxes.erase(vectorOfFoxes.begin() + indexOfFoxZero); // Delete first zero grass
		return;
	}
	if (this->get_createdNow()) {
		this->set_createdNow();
	}
	struct CellRand
	{
		int x;
		int y;
	};
	vector <CellRand> cells;
	int x = this->column;
	int y = this->row;
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			if (0 <= i < 8 && 0 <= j < 8 && world[i][j].countOfLivings != 4) {
				CellRand a;
				a.x = j;
				a.y = i;
				if (a.x >= 0 && a.y >= 0) {
					cells.push_back(a);
				}
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < cells.size(); j++) {
			if (cells[j].x > 8 || cells[j].y > 8) {
				cells.erase(cells.begin() + j);
				break;
			}
		}
	}
	cout << "cells size: " << cells.size() << endl;
	cout << randNumber << " ";
	if (randNumber >= cells.size() - 1) {
		this->column = cells[cells.size() - 1].x;
		this->row = cells[cells.size() - 1].y;
	}
	else
	{
		this->column = cells[randNumber].x;
		this->row = cells[randNumber].y;
	}
	world[this->column][this->row].countOfLivings += 1;
	world[this->column][this->row].fox += 1;

	world[x][y].countOfLivings -= 1; //Delete prev info about fox
	world[x][y].fox -= 1;

	this->health -= 25;
}
int fox::get_column() {
	return column;
}
int fox::get_row() {
	return row;
}

void fox::eat(cell world[9][9], vector<rabbit*> vectorOfRabbits) {
	int x = this->column;
	int y = this->row;
	if (world[x][y].rabbit > 0) {
		world[x][y].rabbit -= 1;
	}
	int indexOfRabbitTarget = -1;
	for (int i = 0; i < vectorOfRabbits.size(); i++) {
		if (vectorOfRabbits[i]->get_column() == x && vectorOfRabbits[i]->get_row() == y) {
			indexOfRabbitTarget = i;
			break;
		}
	}
	if (indexOfRabbitTarget != -1) {
		vectorOfRabbits.erase(vectorOfRabbits.begin() + indexOfRabbitTarget);
	}
}

string fox::get_sex() {
	return this->sex;
}

void fox::set_createdNow() {
	this->createdNow = false;
}

bool fox::get_createdNow() {
	return this->createdNow;
}

void fox::reproduction(cell world[][9], vector<fox*> vectorOfFoxes) {
	string sex = this->get_sex();
	if (world[this->get_column()][this->get_row()].fox >= 2 && world[this->get_column()][this->get_row()].countOfLivings < 4) {
		if (sex == "men") {
			for (int i = 0; i < vectorOfFoxes.size(); i++) {
				if (vectorOfFoxes[i]->get_column() == this->column && vectorOfFoxes[i]->get_row() == this->row) {
					if (vectorOfFoxes[i]->get_sex() == "women" && vectorOfFoxes[i]->get_createdNow() == false) {
						fox* a = new fox(this->get_column(), this->get_row(), 100);
						world[this->get_column()][this->get_row()].fox += 1;
						vectorOfFoxes.push_back(a);
					}
				}
			}
		}
	}
}