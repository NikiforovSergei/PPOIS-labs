#include "function.h"
using namespace std;

function::function(int function_begin, int function_end)
{
	this->begin_func = function_begin;
	this->end_func = function_end;
}

void function::push(int value, bool debug)
{
	if (debug)	cout << "PUSH\t" << value << endl;
	this->stack.push_front(value);
}

void function::push(string label, bool debug)
{
	if (debug)  cout << "PUSH\t" << label << endl;

	for (auto variable : variables)
		if (variable.first == label)
		{
			stack.push_front(variable.second);
			return;
		}

	throw exceptions::name_err("Variables not found: " + label);
}

void function::pop(string label, bool debug)
{
	if (debug)  cout << "POP\t" << label << endl;

	for (auto var : variables)
		if (var.first == label)
		{
			var.second = *stack.begin();
			stack.pop_front();
			return;
		}

	if (debug)	cout << "New variable created\n";
	variables.emplace(label, *stack.begin());
	stack.pop_front();
}

void function::pop(bool debug)
{
	if (debug)	cout << "POP" << endl;
	stack.pop_front();
}

void function::peek(string label, bool debug)
{
	if (debug)	cout << "PEEK\t" << label << endl;

	for (auto variable : variables)
		if (variable.first == label)
		{
			if (debug)
				cout << "Variable exists\n";

			variable.second = *stack.begin();
			return;
		}

	if (debug)	cout << "New variable created\n";
	variables.emplace(label, *stack.begin());
}

void function::dup(bool debug)
{
	if (debug)	cout << "DUP\t" << get_stack_head() << endl;
	stack.push_front(*stack.begin());
}

void function::add(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());
	if (debug)	cout << "ADD\t" << first_value << " + " << second_value << " = " << first_value + second_value << endl;
	stack.push_front(first_value + second_value);
}

void function::sub(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());
	if (debug)	cout << "SUB\t" << first_value << " - " << second_value << " = " << first_value - second_value << endl;
	stack.push_front(first_value - second_value);
}

void function::div(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());
	if (debug)	cout << "DIV\t" << first_value << " / " << second_value << " = " << first_value / second_value << endl;
	stack.push_front(first_value / second_value);
}

void function::mul(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());
	if (debug)	cout << "MUL\t" << first_value << " * " << second_value << " = " << first_value * second_value << endl;
	stack.push_front(first_value * second_value);
}

bool function::ifeq_flag(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug)
	{
		cout << first_value << " IS EQUAL " << second_value << ": ";
		if (first_value == second_value)  cout << "TRUE" << endl;
		else cout << "FALSE" << endl;
	}

	return first_value == second_value;
}

bool function::ifgr_flag(bool debug)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());
	if (debug)
	{
		cout << first_value << " IS GREATER THAN " << second_value << ": ";
		if (first_value > second_value)
			cout << "TRUE" << endl;
		else cout << "FALSE" << endl;
	}

	return first_value > second_value;
}

int function::get_stack_head()
{
	return *stack.begin();
}

void function::push_stack_head(int value)
{
	stack.push_front(value);
}

void function::clear()
{
	variables.clear();
	stack.clear();
}

int function::get_begin()
{
	return begin_func;
}

int function::get_end()
{
	return end_func;
}

void function::show_variables()
{
	for (auto var : variables)	cout << var.first << ":\t" << var.second << endl;
}

void function::show_stack()
{
	int i = 1;
	for (auto x : stack)
	{
		cout << i << ":\t" << x << endl;
		i++;
	}
}
