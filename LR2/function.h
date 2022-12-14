#pragma once

#ifndef _STACK_MACHINE_
#define _STACK_MACHINE_

#include <forward_list>
#include <string>
#include <map>
#include "exceptions.h"


class function
{
public:

	function() = default;

	function(int function_begin, int function_end);

	void push(int value, bool debug = false);

	void push(string label, bool debug = false);

	void pop(string label, bool debug = false);

	void pop(bool debug = false);

	void peek(string label, bool debug = false);

	void dup(bool debug = false);

	void add(bool debug = false);

	void sub(bool debug = false);

	void div(bool debug = false);

	void mul(bool debug = false);

	bool ifeq_flag(bool debug = false);

	bool ifgr_flag(bool debug = false);

	int get_stack_head();

	void push_stack_head(int value);

	void clear();

	int get_begin();

	int get_end();

	void show_variables();

	void show_stack();

private:

	map<string, int> variables;

	forward_list<int> stack;

	int begin_func, end_func;
};


#endif 