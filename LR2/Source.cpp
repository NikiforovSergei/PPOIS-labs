#include "Header.h"
#include <ctime>
#include <vector>

void living::set_dead() {
	this->live = false;
}
//FOX
//fox::fox(int c, int r, int health) {
//	row = r;
//	column = c;
//	health = health;
//}
//
//state fox::who() {
//	return FOX;
//}
//
//void fox::move(cell world[9][9], int randNumber, vector<fox*> vectorOfFoxes) {
//	if (this->health == 0) { // Check health of zero
//		int indexOfFoxZero;
//		world[this->row][this->column].fox -= 1;
//		for (int i = 0; i < vectorOfFoxes.size(); i++) { //find first zero element, it is our element
//			if (vectorOfFoxes[i]->health == 0) {
//				indexOfFoxZero = i;
//				break;
//			}
//		}
//		vectorOfFoxes.erase(vectorOfFoxes.begin() + indexOfFoxZero); // Delete first zero grass
//		return;
//	}
//	if (this->get_createdNow()) {
//		this->set_createdNow();
//	}
//	struct CellRand
//	{
//		int x;
//		int y;
//	};
//	vector <CellRand> cells;
//	int x = this->column;
//	int y = this->row;
//	for (int i = y - 1; i <= y + 1; i++) {
//		for (int j = x - 1; j <= x + 1; j++) {
//			if (0 <= i < 8 && 0 <= j < 8 && world[i][j].countOfLivings != 4) {
//				CellRand a;
//				a.x = j;
//				a.y = i;
//				if (a.x >= 0 && a.y >= 0) {
//					cells.push_back(a);
//				}
//			}
//		}
//	}
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < cells.size(); j++) {
//			if (cells[j].x > 8 || cells[j].y > 8) {
//				cells.erase(cells.begin() + j);
//				break;
//			}
//		}
//	}
//	cout << "cells size: " << cells.size() << endl;
//	cout << randNumber << " ";
//	if (randNumber >= cells.size() - 1) {
//		this->column = cells[cells.size()-1].x;
//		this->row = cells[cells.size()-1].y;
//	}
//	else
//	{
//		this->column = cells[randNumber].x;
//		this->row = cells[randNumber].y;
//	}
//	world[this->column][this->row].countOfLivings += 1;
//	world[this->column][this->row].fox += 1;
//
//	world[x][y].countOfLivings -= 1; //Delete prev info about fox
//	world[x][y].fox -= 1;
//
//	this->health -= 25;
//}
//int fox::get_column() {
//	return column;
//}
//int fox::get_row() {
//	return row;
//}

//RABBIT
//rabbit::rabbit(int c, int r, int health) {
//	row = r;
//	column = c;
//	health = health;
//}
//
//state rabbit::who() {
//	return RABBIT;
//}
//
//int rabbit::get_column() {
//	return column;
//}
//
//int rabbit::get_row() {
//	return row;
//}
//
//void rabbit::move(cell world[9][9], int randNumber, vector<rabbit*> vectorOfRabbits) {
//	if (this->health == 0) { // Check health of zero
//		int indexOfRabbitZero;
//		world[this->row][this->column].rabbit -= 1;
//		for (int i = 0; i < vectorOfRabbits.size(); i++) { //find first zero element, it is our element
//			if (vectorOfRabbits[i]->health == 0) {
//				indexOfRabbitZero = i;
//				break;
//			}
//		}
//		vectorOfRabbits.erase(vectorOfRabbits.begin() + indexOfRabbitZero); // Delete first zero grass
//		return;
//	}
//	if (this->get_createdNow()) {
//		this->set_createdNow();
//	}
//	struct CellRand
//	{
//		int x;
//		int y;
//	};
//	vector <CellRand> cells;
//	int x = this->column;
//	int y = this->row;
//	for (int i = y - 1; i <= y + 1; i++) {
//		for (int j = x - 1; j <= x + 1; j++) {
//			if (0 <= i < 9 && 0 <= j < 9 && world[i][j].countOfLivings != 4) {
//				CellRand a;
//				a.x = j;
//				a.y = i;
//				if (a.x >= 0 && a.y >= 0) {
//					cells.push_back(a);
//				}
//			}
//		}
//	}
//	for (int i = 0; i < 9; i++) {
//			for (int j = 0; j < cells.size(); j++) {
//				if (cells[j].x > 8 || cells[j].y > 8) {
//					cells.erase(cells.begin() + j);
//					break;
//				}
//			}
//	}
//	cout << "Rabbit cells size: " << cells.size() << endl;
//	cout << randNumber << " ";
//	if (randNumber >= cells.size() - 1) {
//		this->column = cells[cells.size() - 1].x;
//		this->row = cells[cells.size() - 1].y;
//	}
//	else
//	{
//		this->column = cells[randNumber].x;
//		this->row = cells[randNumber].y;
//	}
//	world[this->column][this->row].countOfLivings += 1;
//	world[this->column][this->row].rabbit += 1;
//
//	world[x][y].countOfLivings -= 1; //Delete prev info about rabbit
//	world[x][y].rabbit -= 1;
//
//	this->health -= 25;
//}

//GRASS
//grass::grass(int c, int r, int health) {
//	row = r;
//	column = c;
//	health = health;
//}
//
//state grass::who() {
//	return RABBIT;
//}
//
//void grass::move(cell world[9][9], int randNumber, vector<grass*> vectorOfGrass) {
//	if (this->health == 0) { // Check health of zero
//		int indexOfGrassZero;
//		world[this->row][this->column].grass = 0;
//		for (int i = 0; i < vectorOfGrass.size(); i++) { //find first zero element, it is our element
//			if (vectorOfGrass[i]->health == 0) {
//				indexOfGrassZero = i;
//				break;
//			}
//		}
//		vectorOfGrass.erase(vectorOfGrass.begin() + indexOfGrassZero); // Delete first zero grass
//		return;
//	}
//	struct CellRand
//	{
//		int x;
//		int y;
//	};
//	vector <CellRand> cells;
//	int x = this->column;
//	int y = this->row;
//	for (int i = y - 1; i <= y + 1; i++) {
//		for (int j = x - 1; j <= x + 1; j++) {
//			if (0 <= i < 9 && 0 <= j < 9) {
//				CellRand a;
//				a.x = j;
//				a.y = i;
//				if (a.x >= 0 && a.y >= 0) {
//					cells.push_back(a);
//				}
//			}
//		}
//	}
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < cells.size(); j++) {
//			if (cells[j].x > 8 || cells[j].y > 8) {
//				cells.erase(cells.begin() + j);
//				break;
//			}
//		}
//	}
//	cout << randNumber << " ";
//	int childGrassX, childGrassY;
//	if (randNumber >= cells.size() - 1) {
//		childGrassX = cells[cells.size() - 1].x;
//		childGrassY = cells[cells.size() - 1].y;
//
//	}
//	else
//	{
//		childGrassX = cells[randNumber].x;
//		childGrassY = cells[randNumber].y;
//	}
//	grass a(childGrassX, childGrassY, 100); //Create child grass
//	world[childGrassY][childGrassX].countOfLivings += 1;
//	world[childGrassY][childGrassX].grass = 1;
//
//	this->health -= 25; //Lost 25 hp every step 
//}
//
//void grass::set_column(int column) {
//	this->column = column;
//}
//
//void grass::set_row(int row) {
//	this->row = row;
//}
//
//int grass::get_column() {
//	return column;
//}
//
//int grass::get_row() {
//	return row;
//}
//PrintWorld
PrintWorld::PrintWorld(int grass, int rabbits, int foxes) {
	cell a;
	a.countOfLivings = 0;
	a.fox = 0;
	a.grass = 0;
	a.rabbit = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			world[i][j] = a;
		}
	}
	this->startCountOfGrass = grass;
	this->startCountOfRabbits = rabbits;
	this->startCountOfFoxes = foxes;
}
void PrintWorld::print() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << "      |      |";
		}
		cout << endl;
		for (int j = 0; j < 9; j++) {
			cout << "      |      |";
		}
		cout << endl;
		for (int j = 0; j < 9; j++) {
			cout << "--------------";
		}
		cout << endl;
	}
}
void PrintWorld::initWorld() {
	srand(time(NULL));
	this->initGrass();
	this->initRabbits();
	this->initFoxes();
}
void PrintWorld::initGrass() {
	srand(time(NULL));
	for (int i = 0; i < this->startCountOfGrass; i++) {
		int xCoord, yCoord;
		xCoord = rand() % 9;
		yCoord = rand() % 9;
		bool generation = true;
		while (generation) {
			if (world[xCoord][yCoord].grass == 1) {
				xCoord = rand() % 9;
				yCoord = rand() % 9;
				generation = true;
			}
			else if (world[xCoord][yCoord].grass == 0) {
				grass *a = new grass(xCoord, yCoord, 100);
				world[xCoord][yCoord].grass = 1;
				world[xCoord][yCoord].countOfLivings += 1;
				this->vectorOfGrass.push_back(a);
				generation = false;
				//a.set_column(xCoord);
			}
		}
	}
	cout << "Init grass" << endl;
}
void PrintWorld::initRabbits() {
	//srand(time(NULL));
	for (int i = 0; i < this->startCountOfRabbits; i++) {
		int xCoord, yCoord;
		xCoord = rand() % 9;
		yCoord = rand() % 9;
		bool generation = true;
		while (generation) {
			if (world[xCoord][yCoord].countOfLivings == 4) {
				xCoord = rand() % 9;
				yCoord = rand() % 9;
				generation = true;
			}
			else if (world[xCoord][yCoord].countOfLivings < 4) {
				rabbit *a = new rabbit(xCoord, yCoord, 100);
				world[xCoord][yCoord].rabbit += 1;
				world[xCoord][yCoord].countOfLivings += 1;
				this->vectorOfRabbits.push_back(a);
				generation = false;
				//a.set_column(xCoord);
			}
		}
	}
	cout << "Init rabbits" << endl;
}
void PrintWorld::initFoxes() {
	/*srand(time(NULL));*/
	for (int i = 0; i < this->startCountOfFoxes; i++) {
		int xCoord, yCoord;
		xCoord = rand() % 9;
		yCoord = rand() % 9;
		bool generation = true;
		while (generation) {
			if (world[xCoord][yCoord].countOfLivings == 4) {
				xCoord = rand() % 9;
				yCoord = rand() % 9;
				generation = true;
			}
			else if (world[xCoord][yCoord].countOfLivings < 4) {
				fox *a = new fox(xCoord, yCoord, 100);
				world[xCoord][yCoord].fox += 1;
				world[xCoord][yCoord].countOfLivings += 1;
				this->vectorOfFoxes.push_back(a);
				generation = false;
				//a.set_column(xCoord);
			}
		}
	}
	for (int i = 0; i < vectorOfFoxes.size(); i++) {
		cout << i << " column: " << vectorOfFoxes[i]->get_column() << " row: " << vectorOfFoxes[i]->get_row() << endl;
	}
	cout << "Init foxes" << endl;
}
void PrintWorld::printStage() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int counter = 0;
			if (world[i][j].grass) {
				cout << "G";
				counter++;
			}
			for (int k = 0; k < world[i][j].rabbit; k++) {
				cout << "R";
				counter++;
			}
			for (int l = 0; l < world[i][j].fox; l++) {
				cout << "F";
				counter++;
			}
			if (counter == 0) {
				cout << "      |";
			}
			else if (counter == 1) {
				cout << "     |";
			}
			else if (counter == 2) {
				cout << "    |";
			}
			else if (counter == 3) {
				cout << "   |";
			}
			else if (counter == 4) {
				cout << "  |";
			}
		}
		cout << endl;
		for (int j = 0; j < 9; j++) {
			cout << "      |";
		}
		cout << endl;
		for (int j = 0; j < 9; j++) {
			cout << "-------";
		}
		cout << endl;
	}
}
//movement stage
void PrintWorld::movementStage() {
	srand(time(NULL));
	for (int i = 0; i < vectorOfGrass.size(); i++) {
		vectorOfGrass[i]->move(this->world, rand() % 9, vectorOfGrass);
		cout << i << " column: " << vectorOfGrass[i]->get_column() << " row: " << vectorOfGrass[i]->get_row() << endl;
	}
	for (int i = 0; i < vectorOfRabbits.size(); i++) {
		vectorOfRabbits[i]->move(this->world, rand() % 9, vectorOfRabbits);
		cout << i << " column: " << vectorOfRabbits[i]->get_column() << " row: " << vectorOfRabbits[i]->get_row() << endl;
	}
	for (int i = 0; i < vectorOfFoxes.size(); i++) {
		vectorOfFoxes[i]->move(this->world, rand() % 9, vectorOfFoxes);
		cout << i << " column: " << vectorOfFoxes[i]->get_column() << " row: " << vectorOfFoxes[i]->get_row() << endl;
		cout << "sex: " << vectorOfFoxes[i]->get_sex() << endl;
	}
}
// Eating stage
void PrintWorld::eatStage() {
	for (int i = 0; i < vectorOfRabbits.size(); i++) {
		vectorOfRabbits[i]->eating(this->world, vectorOfGrass);
	}
	for (int i = 0; i < vectorOfFoxes.size(); i++) {
		vectorOfFoxes[i]->eat(this->world, vectorOfRabbits);
	}
}

//void rabbit::eating(cell world[][9], vector<grass*> vectorOfGrass) {
//	int x = this->column;
//	int y = this->row;
//	if (world[x][y].grass == 1) {
//		world[x][y].grass = 0;
//	}
//	int indexOfGrassTarget = -1;
//	for (int i = 0; i < vectorOfGrass.size(); i++) {
//		if (vectorOfGrass[i]->get_column() == x && vectorOfGrass[i]->get_row() == y) {
//			indexOfGrassTarget = i;
//			break;
//		}
//	}
//	if (indexOfGrassTarget != -1) {
//		vectorOfGrass.erase(vectorOfGrass.begin() + indexOfGrassTarget);
//	}
//}

//void fox::eat(cell world[9][9], vector<rabbit*> vectorOfRabbits) {
//	int x = this->column;
//	int y = this->row;
//	if (world[x][y].rabbit > 0) {
//		world[x][y].rabbit -= 1;
//	}
//	int indexOfRabbitTarget = -1;
//	for (int i = 0; i < vectorOfRabbits.size(); i++) {
//		if (vectorOfRabbits[i]->get_column() == x && vectorOfRabbits[i]->get_row() == y) {
//			indexOfRabbitTarget = i;
//			break;
//		}
//	}
//	if (indexOfRabbitTarget != -1) {
//		vectorOfRabbits.erase(vectorOfRabbits.begin() + indexOfRabbitTarget);
//	}
//}

//Reproduction stage
//string fox::get_sex() {
//	return this->sex;
//}

//string rabbit::get_sex() {
//	return this->sex;
//}
//
//void rabbit::set_createdNow() {
//	this->createdNow = false;
//}

//void fox::set_createdNow() {
//	this->createdNow = false;
//}

//bool rabbit::get_createdNow() {
//	return this->createdNow;
//}

//bool fox::get_createdNow() {
//	return this->createdNow;
//}

//void rabbit::reproduction(cell world[][9], vector<rabbit*> vectorOfRabbits) {
//	string sex = this->get_sex();
//	if (world[this->get_column()][this->get_row()].rabbit == 2 && world[this->get_column()][this->get_row()].countOfLivings < 4) {
//		if (sex == "men") {
//			for (int i = 0; i < vectorOfRabbits.size(); i++) {
//				if (vectorOfRabbits[i]->get_column() == this->column && vectorOfRabbits[i]->get_row() == this->row) {
//					if (vectorOfRabbits[i]->get_sex() == "women" && vectorOfRabbits[i]->get_createdNow() == false) {
//						rabbit* a = new rabbit(this->get_column(), this->get_row(), 100);
//						world[this->get_column()][this->get_row()].rabbit += 1;
//						vectorOfRabbits.push_back(a);
//					}
//				}
//			}
//		}
//	}
//}

//void fox::reproduction(cell world[][9], vector<fox*> vectorOfFoxes) {
//	string sex = this->get_sex();
//	if (world[this->get_column()][this->get_row()].fox >= 2 && world[this->get_column()][this->get_row()].countOfLivings < 4) {
//		if (sex == "men") {
//			for (int i = 0; i < vectorOfFoxes.size(); i++) {
//				if (vectorOfFoxes[i]->get_column() == this->column && vectorOfFoxes[i]->get_row() == this->row) {
//					if (vectorOfFoxes[i]->get_sex() == "women" && vectorOfFoxes[i]->get_createdNow() == false) {
//						fox* a = new fox(this->get_column(), this->get_row(), 100);
//						world[this->get_column()][this->get_row()].fox += 1;
//						vectorOfFoxes.push_back(a);
//					}
//				}
//			}
//		}
//	}
//}

void PrintWorld::reproductionStage() {
	for (int i = 0; i < this->vectorOfRabbits.size(); i++) {
		vectorOfRabbits[i]->reproduction(this->world, this->vectorOfRabbits);
	}
	for (int i = 0; i < this->vectorOfFoxes.size(); i++) {
		vectorOfFoxes[i]->reproduction(this->world, this->vectorOfFoxes);
	}
}