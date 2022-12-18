#include "ocean.h"

using namespace std;
using namespace ocean_life;


void Ocean_field::display_field()
{
	for (int i = 0; i < width; i++)
		cout << "----";
	cout << "-" << endl;
	for (int i = 0; i < height; i++)
	{
		cout << "|";
		for (int j = 0; j < width; j++)
			cout << scene[j][i][0] << " " << scene[j][i][1] << "|";
		cout << endl << "|";
		for (int j = 0; j < width; j++)
			cout << "   |";
		cout << endl << "|";
		for (int j = 0; j < width; j++)
			cout << scene[j][i][2] << " " << scene[j][i][3] << "|";
		cout << endl << "-";
		for (int j = 0; j < width; j++)
			cout << "----";
		cout << endl;
	}
}

int* Ocean_master::find_empty_cell(bool isPlankton)
{
	int width = ocean_table->get_width();
	int height = ocean_table->get_height();
	int* coords = new int[3];
	int variations = 0;
	int i = rand() % width;
	int j = rand() % height;
	int k = 0;

	while (ocean_table->scene[i][j][k] != ' ' && variations < width * height) // if we are looking for an empty cell and not every cell is full
	{
		for (int c = 0; c < 4; c++)
		{
			if (isPlankton)
				if (ocean_table->scene[i][j][c] == 'P') break;
			if (ocean_table->scene[i][j][c] == ' ')
			{
				coords[0] = i; coords[1] = j; coords[2] = c;
				return coords;
			}
		}
		i = rand() % width;
		j = rand() % height;
		variations++;
	}
	if (variations < width * height)
	{
		coords[0] = i; coords[1] = j; coords[2] = k;
		return coords;
	} // if an empty cell is found

	coords[0] = -1; coords[1] = -1; coords[2] = -1;
	return coords; // if an empty field does not exist
}

void Ocean_master::Tick()
{
	system("cls");
	int plankton_count = fish_plankton.size(),
		clownfish_count = fish_clownfish.size(),
		fugu_count = fish_fugu.size(),
		whale_count = fish_whale.size(),
		dolphin_count = fish_dolphin.size(),
		shark_count = fish_shark.size(),
		killerwhale_count = fish_killerwhale.size();

	// PLANKTON MOVES
	for (int i = 0; i < plankton_count; i++)
		Plankton_move(&fish_plankton[i]);
	for (int i = 0; i < plankton_count; i++)
		Plankton_replicate(&fish_plankton[i]);
	for (int i = plankton_count - 1; i >= 0; i--)
		Plankton_age(&fish_plankton[i], i);

	// CLOWNFISH MOVES
	for (int i = 0; i < clownfish_count; i++)
		for (int j = 0; j < fish_clownfish[i].get_moves(); j++)
			Passive_move(&fish_clownfish[i]);
	for (int i = 0; i < clownfish_count; i++)
		Passive_eat(&fish_clownfish[i]);
	for (int i = 0; i < clownfish_count; i++)
		Passive_replicate(&fish_clownfish[i]);
	for (int i = clownfish_count - 1; i >= 0; i--)
		Passive_age(&fish_clownfish[i], i);

	// FUGU MOVES
	for (int i = 0; i < fugu_count; i++)
		for (int j = 0; j < fish_fugu[i].get_moves(); j++)
			Passive_move(&fish_fugu[i]);
	for (int i = 0; i < fugu_count; i++)
		Passive_eat(&fish_fugu[i]);
	for (int i = 0; i < fugu_count; i++)
		Passive_replicate(&fish_fugu[i]);
	for (int i = fugu_count - 1; i >= 0; i--)
		Passive_age(&fish_fugu[i], i);

	// DOLPHIN MOVES
	for (int i = 0; i < dolphin_count; i++)
		for (int j = 0; j < fish_dolphin[i].get_moves(); j++)
			Neutral_move(&fish_dolphin[i]);
	for (int i = 0; i < dolphin_count; i++)
		Neutral_eat(&fish_dolphin[i]);
	for (int i = 0; i < dolphin_count; i++)
		Neutral_replicate(&fish_dolphin[i]);
	for (int i = dolphin_count - 1; i >= 0; --i)
		Neutral_age(&fish_dolphin[i], i);

	// WHALE MOVES
	for (int i = 0; i < whale_count; i++)
		for (int j = 0; j < fish_whale[i].get_moves(); j++)
			Neutral_move(&fish_whale[i]);
	for (int i = 0; i < whale_count; i++)
		Neutral_eat(&fish_whale[i]);
	for (int i = 0; i < whale_count; i++)
		Neutral_replicate(&fish_whale[i]);
	for (int i = whale_count - 1; i >= 0; --i)
		Neutral_age(&fish_whale[i], i);

	// KILLERWHALE MOVES
	for (int i = 0; i < killerwhale_count; i++)
		for (int j = 0; j < fish_killerwhale[i].get_moves(); j++)
			Aggressive_move(&fish_killerwhale[i]);
	for (int i = 0; i < killerwhale_count; i++)
		Aggressive_eat(&fish_killerwhale[i]);
	for (int i = 0; i < killerwhale_count; i++)
		Aggressive_replicate(&fish_killerwhale[i]);
	for (int i = killerwhale_count - 1; i >= 0; --i)
		Aggressive_age(&fish_killerwhale[i], i);

	// SHARK MOVES
	for (int i = 0; i < shark_count; i++)
		for (int j = 0; j < fish_shark[i].get_moves(); j++)
			Aggressive_move(&fish_shark[i]);
	for (int i = 0; i < shark_count; i++)
		Aggressive_eat(&fish_shark[i]);
	for (int i = 0; i < shark_count; i++)
		Aggressive_replicate(&fish_shark[i]);
	for (int i = shark_count - 1; i >= 0; --i)
		Aggressive_age(&fish_shark[i], i);

	UpdateMap();
	Show();
}

void Ocean_master::Show()
{
	ocean_table->display_field();
}

void Ocean_master::start_random_place(int w_c, int d_c, int k_c, int s_c, int c_c, int f_c, int p_c)
{
	// number of mobs
	for (int i = 1; i <= w_c; i++)
	{
		if (i % 2 != 0)
		{
			Whale fish_whale_obj("Male");
			fish_whale_obj.set_id(whale_number);
			fish_whale.push_back(fish_whale_obj);
		}
		else
		{
			Whale fish_whale_obj("Female");
			fish_whale_obj.set_id(whale_number);
			fish_whale.push_back(fish_whale_obj);
		}
		whale_number++;
	}

	for (int i = 1; i <= d_c; i++)
	{
		if (i % 2 != 0)
		{
			Dolphin fish_dolphin_obj("Male");
			fish_dolphin_obj.set_id(dolphin_number);
			fish_dolphin.push_back(fish_dolphin_obj);
		}
		else
		{
			Dolphin fish_dolphin_obj("Female");
			fish_dolphin_obj.set_id(dolphin_number);
			fish_dolphin.push_back(fish_dolphin_obj);
		}
		dolphin_number++;
	}

	for (int i = 1; i <= k_c; i++)
	{
		if (i % 2 != 0)
		{
			Killerwhale fish_killerwhale_obj("Male");
			fish_killerwhale_obj.set_id(killerwhale_number);
			fish_killerwhale.push_back(fish_killerwhale_obj);
		}
		else
		{
			Killerwhale fish_killerwhale_obj("Female");
			fish_killerwhale_obj.set_id(killerwhale_number);
			fish_killerwhale.push_back(fish_killerwhale_obj);
		}
		killerwhale_number++;
	}

	for (int i = 1; i <= s_c; i++)
	{
		if (i % 2 != 0)
		{
			Shark fish_shark_obj("Male");
			fish_shark_obj.set_id(shark_number);
			fish_shark.push_back(fish_shark_obj);
		}
		else
		{
			Shark fish_shark_obj("Female");
			fish_shark_obj.set_id(shark_number);
			fish_shark.push_back(fish_shark_obj);
		}
		shark_number++;
	}

	for (int i = 1; i <= c_c; i++)
	{
		if (i % 2 != 0)
		{
			Clownfish fish_clownfish_obj("Male");
			fish_clownfish_obj.set_id(clownfish_number);
			fish_clownfish.push_back(fish_clownfish_obj);
		}
		else
		{
			Clownfish fish_clownfish_obj("Female");
			fish_clownfish_obj.set_id(clownfish_number);
			fish_clownfish.push_back(fish_clownfish_obj);
		}
		clownfish_number++;
	}

	for (int i = 0; i < f_c; i++)
	{
		if (i % 2)
		{
			Fugu fish_fugu_obj("Male");
			fish_fugu_obj.set_id(fugu_number);
			fish_fugu.push_back(fish_fugu_obj);
		}
		else
		{
			Fugu fish_fugu_obj("Female");
			fish_fugu_obj.set_id(fugu_number);
			fish_fugu.push_back(fish_fugu_obj);
		}
		fugu_number++;
	}

	for (int i = 0; i < p_c; i++)
	{
		Plankton fish_plankton_obj;
		fish_plankton_obj.set_id(plankton_number);
		plankton_number++;
		fish_plankton.push_back(fish_plankton_obj);
	}

	// start place
	for (int i = 0; i < fish_whale.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_whale[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'W');
	}

	for (int i = 0; i < fish_shark.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_shark[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'S');
	}

	for (int i = 0; i < fish_killerwhale.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_killerwhale[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'K');
	}

	for (int i = 0; i < fish_dolphin.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_dolphin[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'D');
	}

	for (int i = 0; i < fish_fugu.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_fugu[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'F');
	}

	for (int i = 0; i < fish_clownfish.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			fish_clownfish[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'C');
	}

	for (int i = 0; i < fish_plankton.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(1);

		for (int j = 0; j < 3; j++)
			fish_plankton[i].get_location(j) = cell_coords[j];
		ocean_table->put_fish(cell_coords[0], cell_coords[1], cell_coords[2], 'P');
	}

	UpdateMap();
}

void Ocean_master::UpdateMap()
{
	for (int i = 0; i < ocean_table->get_width(); i++)
		for (int j = 0; j < ocean_table->get_height(); j++)
			for (int k = 0; k < 4; k++)
				ocean_table->scene[i][j][k] = ' ';

	for (int i = 0; i < fish_plankton.size(); i++)
		ocean_table->scene[fish_plankton[i].get_location(0)][fish_plankton[i].get_location(1)][fish_plankton[i].get_location(2)] = 'P';
	for (int i = 0; i < fish_clownfish.size(); i++)
		ocean_table->scene[fish_clownfish[i].get_location(0)][fish_clownfish[i].get_location(1)][fish_clownfish[i].get_location(2)] = 'C';
	for (int i = 0; i < fish_fugu.size(); i++)
		ocean_table->scene[fish_fugu[i].get_location(0)][fish_fugu[i].get_location(1)][fish_fugu[i].get_location(2)] = 'F';
	for (int i = 0; i < fish_whale.size(); i++)
		ocean_table->scene[fish_whale[i].get_location(0)][fish_whale[i].get_location(1)][fish_whale[i].get_location(2)] = 'W';
	for (int i = 0; i < fish_killerwhale.size(); i++)
		ocean_table->scene[fish_killerwhale[i].get_location(0)][fish_killerwhale[i].get_location(1)][fish_killerwhale[i].get_location(2)] = 'K';
	for (int i = 0; i < fish_dolphin.size(); i++)
		ocean_table->scene[fish_dolphin[i].get_location(0)][fish_dolphin[i].get_location(1)][fish_dolphin[i].get_location(2)] = 'D';
	for (int i = 0; i < fish_shark.size(); i++)
		ocean_table->scene[fish_shark[i].get_location(0)][fish_shark[i].get_location(1)][fish_shark[i].get_location(2)] = 'S';
}


// PLANKTON PHASE

void Ocean_master::Plankton_move(Plankton* p_obj)
{
	int x = p_obj->get_location(0), y = p_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = ocean_table->get_width(),
		current_height = ocean_table->get_height();

	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 1);
			if (index != -1) // the place is busy
			{
				p_obj->set_location(1, y - 1);
				p_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 1);
			if (index != -1)
			{
				p_obj->set_location(1, y + 1);
				p_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 1);
			if (index != -1)
			{
				p_obj->set_location(0, x + 1);
				p_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 1);
			if (index != -1)
			{
				p_obj->set_location(0, x - 1);
				p_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		variations++;
	}
	ocean_table->scene[p_obj->get_location(0)][p_obj->get_location(1)][p_obj->get_location(2)] = 'P';
}

void Ocean_master::Plankton_replicate(Plankton* p_obj)
{
	int x = p_obj->get_location(0), y = p_obj->get_location(1);
	int direction = rand() % 4 + 1; //1 - up, 2 - down, 3 - right, 4 - left
	int index_plankton, index;
	int current_width = ocean_table->get_width(),
		current_height = ocean_table->get_height(),
		variations = 0;

	// REPLICATING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index_plankton = empty_place(x, y - 1, 1);
			index = empty_place(x, y - 1, 0);
			if (index_plankton != -1) // if there is no plankton in this direction
			{
				Plankton p_child;
				p_child.set_location(0, x);
				p_child.set_location(1, y - 1);
				p_child.set_location(2, index_plankton);
				p_child.set_id(plankton_number);
				plankton_number++;
				fish_plankton.push_back(p_child);
				ocean_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plankton == -1 && index != -1) // if there is plankton in this direction
			{
				for (int i = 0; i < fish_plankton.size(); i++)
					if (fish_plankton[i].get_location(0) == x && fish_plankton[i].get_location(1) == y - 1)
						fish_plankton[i].set_hp(fish_plankton[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 2)
		{
			index_plankton = empty_place(x, y + 1, 1);
			index = empty_place(x, y + 1, 0);
			if (index_plankton != -1) // if there is no plankton in this direction
			{
				Plankton p_child;
				p_child.set_location(0, x);
				p_child.set_location(1, y + 1);
				p_child.set_location(2, index_plankton);
				fish_plankton.push_back(p_child);
				ocean_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plankton == -1 && index != -1) // if there is plankton in this direction
			{
				for (int i = 0; i < fish_plankton.size(); i++)
					if (fish_plankton[i].get_location(0) == x && fish_plankton[i].get_location(1) == y + 1)
						fish_plankton[i].set_hp(fish_plankton[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 3)
		{
			index_plankton = empty_place(x + 1, y, 1);
			index = empty_place(x + 1, y, 0);
			if (index_plankton != -1) // if there is no plankton in this direction
			{
				Plankton p_child;
				p_child.set_location(0, x + 1);
				p_child.set_location(1, y);
				p_child.set_location(2, index_plankton);
				fish_plankton.push_back(p_child);
				ocean_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plankton == -1 && index != -1) // if there is plankton in this direction
			{
				for (int i = 0; i < fish_plankton.size(); i++)
					if (fish_plankton[i].get_location(0) == x + 1 && fish_plankton[i].get_location(1) == y)
						fish_plankton[i].set_hp(fish_plankton[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 4)
		{
			index_plankton = empty_place(x - 1, y, 1);
			index = empty_place(x - 1, y, 0);
			if (index_plankton != -1) // if there is no plankton in this direction
			{
				Plankton p_child;
				p_child.set_location(0, x - 1);
				p_child.set_location(1, y);
				p_child.set_location(2, index_plankton);
				fish_plankton.push_back(p_child);
				ocean_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plankton == -1 && index != -1) // if there is plankton in this direction but the space is ready
			{
				for (int i = 0; i < fish_plankton.size(); i++)
					if (fish_plankton[i].get_location(0) == x - 1 && fish_plankton[i].get_location(1) == y)
						fish_plankton[i].set_hp(fish_plankton[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}
		variations++;
	}
}

void Ocean_master::Plankton_age(Plankton* p_obj, int order)
{
	p_obj->set_age(p_obj->get_age() + 1);
	p_obj->set_hp(p_obj->get_hp() - 1);
	if (p_obj->get_hp() <= 0)
	{
		ocean_table->scene[p_obj->get_location(0)][p_obj->get_location(1)][p_obj->get_location(2)] = ' ';
		fish_plankton.erase(fish_plankton.begin() + order);
	}
}


// PASSIVE PHASE

void Ocean_master::Passive_move(Passive* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = ocean_table->get_width(),
		current_height = ocean_table->get_height();

	if (c_obj->get_food() <= 0.9 * c_obj->get_food_max()) // CHECKING IF THE PASSIVE IS NOT SATURATED
	{
		Plankton p_obj = return_plankton(x, y); 	// CHECKING IF PLANKTON IS RIGHT THERE
		if (p_obj.get_location(0) == x && p_obj.get_location(1) == y)
			return;
	}

	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 0);
			if (index != -1) // the place is busy
			{
				c_obj->set_location(1, y - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 0);
			if (index != -1)
			{
				c_obj->set_location(1, y + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
			{
				direction = rand() % 4 + 1;
			}
		}
		variations++;
	}
	ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = c_obj->get_type();
}

void Ocean_master::Passive_eat(Passive* c_obj)
{
	if (c_obj->get_food() > 0.9 * c_obj->get_food_max())
		return; // if the passive is saturated (not hungry), it will not eat this turn 

	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	Plankton p_obj = return_plankton(x, y);
	int x_plankton = p_obj.get_location(0),
		y_plankton = p_obj.get_location(1);

	if (p_obj.get_location(0) == -1 || p_obj.get_location(1) == -1)
		return;

	if (x_plankton == x && y_plankton == y)
	{
		for (int i = 0; i < fish_plankton.size(); i++)
		{
			if (fish_plankton[i].get_location(0) == x_plankton && fish_plankton[i].get_location(1) == y_plankton)
			{
				c_obj->set_food(c_obj->get_food() + fish_plankton[i].get_hp_max());
				if (c_obj->get_food() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food_max());
				ocean_table->scene[fish_plankton[i].get_location(0)][fish_plankton[i].get_location(1)][fish_plankton[i].get_location(2)] = ' ';
				fish_plankton.erase(fish_plankton.begin() + i);
			} // Killing plankton, replenishing amount of food corresponding to plankton's max hp
		}
	}
}

void Ocean_master::Passive_replicate(Passive* c_obj)
{
	int x1 = c_obj->get_location(0), y1 = c_obj->get_location(1), index = 0;
	int replica_result;

	if (c_obj->get_type() == 'C')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.5)
		{
			for (int i = 0; i < fish_clownfish.size(); i++)
			{
				if (fish_clownfish[i].get_location(0) == x1 && fish_clownfish[i].get_location(1) == y1)
				{
					if (fish_clownfish[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_clownfish[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.3);
							Clownfish c_child("Random");
							c_child.set_id(clownfish_number);
							clownfish_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'C';
							fish_clownfish.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'F')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.5)
		{
			for (int i = 0; i < fish_fugu.size(); i++)
			{
				if (fish_fugu[i].get_location(0) == x1 && fish_fugu[i].get_location(1) == y1)
				{
					if (fish_fugu[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_fugu[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.3);
							Fugu c_child("Random");
							c_child.set_id(fugu_number);
							fugu_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'F';
							fish_fugu.push_back(c_child);
						}
					}
				}
			}
		}
	}
}

void Ocean_master::Passive_age(Passive* c_obj, int order)
{
	c_obj->set_age(c_obj->get_age() + 1);
	c_obj->set_hp(c_obj->get_hp() - 1);
	c_obj->set_food(c_obj->get_food() - 1);

	if (c_obj->get_food() <= 0)
		c_obj->set_hp(c_obj->get_hp() - 3);
	if (c_obj->get_hp() <= 0)
	{
		ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = ' ';
		if (c_obj->get_type() == 'C')
			fish_clownfish.erase(fish_clownfish.begin() + order);
		if (c_obj->get_type() == 'F')
			fish_fugu.erase(fish_fugu.begin() + order);
	}
}


// NEUTRAL PHASE

void Ocean_master::Neutral_move(Neutral* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = ocean_table->get_width(),
		current_height = ocean_table->get_height();

	// CHECKING IF PLANKTON IS RIGHT THERE
	if (c_obj->get_food() <= 0.8 * c_obj->get_food_max())
	{
		Plankton plankton_obj = return_plankton(x, y);
		if (plankton_obj.get_location(0) == x && plankton_obj.get_location(1) == y)
			return;
	}

	// IF THERE IS VERY LITTLE FOOD, NEUTRALS EAT PASSIVES
	if (c_obj->get_food() <= 0.2 * c_obj->get_food_max())
	{
		Clownfish clownfish_obj = return_clownfish(x, y);
		Fugu fugu_obj = return_fugu(x, y);
		if (fugu_obj.get_location(0) == x && fugu_obj.get_location(1) == y)
			return;
		if (clownfish_obj.get_location(0) == x && clownfish_obj.get_location(1) == y)
			return;
	}

	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 0);
			if (index != -1) // the place is busy
			{
				c_obj->set_location(1, y - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 0);
			if (index != -1)
			{
				c_obj->set_location(1, y + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		variations++;
	}
	ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = c_obj->get_type();
}

void Ocean_master::Neutral_eat(Neutral* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;

	if (c_obj->get_food() <= 0.8 * c_obj->get_food_max())
	{
		Plankton plankton_obj = return_plankton(x, y);
		int x_plankton = plankton_obj.get_location(0), y_plankton = plankton_obj.get_location(1);

		if (x_plankton == x && y_plankton == y)
		{
			c_obj->set_food(c_obj->get_food() + plankton_obj.get_hp_max());
			if (c_obj->get_food() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food_max());
			ocean_table->scene[x_plankton][y_plankton][plankton_obj.get_location(2)] = ' ';
			for (int i = 0; i < fish_plankton.size(); i++)
			{
				if (fish_plankton[i].get_location(0) == x_plankton && fish_plankton[i].get_location(1) == y_plankton)
				{
					fish_plankton.erase(fish_plankton.begin() + i);
					return;
				}
			}
			// Killing plankton, replenishing amount of food corresponding to plankton's max hp, 	
		}
	}

	// IF THERE IS VERY LITTLE FOOD, NEUTRALS EAT PASSIVES
	if (c_obj->get_food() <= 0.2 * c_obj->get_food_max())
	{
		Clownfish clownfish_obj = return_clownfish(x, y);
		Fugu fugu_obj = return_fugu(x, y);
		int x_clownfish = clownfish_obj.get_location(0), y_clownfish = clownfish_obj.get_location(1);
		int x_fugu = fugu_obj.get_location(0), y_fugu = fugu_obj.get_location(1);

		if (x_clownfish == x && y_clownfish == y)
		{
			c_obj->set_food(c_obj->get_food() + clownfish_obj.get_hp_max());
			if (c_obj->get_food() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food_max());
			ocean_table->scene[x_clownfish][y_clownfish][clownfish_obj.get_location(2)] = ' ';
			for (int i = 0; i < fish_clownfish.size(); i++)
			{
				if (fish_clownfish[i].get_location(0) == x_clownfish && fish_clownfish[i].get_location(1) == y_clownfish)
				{
					fish_clownfish.erase(fish_clownfish.begin() + i);
					return;
				}
			}
		}

		if (x_fugu == x && y_fugu == y)
		{
			c_obj->set_food(c_obj->get_food() + fugu_obj.get_hp_max());
			if (c_obj->get_food() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food_max());
			c_obj->set_hp(c_obj->get_hp() - 20);
			ocean_table->scene[x_fugu][y_fugu][fugu_obj.get_location(2)] = ' ';
			for (int i = 0; i < fish_fugu.size(); i++)
			{
				if (fish_fugu[i].get_location(0) == x_fugu && fish_fugu[i].get_location(1) == y_fugu)
				{
					fish_fugu.erase(fish_fugu.begin() + i);
					return;
				}
			}
		}
	}
}

void Ocean_master::Neutral_replicate(Neutral* c_obj)
{
	if (c_obj->get_hp() <= 0)
		return;

	int x1 = c_obj->get_location(0), y1 = c_obj->get_location(1), index = 0;
	int replica_result;

	if (c_obj->get_type() == 'D')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.8)
		{
			for (int i = 0; i < fish_dolphin.size(); i++)
			{
				if (fish_dolphin[i].get_location(0) == x1 && fish_dolphin[i].get_location(1) == y1)
				{
					if (fish_dolphin[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_dolphin[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.5);
							Dolphin c_child("Random");
							c_child.set_id(dolphin_number);
							dolphin_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'D';
							fish_dolphin.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'W')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.9)
		{
			for (int i = 0; i < fish_whale.size(); i++)
			{
				if (fish_whale[i].get_location(0) == x1 && fish_whale[i].get_location(1) == y1)
				{
					if (fish_whale[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_whale[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.6);
							Whale c_child("Random");
							c_child.set_id(whale_number);
							whale_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'W';
							fish_whale.push_back(c_child);
						}
					}
				}
			}
		}
	}
}

void Ocean_master::Neutral_age(Neutral* c_obj, int order)
{
	c_obj->set_age(c_obj->get_age() + 1);
	c_obj->set_hp(c_obj->get_hp() - 1);
	c_obj->set_food(c_obj->get_food() - 1);

	if (c_obj->get_food() <= 0)
		c_obj->set_hp(c_obj->get_hp() - 3);
	if (c_obj->get_hp() <= 0)
	{
		ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = ' ';
		if (c_obj->get_type() == 'D')
			fish_dolphin.erase(fish_dolphin.begin() + order);
		if (c_obj->get_type() == 'W')
			fish_whale.erase(fish_whale.begin() + order);
	}
}


// AGGRESSIVE PHASE

void Ocean_master::Aggressive_move(Aggressive* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = ocean_table->get_width(),
		current_height = ocean_table->get_height();

	if (c_obj->get_food() <= 0.4 * c_obj->get_food_max())
	{
		Dolphin dolphin_obj = return_dolphin(x, y);
		Whale whale_obj = return_whale(x, y);
		if (dolphin_obj.get_location(0) == x && dolphin_obj.get_location(1) == y)
			return;
		if (whale_obj.get_location(0) == x && whale_obj.get_location(1) == y)
			return;
	}

	if (c_obj->get_food() <= 0.8 * c_obj->get_food_max())
	{
		Clownfish clownfish_obj = return_clownfish(x, y);
		Fugu fugu_obj = return_fugu(x, y);
		if (fugu_obj.get_location(0) == x && fugu_obj.get_location(1) == y)
			return;
		if (clownfish_obj.get_location(0) == x && clownfish_obj.get_location(1) == y)
			return;
	}


	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 0);
			if (index != -1) // the place is busy
			{
				c_obj->set_location(1, y - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 0);
			if (index != -1)
			{
				c_obj->set_location(1, y + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		variations++;
	}
	ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = c_obj->get_type();
}

void Ocean_master::Aggressive_eat(Aggressive* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;

	// ATTACK NEUTRAL
	if (c_obj->get_food() <= 0.4 * c_obj->get_food_max())
	{
		Dolphin dolphin_obj = return_dolphin(x, y);
		Whale whale_obj = return_whale(x, y);
		int x_dolphin = dolphin_obj.get_location(0), y_dolphin = dolphin_obj.get_location(1);
		int x_whale = whale_obj.get_location(0), y_whale = whale_obj.get_location(1);

		if (x_dolphin == x && y_dolphin == y)
		{
			if (c_obj->get_damage() >= dolphin_obj.get_hp())	// KILLING DOLPHIN
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				ocean_table->scene[x_dolphin][y_dolphin][dolphin_obj.get_location(2)] = ' ';
				for (int i = 0; i < fish_dolphin.size(); i++)
				{
					if (fish_dolphin[i].get_location(0) == x_dolphin && fish_dolphin[i].get_location(1) == y_dolphin)
					{
						fish_dolphin.erase(fish_dolphin.begin() + i);
						return;
					}
				}
			}
			else                                   // DAMAGE DOLPHIN
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				for (int i = 0; i < fish_dolphin.size(); i++)
				{
					if (fish_dolphin[i].get_location(0) == x_dolphin && fish_dolphin[i].get_location(1) == y_dolphin)
					{
						fish_dolphin[i].set_hp(fish_dolphin[i].get_hp() - c_obj->get_damage());
						return;
					}
				}
			}
		}
		if (x_whale == x && y_whale == y)
		{
			if (c_obj->get_damage() >= whale_obj.get_hp())	// KILLING WHALE
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				ocean_table->scene[x_whale][y_whale][whale_obj.get_location(2)] = ' ';
				for (int i = 0; i < fish_whale.size(); i++)
				{
					if (fish_whale[i].get_location(0) == x_whale && fish_whale[i].get_location(1) == y_whale)
					{
						fish_whale.erase(fish_whale.begin() + i);
						return;
					}
				}
			}
			else                                   // DAMAGE WHALE
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				for (int i = 0; i < fish_whale.size(); i++)
				{
					if (fish_whale[i].get_location(0) == x_whale && fish_whale[i].get_location(1) == y_whale)
					{
						fish_whale[i].set_hp(fish_whale[i].get_hp() - c_obj->get_damage());
						return;
					}
				}
			}
		}
	}

	// EAT PASSIVE
	if (c_obj->get_food() <= 0.8 * c_obj->get_food_max())
	{
		Clownfish clownfish_obj = return_clownfish(x, y);
		Fugu fugu_obj = return_fugu(x, y);
		int x_clownfish = clownfish_obj.get_location(0), y_clownfish = clownfish_obj.get_location(1);
		int x_fugu = fugu_obj.get_location(0), y_fugu = fugu_obj.get_location(1);

		if (x_clownfish == x && y_clownfish == y)
		{
			if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
			else
				c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
			ocean_table->scene[x_clownfish][y_clownfish][clownfish_obj.get_location(2)] = ' ';
			for (int i = 0; i < fish_clownfish.size(); i++)
			{
				if (fish_clownfish[i].get_location(0) == x_clownfish && fish_clownfish[i].get_location(1) == y_clownfish)
				{
					fish_clownfish.erase(fish_clownfish.begin() + i);
					return;
				}
			}
		}

		if (x_fugu == x && y_fugu == y)
		{
			if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
			else
				c_obj->set_food(c_obj->get_food() + c_obj->get_damage());

			if (c_obj->get_type() != 'S')
				c_obj->set_hp(c_obj->get_hp() - 20);

			ocean_table->scene[x_fugu][y_fugu][fugu_obj.get_location(2)] = ' ';
			for (int i = 0; i < fish_fugu.size(); i++)
			{
				if (fish_fugu[i].get_location(0) == x_fugu && fish_fugu[i].get_location(1) == y_fugu)
				{
					fish_fugu.erase(fish_fugu.begin() + i);
					return;
				}
			}
		}
	}
}

void Ocean_master::Aggressive_replicate(Aggressive* c_obj)
{
	if (c_obj->get_hp() <= 0)
		return;

	int x1 = c_obj->get_location(0), y1 = c_obj->get_location(1), index = 0;
	int replica_result;

	if (c_obj->get_type() == 'S')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.9)
		{
			for (int i = 0; i < fish_shark.size(); i++)
			{
				if (fish_shark[i].get_location(0) == x1 && fish_shark[i].get_location(1) == y1)
				{
					if (fish_shark[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_shark[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.5);
							Shark c_child("Random");
							c_child.set_id(shark_number);
							shark_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'D';
							fish_shark.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'K')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.9)
		{
			for (int i = 0; i < fish_killerwhale.size(); i++)
			{
				if (fish_killerwhale[i].get_location(0) == x1 && fish_killerwhale[i].get_location(1) == y1)
				{
					if (fish_killerwhale[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == fish_killerwhale[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.6);
							Killerwhale c_child("Random");
							c_child.set_id(killerwhale_number);
							killerwhale_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							ocean_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'W';
							fish_killerwhale.push_back(c_child);
						}
					}
				}
			}
		}
	}
}

void Ocean_master::Aggressive_age(Aggressive* c_obj, int order)
{
	c_obj->set_age(c_obj->get_age() + 1);
	c_obj->set_hp(c_obj->get_hp() - 1);
	c_obj->set_food(c_obj->get_food() - 1);

	if (c_obj->get_food() <= 0)
		c_obj->set_hp(c_obj->get_hp() - 3);
	if (c_obj->get_hp() <= 0)
	{
		ocean_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = ' ';
		if (c_obj->get_type() == 'S')
			fish_shark.erase(fish_shark.begin() + order);
		if (c_obj->get_type() == 'K')
			fish_killerwhale.erase(fish_killerwhale.begin() + order);
	}
}


// UTILITY

Plankton& Ocean_master::return_plankton(int x1, int y1)
{
	for (int i = 0; i < fish_plankton.size(); i++)
		if (fish_plankton[i].get_location(0) == x1 && fish_plankton[i].get_location(1) == y1)
			return fish_plankton[i];
	p_extra->set_location(0, -1);
	p_extra->set_location(1, -1);
	p_extra->set_location(2, -1);
	return *p_extra;
}

Clownfish& Ocean_master::return_clownfish(int x1, int y1)
{
	for (int i = 0; i < fish_clownfish.size(); i++)
		if (fish_clownfish[i].get_location(0) == x1 && fish_clownfish[i].get_location(1) == y1)
			return fish_clownfish[i];
	cl_extra->set_location(0, -1);
	cl_extra->set_location(1, -1);
	cl_extra->set_location(2, -1);
	return *cl_extra;
}

Fugu& Ocean_master::return_fugu(int x1, int y1)
{
	for (int i = 0; i < fish_fugu.size(); i++)
		if (fish_fugu[i].get_location(0) == x1 && fish_fugu[i].get_location(1) == y1)
			return fish_fugu[i];
	f_extra->set_location(0, -1);
	f_extra->set_location(1, -1);
	f_extra->set_location(2, -1);
	return *f_extra;
}

Dolphin& Ocean_master::return_dolphin(int x1, int y1)
{
	for (int i = 0; i < fish_dolphin.size(); i++)
		if (fish_dolphin[i].get_location(0) == x1 && fish_dolphin[i].get_location(1) == y1)
			return fish_dolphin[i];
	d_extra->set_location(0, -1);
	d_extra->set_location(1, -1);
	d_extra->set_location(2, -1);
	return *d_extra;
}

Whale& Ocean_master::return_whale(int x1, int y1)
{
	for (int i = 0; i < fish_whale.size(); i++)
		if (fish_whale[i].get_location(0) == x1 && fish_whale[i].get_location(1) == y1)
			return fish_whale[i];
	w_extra->set_location(0, -1);
	w_extra->set_location(1, -1);
	w_extra->set_location(2, -1);
	return *w_extra;
}

int Ocean_master::empty_place(int x1, int y1, bool isPlankton)
{
	if (x1 < 0 || y1 < 0 || x1 >= ocean_table->get_width() || y1 >= ocean_table->get_height())
		return -1;
	if (isPlankton)			// only 1 plankton per 1 cell
		for (int i = 0; i < fish_plankton.size(); i++)
			if (fish_plankton[i].get_location(0) == x1 && fish_plankton[i].get_location(1) == y1)
				return -1;
	for (int i = 0; i < 4; i++)
		if (ocean_table->scene[x1][y1][i] == ' ')
			return i;
	return -1;
}