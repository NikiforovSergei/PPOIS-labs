#include <iostream>
#include <string>
#include <regex>
#include "Header.h"

using namespace std;

MySet enterSecondSet();

int main()
{
	setlocale(LC_ALL, "Russian");
	
	MySet myset;
	MySet secondSet;
	MySet result;

	//myset.add("a");
	//myset.add("b");
	//myset.add("c");
	//myset.add("{a, d}");
	//myset.display();
	//myset.clear();

	myset.input("{a,v,d,{c,d,{s}},b,{t}}");
	myset.display();
	//cout << endl << endl;

	myset.input("{a,v,d,{c,d,{s,t}},b,{c,{t,s},d}}");
	myset.display();

	//myset.boolean();

	myset.input("{a,b,c,{g,f},{f,g}}");
	myset.display();

	myset.clear();

	string inputStr;

	int n = 1;
	while (n)
	{	
		cout << "1 - Ввод множества\n"
			<< "2 - Вывод множества\n"
			<< "3 - Проверка на пустое множество\n"
			<< "4 - Добавить элемент множества\n"
			<< "5 - Удалить элемент множества\n"
			<< "6 - Очистить множество\n"
			<< "7 - Мощность множества\n"
			<< "8 - Поиск элемента по ключу\n"
			<< "9 - Объединение множеств\n"
			<< "10 - Пересечение множеств\n"
			<< "11 - Разность множеств\n"
			<< "12 - Построение булеана множества\n";

		int choice;
		cin >> choice;
		cout << endl;


		switch (choice)
		{
		case 1:
			cout << "Введите множество: ";
			cin >> inputStr;

			myset.input(inputStr);
			break;

		case 2:
			myset.display();
			break;

		case 3:
			if (myset.empty())
				cout << "Множество пусто" << endl;
			else
			{
				cout << "Множество не пусто: ";
				myset.display();
				cout << endl;
			}
			break;

		case 4:
			cout << "Введите элемент, который хотите добавить: ";
			cin >> inputStr;

			myset.add(inputStr);
			break;

		case 5:
			cout << "Введите элемент, который хотите удалить: ";
			cin >> inputStr;

			myset.erase(inputStr);
			break;

		case 6:
			myset.clear();
			cout << "Множество очищено" << endl;
			break;

		case 7:
			cout << "Мощность множества: " << to_string(myset.capacity()) << endl;
			break;

		case 8:
			cout << "Введите элемент, который хотите найти: ";
			cin >> inputStr;

			myset.find(inputStr);
			break;

		case 9:
			secondSet = enterSecondSet();

			result = myset + secondSet;
			result.display();

			secondSet.clear();
			result.clear();
			break;

		case 10:
			secondSet = enterSecondSet();

			result = myset * secondSet;
			result.display();

			secondSet.clear();
			result.clear();
			break;

		case 11:
			secondSet = enterSecondSet();

			result = myset - secondSet;
			result.display();

			secondSet.clear();
			result.clear();
			break;

		case 12:
			result = myset.boolean();

			result.display();
			break;

		default:
			cout << "Такого варианта нет" << endl;
		}
	}
	return 0;
}

MySet enterSecondSet()
{
	MySet secondSet;

	string inputString;
	cout << "Введите второе множество: ";
	cin >> inputString;

	secondSet.input(inputString);
	
	return secondSet;
}