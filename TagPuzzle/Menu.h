///
/// Simple menu that lets player choose a level and start the game
///

#pragma once

#include <iostream>

#include "Puzzle.h"

static class Menu
{
public:
	void StartUpMenu();
private:
	Puzzle *puzzle;

	int LevelChoice();
	void PrintMenu() const;
	void StartGame();
	void Congratulate() const;
	int GetPlayerChoice();
};

