/*!
	\brief Empty class file

	file contains Empty class for filling empty cells
*/
#pragma once
#include "Living.h"
#include "Plankton.h"
using namespace settings;

/*!
	\brief Empty 

	inherited from Living and contains it`s another methods
*/
class Empty : public Living
{
public:
	Empty(int row, int column, int cell_position)
	{
		this->row = row;
		this->column = column;
		this->cell_position = cell_position;
	}

	State who() { return EMPTY; }
	void next(Ocean old_ocean, Ocean new_ocean);
	int get_hp() { return 0; }
	int get_sex() { return 0; }
	int get_age() { return 0; }
	int get_size() { return 0; }

	void set_hp(int hp) {}
	void set_age(int age) {}
};