/*!
	c\brief ontains namespace settings for ocean model
	
	file contains namespace for global settings for every ocen model in application
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/*!
	\brief namespace of ocean model settings

	this namespace contains all settings for ocen model in application
*/
namespace settings
{
	std::string path;

	// ocean SIZE
	const int OCEAN_LENGHT = 5;
	const int OCEAN_WIDTH = 5;
	const int LIFE_IN_CELL = 4;

	std::vector<std::vector<int>> changed_cells; ///< changed after updating cells coordinates
	std::vector<std::vector<int>> reproducted_plankton; ///< changed after plankton reproduction cells coordinates

	// the age border of sharks and whales 
	const int DSHARK = 7;
	const int DWHALE = 9;

	int CYCLES;

	enum State
	{
		EMPTY,
		PLANKTON,
		SHARK,
		WHALE,
		STATES
	};

	enum Size
	{
		SMALL,
		MEDIUM,
		BIG,
		SIZES
	};

	enum Sex
	{
		FEMALE,
		MALE,
		SEXES
	};

	std::vector<std::vector<int>> plankton, whale, shark; ///< params of populaton positions
}

