#include <iostream>
#include "TicTacToe.h"

using namespace std;

int main()
{
	int menu, size;

	TTT game(3);

	while (2 > 0) {
		cout << "0 - who is the winner test,		1 - >> << test,		2 - [] test,		3 - play game,\n4 - exit" << endl;
		cin >> menu;

		if (menu == 4) {
			break;
		}

		switch (menu) {
		case 0:

			game.NewGame(3);

			game.SetPosition(4);
			game.SetPosition(7);
			game.SetPosition(3);
			game.SetPosition(0);
			game.SetPosition(5);
			game.SetPosition(0);

			cout << endl << game << endl;

			game.NewGame(3);

			game.SetPosition(0);
			game.SetPosition(2);
			game.SetPosition(4);
			game.SetPosition(5);
			game.SetPosition(7);
			game.SetPosition(8);
			game.SetPosition(8);


			cout << endl << game << endl;

			game.NewGame(4);

			game.SetPosition(3);
			game.SetPosition(0);
			game.SetPosition(6);
			game.SetPosition(15);
			game.SetPosition(9);
			game.SetPosition(5);
			game.SetPosition(12);

			cout << endl << game << endl;

			game.NewGame(4);

			game.SetPosition(3);
			game.SetPosition(0);
			game.SetPosition(6);
			game.SetPosition(15);
			game.SetPosition(8);
			game.SetPosition(5);
			game.SetPosition(12);
			game.SetPosition(10);


			cout << endl << game << endl;

			break;
		
		case 1:
			cout << "Enter size" << endl;
			cin >> size;
			game.NewGame(size);
			cout << "Enter elements in grid" << endl;
			cin >> game;
			cout << game;
			break;
			
		case 2:
			cout << "Enter size" << endl;
			cin >> size;

			game.NewGame(size);
			cout << "Enter elements in grid" << endl;

			for (int i = 0; i < size * size; i++) {
				cin >> game[i];
			}

			for (int i = 0; i < size * size; i++) {
				if (i % size == 0) {
					cout << endl;
				}
				cout << game[i];
			}
			cout << endl;
			break;

		case 3:
			cout << "Enter size" << endl;
			cin >> size;

			game.NewGame(size);

			int action;
			while (2 > 1) {
				cout << "0 - Show the grid,		1 - put,		2 - exit" << endl;
				cin >> action;

				if (action == 2) {
					break;
				}
				
				switch (action) {
				case 0:
					cout << game;
					break;

				case 1:
					cout << "Set position" << endl;
					int position;
					cin >> position;
					game.SetPosition(position);
					break;
				}
			}
			break;
		}
	}

	return 0;
}