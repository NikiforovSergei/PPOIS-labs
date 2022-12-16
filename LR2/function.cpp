#include "function.h"
#include <vector>
#include <strin >
#include <iostream>

using namespace std;

Function::Function(int begin, int end)
{
	this->funcBegin = begin;
	this->funcEnd = end;
}

void Function::push(int value, bool debug)
{
	stack.push(value);
}

void Function::push(string label, bool debug)
{
	if (debug)
		cout << "Push\t" << label << endl;

	for (auto variable : variables)
		if (variable.first == label)
		{
			stack.push(variable.second);
			return;
		}

	throw Exception::name_err("There is no variable " + label);
}

void Function::pop(bool debug)
{
	if (debug)
		cout << "POP" << endl;
	stack.pop();
}

void Function::pop(string label, bool debug)
{
	if (debug)
		cout << "Pop\t" << label << endl;

	for (auto var : variables)
	{
		if (var.first == label)
		{
			var.second = stack.top();
			stack.pop();
			return;
		}
	}

	if (debug)
		cout << "Variable has been created\n";

	variables.emplace(label, stack.top());
	stack.pop();
}

void Function::printStack()
{
	vector <int> copy;
	int i = 0;

	while (!stack.empty())
	{
		copy.push_back(stack.top());
		stack.pop();
		cout << copy.back() << endl;
		i++;
	}
	while (!copy.empty())
	{
		stack.push(copy.back());
		copy.pop_back();
	}
	cout << endl;
}

void Function::printVariables()
{
	for (auto var : variables)
		cout << var.first << ":\t" << var.second << endl;
}

void Function::clear()
{
	while (!stack.empty())
	{
		stack.pop();
	}
}

int Function::size()
{
	return stack.size();
}

void Function::peek(string label, bool debug)
{
	if (debug)
		cout << "PEEK\t" << label << endl;

	for (auto variable : variables)
		if (variable.first == label)
		{
			if (debug)
				cout << "Variable exists\n";

			variable.second = stack.top();
			return;
		}

	if (debug)
		cout << "New variable created\n";

	variables.emplace(label, stack.top());
}

void Function::dup(bool debug)
{
	if (debug)
		cout << "DUP\t" << stack.top() << endl;

	stack.push(stack.top());
}


void Function::add(bool debug)
{
	int last = stack.top();
	int res = stack.top();
	stack.pop();
	res += stack.top();
	stack.push(last);
	stack.push(res);
}

void Function::sub(bool debug)
{
	int last = stack.top();
	int res = stack.top();
	stack.pop();
	res -= stack.top();
	stack.push(last);
	stack.push(res);
}

void Function::div(bool debug)
{
	int last = stack.top();
	int res = stack.top();
	stack.pop();
	res /= stack.top();
	stack.push(last);
	stack.push(res);
}

void Function::mul(bool debug)
{
	int last = stack.top();
	int res = stack.top();
	stack.pop();
	res *= stack.top();
	stack.push(last);
	stack.push(res);
}

bool Function::isEqual(bool debug)
{
	int first = stack.top();
	stack.pop();
	int second = stack.top();
	stack.push(first);
	string res;
	if (first == second) res = "true";
	else res = "false";

	if (debug)
		cout << first << " equales " << second << ": " << res << endl;

	return first == second;
}

bool Function::isOver(bool debug)
{
	int first = stack.top();
	stack.pop();
	int second = stack.top();
	stack.push(first);
	string res;
	if (first > second) res = "true";
	else res = "false";

	if (debug)
		cout << first << " over " << second << ": " << res << endl;

	return first > second;
}