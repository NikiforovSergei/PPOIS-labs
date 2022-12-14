#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "function.h"

using namespace std;

class machine
{
public:

	machine(string filename, bool debug_level);

	~machine();

	void interpret();

	int get_result();


private:

	enum commands
	{
		PUSH_DIGIT = 0,
		PUSH_LABEL,
		POP,
		POP_LABEL,
		PEEK,
		DUP,
		ADD,
		SUB,
		DIV,
		MUL,
		IFEQ,
		IFGR,
		GOTO_LABEL,
		CALL_FUNC,
		RETURN_FUNC,
		CALLEXT_FUNC,
		LABEL,
		FUNCTION,
		COMMENT,
		FUNCTION_BRACKET_OPEN,
		FUNCTION_BRACKET_CLOSED
	};

	vector<pair<regex, commands>> command_templates
	{
		{regex("^push +(\\d+) *(#(.*))? *$"), PUSH_DIGIT},
		{regex("^push +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), PUSH_LABEL},
		{regex("^pop *(#(.*))? *$"), POP},
		{regex("^pop +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), POP_LABEL},
		{regex("^peek +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), PEEK},
		{regex("^dup *(#(.*))? *$"), DUP},
		{regex("^add *(#(.*))? *$"), ADD},
		{regex("^sub *(#(.*))? *$"), SUB},
		{regex("^div *(#(.*))? *$"), DIV},
		{regex("^mul *(#(.*))? *$"), MUL},
		{regex("^ifeq +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), IFEQ},
		{regex("^ifgr +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), IFGR},
		{regex("^goto +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), GOTO_LABEL},
		{regex("^call +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), CALL_FUNC},
		{regex("^return *(#(.*))? *$"), RETURN_FUNC},
		{regex("^callext +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), CALLEXT_FUNC},
		{regex("^([A-Za-z_]{1}\\S*?): *(#(.*))? *$"), LABEL},
		{regex("^function +([A-Za-z_]{1}\\S*?) *(\\{)? *(#(.*))? *$"), FUNCTION},
		{regex(" *(#(.*))? *$"), COMMENT},
		{regex("^ *\\{ *(#(.*))? *$"), FUNCTION_BRACKET_OPEN},
		{regex("^ *\\} *(#(.*))? *$"), FUNCTION_BRACKET_CLOSED}
	};

	void ifeq_label(string label);

	void ifgr_label(string label);

	void goto_label(string label);

	void call_func(string function_name);

	void return_func();

	void callext_func(string label);

	void compile_functions();

	void is_unique(string function_name);

	void check_for_main();

	pair<cmatch, commands> define_command(string& line);

	void call_command(pair<cmatch, commands> command_to_call);

	void show_function_call_stack();

	forward_list<pair<string, function>> function_call_stack;

	map<string, pair<int, int>> defined_functions;

	forward_list<int> reader_checkpoints;

	string filename;

	fstream file;

	bool debug;

	bool main_is_called;

	int result;
};

#endif 

