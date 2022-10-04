#pragma once

#include <iostream>
#include <conio.h>

class Game
{
public:
	Game();
	~Game();

	/// <summary>
	///Get current step of player
	/// </summary>
	/// <returns>if true return X, else return 0</returns>
	bool GetPlayer();

	/// <summary>
	///Set step of player
	/// </summary>
	void SetPlayer(bool player);

	/// <summary>
	///show game field
	/// </summary>
	void show();	

	/// <summary>
	//check player win
	/// </summary>
	/// <returns>true or false</returns>
	bool check();

	/// <summary>
	///Put a sign of a player
	/// </summary>
	void PutASign(int row, int collumn);

	/// <summary>
	///shift and bold X on the game field
	/// </summary>
	void move_X(int row, int collumn);		

	/// <summary>
	///shift and bold O on the game field
	/// </summary>
	void move_O(int row, int collumn);		

	/// <summary>
	/// get amount of game cells
	/// </summary>
	/// <returns>variable cell</returns>
	int GetCells();

	/// <summary>
	/// get sign of the cell
	/// </summary>
	/// <returns>variable sign</returns>
	int GetSigns();

	/// <summary>
	/// get variable field
	/// </summary>
	/// <returns>pointer</returns>
	char** GetField();

	/// <summary>
	/// overload of [][]
	/// </summary>
	/// <param name="index"></param>
	/// <returns>value of cell</returns>
	char*& operator[](const int& index) const;

protected:
	bool player;	//True - sign X; False - sign O
	int cell;		//game sqare
	int signs;		//amount of signs on the game field
	char** field;

private:
	void shift_X(int row, int collumn);		//shift X on the game field
	void bold_X(int row, int collumn);		//bold X on the game field
	void shift_O(int row, int collumn);		//shift O on the game field
	void bold_O(int row, int collumn);		//bold O on the game field
};
