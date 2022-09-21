#pragma once

#include <conio.h>
#include <iostream>

#include "Tile.h"
#include "Direction.h"

/// <summary>
/// Creates, shuffles and lets player control puzzle board.
/// </summary>
class Puzzle
{
public:
	/// <summary>
	/// Initializes a new instance of Puzzle class.
	/// </summary>
	Puzzle(int level);
	Tile operator[](int x);
private:
	void PrintBoard() const;
	void Shuffle();
	bool CheckWinCondition() const;
	void Move(Direction dir);
	void Swap(Tile &one, Tile &two);
	void AwaitPlayerInput();
	void SetLevel(int level);
	
	int size;
	int currentLevel;
	int blankX;
	int blankY;
	
	Tile **puzzleBoard;

	Tile level1[3][3] = { Tile(201, 0, 0), Tile(203, 0, 1), Tile(187, 0, 2),
						  Tile(204, 1, 0), Tile(206, 1, 1), Tile(185, 1, 2),
						  Tile(200, 2, 0), Tile(202, 2, 1), Tile(' ', 2, 2)};
	Tile level2[4][4] = { Tile('A', 0, 0), Tile('B', 0, 1), Tile('C', 0, 2), Tile('D', 0, 3),
						  Tile('E', 1, 0), Tile('F', 1, 1), Tile('G', 1, 2), Tile('H', 1, 3),
						  Tile('I', 2, 0), Tile('J', 2, 1), Tile('K', 2, 2), Tile('L', 2, 3),
						  Tile('M', 3, 0), Tile('N', 3, 1),	Tile('O', 3, 2), Tile(' ', 3, 3), };
	Tile level3[5][5] = { Tile('A', 0, 0), Tile('B', 0, 1), Tile('C', 0, 2), Tile('D', 0, 3), Tile('E', 0, 4),
						  Tile('F', 1, 0), Tile('G', 1, 1), Tile('H', 1, 2), Tile('I', 1, 3), Tile('J', 0, 3),
						  Tile('K', 2, 0), Tile('L', 2, 1), Tile('M', 2, 2), Tile('N', 2, 3), Tile('O', 0, 3),
						  Tile('P', 3, 0), Tile('Q', 3, 1),	Tile('R', 3, 2), Tile('S', 3, 3), Tile('T', 0, 3),
						  Tile('U', 3, 0), Tile('V', 3, 1),	Tile('W', 3, 2), Tile('X', 3, 3), Tile(' ', 0, 3) };
};