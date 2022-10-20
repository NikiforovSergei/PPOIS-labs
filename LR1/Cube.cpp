#include "Cube.h"
#include <vector>

void Cube::changeOrientToLeft(int neighbor)
{
	vector<vector<int>> helper;
	helper = faces[neighbor].vertical;

	for (int i = 0; i < cubeSize; i++)
	{
		reverse(faces[neighbor].horizontal[i].begin(), faces[neighbor].horizontal[i].end());
		faces[neighbor].vertical[i] = faces[neighbor].horizontal[i];
	}
	reverse(helper.begin(), helper.end());
	faces[neighbor].horizontal = helper;
	
}

void Cube::changeOrientToRight(int neighbor)
{
	vector<vector<int>> helper;
	helper = faces[neighbor].horizontal;

	for (int i = 0; i < cubeSize; i++)
	{
		reverse(faces[neighbor].vertical[i].begin(), faces[neighbor].vertical[i].end());
		faces[neighbor].horizontal[i] = faces[neighbor].vertical[i];
	}
	reverse(helper.begin(), helper.end());
	faces[neighbor].vertical = helper;
}

void Cube::rotateY(int face, int line, string currentNaighbor)
{
	Face currentFace = faces[face];
	vector<int> helper;

	helper = faces[face].vertical[line];

	for (int i = 0; i < 3; i++)
	{
		faces[currentFace.index].vertical[line] = faces[currentFace.naighbor[currentNaighbor]].vertical[line];

		for (int j = 0; j < 3; j++)
		{
			faces[currentFace.index].horizontal[j][line] = faces[currentFace.naighbor[currentNaighbor]].vertical[line][j];
		}
		currentFace = faces[currentFace.naighbor[currentNaighbor]];
	}
	faces[currentFace.index].vertical[line] = helper;

	for (int j = 0; j < 3; j++)
	{
		faces[currentFace.index].horizontal[j][line] = helper[j];
	}
}

void Cube::rotateX(int face, int line, string currentNaighbor)
{
	Face currentFace = faces[face];
	vector<int> helper;
	helper = faces[face].horizontal[line];

	for (int i = 0; i < 3; i++)
	{
		faces[currentFace.index].horizontal[line] = faces[currentFace.naighbor[currentNaighbor]].horizontal[line];

		for (int j = 0; j < 3; j++)
		{
			faces[currentFace.index].vertical[j][line] = faces[currentFace.naighbor[currentNaighbor]].horizontal[line][j];
		}
		currentFace = faces[currentFace.naighbor[currentNaighbor]];
	}
	faces[currentFace.index].horizontal[line] = helper;

	for (int j = 0; j < 3; j++)
	{
		faces[currentFace.index].vertical[j][line] = helper[j];
	}
}

Cube::Cube(vector<vector<vector<vector<int>>>> &bars)
{
	cubeSize = bars[0][0].size();

	for (int i = 0; i < 6; i++)
	{
		faces[i] = Face(i, bars[i][0], bars[i][1]);
	}
}

/// \code 
void Cube::print()
{
	//2
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize + 2; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < cubeSize; j++)
		{
			cout << faces[2].horizontal[i][j];
		}
		cout << endl;
	}
	cout << endl;

	//4,3,5,1
	for (int i = 0; i < cubeSize; i++)
	{
		cout << faces[4].horizontal[i][0] << faces[4].horizontal[i][1] << faces[4].horizontal[i][2] << "  ";
		cout << faces[3].horizontal[i][0] << faces[3].horizontal[i][1] << faces[3].horizontal[i][2] << "  ";
		cout << faces[5].horizontal[i][0] << faces[5].horizontal[i][1] << faces[5].horizontal[i][2] << "  ";
		cout << faces[1].horizontal[i][0] << faces[1].horizontal[i][1] << faces[1].horizontal[i][2] << "  ";
		cout << endl;
	}
	cout << endl;

	//0
	for (int i = 0; i < cubeSize; i++)
	{
		for (int j = 0; j < cubeSize + 2; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < cubeSize; j++)
		{
			cout << faces[0].horizontal[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
/// \endcode

/// \code
void Cube::rotate(int face, int direction, int line)
{
	Face currentFace = faces[face];
	string currentNaighbor;

	if (direction == 0) //up
	{
		if (line == 0)
		{
			changeOrientToLeft(currentFace.naighbor["leftFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToRight(currentFace.naighbor["rightFace"]);
		}
		rotateY(face, line, "bottomFace");
	}

	if (direction == 1) //down
	{
		if (line == 0)
		{
			changeOrientToRight(currentFace.naighbor["leftFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToLeft(currentFace.naighbor["rightFace"]);
		}
		rotateY(face, line, "topFace");
	}

	if (direction == 2) //left
	{
		if (line == 0)
		{
			changeOrientToRight(currentFace.naighbor["topFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToRight(currentFace.naighbor["bottomFace"]);
		}
		rotateX(face, line, "rightFace");
	}

	if (direction == 3) //right
	{
		if (line == 0)
		{
			changeOrientToLeft(currentFace.naighbor["topFace"]);
		}
		if (line == cubeSize - 1)
		{
			changeOrientToLeft(currentFace.naighbor["bottomFace"]);
		}
		rotateX(face, line, "leftFace");
	}
}
/// \endcode

/// \code
bool Cube::check()
{
	for (int i = 0; i < size(faces); i++)
	{
		for (int j = 0; j < cubeSize; j++)
		{
			for (int k = 0; k < cubeSize; k++)
			{
				if (faces[i].horizontal[j][k] != i)
				{
					return false;
				}
			}
		}
	}
	return true;
}
/// \endcode
