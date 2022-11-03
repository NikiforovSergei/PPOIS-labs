#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

enum state { EMPTY, GRASS, RABBIT, FOX};

struct cell {
	int countOfLivings;
	int grass;
	int rabbit;
	int fox;
};

class living
{
public:
	virtual state who() = 0;
	void set_dead();
	int row;
	int column;
protected:
	
	string role;
	int health;
	bool live = true;
	int age = 0;
};

class grass : public living {
public:
	grass(int c, int r, int health);

	state who();

	void move(cell world[9][9], int randNumber, vector<grass*> vectorOfGrass);

	void set_column(int column);
	void set_row(int row);

	int get_column();
	int get_row();
protected:
	int health;
	bool live = true;
	int column;
	int row;
};

class rabbit : public living {
public:
	rabbit(int c, int r, int health);

	state who();

	int get_column();
	int get_row();

	void move(cell world[9][9], int randNumber, vector<rabbit*> vectorOfRabbits);

	void eating(cell world[][9], vector<grass*> vectorOfGrass);

	void reproduction(cell world[][9], vector<rabbit*> vectorOfRabbits);

	string get_sex();
	bool get_createdNow();

	void set_createdNow();
protected:
	int health = 100;
	string sex = (rand() % 2) == 0 ? "men" : "women";
	bool live = true;
	bool createdNow = true;
	int column;
	int row;
};

class fox : public living {
public:
	fox(int c, int r, int health);

	state who();

	int get_column();
	int get_row();

	void move(cell world[9][9], int randNumber, vector<fox*> vectorOfFoxes);

	void eat(cell world[9][9], vector<rabbit*> vectorOfRabbits);

	void reproduction(cell world[][9], vector<fox*> vectorOfFoxes);

	string get_sex();
	bool get_createdNow();

	void set_createdNow();
protected:
	int health = 100;
	string sex = (rand() % 2) == 0 ? "men" : "women";
	bool live = true;
	bool createdNow = true;
	int column;
	int row;
};

class PrintWorld {
public:
	PrintWorld(int grass, int rabbits, int foxes);
	void print();
	void initWorld();
	void initGrass();
	void initRabbits();
	void initFoxes();

	void printStage();

	void movementStage();
	void eatStage();
	void reproductionStage();

	int startCountOfGrass;
	int startCountOfRabbits;
	int startCountOfFoxes;
	vector <grass*> vectorOfGrass;
	vector <rabbit*> vectorOfRabbits;
	vector <fox*> vectorOfFoxes;
	cell world[9][9];
};
//Living::Living()
//{
//}
//
//Living::~Living()
//{
//}