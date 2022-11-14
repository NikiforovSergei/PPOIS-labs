#include "Model.h"

// start of creating ocean model
void Model::run()
{
	this->ocean_model(path);

	// we have two stages of ocean. It is odd end even. They replace each other
	Ocean odd, even;

	// create an empty ocean model frame
	this->init(odd);
	this->init(even);
	// added creatures in the begin ocean (preparation start model)
	this->eden_plankton(even, settings::plankton);
	this->eden_shark(even, settings::shark);
	this->eden_whale(even, settings::whale);

	// print ocean model (cycle -1 is a preparation cycle)
	this->view(even, -1);

	// simulate life in the ocean in depend of the CYCLES count
	for (int i = 0; i < CYCLES; ++i)
	{
		if (i % 2)
		{
			// make the next step of the ocean, print is step and clear the previous step
			this->update(even, odd);
			this->view(even, i);
			this->clear(odd);
		}
		else
		{
			// the same
			this->update(odd, even);
			this->view(odd, i);
			this->clear(even);
		}
	}
}

void Model::init(Ocean ocean)
{
	// create empty cells
	for (int m = 0; m < OCEAN_LENGHT; ++m)
		for (int n = 0; n < OCEAN_WIDTH; ++n)
			for (int i = 0; i < LIFE_IN_CELL; ++i)
			{
				ocean[m][n][i] = new Empty(m, n, i);
			}
}


void Model::eden_plankton(Ocean ocean, vector<vector<int>> params)
{
	// fill plankton in the ocean (we got coordinates from file)
	for (auto vec : params)
	{
		delete ocean[vec[0]][vec[1]][vec[2]];
		ocean[vec[0]][vec[1]][vec[2]] = new Plankton(vec[0], vec[1], vec[2]);
	}
}

void Model::eden_shark(Ocean ocean, vector<vector<int>> params)
{
	// fill shark in the ocean (we got coordinates from file)
	for (auto vec : params)
	{
		delete ocean[vec[0]][vec[1]][vec[2]];
		ocean[vec[0]][vec[1]][vec[2]] = new Shark(vec[0], vec[1], vec[2], vec[3]);
	}
}

void Model::eden_whale(Ocean ocean, vector<vector<int>> params)
{
	// fill whale in the ocean (we got coordinates from file)
	for (auto vec : params)
	{
		delete ocean[vec[0]][vec[1]][vec[2]];
		ocean[vec[0]][vec[1]][vec[2]] = new Whale(vec[0], vec[1], vec[2], vec[3]);
	}
}

void Model::update(Ocean new_ocean, Ocean old_ocean)
{
	for (int m = 0; m < OCEAN_LENGHT; ++m)
		for (int n = 0; n < OCEAN_WIDTH; ++n)
			for (int i = 0; i < LIFE_IN_CELL; ++i)
			{
				// we change cell position only if this cell didn`t change before (in a process of changing the previous cells. For example in a process of perpoduction and subsequent creation a new creature)
				if (!(changed_cell(m, n, i)))
					old_ocean[m][n][i]->next(old_ocean, new_ocean);
			}

	// fill new creatures after reproduction function
	update_reproduct_animals(new_ocean);
	// unmark change cells for the next ocean update
	changed_cells.clear();
	// generally update_reproduct_animals only applies to plankton and reproducted_plankton is connected with update_reproduct_animals 
	reproducted_plankton.clear();
}

void Model::clear(Ocean ocean)
{
	// clear the memory after no not up-to-date oceal model
	for (int m = 0; m < OCEAN_LENGHT; ++m)
		for (int n = 0; n < OCEAN_WIDTH; ++n)
			for (int i = 0; i < LIFE_IN_CELL; i++)
				delete(ocean[m][n][i]);
}

void Model::view(Ocean ocean, int CYCLE)
{
	int i, j, k,
		emptyNum, planktonNum;

	cout << "\t   CYCLE " << CYCLE << endl;

	// print ocean model on the every life cycle in matrix format
	for (i = 0; i < OCEAN_LENGHT; i++)
	{
		cout << endl;
		for (j = 0; j < OCEAN_WIDTH; j++)
		{
			planktonNum = 0;
			emptyNum = 0;
			int counter = 0;
			for (k = 0; k < LIFE_IN_CELL; k++)
			{
				if (ocean[i][j][k]->who() == 0)
				{
					// print empty cell position
					cout << "\t\t" << "e";
					//emptyNum++;
				}
				else if (ocean[i][j][k]->who() == 1)
				{
					// print plankton with hp parameter
					cout << "\t\t" << "PL," << ocean[i][j][k]->get_hp();
					//planktonNum++;
				}
				else if (ocean[i][j][k]->who() == 2)
				{
					// print shark with hp and sex and age parameters
					cout << "\t\t" << "SH," << ocean[i][j][k]->get_hp() << "," << ocean[i][j][k]->get_sex() << "," << ocean[i][j][k]->get_age();
					//emptyNum++;
				}
				else if (ocean[i][j][k]->who() == 3)
				{
					// print whale with hp and sex and age parameters
					cout << "\t\t" << "WH," << ocean[i][j][k]->get_hp() << "," << ocean[i][j][k]->get_sex() << "," << ocean[i][j][k]->get_age();
					//planktonNum++;
				}
			}
			cout << endl;
			//cout << setw(4) << "e-" << emptyNum << "p-" << planktonNum << " ";
		}
	}
}

// fill created plankton in the actual ocean model
void Model::update_reproduct_animals(Ocean ocean)
{
	for (auto vec : reproducted_plankton)
		ocean[vec[0]][vec[1]][vec[2]] = new Plankton(vec[0], vec[1], vec[2]);
}

// read setting from file and prepared it for the next step of creating ocean model
void Model::ocean_model(std::string path)
{
	std::fstream fs;
	std::vector<int> params;
	int animal_count;

	try
	{
		fs.open(path, std::fstream::in);
		std::cout << "\nsuccessful open file!\n";
	}
	catch (const std::exception&)
	{
		std::cout << "\nFile open error!\n";
	}

	// get CYCLES and every creature position coordinates (put coordinates in the appropriate container)
	fs >> CYCLES;
	fs >> animal_count;
	int iter = 0;

	while (iter < animal_count)
	{
		int position;
		for (int i = 0; i < 3; i++)
		{
			fs >> position;
			params.push_back(position);
		}
		iter++;
		plankton.push_back(params);
		params.clear();
	}

	fs >> animal_count;
	iter = 0;

	while (iter < animal_count)
	{
		int position;
		for (int i = 0; i < 4; i++)
		{
			fs >> position;
			params.push_back(position);
		}
		iter++;
		shark.push_back(params);
		params.clear();
	}

	fs >> animal_count;
	iter = 0;

	while (iter < animal_count)
	{
		int position;
		for (int i = 0; i < 4; i++)
		{
			fs >> position;
			params.push_back(position);
		}
		iter++;
		whale.push_back(params);
		params.clear();
	}

	fs.close();
}

// check if we don`t run of the ocean model borders
bool Model::border(int row, int column)
{
	if ((row >= 0 && row < OCEAN_LENGHT) && (column >= 0 && column < OCEAN_WIDTH))
		return true;

	return false;
}

// check if some cell is mark as changed in a process of generating next step of the ocean model
bool Model::changed_cell(int row, int column, int cell_position)
{
	for (auto vec : changed_cells)
	{
		if (row == vec[0] && column == vec[1] && cell_position == vec[2])
			return true;
	}

	return false;
}
