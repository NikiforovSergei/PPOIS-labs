#include "Tree.h"
#include <windows.h>
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	dictionary dic;
	dic.node = dic.node->inputDictionary(dic.node, "data.txt");
	while (true)
	{
		int input;
		cout << "Добавить слово - 1\nУдалить слово - 2\nПоиск перевода английского слова - 3\nЗамена перевода английского слова - 4\nКоличество слов в словаре - 5\nВывести дерево - 6\nВыход - 7: ";
		cin >> input;
		switch (input)
		{
		case 1:
		{
			system("cls");
			string eng, rus;
			cout << "Введите слово на английском: ";
			cin >> eng;
			cout << "Введите перевод слова: ";
			cin >> rus;
			dic += make_pair(eng, rus);
		}break;
		case 2:
		{
			system("cls");
			string eng, rus;
			cout << "Введите слово на английском: ";
			cin >> eng;
			dic -= eng;
		}break;
		case 3:
		{
			system("cls");
			string eng, rus;
			cout << "Введите слово на английском: ";
			cin >> eng;
			rus = dic[eng];
			if (rus.length() == 0)
			{
				cout << "Слово отсутствует!\n";
			}
			else cout << "Перевод слова на английский:" << eng << " русский:" << rus << '\n';
		}break;
		case 4:
		{
			system("cls");
			string eng, rus;
			cout << "Введите слово на английском: ";
			cin >> eng;
			cout << "Введите перевод слова: ";
			cin >> rus;
			dic[make_pair(eng, rus)];
			system("cls");
		}break;
		case 5:
		{
			int number = 0;
			dic.node->getNumber(dic.node, number);
			system("cls");
			cout << "Количество слов в словаре: " << number << '\n';
		}break;
		case 6:
		{
			system("cls");
			dic.node->Print(dic.node);
		} break;
		case 7:
		{
			dic.node->clearTree(dic.node);
			exit(0);
		}
		}
	}
}

