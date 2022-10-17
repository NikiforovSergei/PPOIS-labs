#include "Game.h"

int main()
{
	Game TicTacToe;
	system("cls");
	TicTacToe.show();
	int row = 0, collumn = 0;

	while (true)
	{
		switch  (char click = _getch())
		{
		case 'w':
			if (row)
				row--;
			else row = TicTacToe.GetCells() - 1;

			if (TicTacToe.GetPlayer())
				TicTacToe.move_X(row, collumn);
			else
				TicTacToe.move_O(row, collumn);
			break;

		case 's':
			if (row == TicTacToe.GetCells() - 1)
				row = 0;
			else row++;
			
			if (TicTacToe.GetPlayer())
				TicTacToe.move_X(row, collumn);
			else
				TicTacToe.move_O(row, collumn);
			break;

		case 'a':
			if (collumn)
				collumn--;
			else collumn = TicTacToe.GetCells() - 1;

			if (TicTacToe.GetPlayer())
				TicTacToe.move_X(row, collumn);
			else
				TicTacToe.move_O(row, collumn);
			break;

		case 'd':
			if (collumn == TicTacToe.GetCells() - 1)
				collumn = 0;
			else collumn++;

			if (TicTacToe.GetPlayer())
				TicTacToe.move_X(row, collumn);
			else
				TicTacToe.move_O(row, collumn);
			break;

		case 13:
			TicTacToe.PutASign(row, collumn);		//changes player after "PutASign"
			if (TicTacToe.GetSigns() >= 5)
			{
				if (TicTacToe.check())
				{
					if (!TicTacToe.GetPlayer())		//not "GetPlayer" takes player before changes of player by "PutASign"
					{
						std::cout << "You Win - X";
						_getch();
						return 0;
					}
					else
					{
						std::cout << "You Win - O";
						_getch();
						return 0;
					}
				}
			}
			if (TicTacToe.GetSigns() == TicTacToe.GetCells() * TicTacToe.GetCells())
			{
				std::cout << "Draw";
				_getch();
				return 0;
			}
			break;

		case 27:
			return 0;
		}
	}
}