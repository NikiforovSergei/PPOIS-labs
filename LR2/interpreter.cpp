#include "interpreter.h"
#include <iostream>
using namespace std;

void Interpreter::ifeq_label(string label, bool debug)
{
	if (debug)
	{
		cout << "IFEQ";
		if ((*function_call_stack.begin()).second.isEqual(debug))
		{
			cout << "True ifeq. Go to label\n";
			goto_label(label, debug);
		}
		else
			cout << "Condition not met\n";
	}
	else
	{
		if ((*function_call_stack.begin()).second.isEqual(debug))
			goto_label(label, debug);
	}
}

void Interpreter::ifgr_label(string label, bool debug)
{
	if (debug)
	{
		cout << "IFGR ";

		if ((*function_call_stack.begin()).second.isOver(debug))
		{
			cout << "Condition met. Go to label\n";
			goto_label(label, debug);
		}
		else
			cout << "Condition not met\n";
	}
	else
	{
		if ((*function_call_stack.begin()).second.isOver(debug))
			goto_label(label, debug);
	}

}

void Interpreter::goto_label(string label, bool debug)
{
	if (debug)
	{
		cout << "GOTO\t" << label << endl;

		string line;

		file.seekg((*function_call_stack.begin()).second.funcBegin, ios_base::beg);

		pair<cmatch, commands> command;

		do
		{
			getline(file, line);
			command = define_command(line);
			if (command.second == LABEL)
				if (command.first[1].str() == label)
					return;

		} while (command.second != FUNCTION_BRACKET_CLOSED);

		throw Exception::name_err("No label with name " + label);
	}
	else
	{
		string line;

		file.seekg((*function_call_stack.begin()).second.funcBegin, ios_base::beg);

		pair<cmatch, commands> command;

		do
		{
			getline(file, line);
			command = define_command(line);

			if (command.second == LABEL)
				if (command.first[1].str() == label)
					return;

		} while (command.second != FUNCTION_BRACKET_CLOSED);

		throw Exception::name_err("No label with name " + label);
	}
}

void Interpreter::call_func(string name_func, bool debug)
{
	if (debug)
	{
		cout << "CALL function\t" << name_func << endl;

		if (main_is_called)
		{
			if (name_func == "main") throw Exception::syntax_err("Function	MAIN isn't callable.");

			int argument = (*function_call_stack.begin()).second.funcBegin;

			Function func_namespace(defined_functions[name_func].first, defined_functions[name_func].second);

			func_namespace.stack.push(argument);

			function_call_stack.push_front({ name_func, func_namespace });

			reader_checkpoints.push_front(file.tellg());
		}
		else
		{
			Function main(defined_functions[name_func].first, defined_functions[name_func].second);

			function_call_stack.push_front({ name_func, main });

			main_is_called = true;
		}
		file.seekg((*function_call_stack.begin()).second.funcBegin, ios_base::beg);

		show_function_call_stack();
	}
	else
	{
		if (main_is_called)
		{
			if (name_func == "main")
				throw Exception::syntax_err("Function MAIN isn't callable.");

			int argument = (*function_call_stack.begin()).second.stack.top();

			Function func(defined_functions[name_func].first, defined_functions[name_func].second);

			func.stack.push(argument);

			function_call_stack.push_front({ name_func, func });

			reader_checkpoints.push_front(file.tellg());
		}
		else
		{
			Function main(defined_functions[name_func].first, defined_functions[name_func].second);

			function_call_stack.push_front({ name_func, main });

			main_is_called = true;
		}
		file.seekg((*function_call_stack.begin()).second.funcBegin, ios_base::beg);
	}
}

void Interpreter::return_func(bool debug)
{
	if (debug)
	{
		cout << "RETURN for function \"" << (*function_call_stack.begin()).first << "\"" << endl;

		int value_to_return = (*function_call_stack.begin()).second.stack.top();

		function_call_stack.pop_front();

		if (function_call_stack.empty())
		{
			result = value_to_return;
			return;
		}

		file.seekg(*reader_checkpoints.begin(), ios_base::beg);

		reader_checkpoints.pop_front();

		(*function_call_stack.begin()).second.stack.push(value_to_return);

		cout << "Returned value:\t" << value_to_return << " to function \"" << (*function_call_stack.begin()).first << "\"" << endl;

		show_function_call_stack();
	}
	else
	{
		int return_value = (*function_call_stack.begin()).second.stack.top();

		if ((*function_call_stack.begin()).first == "main")
		{
			cout << "Stack of MAIN function:\n";
			(*function_call_stack.begin()).second.printStack();
			result = return_value;
			function_call_stack.pop_front();
			return;
		}

		function_call_stack.pop_front();

		file.seekg(*reader_checkpoints.begin());

		reader_checkpoints.pop_front();

		(*function_call_stack.begin()).second.stack.push(return_value);
	}
}

void Interpreter::compile_functions()
{
	fstream book;

	book.open(filename);

	string line;

	while (getline(book, line))
	{
		cmatch function_matches;

		if (regex_match(line.c_str(), function_matches, command_templates[FUNCTION].first))
		{
			int function_begin, function_end;

			string function_name = function_matches[1].str();

			if (!function_matches[2].matched)
			{
				cmatch check_for_open;

				while (getline(book, line))
				{
					if (regex_match(line.c_str(), check_for_open, command_templates[FUNCTION_BRACKET_OPEN].first))
						break;
					if (regex_match(line.c_str(), check_for_open, command_templates[COMMENT].first))
						continue;
					throw Exception::syntax_err("Error in \"" + function_name + "\" function.");
				}
			}

			function_begin = book.tellg();

			cmatch check_for_closed;

			while (getline(book, line))
			{
				if (regex_match(line.c_str(), check_for_closed, command_templates[FUNCTION_BRACKET_CLOSED].first))
					break;

				if (regex_match(line.c_str(), check_for_closed, command_templates[FUNCTION].first))
					throw Exception::syntax_err(" Error in definition of \"" + function_name + "\" function.");

				if (regex_match(line.c_str(), check_for_closed, command_templates[FUNCTION_BRACKET_OPEN].first))
					throw Exception::syntax_err("Error in definition of \"" + function_name + "\" function.");
			}

			if (check_for_closed.size() == 0)
				throw Exception::syntax_err("No \"}\" used in \"" + function_name + "\" function.");

			function_end = book.tellg();

			is_unique(function_name);

			defined_functions.emplace(function_name, pair<int, int>(function_begin, function_end));
		}
	}

	check_for_main();
}

void Interpreter::is_unique(string function_name)
{
	for (auto function : defined_functions)
		if (function.first == function_name)
			throw Exception::syntax_err("Function \"" + function_name + "\" already exists.");
	return;
}

void Interpreter::check_for_main()
{
	for (auto function : defined_functions)
		if (function.first == "main")
			return;
	throw Exception::interpret_err("Error. There is no MAIN");
}

pair<cmatch, Interpreter::commands> Interpreter::define_command(string& line)
{
	cmatch matches;

	for (auto command_template : command_templates)
		if (regex_match(line.c_str(), matches, command_template.first))
			return { matches, command_template.second };

	throw Exception::syntax_err("No such command: \"" + line + "\".");
}

void Interpreter::call_command(pair<cmatch, Interpreter::commands> command_to_call, bool debug)
{
	switch (command_to_call.second)
	{
	case Interpreter::PUSH_DIGIT:
		(*function_call_stack.begin()).second.push(stoi(command_to_call.first[1].str()), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::PUSH_LABEL:
		(*function_call_stack.begin()).second.push(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::POP:
		(*function_call_stack.begin()).second.pop(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::POP_LABEL:
		(*function_call_stack.begin()).second.pop(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::PEEK:
		(*function_call_stack.begin()).second.peek(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::DUP:
		(*function_call_stack.begin()).second.dup(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::ADD:
		(*function_call_stack.begin()).second.add(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::SUB:
		(*function_call_stack.begin()).second.sub(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::DIV:
		(*function_call_stack.begin()).second.div(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::MUL:
		(*function_call_stack.begin()).second.mul(debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::IFEQ:
		ifeq_label(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::IFGR:
		ifgr_label(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::GOTO_LABEL:
		goto_label(command_to_call.first[1].str(), debug);
		if (debug)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case Interpreter::CALL_FUNC:
		call_func(command_to_call.first[1].str(), debug);
		if (debug)
			system("pause");
		break;

	case Interpreter::RETURN_FUNC:
		return_func(debug);
		break;

	case Interpreter::LABEL:
		break;

	case Interpreter::FUNCTION:
		throw Exception::interpret_err("Error in rhe definition of commands");
		break;

	case Interpreter::COMMENT:
		break;

	case Interpreter::FUNCTION_BRACKET_OPEN:
		throw Exception::syntax_err("Use { only to define function.");
		break;

	case Interpreter::FUNCTION_BRACKET_CLOSED:
		throw Exception::syntax_err("Function \"" + (*function_call_stack.begin()).first + "\" doesn't have RETURN");
		break;
	}
}

void Interpreter::show_function_call_stack()
{
	cout << "Function call stack:\n";
	int i = 1;
	for (auto function : this->function_call_stack)
	{
		cout << endl;
		cout << i << ".\nFunction:\t" << function.first << "\n.....................................\n" << "\nStack:\n";
		function.second.printStack();
		cout << "\n.....................................\n" << "Variables:\n";
		function.second.printVariables();
		i++;
	}
	cout << endl;
}

Interpreter::Interpreter(string filename, bool debug)
{
	this->filename = filename;

	file.open(filename);

	this->debug = debug;

	compile_functions();

	main_is_called = false;
}

void Interpreter::interpret()
{
	string line;

	call_func("main", debug);

	while (getline(file, line))
	{
		call_command(define_command(line), debug);

		if (function_call_stack.empty())
			return;
	}

	throw Exception::interpret_err("Unexpected end of file. Function call stack isn't empty");
}

int Interpreter::get_result()
{
	return result;
}

Interpreter::~Interpreter()
{
	function_call_stack.clear();
	defined_functions.clear();
	filename.clear();
	file.close();
}