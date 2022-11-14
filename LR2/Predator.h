/*!
	\brief Predator class file

	file contains Predator class for generate new danger animals
*/
#pragma once
#include "Settings.h"
#include "Living.h"


/*!
	\brief Predator

	inherited from Living and is abstract class that contains additional interface for Shark and Whale

	\code

	Predator(int row, int column, int cell_position, int sex, int size = MEDIUM, int hp = 100, int age = 0)
	{
		this->row = row;
		this->column = column;
		this->cell_position = cell_position;

		this->hp = hp;
		this->age = age;

		this->sex = sex;
		this->size = size;
	}

	\encode
*/
class Predator : public Living
{
protected:
	int hp, age, sex, size;
	int move;
public:
	Predator(int row, int column, int cell_position, int sex, int size = MEDIUM, int hp = 100, int age = 0)
	{
		this->row = row;
		this->column = column;
		this->cell_position = cell_position;

		this->hp = hp;
		this->age = age;

		this->sex = sex;
		this->size = size;
	}

	virtual int get_hp() = 0;
	virtual int get_age() = 0;
	virtual int get_sex() = 0;
	virtual int get_size() = 0;

	virtual void set_hp(int hp) = 0;
	virtual void set_age(int age) = 0;

	int empty_cell_for_move(Ocean old_ocean, Ocean new_ocean, int m, int n);
};

