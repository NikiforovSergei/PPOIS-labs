/**
	\brief file with the main functions for manage the ocean model

	This file contains main function and ither methods for generate, build,
	populate, view and clear ocean model.
*/
#pragma once
#include <iostream>
#include <iomanip>
#include "Living.h"
#include "Settings.h"
#include "Empty.h"
#include <vector>
#include "Shark.h"
#include "Whale.h"

using namespace std;

class Model
{
	string path;
public:
	Model(){}
	Model(string path)
	{
		this->path = path;
		run();
	}

	void run();
	/**
	initialize ocean model

	\param ocean
*/
	void init(Ocean ocean);
	/**
		populate ocean model in general case

		\param ocean
	*/
	void eden(Ocean ocean);
	/**
		populate ocean model with planktons

		receive vector of planktons coordinates

		\param ocean, params
	*/
	void eden_plankton(Ocean ocean, vector<vector<int>> params);
	/**
		populate ocean model with sharks

		receive vector of sharks coordinates

		\param ocean, params
	*/
	void eden_shark(Ocean ocean, vector<vector<int>> params);
	/**
		populate ocean model with whales

		receive vector of whales coordinates

		\param ocean, params
	*/
	void eden_whale(Ocean ocean, vector<vector<int>> params);
	/**
		update the ocean model to the next life cycle

		\param old_ocean, new_ocean
	*/
	void update(Ocean new_ocean, Ocean old_ocean);
	/**
		clear old_ocean after updating

		\param ocean
	*/
	void clear(Ocean ocean);
	/**
		show in console the ocealn model condition on every cycle

		\param ocean, CYCLE
	*/
	void view(Ocean ocean, int CYCLE);
	/**
		update ocean model according to new animals after reprodiction

		\param ocean
	*/
	void update_reproduct_animals(Ocean ocean);

	/*!
		ocean model settings from file

		get ocean model settings from .txt file and set it data into variables

		\aram path
	*/
	void ocean_model(std::string path);
	/*!
		check ocean model border

		check if current cell depends on the ocean model and it can be reached

		\param row, column

		\return true-if ocean model cell, false-if cell doesn`t depend of ocean model
	*/
	bool border(int row, int column);
	/*!
		answer if cell was changing

		receive coordinates of cell, ckeck and answer if cell will be change

		\param row, column, cell_position

		\return true-if cell was changing, false-if cell didn`t changed
	*/
	bool changed_cell(int row, int column, int cell_position);
};