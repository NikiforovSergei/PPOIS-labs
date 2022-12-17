#include"Header.h"
#include<vector>
#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;



	///Constructor
	game_field::game_field(vector<vector<int>> _data) { data = _data; };

	/// Method to move the cell to the left
	void game_field::Move_left() { 
		for(int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++)
				if (data[i][j] == 0 && j < 3) {
					data[i][j] = data[i][j+1];
					data[i][j + 1] = 0;
					return;

				}

	} 

	/// Method to move the cell to the right
	void game_field::Move_right() { 
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (data[i][j] == 0 && j > 0) {
					data[i][j] = data[i][j - 1];
					data[i][j - 1] = 0;
					return;

				}

	} 

	/// Method to move the cell up
	void game_field::Move_up() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (data[i][j] == 0 && i <3) {
					data[i][j] = data[i+1][j];
					data[i+1][j] = 0;
					return;
				}

	} 

	/// Method to move the cell down
	void game_field::Move_down() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (data[i][j] == 0 && i >0) {
					data[i][j] = data[i-1][j];
					data[i-1][j] = 0;
					return;
				}

	}

	/// Method to display the field on the screen
	void game_field::Screen() {
		system("cls");
		cout << "Press the space bar to get the cell value in the specified coordinates;" << endl;
		cout << "Controls - Arrows. To finish the game, press escape" << endl << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (data[i][j] == 0) cout << "**" << ' ';
				else if (data[i][j] < 10) cout << '0' << data[i][j] << ' ';
				else cout << data[i][j] << ' ';

			}
			cout << endl << endl;
		}

	}
	
	/// Method that return field data
	vector<vector<int>> game_field::Get_data() { return data; };

	int game_field::operator()(int i, int j) { return data[i][j]; };

	/// Destructor
	game_field::~game_field() {};



/// Function that builds a winning field
vector<vector<int>> Build_right_field() {
	vector <vector <int>> field(4, vector <int>(4));
	int temp = 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			field[i][j] = temp;
			temp++;
	}
	field[3][3] = 0;

	return field;
}


/// Function that builds a random field
vector<vector<int>> Build_game_field() {
	srand(time(NULL));
	vector <vector <int>> field(4, vector <int>(4));
	vector<int> temp;
	int a;

	while (temp.size() != 16) {

		a = rand() % 16;

		if (find(temp.begin(), temp.end(), a) == temp.end())
			temp.push_back(a);
	}

	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			field[i][j] = temp[0];
			temp.erase(temp.begin());
		}

	return field;
}

void Return_value(game_field Field) {
	cout << "Enter the coordinates(x y): ";
	int i, j; cin >> i >> j;
	
	cout << "Cell value in x, y coordinates: " << Field(i - 1, j - 1) << endl;
	cout << "Press any key to continue the game..."; _getch();
}
