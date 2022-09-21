#pragma once

#include <iostream>

#include "Puzzle.h"

/// <summary>
/// Simple menu that lets player choose a level and start the game.
/// <summary>
static class Menu
{
public:
	/// <summary>
	/// Starts up a new game.
	/// <summary>
	void StartUpMenu();
private:
	Puzzle *puzzle;

	int LevelChoice();
	void PrintMenu() const;
	void StartGame();
	void Congratulate() const;
	int GetPlayerChoice();
};

