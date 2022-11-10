#include <iostream>
#include "Cube.h"
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;


void buildFromFile(vector<vector<vector<vector<int>>>> &bars)
{
	bars.clear();

	vector<int> v1;
	vector<vector<int>> v2;
	vector<vector<vector<int>>> v3;

	ifstream in("test.txt");

	char ch;
	int value = 0;

	if (in.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int m = 0; m < 3; m++)
					{
						in.get(ch);
						value = ch - '0';
						if (value != -38)
							v1.push_back(value);
						else
							m--;
					}
					v2.push_back(v1);
					v1.clear();
				}
				v3.push_back(v2);
				v2.clear();
			}
			bars.push_back(v3);
			v3.clear();
		}
	}
	else
	{
		cout << "data error";
	}
	in.close();
}

void buildRandom(vector<vector<vector<vector<int>>>>& bars)
{
	bars.clear();

	vector<int> v1;
	vector<vector<int>> v2;
	vector<vector<vector<int>>> v3;

	int barsLimit[6] = { 0, 0, 0, 0, 0, 0 };
	int value = 0;

	srand(time(0));

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					while (true)
					{
						value = 0 + rand() % 6;
						if (barsLimit[value] < 9)
						{
							break;
						}
					}
					barsLimit[value]++;
					v1.push_back(value);
				}
				v2.push_back(v1);
				v1.clear();
			}
			v3.push_back(v2);
			v2.clear();
		}
		bars.push_back(v3);
		v3.clear();
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					value = bars[i][j][m][k];
					v1.push_back(value);
				}
				v2.push_back(v1);
				v1.clear();
			}
			bars[i].push_back(v2);
			v2.clear();
		}
	}
}

int main()
{
	vector<vector<vector<vector<int>>>> bars;

	Cube cube = Cube();

	int a = 1;
	while (a != 0)
	{
		cout << endl << "1. buildFromFile" << endl << "2. buildRandom" << endl << "3. check" << endl << "4. print" << endl << "5. rotate" << endl << "0. exit" << endl << endl;
		cin >> a;
		
		switch (a)
		{
		case 1:
			buildFromFile(bars);
			cube = Cube(bars);
			break;
		case 2:
			buildRandom(bars);
			cube = Cube(bars);
			break;
		case 3:
			cout << cube.check() << endl;
			break;
		case 4:
			cube.print();
			break;
		case 5:
			cout << "Enter face(0..5), diraction(0 = up, 1 = down, 2 = left, 3 = right), line(0..2)" << endl;
			int face, diraction, line;
			cin >> face >> diraction >> line;
			cube.rotate(face, diraction, line);
			break;
		}
	}
	
}
