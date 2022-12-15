#include "Game.h"

void krestiki_noliki::SetLength(int x_length, int y_length) {
	cin >> x_length >> y_length;
	x_length_p = x_length;
	y_length_p = y_length;
}
int krestiki_noliki::GetLength(int x_length, int y_length) {
	x_length = x_length_p;
	y_length = y_length_p;
	return x_length, y_length;
}
void krestiki_noliki::init(int x_length, int y_length) {
	cout << "vvedite correct size polya";
	SetLength(x_length, y_length);
	x_length = GetLength(x_length, y_length);
	y_length = GetLength(x_length, y_length);
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		system("clear");
		init(x_length, y_length);
	}
	for (size_t i = 0; i < x_length; ++i)
	{
		for (size_t j = 0; j < y_length; ++j)
		{
			temp.push_back("-");
		}
		field_p.push_back(temp);
		temp.clear();
	}
}
void krestiki_noliki::paint(int x_length, int y_length) {
	for (size_t i = 0; i < x_length; ++i)
	{
		for (size_t j = 0; j < y_length; ++j)
		{
			cout << field_p[i][j] << " ";
		}
		cout << endl;
	}
}
void krestiki_noliki::check_win(bool* check, int x_length, int y_length) {
	x_length, y_length = GetLength(x_length, y_length);
	for (size_t i = 0; i < x_length; ++i)
	{
		for (size_t j = 0; j < y_length; ++j) {
			if ((field_p[i][j] == "X" || field_p[i][j] == "O"))
			{
				if (j != 0 && j != x_length - 1)
				{
					if (field_p[i][j] == field_p[i][j - 1] && field_p[i][j] == field_p[i][j + 1])
					{
						cout << endl << "Win " << field_p[i][j];
						*check = true;
					}
				}
				if (i != 0 && i != y_length - 1) 
				{
					if (field_p[i][j] == field_p[i - 1][j] && field_p[i][j] == field_p[i + 1][j])
					{
						cout << endl << "Win " << field_p[i][j];
						*check = true;
					}
				}
				if (i != 0 && j != 0 && i != y_length - 1 && j != x_length - 1)
				{
					if (field_p[i][j] == field_p[i - 1][j - 1] && field_p[i][j] == field_p[i + 1][j + 1]) // crush
					{
						cout << endl << "Win " << field_p[i][j];
						*check = true;
					}
				}
				if (i != 0 && j != 0 && i != y_length - 1 && j != x_length - 1) 
				{
					if (field_p[i][j] == field_p[i - 1][j + 1] && field_p[i][j] == field_p[i + 1][j - 1])
					{
						cout << endl << "Win " << field_p[i][j];
						*check = true;
					}
				}
			}
		}
	}
}
int krestiki_noliki::turn_cross(int x_length, int y_length) {
	cout << "seichas xod igroka isp krestiki" << endl << "vvedite pizition na kotoryu xotite poxodit";
	correct_input(&position_y, &position_x, x_length, y_length);
	place_cross(position_y, position_x, x_length, y_length);
	system("clear");
	paint(x_length, y_length);
	return 2;
}
void krestiki_noliki::place_cross(int position_y, int position_x, int x_length, int y_length) {
	field_p[position_y - 1][position_x - 1] = "X";
}
int krestiki_noliki::turn_zero(int x_length, int y_length) {
	cout << "Now it's the player's turn using the zeroes" << endl << "Enter the position you want to be";
	correct_input(&position_y, &position_x, x_length, y_length);
	field_p[position_y - 1][position_x - 1] = "O";
	system("clear");
	paint(x_length, y_length);
	return 1;
}
void krestiki_noliki::place_zero(int position_y, int position_x, int x_length, int y_length) {
	field_p[position_y - 1][position_x - 1] = "O";
}
void krestiki_noliki::input_error(int* y_pos, int* x_pos, int x_length, int y_length) {
	system("clear");
	paint(x_length, y_length);
	cout << "Enter a valid move position" << endl;
	correct_input(&position_y, &position_x, x_length, y_length);
}
void krestiki_noliki::InputTypeCheck(int* y_pos, int* x_pos) {
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
	}
}
void krestiki_noliki::correct_input(int* y_pos, int* x_pos, int x_length, int y_length) {
	cin >> position_y >> position_x;
	InputTypeCheck(&position_y, &position_x);
	if (0 < position_y && position_y <= y_length && 0 < position_x && position_x <= x_length && field_p[position_y - 1][position_x - 1] == "-")
	{
		paint(x_length, y_length);
		exit;
	}
	else
	{
		input_error(&position_y, &position_x, x_length, y_length);
	}
}
const void krestiki_noliki::operator()(const double num1, const double num2)
{
	cout << field_p[num1][num2] << endl;	
}