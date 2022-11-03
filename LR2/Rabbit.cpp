#include "Header.h"

rabbit::rabbit(int c, int r, int health) {
	row = r;
	column = c;
	health = health;
}

state rabbit::who() {
	return RABBIT;
}

int rabbit::get_column() {
	return column;
}

int rabbit::get_row() {
	return row;
}

void rabbit::move(cell world[9][9], int randNumber, vector<rabbit*> vectorOfRabbits) {
	if (this->health == 0) { // Check health of zero
		int indexOfRabbitZero;
		world[this->row][this->column].rabbit -= 1;
		for (int i = 0; i < vectorOfRabbits.size(); i++) { //find first zero element, it is our element
			if (vectorOfRabbits[i]->health == 0) {
				indexOfRabbitZero = i;
				break;
			}
		}
		vectorOfRabbits.erase(vectorOfRabbits.begin() + indexOfRabbitZero); // Delete first zero grass
		return;
	}
	if (this->age < 6) {
		this->age += 1;
	}
	else {
		int indexOfRabbitZero;
		world[this->row][this->column].rabbit -= 1;
		for (int i = 0; i < vectorOfRabbits.size(); i++) { //find first zero element, it is our element
			if (vectorOfRabbits[i]->age == 6) {
				indexOfRabbitZero = i;
				break;
			}
		}
		vectorOfRabbits.erase(vectorOfRabbits.begin() + indexOfRabbitZero); // Delete first zero grass
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
			if (0 <= i < 9 && 0 <= j < 9 && world[i][j].countOfLivings != 4) {
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
			if (cells[j].x > 8 || cells[j].y > 8 || cells[j].x < 0 || cells[j].y < 0) {
				cells.erase(cells.begin() + j);
				break;
			}
		}
	}
	cout << "Rabbit cells size: " << cells.size() << endl;
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
	world[this->column][this->row].rabbit += 1;

	world[x][y].countOfLivings -= 1; //Delete prev info about rabbit
	world[x][y].rabbit -= 1;

	this->health -= 25;
}

void rabbit::reproduction(cell world[][9], vector<rabbit*> vectorOfRabbits) {
	string sex = this->get_sex();
	if (world[this->get_column()][this->get_row()].rabbit == 2 && world[this->get_column()][this->get_row()].countOfLivings < 4) {
		if (sex == "men") {
			for (int i = 0; i < vectorOfRabbits.size(); i++) {
				if (vectorOfRabbits[i]->get_column() == this->column && vectorOfRabbits[i]->get_row() == this->row) {
					if (vectorOfRabbits[i]->get_sex() == "women" && vectorOfRabbits[i]->get_createdNow() == false) {
						rabbit* a = new rabbit(this->get_column(), this->get_row(), 100);
						world[this->get_column()][this->get_row()].rabbit += 1;
						vectorOfRabbits.push_back(a);
					}
				}
			}
		}
	}
}

bool rabbit::get_createdNow() {
	return this->createdNow;
}

string rabbit::get_sex() {
	return this->sex;
}

void rabbit::set_createdNow() {
	this->createdNow = false;
}

void rabbit::eating(cell world[][9], vector<grass*> vectorOfGrass) {
	int x = this->column;
	int y = this->row;
	if (world[x][y].grass == 1) {
		world[x][y].grass = 0;
	}
	int indexOfGrassTarget = -1;
	for (int i = 0; i < vectorOfGrass.size(); i++) {
		if (vectorOfGrass[i]->get_column() == x && vectorOfGrass[i]->get_row() == y) {
			indexOfGrassTarget = i;
			break;
		}
	}
	if (indexOfGrassTarget != -1) {
		vectorOfGrass.erase(vectorOfGrass.begin() + indexOfGrassTarget);
	}
}