#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <cstdlib>

class RubicsCube
{
public:
	void Menu();
	/// <summary>
	/// Storing Rubik's Cube Strings
	/// </summary>
	std::vector<std::vector<std::vector<char>>> LinesOfCube;
	/// <summary>
	/// Storing Rubik's Cube columns
	/// </summary>
	std::vector<std::vector<std::vector<char>>> RowsOfCube;
	void CreateCube();
	void ShowCube();
	void FaceTurn(int NumberOfFace);
	void FTurn();
	void BTurn();
	void LTurn();
	void RTurn();
	void UTurn();
	void DTurn();
	bool CheckCube();
	void RandomCube();
	void CubeFromFile();
	void Keys();
};