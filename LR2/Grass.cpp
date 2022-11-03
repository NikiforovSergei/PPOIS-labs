#include "Header.h"

grass::grass(int c, int r, int health) {
	row = r;
	column = c;
	health = health;
}

state grass::who() {
	return RABBIT;
}

void grass::move(cell world[9][9], int randNumber, vector<grass*> vectorOfGrass) {
	if (this->health == 0) { // Check health of zero
		int indexOfGrassZero;
		world[this->row][this->column].grass = 0;
		for (int i = 0; i < vectorOfGrass.size(); i++) { //find first zero element, it is our element
			if (vectorOfGrass[i]->health == 0) {
				indexOfGrassZero = i;
				break;
			}
		}
		vectorOfGrass.erase(vectorOfGrass.begin() + indexOfGrassZero); // Delete first zero grass
		return;
	}
	if (this->age < 10) {
		this->age += 1;
	}
	else {
		int indexOfGrassZero;
		world[this->row][this->column].rabbit -= 1;
		for (int i = 0; i < vectorOfGrass.size(); i++) { //find first zero element, it is our element
			if (vectorOfGrass[i]->age == 10) {
				indexOfGrassZero = i;
				break;
			}
		}
		vectorOfGrass.erase(vectorOfGrass.begin() + indexOfGrassZero); // Delete first zero grass
		return;
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
			if (0 <= i < 9 && 0 <= j < 9) {
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
	cout << randNumber << " ";
	int childGrassX, childGrassY;
	if (randNumber >= cells.size() - 1) {
		childGrassX = cells[cells.size() - 1].x;
		childGrassY = cells[cells.size() - 1].y;

	}
	else
	{
		childGrassX = cells[randNumber].x;
		childGrassY = cells[randNumber].y;
	}
	grass a(childGrassX, childGrassY, 100); //Create child grass
	world[childGrassY][childGrassX].countOfLivings += 1;
	world[childGrassY][childGrassX].grass = 1;

	this->health -= 25; //Lost 25 hp every step 
}

void grass::set_column(int column) {
	this->column = column;
}

void grass::set_row(int row) {
	this->row = row;
}

int grass::get_column() {
	return column;
}

int grass::get_row() {
	return row;
}