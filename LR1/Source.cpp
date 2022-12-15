#include <iostream>
#include "Game.h"

int main() {
	setlocale(LC_ALL, "Russian");
	bool win = 0;
	int turn_count = 1, game_variation = 1, x_length = 0, y_length = 0;
	krestiki_noliki match;
	match.init(x_length, y_length);
	x_length = match.GetLength(x_length, y_length);
	y_length = match.GetLength(x_length, y_length);
	match.paint(x_length, y_length);
	while (win == 0) {
		switch (game_variation)
		{
		case 1:
			if (turn_count == 1)
			{
				turn_count = match.turn_cross(x_length, y_length);
				match.check_win(&win, x_length, y_length);
				if (win == true)
				{
					break;
				}
			}
			if (turn_count == 2) {
				turn_count = match.turn_zero(x_length, y_length);
				match.check_win(&win, x_length, y_length);
			}
			break;
		}
	}
	cout << "check" << endl;
	int s1 =0 , s2 = 0;
	cin >> s1;
	cin >> s2;
		match(s1, s2);
	return 0;
}