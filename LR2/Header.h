#pragma once
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

class Set {
private:
	string indtf;

	vector<int> nums;
	vector<string> elements;
	vector<Set> subsets;

public:
	Set();
	void build_new_indtf();
	void set_indtf(string  _indtf);
	void Add_subset(Set _subset);
	void Add_element(string _element);
	void clear();
	bool empty();
	void Add_num(int _num);
	void print();
	string get_indtf();
	vector<string> get_elements();
	vector<Set> get_subsets();
	~Set();

	vector<Set> Assignment(Set s1, Set s2, vector<Set> _data);
	Set Intersection(Set s1, Set s2);
	Set Symmetric_difference(Set s1, Set s2);
	Set Unification(Set s1, Set s2);
};

class Input_Processing {
private:

public:
	Input_Processing();
	string line;
	int get_size_of_line();
	Input_Processing(string _str);
	bool Syntax_check();
	bool Is_only_one_bool_argument(string _str);
	void Ignore_space();
	vector<Set> Parse(string str);
};

class Operations : public Set{
public:
	Operations();
	Set set_boolean(Set set);
	Set Boolean(Set _set);
};

class Solver : public Operations, public Input_Processing{
private:
	vector<Set> Sets;
	string stack_ops;
public:
	Solver();
	string To_post_form(string _str, vector<Set> _Sets);
	vector<Set> Solve_post_form(string _post_form);
};

vector<Set> Insert(vector<Set> v1, vector<Set> v2);

#define ERROR_THROW(id) Error::geterror(id);				 		// throw ERRPR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c);		// throw ERRPR_THROW_IN(id, строка, колонка)
#define ERROR_ENTRY(id, m) {id, m, {-1,-1}}							// элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200									// максимальаня длина сообщения об ошибке
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id, "Неопрделённая ошибка")	// 1 неопределенный элемент таблицы ошибок

#define ERROR_MAX_ENTRY 1000	// количество элементов в таблице ошибок

namespace Error
{
	struct ER	// тип исключения для throw ERROR_THROW | ERROR_THROW_IN и catch(ERROR)
	{
		int id;									// код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];	// сообщение об ошибке
		struct IN								// расширение для ошибки при обработке входных данных
		{
			short line;							// номер строки (0, 1, 2, ...)
			short col;							// номер позиции в стркое (0, 1, 2, ...)
		} inext;
	};

	ER geterror(int id);							// сформировать ERROR для ERROR_THROW
	ER geterrorin(int id, int line, int col);	// сформировать ERROR для ERROR_THROW_IN
}