#include <iostream>
#include"Info.h"
#include <conio.h>
#include <fstream>

using namespace std;
int main()
{
	int width = 11, height = 8, input, input_2 = 1;
	int whale = 8, shark = 8, herring = 8, plankton = 15;
	cout << "1 ENTER HERE" << endl;
	cout << "2 READ FROM FILE" << endl;
	cout << "3 DEFAULT(8 whales, 8 sharks, 8 hearrings, 15 planktons" << endl << endl;
	cin >> input;
	system("cls");
	while (input_2 && input != 3)
	{
		if (input == 1)
		{
			while (1)
			{
				try
				{
					cout << "Enter the width and the height of area: " << endl;
					cin >> width >> height;
					cout << "Whale: ";	cin >> whale;
					cout << "Shark: ";	cin >> shark;
					cout << "Herring: ";	cin >> herring;
					cout << "Plankton: ";	cin >> plankton;
					if (whale + shark + herring + plankton > (width * height) * 4 || plankton > (width * height))	throw 1;
					else
					{
						input_2 = 0;
						break;
					}
				}
				catch (int)
				{
					cout << "Non-correct data, try again" << endl;
					_getch();
				}
			}
		}
		if (input == 2)
		{
			while (1)
			{
				string filename;
				fstream file;
				cout << "Enter filename: ";
				cin >> filename;
				try
				{
					file.open(filename);
					if (!file.is_open()) throw 1;
					else
					{
						file >> width >> height >> whale >> shark >> herring >> plankton;
						file.close();
						input_2 = 0;
						break;
					}
				}
				catch (int)
				{
					system("cls");
					cout << "File not found! Enter here-1, try again-2" << endl;
					cin >> input;
					break;
				}
			}
		}
	}

	srand(time(0));
	Ocean_master ocean(width, height);
	system("cls");
	ocean.Beginning(whale, shark, herring, plankton);

	int move_count = 0;
	while (true)
	{
		cout << "Move " << move_count << endl;
		move_count++;
		input = _getch();
		if (input == '\033')
			return 0;
		ocean.Move();
	}

}

