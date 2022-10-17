#pragma once

#ifndef _STACK_MACHINE_
#define _STACK_MACHINE_

#include <forward_list>
#include <string>
#include <map>
#include "Exceptions.h"


class function_namespace
{
public:

	function_namespace() = default;

	function_namespace(int function_begin, int function_end);

	void push(int value, bool debug_level = false);
	void push(std::string label, bool debug_level = false);

	void pop(std::string label, bool debug_level = false);
	void pop(bool debug_level = false);

	void peek(std::string label, bool debug_level = false);

	void dup(bool debug_level = false);

	void add(bool debug_level = false);
	
	void sub(bool debug_level = false);

	void div(bool debug_level = false);

	void mul(bool debug_level = false);

	bool ifeq_flag(bool debug_level = false);

	bool ifgr_flag(bool debug_level = false);

	int get_stack_head();

	void push_stack_head(int value);

	void clear();

	int begin();

	int end();

	void show_variables();

	void show_stack();

private:

	std::map<std::string, int> variables;

	std::forward_list<int> stack;

	int function_begin;

	int function_end;
};


#endif // !_STACK_MACHINE_