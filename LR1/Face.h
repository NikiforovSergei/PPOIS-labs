#pragma once

#include <iostream>
#include <map>
#include <vector>
using namespace std;

/// This class represents the cube face entity


class Face
{
	friend class Cube; ///< The cube class has access to the private fields and mathods of the face class 

private:

	int index;
	vector<vector<int>> vertical;
	vector<vector<int>> horizontal;
	map <string, int> naighbor;

	Face();
	Face(int valueIndex, vector<vector<int>> &, vector<vector<int>> &);
};

