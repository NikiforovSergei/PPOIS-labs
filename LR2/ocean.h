#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

class Field
{
public:
	vector<vector<vector<char>>> field;
	int width, height;
	Field(int w_inp, int h_inp)
	{
		width = w_inp;
		height = h_inp;
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
			field.push_back(temp_j);
		}
	}

	void put_fish(int X, int Y, int Z, char fish)
	{
		field[X][Y][Z] = fish;
	}
};

class Fish
{
protected:
	char type;
	int age = 0, id, hp, max_age, max_hp, food, max_food, moves;
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
	int get_max_age()
	{
		return max_age;
	}
	int get_id()
	{
		return id;
	}
	int get_hp()
	{
		return hp;
	}
	int get_hp_max()
	{
		return max_hp;
	}
	int get_food()
	{
		return food;
	}
	int get_food_max()
	{
		return max_food;
	}
	int get_moves()
	{
		return moves;
	}
	void set_type(char inp_type)
	{
		this->type = inp_type;
	}
	void set_age(int inp_age)
	{
		this->age = inp_age;
	}
	void set_id(int inp_id)
	{
		this->id = inp_id;
	}
	void set_hp(int inp_hp)
	{
		this->hp = inp_hp;
	}
	void set_food(int inp_food)
	{
		this->food = inp_food;
	}
};

class Plankton : public Fish
{
public:
	Plankton()
	{
		max_hp = 5;
		hp = max_hp;
		moves = 1;
		max_age = 10;
		type = 'P';
	}
};

class Predator : public Fish
{
public:
	bool isMale;
	bool get_isMale() { return isMale; }
};

class Herring : public Predator
{
public:
	Herring(string sex)
	{
		max_hp = 15; hp = max_hp;
		max_food = 10; food = max_food;
		moves = 2;
		max_age = 20;
		type = 'H';
		if (sex == "Male")
			isMale = true;
		if (sex == "Female")
			isMale = false;
		if (sex == "Random")
			isMale = rand() % 2;
	}
};

class Shark : public Predator
{
public:
	Shark(string sex)
	{
		max_hp = 30;
		hp = max_hp;
		max_food = 25;
		food = max_food;
		moves = 3;
		max_age = 60;
		type = 'S';
		if (sex == "Male")
			isMale = true;
		if (sex == "Female")
			isMale = false;
		if (sex == "Random")
			isMale = rand() % 2;
	}
};

class Whale : public Predator
{
public:
	Whale(string sex)
	{
		max_hp = 50;
		hp = max_hp;
		max_food = 40;
		food = max_food;
		moves = 2;
		max_age = 100;
		type = 'W';
		if (sex == "Male")
			isMale = true;
		if (sex == "Female")
			isMale = false;
		if (sex == "Random")
			isMale = rand() % 2;
	}
};

class Ocean_master
{
	Field* ocean_table;

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
	template<typename T>void Start_location(char type, vector<T>& fish);
	template<typename T> void Moving(T* org, int x, int y, bool plankton);
	void Place_planktons_child(int new_x, int new_y, bool& success);

	template<typename T> void Predator_replicate(T* predator, vector<T>& predators, int& fish_number);
	template<typename T> void Death(T* org, int index, vector<T>& fish, bool plankton);


	Ocean_master(int width_inp, int height_inp)
	{
		srand(time(0));
		ocean_table = new Field(width_inp, height_inp);
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