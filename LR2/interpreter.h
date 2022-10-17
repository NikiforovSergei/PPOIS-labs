#pragma once
#ifndef _INTERPRETER_
#define _INTERPRETER_

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "function_namespace.h"


class interpreter
{
public:

	interpreter(std::string filename, bool debug_level);

	void interpret();

	int get_result();

	~interpreter();

private:

	enum commands
	{
		PUSH_DIGIT = 0,
		PUSH_LABEL = 1,
		POP = 2,
		POP_LABEL = 3,
		PEEK = 4,
		DUP = 5,
		ADD = 6,
		SUB = 7,
		DIV = 8,
		MUL = 9,
		IFEQ = 10, 
		IFGR = 11,
		GOTO_LABEL = 12,
		CALL_FUNC = 13,
		RETURN_FUNC = 14,
		CALLEXT_FUNC = 15,
		LABEL = 16,
		FUNCTION = 17,
		COMMENT = 18,
		FUNCTION_BRACKET_OPEN = 19,
		FUNCTION_BRACKET_CLOSED = 20
	};

	std::vector<std::pair<std::regex, commands>> command_templates
	{
		{std::regex("^push +(\\d+) *(#(.*))? *$"), PUSH_DIGIT},
		{std::regex("^push +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), PUSH_LABEL},
		{std::regex("^pop *(#(.*))? *$"), POP},
		{std::regex("^pop +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), POP_LABEL},
		{std::regex("^peek +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), PEEK},
		{std::regex("^dup *(#(.*))? *$"), DUP},
		{std::regex("^add *(#(.*))? *$"), ADD},
		{std::regex("^sub *(#(.*))? *$"), SUB},
		{std::regex("^div *(#(.*))? *$"), DIV},
		{std::regex("^mul *(#(.*))? *$"), MUL},
		{std::regex("^ifeq +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), IFEQ},
		{std::regex("^ifgr +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), IFGR},
		{std::regex("^goto +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), GOTO_LABEL},
		{std::regex("^call +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), CALL_FUNC},
		{std::regex("^return *(#(.*))? *$"), RETURN_FUNC},
		{std::regex("^callext +([A-Za-z_]{1}\\S*?) *(#(.*))? *$"), CALLEXT_FUNC},
		{std::regex("^([A-Za-z_]{1}\\S*?): *(#(.*))? *$"), LABEL},
		{std::regex("^function +([A-Za-z_]{1}\\S*?) *(\\{)? *(#(.*))? *$"), FUNCTION},
		{std::regex(" *(#(.*))? *$"), COMMENT},
		{std::regex("^ *\\{ *(#(.*))? *$"), FUNCTION_BRACKET_OPEN},
		{std::regex("^ *\\} *(#(.*))? *$"), FUNCTION_BRACKET_CLOSED}
	};

	void ifeq_label(std::string label);

	void ifgr_label(std::string label);

	void goto_label(std::string label);

	void call_func(std::string function_name);

	void return_func();

	void callext_func(std::string label);

	void compile_functions();

	void is_unique(std::string function_name);

	void check_for_main_function();
 
	std::pair<std::cmatch, commands> define_command(std::string& line);

	void call_command(std::pair<std::cmatch, commands> command_to_call);

	void show_function_call_stack();

	std::forward_list<std::pair<std::string, function_namespace>> function_call_stack;

	std::map<std::string, std::pair<int, int>> defined_functions;

	std::forward_list<int> reader_checkpoints;

	std::string filename;

	std::fstream reader;

	bool debug_level;

	bool main_is_called;

	int result;
};

#endif 

