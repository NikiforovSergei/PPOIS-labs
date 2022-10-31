#pragma once
#include <iostream>
#include <type_traits>
class Error
{
public:
	Error(int errorCode)
	{
		errorCode;
		std::cout << "Код ошибки: " << errorCode;
		switch (errorCode)
		{
		case 0: std::cout << ". Неопознанный тип.(Доступные типы графов: int, string, double) "; system("pause"); exit(0); break;
		case 100: std::cout << ". Введите целочисленное число: "; break;
		case 101: std::cout << ". Введите букву: "; break;
		case 102: std::cout << ". Введите вещественное число: "; break;
		case 103: std::cout << ". Введите строку: "; break;
		case 200: std::cout << ". Такого параметра не существует." << std::endl; break;
		case 300: std::cout << ". Вершины с таким индексом не существует." << std::endl; break;
		case 301: std::cout << ". Ребра с таким именем не существует." << std::endl; break;
		case 302: std::cout << ". Нельзя создать ребро для одной вершины." << std::endl; break;
		case 303: std::cout << ". Превышен лимит добавления ребер! Добавьте вершину." << std::endl; break;
		case 304: std::cout << ". Вершин(а/ы) не существует! Добавьте вершину." << std::endl; break;
		case 305: std::cout << ". Ребро между выбранными вершинами уже существует. Создайте новую вершину или соедините другие вершины." << std::endl; break;
		case 306: std::cout << ". Ребро с таким именем уже существует. Задайте ребро с другим именем." << std::endl; break;
		case 400: std::cout << ". Превышен индекс итератора вершин!" << std::endl; break;
		case 401: std::cout << ". Превышен индекс итератора ребер!" << std::endl; break;
		}
	}
};
template<class type>
type getChoice()
{
	while (true)
	{
		type choice;
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			if (std::is_same<type, int>::value)
			{
				Error error(100);
				continue;
			}
			else if (std::is_same<type, char>::value)
			{
				Error error(101);
				continue;
			}
			else if (std::is_same<type, double>::value)
			{
				Error error(102);
				continue;
			}
			else if (std::is_same<type, std::string>::value)
			{
				Error error(103);
				continue;
			}
			else Error error(0);
		}
		else
			return choice;
	}
}
