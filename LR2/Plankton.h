/*!
	\brief Plankton class file

	file contains Plankton class that is food for predator
*/
#pragma once
#include "Living.h"
#include "Empty.h"
#include "Model.h"


/*!
	\brief Plankton

	inherited from Living and contains it`s another methods and fields such as reproduction and hp
*/
class Plankton : public Living
{
	int hp;
public:

	Plankton(int row, int column, int cell_position, int hp = 100)
	{
		this->row = row;
		this->column = column;
		this->cell_position = cell_position;
		this->hp = hp;
	}

	State who() { return PLANKTON; }
	void next(Ocean old_ocean, Ocean new_ocean);
	int get_hp() { return this->hp; }
	int get_sex() { return 0; }
	int get_age() { return 0; }
	int get_size() { return 0; }

	void set_hp(int hp) { this->hp = hp; }
	void set_age(int age) {}
};

