
#include <iostream>
#include "Set.h"
#include "Error.h"
#include "Function.h"

void formation_set_elements(Name& set_name) {
	int size;
	char a;
	std::cout << "Введите количество элементов\n";
	std::cin >> size;
	std::cout << "Введите элементы\n";
	for (int i = 0; i < size; i++) {
		std::cin >> a;
		set_name.set.add_elements(a);
	}
}

void formayion_set_set(Name& set_name) {
	char a;
	int size;
	std::cout << "Введите размер множества\n";
	std::cin >> size;
	std::cout << "Введите элементы множества\n";
	Set buf;
	for (int i = 0; i < size; i++) {

		std::cin >> a;
		buf.add_elements(a);
	}
	set_name.set.add_set(buf);
}

int main()
{
	setlocale(LC_ALL, "ru");
	Set set_buf;
	Set empty_set;
	Name set_name1;
	Name set_name2;
	int size, choice;
	char a;
	std::string buf_name;
	try
	{
		while (true) {
			std::cout << "1 - Ввести множество 1\n"
				<< "2 - Ввести множество 2\n"
				<< "3 - Операция объединения\n"
				<< "4 - Операция пересечения\n"
				<< "5 - Операция симметрическая разность\n"
				<< "6 - Boolean\n"
				<< "7 - Вывести множество по имени\n"
				<< "0 - Заврешить\n";
			std::cin >> choice;
			switch (choice) {
			case 1: {
				std::cout << "Введите Имя 1 множества\n";
				std::cin >> buf_name;
				set_name1.check_name(buf_name);
				if (set_name1.name == set_name2.name)
					throw ERROR_THROW(4);
				while (true) {
					std::cout << "1 - Ввести элементы множества \n"
						<< "2 - Ввести вложенное множество\n"
						<< "3 - Выход\n";
					std::cin >> choice;
					if (choice == 1) {
						formation_set_elements(set_name1);
					}
					if (choice == 2) {
						formayion_set_set(set_name1);
					}
					else if (choice == 3)
						break;
				}
				set_name1.set.show_elements();
				break;
			}
			case 2: {
				std::cout << "Введите Имя 2 множества\n";
				std::cin >> buf_name;
				set_name2.check_name(buf_name);
				if (set_name1.name == set_name2.name)
					throw ERROR_THROW(4);
				while (true) {
					std::cout << "1 - Ввести элементы множества \n"
						<< "2 - Ввести вложенное множество\n"
						<< "3 - Выход\n";
					std::cin >> choice;
					if (choice == 1) {
						formation_set_elements(set_name2);
					}
					if (choice == 2) {
						formayion_set_set(set_name2);
					}
					else if (choice == 3)
						break;
				}
				set_name2.set.show_elements();
				break;
			}
			case 3: {
				set_buf = Operation::set_union(set_name1.set, set_name2.set);
				set_buf.show_elements();
				std::cout << "Продолжить работать с данным множеством\n"
					<< "1 - Да\n"
					<< "2 - Нет\n";
				std::cin >> choice;
				if (choice == 1) {
					set_name1.set = set_buf;
					set_name2.set = empty_set;
				}
				else if(choice == 2) {
					set_name1.set = empty_set;
					set_name2.set = empty_set;
				}
				else
					throw ERROR_THROW(7);
				break;
			}
			case 4: {
				set_buf = Operation::set_traversal(set_name1.set, set_name2.set);
				set_buf.show_elements();
				std::cout << "Продолжить работать с данным множеством\n"
					<< "1 - Да\n"
					<< "2 - Нет\n";
				std::cin >> choice;
				if (choice == 1) {
					set_name1.set = set_buf;
					set_name2.set = empty_set;
				}
				else if (choice == 2) {
					set_name1.set = empty_set;
					set_name2.set = empty_set;
				}
				else
					throw ERROR_THROW(7);
				break;
			}
			case 5: {
				set_buf = Operation::set_symmetric_difference(set_name1.set, set_name2.set);
				set_buf.show_elements();
				std::cout << "Продолжить работать с данным множеством\n"
					<< "1 - Да\n"
					<< "2 - Нет\n";
				std::cin >> choice;
				if (choice == 1) {
					set_name1.set = set_buf;
					set_name2.set = empty_set;
				}
				else if (choice == 2) {
					set_name1.set = empty_set;
					set_name2.set = empty_set;
				}
				else
					throw ERROR_THROW(7);
				break;
			}
			case 6: {
				std::cout << "Введите имя множества, для которого выполнить данную операцию\n";
				std::cin >> buf_name;
				if (buf_name == set_name1.name)
					set_buf = Operation::set_boolean(set_name1.set);
				else if (buf_name == set_name2.name)
					set_buf = Operation::set_boolean(set_name2.set);
				else
					throw ERROR_THROW(8);
				set_buf.show_elements();
				std::cout << "Продолжить работать с данным множеством\n"
					<< "1 - Да\n"
					<< "2 - Нет\n";
				std::cin >> choice;
				if (choice == 1) {
					set_name1.set = set_buf;
					set_name2.set = empty_set;
				}
				else if (choice == 2) {
					set_name1.set = empty_set;
					set_name2.set = empty_set;
				}
				else
					throw ERROR_THROW(7);
				break;

			}
			case 7: {
				std::cout << "Введите имя множества\n";
				std::cin >> buf_name;
				for (int i = 0; i < buf_name.size(); i++) {
					if (buf_name[i] == set_name1.name[i])
						set_name1.set.show_elements();
					else if (buf_name[i] == set_name2.name[i])
						set_name2.set.show_elements();
					else
						throw ERROR_THROW(8);
				}
				break;
			}
			case 0:
				return 0;
			default:
				throw ERROR_THROW(7);
			}

		}
	}
	catch (Error::ER error)
	{
		std::cout << error.message << std::endl;
	}
}

