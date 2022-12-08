#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

class Area
{
public:
	vector<vector<vector<char>>> area;
	int width, height;
	Area(int w_input, int h_input)
	{
		width = w_input;
		height = h_input;
		for (int i = 0; i < width; i++)
		{
			vector<vector<char>> temp_j;
			for (int j = 0; j < height; j++)
			{
				vector<char> temp_k;
				for (int k = 0; k < 4; k++)
				{
					temp_k.push_back(' ');
				}
				temp_j.push_back(temp_k);
			}
			area.push_back(temp_j);
		}
	}

	void put_fish(int X, int Y, int Z, char fish)
	{
		area[X][Y][Z] = fish;
	}
};

class Fish
{
protected:
	char type;
	int age = 0, id, hp, m_age, m_hp, food, m_food, moves;
public:
	vector<int> location = { -1, -1, -1 };
	char get_type()
	{
		return type;
	}
	int get_age()
	{
		return age;
	}
	int get_m_age()
	{
		return m_age;
	}
	int get_id()
	{
		return id;
	}
	int get_hp()
	{
		return hp;
	}
	int get_m_hp()
	{
		return m_hp;
	}
	int get_food()
	{
		return food;
	}
	int get_m_food()
	{
		return m_food;
	}
	int get_moves()
	{
		return moves;
	}
	void set_type(char input_type)
	{
		this->type = input_type;
	}
	void set_age(int input_age)
	{
		this->age = input_age;
	}
	void set_id(int input_id)
	{
		this->id = input_id;
	}
	void set_hp(int input_hp)
	{
		this->hp = input_hp;
	}
	void set_food(int input_food)
	{
		this->food = input_food;
	}
};

class Plankton : public Fish
{
public:
	Plankton()
	{
		m_hp = 10;
		hp = m_hp;
		moves = 1;
		m_age = 10;
		type = 'P';
	}
};

class Predator : public Fish
{
public:
	bool is_male;
	bool get_is_male() { return is_male; }
};

class Herring : public Predator
{
public:
	Herring(string jins)
	{
		m_hp = 20; 
		hp = m_hp;
		m_food = 15; 
		food = m_food;
		moves = 2;
		m_age = 20;
		type = 'H';
		if (jins == "Male")
			is_male = true;
		if (jins == "Female")
			is_male = false;
		if (jins == "Random")
			is_male = rand() % 2;
	}
};

class Shark : public Predator
{
public:
	Shark(string jins)
	{
		m_hp = 35;
		hp = m_hp;
		m_food = 30;
		food = m_food;
		moves = 4;
		m_age = 60;
		type = 'S';
		if (jins == "Male")
			is_male = true;
		if (jins == "Female")
			is_male = false;
		if (jins == "Random")
			is_male = rand() % 2;
	}
};

class Whale : public Predator
{
public:
	Whale(string jins)
	{
		m_hp = 55;
		hp = m_hp;
		m_food = 40;
		food = m_food;
		moves = 3;
		m_age = 100;
		type = 'W';
		if (jins == "Male")
			is_male = true;
		if (jins == "Female")
			is_male = false;
		if (jins == "Random")
			is_male = rand() % 2;
	}
};

class Ocean_master
{
	Area* ocean_table;

	vector<Whale> whales;
	int whale_number;
	vector<Shark> sharks;
	int shark_number;
	vector<Herring> herrings;
	int herring_number;
	vector<Plankton> planktons;
	int plankton_number;

public:
	void Create_vector(int whale_amount, int shark_amount, int herring_amount, int plankton_amount);
	void Get_coordinates(bool plankton, vector<int>& coordinates);
	void Plankton_replicate(Plankton* p_obj, bool& success);
	void Herring_eat(Herring* c_obj);
	void Whale_eat(Whale* c_obj);
	void Shark_eat(Shark* c_obj);
	int empty_place(int x, int y, bool isPlankton);
	template<typename T> void Fish_move(T* org, bool plankton);
	template<typename T>void First_location(char type, vector<T>& fish);
	template<typename T> void Moving(T* org, int x, int y, bool plankton);
	void Place_planktons_child(int new_x, int new_y, bool& success);

	template<typename T> void Predator_replicate(T* predator, vector<T>& predators, int& fish_number);
	template<typename T> void Death(T* org, int index, vector<T>& fish, bool plankton);


	Ocean_master(int width_input, int height_input)
	{
		srand(time(0));
		ocean_table = new Area(width_input, height_input);
		whale_number = 0;
		shark_number = 0;
		herring_number = 0;
		plankton_number = 0;
	}

	void Beginning(int whale_amount, int shark_amount, int herring_amount, int plankton_amount);

	void Move();

	void Show();

	void UpdateMap();
};
