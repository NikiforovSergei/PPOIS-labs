#pragma once
#include <stack>
#include <map>
#include "Exception.h"


class Function
{
public:
	Function(int begin, int end);

	void push(int value, bool debug = false);
	void push(string label, bool debug = false);
	void pop(bool debug = false);
	void pop(string label, bool debug = false);
	void printStack();
	void printVariables();
	void clear();
	int size();
	void peek(string label, bool debug = false); //Занести вершину стэка в качестве значения переменной
	void dup(bool debug = false); //Продублировать число на вершине стэка (т.е. положить в стэк число с вершины стэка):
	void add(bool debug = false); //Извлечь два числа из стэка, сложить их и сумму положить в стэк
	void sub(bool debug = false); //Извлечь два числа из стэка, отнять от первого аргумента второй и разность положить в стэк
	void div(bool debug = false); //Извлечь два числа из стэка, разделить первый аргумент на второй и частное положить в стэк
	void mul(bool debug = false); //Извлечь два числа из стэка, перемножить их и произведение положить в стэк
	bool isEqual(bool debug);
	bool isOver(bool debug);

	int funcBegin, funcEnd;
	stack <int> stack;
	map <string, int> variables;

};

 

