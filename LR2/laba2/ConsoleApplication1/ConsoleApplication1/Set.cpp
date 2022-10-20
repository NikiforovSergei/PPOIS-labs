
#include "Set.h"
#include "Error.h"
#include <fstream>
#include <iostream>



El Elements::getin(char * element, int size){	// описываем функцию{
	El in;							// создаём переменную структуры
	in.size = 0; in.lines = 1; 	// везде отсчёт от 0
	int col = 1;
	unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];
	for (int i = 0; i < size; i++) {
		unsigned char x = element[i];

		switch (in.code[x]) {
		case in.F:
			throw ERROR_THROW_IN(5, in.lines, col);	// генерация ошибки
			break;
		case in.T:
			text[in.size] = x;	// добавляем символ в наш текст
			in.size++;			// размер текста тогда увеличивается
			col++;				// и счётчик столбцов увеличивается
			break;
		default:				// замена
			text[in.size] = in.code[x];
			in.size++;
			col++;
		}

		if (x == IN_CODE_ENDL) {	//если мы встретили \n, то добавляем строчку
			in.lines++;
			col = 0;
		}
	}
	in.text = text;
	return in;
}

void Name::check_name(std::string buf_name) {	
	if(buf_name.size() > 3)
		throw ERROR_THROW(2);
	char* buf = new char[buf_name.size() + 1];
	for (size_t i = 0; i < buf_name.size(); i++)
		buf[i] = buf_name[i];
	if (buf_name.size() == 3) {
		if (buf[1] != '_')
			throw ERROR_THROW(3);
	}
	else if(buf_name.size() == 2)
		throw ERROR_THROW(3);
	Elements::getin(buf, buf_name.size());
	delete[]buf;
	this->name = buf_name;
}

void Set::add_elements(char element) {
	char* buf = new char[1];
	buf[0] = element;
	Elements::getin(buf, 1);

	if (set_elements.size() != 0 && std::find(set_elements.begin(), set_elements.end(), element) != set_elements.end()) {
		throw ERROR_THROW(6);
	}
	else {
		this->set_elements.push_back(element);
	}
	delete[]buf;
}

void Set::show_elements() {
	if (set_elements.empty() && set.empty())
		std::cout << "{ ";
	else if (!set_elements.empty() && !set.empty()) {
		std::cout << '{';
		for (size_t i = 0; i < set_elements.size() - 1; i++) {
			std::cout << set_elements[i] << ", ";
		}
		std::cout << set_elements[set_elements.size() - 1];
		for (size_t i = 0; i < set.size(); i++) {
			std::cout << ", {";
			for (size_t j = 0; j < set[i].set_elements.size() - 1; j++) {
				std::cout << set[i].set_elements[j] << ", ";
			}
			std::cout << set[i].set_elements[set[i].set_elements.size() - 1] << '}';
		}
	}
	else if(set_elements.empty() && !set.empty()) {
		std::cout << '{';
		for (size_t i = 0; i < set.size(); i++) {
			std::cout << "{";
			for (size_t j = 0; j < set[i].set_elements.size() - 1; j++) {
				std::cout << set[i].set_elements[j] << ", ";
			}
			std::cout << set[i].set_elements[set[i].set_elements.size() - 1] << '}';
		}
	}
	else {
		std::cout << '{';
		for (size_t i = 0; i < set_elements.size() - 1; i++) {
			std::cout << set_elements[i] << ", ";
		}
		std::cout << set_elements[set_elements.size() - 1];
	}
	std::cout << "}\n";
}

std::vector<char> Set::get_char_vector() {
	return this->set_elements;
}

std::vector<Set> Set::get_set_vector() {
	return this->set;
}

void Set::add_set(Set set) {
	this->set.push_back(set);
}

const bool operator == (Set s1, Set s2) {
	int n = s1.set_elements.size();
	for (int i = 0; i < n; i++) {
		if (s1.set_elements[i] != s2.set_elements[i])
			return false;
	}
	return true;
}