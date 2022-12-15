#pragma once

#include <iostream>

#include <conio.h>

#include <stdlib.h>

#include <Windows.h>

#include <string>

#include <vector>

#include <string>

#include <fstream>

#include <filesystem>

#include <new>

const int N = 3;
const int decLifePlant = 10;
const int decLifeMamale = 20;
const int MAX_LIFE = 100;
const int MAX_STEPS_HUNGRY = 3;
const int MAX_SELL = 4;
int cycles = 20;
bool game = true;

enum class_predator
{
	FOX,//лиса вес 10 кг
	WOLF,//волк вес 50 кг
	BEAR,//медведь 200 кг
	MAX_CLASS_PREDATOR
};

enum class_herbivorous
{
	RABBIT,//кролик 2кг
	GOAT,//козел 20кг
	DEER,//олень 200кг
	MAX_CLASS_HERBIVOROUS
};

enum state
{
	EMPTY,
	PLANTS,
	HERBIVOROUS,
	PREDATOR,
	MAX_STATES
};

class living;
typedef living* world[N][N][MAX_SELL];

class living
{
public:

	virtual state who() = 0;
	virtual living* next(world w) = 0;
	virtual living* copy(world w) = 0;
	virtual char designation() = 0;
	virtual int get_age() = 0;
	virtual int get_move() = 0;
	virtual int get_hungry() = 0;
	virtual int get_size() = 0;
	virtual int get_step() = 0;
	virtual int get_name_class() = 0;
	virtual char gend() = 0;
	char set_gender(char g);
	char gender; //f-female , m-male

protected:
	int row, column, sell;
	void sums(world w, int sm[]);
	int dice_roll(int range);


};

void living::sums(world w, int sm[])
{
	//подсчет количества видов существ в €чейке
	sm[EMPTY] = sm[PLANTS] = sm[HERBIVOROUS] = sm[PREDATOR] = 0;

	for (int k = 0; k < MAX_SELL; k++)
	{
		sm[w[row][column][k]->who()]++;
	}
}

int living::dice_roll(int range)
{
	int diceValue = 0;

	diceValue = rand() % range;

	return diceValue;
}

char living::set_gender(char g)
{
	gender = g;
	return gender;
}

class predator : public living
{
public:

	predator(int r, int c, int s, int a = MAX_LIFE, char g = '.', int m = 1, int h = 0, class_predator name = FOX, int sz = 10)
		:life(a), gender(g), move(m), hungry(h), name_class(name), size(10)
	{
		row = r; column = c; sell = s;
		//вес животного в зависимости от вида
		switch (name_class)
		{
		case FOX:
			size = 10;
			step = 1;
			break;
		case WOLF:
			size = 50;
			step = 1;
			break;
		case BEAR:
			size = 200;
			step = 1;
			break;
		}
	}

	state who()override
	{
		return PREDATOR;
	}

	char designation()override
	{
		// predator
		char n = '?';
		switch (name_class)
		{
		case FOX:
			n = 'F';//fox
			break;
		case WOLF:
			n = 'W';//wolf
			break;
		case BEAR:
			n = 'B';//bear
			break;
		}
		return n;
	}

	int get_age()override
	{
		return life;
	}

	int get_move()override
	{
		return move;
	}

	int get_hungry()override
	{
		return hungry;
	}

	char gend()override
	{
		//predator
		return gender;
	}

	int get_size()override
	{
		return size;
	}

	int get_step()override
	{
		return step;
	}

	int get_name_class()override
	{
		return name_class;
	};

	living* next(world w)override;

	living* copy(world w)override;

protected:
	char gender; //f-female , m-male
	int life, size, move;//for move---> 0 -stop  1-move
	int hungry, step;
	class_predator  name_class;
};

class herbivorous : public living
{
public:

	herbivorous(int r, int c, int s, int a = MAX_LIFE, char g = '.', int m = 1, int h = 0, class_herbivorous name = RABBIT, int sz = 2)
		:life(a), gender(g), move(m), hungry(h), name_class(name), size(sz)
	{
		row = r; column = c; sell = s;
		//вес животного в зависимости от вида
		switch (name_class)
		{
		case RABBIT:
			size = 2;
			step = 1;
			break;
		case GOAT:
			size = 20;
			step = 1;
			break;
		case DEER:
			size = 200;
			step = 1;
			break;
		}
	}

	state who()override
	{
		return HERBIVOROUS;
	}

	int get_age()override
	{
		return life;
	}

	int get_move()override
	{
		return move;
	}

	int get_hungry()override
	{
		return hungry;
	}

	char designation()override
	{
		//HERBIVOROUS
		char n = '?';
		switch (name_class)
		{
		case RABBIT:
			n = 'R';//rabbit
			break;
		case GOAT:
			n = 'G';//goat
			break;
		case DEER:
			n = 'D';//deer
			break;
		}
		return n;
	}

	char gend()override
	{
		//HERBIVOROUS
		return gender;
	}

	int get_size()override
	{
		return size;
	}

	int get_step()override
	{
		return step;
	}

	int get_name_class()override
	{
		return name_class;
	};

	living* next(world w)override;

	living* copy(world w)override;
protected:
	char gender; //f-female , m-male
	int life, size, move;//for move---> 0 -stop  1-move;
	int hungry, step;
	class_herbivorous name_class;
};

class plants : public living
{
public:

	plants(int r, int c, int s, int a = MAX_LIFE, int m = 1, int sz = 20)
		:life(a), move(m), size(sz)
	{
		row = r; column = c; sell = s;  gender = '.';
	}

	state who()override
	{
		return PLANTS;
	}

	int get_age()override
	{
		return life;
	}

	int get_move()override
	{
		return move;
	}

	char designation()override
	{
		return 'P';
	}

	char gend()override
	{
		//plants
		return gender;
	}

	int get_hungry()override
	{
		return 0;
	}

	int get_size()override
	{
		return size;
	}

	int get_step()override
	{
		return 0;
	}
	int get_name_class()override
	{
		return 0;
	};

	living* next(world w)override;
	living* copy(world w)override;

protected:

	int life, move, size;
};

class empty : public living
{
public:

	empty(int r, int c, int s)
	{
		row = r; column = c; sell = s; gender = '.';
	}

	state who()override
	{
		return EMPTY;
	}

	char designation()override
	{
		return '.';
	}

	int get_age()override
	{
		return 0;
	}

	int get_move()override
	{
		return 1;
	}

	char gend()override
	{
		return gender;
	}

	int get_hungry()override
	{
		return 0;
	}

	int get_size()override
	{
		return 0;
	}

	int get_step()override
	{
		return 0;
	}

	int get_name_class()override
	{
		return 0;
	};

	living* next(world w)override;
	living* copy(world w)override;
};

