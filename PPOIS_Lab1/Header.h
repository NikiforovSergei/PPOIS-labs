#pragma once

#include<iostream>
#include<vector>
using namespace std;


class game_field {
private:
	vector<vector<int>> data;
public:
	game_field(vector<vector<int>>);
	void Screen();
	void Move_left();
	void Move_right();
	void Move_up();
	void Move_down();
	int operator()(int, int);
	~game_field();
	vector<vector<int>> Get_data();
};

void Return_value(game_field);
vector<vector<int>> Build_right_field();
vector<vector<int>> Build_game_field();

