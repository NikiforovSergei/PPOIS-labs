#include <iostream>
#include <conio.h>
#include <fstream>
#include "ocean.h"
using namespace std;

int main()
{
	int width = 11, height = 8, input, input_2=1;
	int w = 8, s = 8, h = 8, p = 15; 
	cout << "1 ENTER HERE"<<endl;
	cout << "2 READ FROM FILE"<<endl;
	cout << "3 DEFAULT(8 whales, 8 sharks, 8 hearrings, 15 planktons"<<endl<<endl;
	cin >> input;
	system("cls");
	while (input_2 && input!=3) 
	{
		if (input == 1)
		{
			while (1)
			{
				try
				{
					cout << "Enter the width and the height of field: " << endl;
					cin >> width >> height;
					cout << "W: ";	cin >> w;
					cout << "S: ";	cin >> s;
					cout << "H: ";	cin >> h;
					cout << "P: ";	cin >> p;
					if (w + s + h + p > (width * height) * 4 || p > (width * height))	throw 1;
					else
					{
						input_2 = 0;
						break;
					}
				}
				catch (int)
				{
					cout << "Non-correct data, try again"<<endl;
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
						file >> width >> height >> w >> s >> h >> p;
						file.close();
						input_2 = 0;
						break;
					}
				}
				catch (int)
				{
					system("cls");
					cout << "File not found! Enter here-1, try again-2"<<endl;
					cin >> input;
					break;
				}
			}
		}
	}

	srand(time(0));
	Ocean_master ocean(width, height);
	system("cls");
	ocean.Beginning(w, s, h, p);

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