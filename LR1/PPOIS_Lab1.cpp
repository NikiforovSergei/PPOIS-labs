#include<iostream>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include"Header.h"
using namespace std;




int main() {
	game_field right_field(Build_right_field()); /// Right field
	game_field game_field1(Build_game_field()); /// Gaming(random generated) field 
	int key_code;

	do {
		

		game_field1.Screen();
		key_code = _getch();

		switch (key_code) {
			///UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
		case 72:
			game_field1.Move_up(); break;
		case 80:
			game_field1.Move_down(); break;
		case 77:
			game_field1.Move_right(); break;
		case 75:
			game_field1.Move_left(); break;
		case 32:
			Return_value(game_field1); break;
		case 27:
			return 0;
		}

	} while (right_field.Get_data() != game_field1.Get_data()); ///check(is the field correct)


	return 0;
}