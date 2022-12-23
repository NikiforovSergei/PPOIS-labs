#include <iostream>
#include <conio.h>
#include <fstream>
#include "ocean.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int width = 8, height = 8, input, input_2 = 1;
	int whale = 8, shark = 6, herring = 4, plankton = 15;
	cout << "1 - Ввод значений с клавиатуры " << endl;
	cout << "2 - Чтение значений из файла" << endl;	
	cout << "3 - Предустановленны значения (8 китов, 6 акул, 4 сельдь, 15 планктона)" << endl << endl;
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
					cout << "Кит: ";	cin >> whale;
					cout << "Акула: ";	cin >> shark;
					cout << "Сельдь: ";	cin >> herring;
					cout << "Планктон: ";	cin >> plankton;
					if (whale + shark + herring + plankton > (width * height) * 4 || plankton > (width * height))	throw 1;
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
						file >> width >> height >> whale >> shark >> herring >> plankton;
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
	ocean.Beginning(whale, shark, herring, plankton);

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