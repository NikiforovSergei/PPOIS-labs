#include <iostream>
#include <conio.h>
#include <fstream>
#include "ocean.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int width = 8, height = 8, input, input_2 = 1;
	int w = 10, s = 5, h = 7, p = 15;
	cout << "1 - Ввод с клавиатуры " << endl;
	cout << "2 - Чтение из файла" << endl;
	cout << "3 - Предуст.(10 китов, 5 акул, 7 сельдь, 15 планктона)" << endl << endl;
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
					cout << "Введите размеры поля: " << endl;
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
					cout << "Некорректные данные, попробуйте снова" << endl;
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
				cout << "Введите имя файла: ";
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
					cout << "Файл не найден! Ввод с клавиатуры - 1, Попытаться снова - 2" << endl;
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
		cout << "Ход " << move_count << endl;
		move_count++;
		input = _getch();
		if (input == '0')
			return 0;
		ocean.Move();
	}

}