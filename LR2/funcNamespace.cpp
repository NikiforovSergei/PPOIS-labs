#include "funcNamespace.h"

function_namespace::function_namespace(int function_begin, int function_end)
{
	this->function_begin = function_begin;
	this->function_end = function_end;
}

void function_namespace::push(int value, bool debug_level)
{
	if (debug_level) { std::cout << "Command \"push\". Value to push:\t" << value << std::endl; }

	this->stack.push_front(value);
}

void function_namespace::push(std::string label, bool debug_level)
{
	if (debug_level) { std::cout << "Command \"push\". Variable label:\t" << label << std::endl; }

	for (auto variable : variables)
	{
		if (variable.first == label)
		{
			stack.push_front(variable.second);
			return;
		}
	}
	throw Exceptions::NameError("No variable named \"" + label + "\".");
}

void function_namespace::pop(std::string label, bool debug_level)
{
	if (debug_level) { std::cout << "Command \"pop\". Variable label:\t" << label << std::endl; }

	for (auto variable : variables)
	{
		if (variable.first == label)
		{
			if (debug_level) { std::cout << "Variable exists\n"; }
			variable.second = *stack.begin();
			stack.pop_front();
			return;
		}
	}
	if (debug_level) { std::cout << "New variable created\n"; }
	variables.emplace(label, *stack.begin());
	stack.pop_front();
}

void function_namespace::pop(bool debug_level)
{
	if (debug_level) { std::cout << "Command \"pop\"" << std::endl; }

	stack.pop_front();
}

void function_namespace::peek(std::string label, bool debug_level)
{
	if (debug_level) { std::cout << "Command \"peek\". Variable label:\t" << label << std::endl; }

	for (auto variable : variables)
	{
		if (variable.first == label)
		{
			if (debug_level) { std::cout << "Variable exists\n"; }
			variable.second = *stack.begin();
			return;
		}
	}
	if (debug_level) { std::cout << "New variable created\n"; }
	variables.emplace(label, *stack.begin());
}

void function_namespace::dup(bool debug_level)
{
	if (debug_level) { std::cout << "Command \"dup\". Value to duplicate:\t" << get_stack_head() << std::endl; }
	stack.push_front(*stack.begin());
}

void function_namespace::add(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level) { std::cout << "Command \"add\". " << first_value << " + " << second_value << " = " << first_value + second_value << std::endl; }

	stack.push_front(first_value + second_value);
}

void function_namespace::sub(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level) { std::cout << "Command \"sub\". " << first_value << " - " << second_value << " = " << first_value - second_value << std::endl; }

	stack.push_front(first_value - second_value);
}

void function_namespace::div(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level) { std::cout << "Command \"div\". " << first_value << " / " << second_value << " = " << first_value / second_value << std::endl; }

	stack.push_front(first_value / second_value);
}

void function_namespace::mul(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level) { std::cout << "Command \"mul\". " << first_value << " * " << second_value << " = " << first_value * second_value << std::endl; }

	stack.push_front(first_value * second_value);
}

bool function_namespace::ifeq_flag(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level)
	{
		std::cout << first_value << " is equale " << second_value << ": ";
		if (first_value == second_value) std::cout << "true" << std::endl;
		else std::cout << "false" << std::endl;
	}

	return first_value == second_value;
}

bool function_namespace::ifgr_flag(bool debug_level)
{
	int first_value = *stack.begin();
	int second_value = *(++stack.begin());

	if (debug_level)
	{
		std::cout << first_value << " is greater than " << second_value << ": ";
		if (first_value > second_value) std::cout << "true" << std::endl;
		else std::cout << "false" << std::endl;
	}

	return first_value > second_value;
}

int function_namespace::get_stack_head()
{
	return *stack.begin();
}

void function_namespace::push_stack_head(int value)
{
	stack.push_front(value);
}

void function_namespace::clear()
{
	variables.clear();
	stack.clear();
}

int function_namespace::begin()
{
	return function_begin;
}

int function_namespace::end()
{
	return function_end;
}

void function_namespace::show_variables()
{
	for (auto var : variables)
	{
		std::cout << var.first << ":\t" << var.second << std::endl;
	}
}

void function_namespace::show_stack()
{
	int i = 1;
	for (auto stack_element : stack)
	{
		std::cout << i << ":\t" << stack_element << std::endl;
		i++;
	}
}
