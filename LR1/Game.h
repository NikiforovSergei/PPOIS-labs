/**
* @file
* @brief Game class header file.
* 
* Contains function and member variable declarations.
*/
#pragma once
#include<iostream>

enum Direction {UP, RIGHT, DOWN, LEFT }; ///< Enumerator containing all the possible directions in clockwise order.

using namespace std;

class Game
{
private: 
	/**@privatesection*/
	int cells[4][4];
	bool move(int x, int y, Direction dir);
	bool solvable();/**<
	@return true if the puzzle is solvable, false otherwise.
	*/
public:
	/**@publicsection*/
	Game(); ///< Default constructor.
	Game(const Game& obj); ///< Copy constructor

	bool move(int val, Direction dir); /**< 
	Attemps to move a cell value to the new location. 
	
	@param val Cell value to move.
	@param dir Direction to move the cell value.

	@return true if the movement was sucessfull, false otherwise.*/
	
	bool solved(); /**< 
	@return true if the puzzle is solved, false otherwise.*/
	
	void draw(); /**< 
	Draws the puzzle state in console.*/

	int blank_line(); /**<
	@return The line number where the blank space is, countring from the bottom.*/

	int get_invertions(); /**<
	@return The number of every possible invertions in the puzzle.*/

	static Direction ctod(char ch); /**<
	@param ch Character representation of the direction.
	@return Enum value represented by the character.*/

	int& operator[](int val);
	bool operator==(Game& rhs);
	bool operator!=(Game& rhs) { return !operator==(rhs); }
	friend ostream& operator<<(ostream& os, Game& x);
	friend istream& operator>>(istream& is, Game& x);

};

