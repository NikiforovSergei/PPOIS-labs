#pragma once

#include "Face.h"
#include <vector>


/// This class represents the cube entity
class Cube
{
private:

	int	cubeSize; 
	Face faces[6];

	void changeOrientToLeft(int neighbor); 
	void changeOrientToRight(int neighbor);
	void rotateY(int face, int line, string currentNaighbor);
	void rotateX(int face, int line, string currentNaighbor);

public:

	Cube(vector<vector<vector<vector<int>>>>&);		///<\brief Constructor takes as input a multidimensional vector that stores all bars
	void print();	///<\brief Print the scan of the cube in the console
	void rotate(int face, int direction, int line);		///<\brief Rotate the face of the cube
	bool check();	///<\brief Check if cube is built
};

