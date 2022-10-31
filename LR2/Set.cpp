
#include "Set.h"
#include "Error.h"
#include "Function.h"
#include <fstream>
#include <iostream>
#include <sstream>



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
			std::cout << set[i].set_elements[set[i].set_elements.size() - 1] << "}, ";
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

void Set::parse(std::string& context) {
	
	context = context.substr(1, context.size() - 2);
	std::vector<std::string> elements;

	int countOpen = 0, countClose = 0;
	for (char a : context) {
		if (a == '{') countOpen++;
		else if (a == '}') countClose++;
	}

	if (countOpen != countClose) {
		throw ERROR_THROW(7);
	}

	int start = 0, i = 0;
	while (i < context.size())
	{
		if (context.at(i) == '{') {
			start = i;
			while (true) {
				if (context.at(i) == '{') {
					countOpen--;
				}
				else if (context.at(i) == '}') {
					countClose--;
					if (countOpen == countClose) break;
				}
				i++;
			}
			elements.push_back(context.substr(start, i - start + 1));
			if (i + 1 < context.size())i++;
			start = i + 1;
		}
		else if (context.at(i) == ',') {
			elements.push_back(context.substr(start, i - start));
			start = i + 1;
		}
		else if (i == context.size() - 1) {
			elements.push_back(context.substr(start));
		}
		i++;
	}
	for (size_t i = 0; i < elements.size(); i++) {
		char buf;
		std::stringstream ss; ss << elements[i];
		ss >> buf;
		if (buf == '{') {
			Set buf_set;
			buf_set.parse(elements[i]);
			this->add_set(buf_set);
		}
		else {
			add_elements(buf);
		}
	}
}


void Set::split(std::string str, std::string& fir_set, std::string& sec_set, std::string& sign) {
	int countOpen = 0, countClose = 0, set_start = 0, set_end = 0;
	for (char a : str) {
		if (a == '{') countOpen++;
		else if (a == '}') countClose++;
		if (countOpen != 0 && countOpen == countClose) {
			break;
		}
		set_end++;
	}
	std::string first_set = str.substr(set_start, ++set_end);
	set_start = set_end;
	while (str.at(set_start) != '{') set_start++;
	set_end = set_start;
	for (char a : str) {
		if (a == '{') countOpen++;
		else if (a == '}') countClose++;
		if (countOpen != 0 && countOpen == countClose) {
			break;
		}
		set_end++;
	}
	std::string second_set = str.substr(set_start, set_end);
	for (char a : str) {
		if (a == '+' || a == '*' || a == '-') {
			std::string buf_sign(1, a);
			sign = buf_sign;
		}
	}
	fir_set = first_set;
	sec_set = second_set;
}

void Set::processing(Set& set1, Set& set2, std::string& sign) {
	Set buf_set;
	if (sign == "+") {
		buf_set = Operation::set_union(set1, set2);
		buf_set.show_elements();
	}
	else if (sign == "*") {
		buf_set = Operation::set_traversal(set1, set2);
		buf_set.show_elements();
	}
	else if (sign == "-") {
		buf_set = Operation::set_symmetric_difference(set1, set2);
		buf_set.show_elements();
	}
	else
		throw ERROR_THROW(9);
}

void Set::check_boolean(std::string& str, bool& a) {
	std::string buf_str = "Boolean";
	int n = 0;
	for (size_t i = 0; i < buf_str.size(); i++) {
		if (buf_str[i] == str[i])
			n++;
	}
	if (n == buf_str.size()) {
		int amount = 0;
		for (int i = n; i < str.size(); i++) {
			if (str[i] == '{')
				amount++;
			else if (str[i] == '}')
				amount--;
			if (amount == 0 && i < str.size() - 10)
				throw ERROR_THROW(10);	
		}
		/*
		buf_str = str;
		int amount = 1;
		for (size_t i = 8; i < str.size(); i++) {
			if (buf_str.at(i) = '{' && amount == 0)
				throw ERROR_THROW(10)
			else if (buf_str.at(i) = '{' && amount > 0)
				amount++;
			else if (buf_str.at(i) = '}')
				amount -2;
		}
		*/
		a = 1;
		str = str.substr(0, str.size() - 1);
		str = str.substr(8, str.size() - 1);
		Set set;
		set.parse(str);
		Set buf_set = Operation::set_boolean(set);
		buf_set.show_elements();
	}
}