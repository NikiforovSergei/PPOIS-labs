#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
/*
	\Krestiki_noliki A class that represents an implementation of the Tic-Tac-Toe game

	This class has a full set of functions necessary for a full and comfortable game: the choice of field sizes, the ability to set a symbol,
checking the input of all values ​​that are set by the user, as well as checking the victory of one of the parties
*/
class krestiki_noliki {
private:
	vector <vector<string>> field_p;
	vector<string> temp;
	string position;
	char x;
	int x_length_p, y_length_p, position_x, position_y;
public:
	void SetLength(int x_length_, int y_length_);
	/* Sets the size of the playing field
		\param[x_length] x_length The size of the playing field horizontally
		\param[y_length] y_length The size of the playing field vertical
	*/
	void InputTypeCheck(int* y_pos, int* x_pos);
	/* Checking the input data type
	   \param[y_pos] position_y The horizontal coordinates of the cell in which you want to set the cross
		\param[x_pos] position_x The vertical coordinates of the cell in which you want to set the cross
	*/
	void correct_input(int* y_pos, int* x_pos, int x_length, int y_length);
	/* Getting data from the user and checking the cell
		\param[y_pos] position_y Horizontal coordinates of the cell where the cross should be placed
		\param[x_pos] position_x Vertical coordinates of the cell where the cross should be placed
		\param[x_length] x_length Horizontal size of the playing field
		\param[y_length] y_length Vertical size of the playing field
	*/
	void init(int x_length, int y_length);
	/* Match initialization, playing field creation
		\param[x_length] x_length Horizontal size of the playing field
		\param[y_length] y_length Vertical size of the playing field
	*/
	void paint(int x_length, int y_length);
	/* Displaying the current state of the playing field on the screen
		\param[x_length] x_length Horizontal size of the playing field
		\param[y_length] y_length Vertical size of the playing field
	*/
	void check_win(bool* check, int x_length, int y_length);
	/* Checking for the victory of one of the parties
		\param[check] check victory status indicator (0 - neither side wins, 1 - one side wins)
		\param[x_length] x_length Horizontal size of the playing field
		\param[y_length] y_length Vertical size of the playing field
	*/
	int turn_cross(int x_length, int y_length);
	/* Checking the progress of the crosses
		\param[x_length] x_length Horizontal size of the playing field
	\param[y_length] y_length Vertical size of the playing field
	*/
	void place_cross(int position_y, int position_x, int x_length, int y_length);
	/* 
		Setting the cross to the specified position
		\param[position_y] position_y Horizontal coordinates of the cell where the cross should be placed
		\param[position_x] position_x Vertical coordinates of the cell where the cross should be placed
		\param[x_length] x_length Horizontal size of the playing field
		\param[y_length] y_length Vertical size of the playing field
	*/
	int GetLength(int x_length, int y_length);
	/* Getting values ​​for the size of the playing field
\		param[x_length] x_length Horizontal size of the playing field
\		param[y_length] y_length Vertical size of the playing field
	*/
	void input_error(int* y_pos, int* x_pos, int x_length, int y_length);
	/* Displaying an error about incorrect input and prompting for re-entry
\		param[y_pos] position_y Horizontal coordinates of the cell where the cross should be placed
\		param[x_pos] position_x Vertical coordinates of the cell where the cross should be placed
\		param[x_length] x_length Horizontal size of the playing field
\		param[y_length] y_length Vertical size of the playing field
	*/
	int turn_zero(int x_length, int y_length);
	/* Zero travel checks
\		param[x_length] x_length Horizontal size of the playing field
\		param[y_length] y_length Vertical size of the playing field
	*/
	void place_zero(int position_y, int position_x, int x_length, int y_length);
	/* Setting the zero to the specified position
\		param[position_y] position_y Horizontal coordinates of the cell in which you want to set the zero
\		param[position_x] position_x Vertical coordinates of the cell in which you want to set the zero
\		param[x_length] x_length Horizontal size of the playing field
\		param[y_length] y_length Vertical size of the playing field
	*/
	const void operator() (const double num1, const double num2); //Overload
};
