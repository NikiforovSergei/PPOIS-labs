#include <iostream>
#include <conio.h>
#include <fstream>
#include "ocean.h"

using namespace std;
using namespace ocean_life;


int main()
{
	char input;
	int x_size = 14, y_size = 5;
	int w = 4,  // whale
		d = 4,  // dolphin
		k = 4,  // killerwhale
		s = 4,  // shark
		c = 8,  // clownfish
		f = 8,  // fugu
		p = 10; // plankton

	for (int i = 0; i < 45; i++)
		cout << "-";
	cout << "\nFILE POSITIONING\t\t---> TAB\n";
	for (int i = 0; i < 45; i++)
		cout << "-";
	cout << "\nCUSTOM POSITIONING\t\t---> SPACE\n";
	for (int i = 0; i < 45; i++)
		cout << "-";
	cout << "\nDEFAULT POSITIONING (14x5)\t---> ENTER\n";
	cout << "4 whales, 4 dolphins,\n4 killerwhales, 4 sharks,\n8 clownfish, 8 fugu, 10 plankton\n";
	for (int i = 0; i < 45; i++)
		cout << "-";

	input = _getch();
	system("cls");
	if (input == ' ') // SPACE
	{
		try
		{
			cout << "Enter the game table size (AxB): ";
			cin >> x_size >> y_size;
			cout << "Enter organism numbers (W -> D -> K -> S -> C -> F -> P): ";
			cin >> w >> d >> k >> s >> c >> f >> p;
			if (w + d + k + s + c + f + p > (x_size * y_size) * 4 || p > (x_size * y_size))
			{
				throw;
			}
		}
		catch (...)
		{
			cout << "Too many animals, using default positioning instead!\n";
			x_size = 14;
			y_size = 5;
			w = 4;
			d = 4;
			k = 4;
			s = 4;
			c = 8;
			f = 8;
			p = 10;
			_getch();
		}
	}
	if (input == '\011') // TAB
	{
		string filename;
		fstream file;
		int test;
		while (true)
		{
			cout << "Enter filename: ";
			cin >> filename;
			try
			{
				file.open(filename);
				if (!file.is_open())
				{
					throw 1;
				}
				break;
			}
			catch (int)
			{
				system("cls");
				cout << "File not found!\n";
			}
		}

		file >> x_size >> y_size >> w >> d >> k >> s >> c >> f >> p;
		file.close();
	}
	if (input == '\033')
		return 0; // ESC




	srand(time(0));
	Ocean_master ocean(x_size, y_size);

	system("cls");
	ocean.start_random_place(w, d, k, s, c, f, p);
	ocean.Show();

	int move_count = 0;
	while (true)
	{
		move_count++;
		cout << "Move #" << move_count << endl;
		input = _getch();
		if (input == '\033')
			return 0; // if you press ESC, the program ends
		ocean.Tick();
	}
}


// THE PLANKTON DOESN'T EAT BUT REPLICATES RAPIDLY
// THE PASSIVES ONLY EAT PLANKTON 
// THE NEUTRALS EAT PLANKTON BUT CAN EAT THE PASSIVES
// THE AGGRESSIVES CAN NOT EAT PLANKTON, BUT CAN EAT BOTH PASSIVES AND NEUTRALS