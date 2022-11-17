#include "interpreter.h"

using namespace std;

void interpreter::ifeq_label(std::string label)
{
	if (debug_level)
	{
		cout << "\"ifeq\" command.";
		if ((*function_call_stack.begin()).second.ifeq_flag(debug_level))
		{
			cout << "Condition met. Go to label\n";
			goto_label(label);
		}
		else cout << "Condition not met\n";
	}
	else
	{
		if ((*function_call_stack.begin()).second.ifeq_flag())
		{
			goto_label(label);
		}
	}
}

void interpreter::ifgr_label(std::string label)
{
	if (debug_level)
	{
		cout << "\"ifgr\" command.";
		if ((*function_call_stack.begin()).second.ifgr_flag(debug_level))
		{
			cout << "Condition met. Go to label\n";
			goto_label(label);
		}
		else cout << "Condition not met\n";
	}
	else
	{
		if ((*function_call_stack.begin()).second.ifgr_flag())
		{
			goto_label(label);
		}
	}

}

void interpreter::goto_label(std::string label)
{
	if (debug_level)
	{
		cout << "\"goto\" command. Label:\t" << label << endl;

		std::string buffer;
		reader.seekg((*function_call_stack.begin()).second.begin(), ios_base::beg);
		pair<cmatch, commands> command;
		do
		{
			getline(reader, buffer);
			command = define_command(buffer);
			if (command.second == LABEL)
			{
				if (command.first[1].str() == label) return;
			}
		} while (command.second != FUNCTION_BRACKET_CLOSED);
		throw Exceptions::NameError("No label named\"" + label + "\" founed.");
	}
	else
	{
		std::string buffer;
		reader.seekg((*function_call_stack.begin()).second.begin(), ios_base::beg);
		pair<cmatch, commands> command;
		do
		{
			getline(reader, buffer);
			command = define_command(buffer);
			if (command.second == LABEL)
			{
				if (command.first[1].str() == label) return;
			}
		} while (command.second != FUNCTION_BRACKET_CLOSED);
		throw Exceptions::NameError("No label named\"" + label + "\" founed.");
	}
}

void interpreter::call_func(std::string function_name)
{
	if (debug_level)
	{
		cout << "\"call\" command. Function name:\t" << function_name << endl;
		if (main_is_called)
		{
			if (function_name == "main") throw Exceptions::SyntaxError("Function \"main\" isn't callable.");
			int argument = (*function_call_stack.begin()).second.get_stack_head();
			function_namespace func_namespace(defined_functions[function_name].first, defined_functions[function_name].second);
			func_namespace.push_stack_head(argument);
			function_call_stack.push_front({ function_name, func_namespace });
			reader_checkpoints.push_front(reader.tellg());
		}
		else
		{
			function_namespace main(defined_functions[function_name].first, defined_functions[function_name].second);
			function_call_stack.push_front({ function_name, main });
			main_is_called = true;
		}
		reader.seekg((*function_call_stack.begin()).second.begin(), ios_base::beg);
		show_function_call_stack();
	}
	else
	{
		if (main_is_called)
		{
			if (function_name == "main") throw Exceptions::SyntaxError("Function \"main\" isn't callable.");
			int argument = (*function_call_stack.begin()).second.get_stack_head();
			function_namespace func_namespace(defined_functions[function_name].first, defined_functions[function_name].second);
			func_namespace.push_stack_head(argument);
			function_call_stack.push_front({ function_name, func_namespace });
			reader_checkpoints.push_front(reader.tellg());
		}
		else
		{
			function_namespace main(defined_functions[function_name].first, defined_functions[function_name].second);
			function_call_stack.push_front({ function_name, main });
			main_is_called = true;
		}
		reader.seekg((*function_call_stack.begin()).second.begin(), ios_base::beg);
	}
}

void interpreter::return_func()
{
	if (debug_level)
	{
		cout << "\"return\" command for function \"" << (*function_call_stack.begin()).first << "\"" << endl;
		int value_to_return = (*function_call_stack.begin()).second.get_stack_head();

		function_call_stack.pop_front();

		if (function_call_stack.empty())
		{
			result = value_to_return;
			return;
		}

		reader.seekg(*reader_checkpoints.begin(), ios_base::beg);
		reader_checkpoints.pop_front();
		(*function_call_stack.begin()).second.push_stack_head(value_to_return);

		cout << "Returned value:\t" << value_to_return << " to function \"" << (*function_call_stack.begin()).first << "\"" << endl;
		show_function_call_stack();
	}
	else
	{
		int value_to_return = (*function_call_stack.begin()).second.get_stack_head();

		if ((*function_call_stack.begin()).first == "main")
		{
			cout << "Stack of \"main\" function:\n";
			(*function_call_stack.begin()).second.show_stack();
			result = value_to_return;
			function_call_stack.pop_front();
			return;
		}

		function_call_stack.pop_front();

		reader.seekg(*reader_checkpoints.begin(), ios_base::beg);
		reader_checkpoints.pop_front();
		(*function_call_stack.begin()).second.push_stack_head(value_to_return);
	}
}

void interpreter::callext_func(std::string label)
{
}

void interpreter::compile_functions()
{
	fstream fin;
	fin.open(filename, fstream::in);
	string line;
	while (getline(fin, line))
	{
		cmatch function_definition;
		if (regex_match(line.c_str(), function_definition, command_templates[FUNCTION].first))
		{
			int function_begin, function_end;
			string function_name = function_definition[1].str();

			if (!function_definition[2].matched)
			{
				cmatch check_for_open_bracket;
				while (getline(fin, line))
				{
					if (regex_match(line.c_str(), check_for_open_bracket, command_templates[FUNCTION_BRACKET_OPEN].first))	break;
					if (regex_match(line.c_str(), check_for_open_bracket, command_templates[COMMENT].first))	continue;
					throw Exceptions::SyntaxError("Incorrect order of function definition.\"" + function_name + "\" function.");
				}
			}

			function_begin = fin.tellg();

			cmatch check_for_closed_bracket;
			while (getline(fin, line))
			{
				if (regex_match(line.c_str(), check_for_closed_bracket, command_templates[FUNCTION_BRACKET_CLOSED].first)) break;
				if (regex_match(line.c_str(), check_for_closed_bracket, command_templates[FUNCTION].first))
				{
					throw Exceptions::SyntaxError("You can't define function in the other function. Error in definition of \"" + function_name + "\" function.");
				}
				if (regex_match(line.c_str(), check_for_closed_bracket, command_templates[FUNCTION_BRACKET_OPEN].first))
				{
					throw Exceptions::SyntaxError("You can't use \"{\" in this case. Error in definition of \"" + function_name + "\" function.");
				}
			}
			if (check_for_closed_bracket.size() == 0) throw Exceptions::SyntaxError("No \"}\" used in definition of \"" + function_name + "\" function.");

			function_end = fin.tellg();

			is_unique(function_name);
			defined_functions.emplace(function_name, pair<int, int>(function_begin, function_end));
		}
	}

	check_for_main_function();
}

void interpreter::is_unique(std::string function_name)
{
	for (auto function : defined_functions)
	{
		if (function.first == function_name) throw Exceptions::SyntaxError("Function names must be unique. Name \"" + function_name + "\" already exists.");;
	}
	return;
}

void interpreter::check_for_main_function()
{
	for (auto function : defined_functions)
	{
		if (function.first == "main") return;
	}
	throw Exceptions::InterpreterError("No function \"main\" found. No point of entry.");
}

pair<cmatch, interpreter::commands> interpreter::define_command(std::string& line)
{
	cmatch result;
	for (auto command_template : command_templates)
	{
		if (regex_match(line.c_str(), result, command_template.first))
		{
			return { result, command_template.second };
		}
	}
	throw Exceptions::SyntaxError("No such command: \"" + line + "\".");
}

void interpreter::call_command(pair<cmatch, interpreter::commands> command_to_call)
{
	switch (command_to_call.second)
	{
	case interpreter::PUSH_DIGIT:
		(*function_call_stack.begin()).second.push(stoi(command_to_call.first[1].str()), debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::PUSH_LABEL:
		(*function_call_stack.begin()).second.push(command_to_call.first[1].str(), debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::POP:
		(*function_call_stack.begin()).second.pop(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::POP_LABEL:
		(*function_call_stack.begin()).second.pop(command_to_call.first[1].str(), debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::PEEK:
		(*function_call_stack.begin()).second.peek(command_to_call.first[1].str(), debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::DUP:
		(*function_call_stack.begin()).second.dup(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::ADD:
		(*function_call_stack.begin()).second.add(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::SUB:
		(*function_call_stack.begin()).second.sub(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::DIV:
		(*function_call_stack.begin()).second.div(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::MUL:
		(*function_call_stack.begin()).second.mul(debug_level);
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::IFEQ:
		ifeq_label(command_to_call.first[1].str());
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::IFGR:
		ifgr_label(command_to_call.first[1].str());
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::GOTO_LABEL:
		goto_label(command_to_call.first[1].str());
		if (debug_level)
		{
			show_function_call_stack();
			system("pause");
		}
		break;

	case interpreter::CALL_FUNC:
		call_func(command_to_call.first[1].str());
		if (debug_level) system("pause");
		break;

	case interpreter::RETURN_FUNC:
		return_func();
		break;

	case interpreter::CALLEXT_FUNC:
		callext_func(command_to_call.first[1].str());
		break;

	case interpreter::LABEL:
		break;

	case interpreter::FUNCTION:
		throw Exceptions::InterpreterError("Interpreter breaked namespaces. Program stopped to prevent errors.");
		break;

	case interpreter::COMMENT:
		break;

	case interpreter::FUNCTION_BRACKET_OPEN:
		//Придерживаясь логики создания функций, такой исход возможен лишь при синтаксической ошибке.
		throw Exceptions::SyntaxError("Use \"{\" only to define function.");
		break;

	case interpreter::FUNCTION_BRACKET_CLOSED:
		throw Exceptions::SyntaxError("Function \"" + (*function_call_stack.begin()).first + "\" has no operator \"return\"");
		break;
	}
}

void interpreter::show_function_call_stack()
{
	cout << "Function call stack:\n";
	int i = 1;
	for (auto function : this->function_call_stack)
	{
		cout << endl;
		cout << i << ".\nName:\t" << function.first << "\n========================================\n" << "\nStack:\n";
		function.second.show_stack();
		cout << "\n========================================\n" << "Variables:\n";
		function.second.show_variables();
		i++;
	}
	cout << endl;
}

interpreter::interpreter(std::string filename, bool debug_level)
{
	this->filename = filename;
	reader.open(filename, fstream::in);

	this->debug_level = debug_level;

	compile_functions();
	main_is_called = false;
}

void interpreter::interpret()
{
	string buffer;
	call_func("main");
	while (getline(reader, buffer))
	{
		call_command(define_command(buffer));
		if (function_call_stack.empty()) return;
	}
	throw Exceptions::InterpreterError("Unexpected end of file. Function call stack isn't empty");
}

int interpreter::get_result()
{
	return result;
}

interpreter::~interpreter()
{
	function_call_stack.clear();
	defined_functions.clear();
	filename.clear();
	reader.close();
}
