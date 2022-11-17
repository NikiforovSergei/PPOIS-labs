#pragma once

#include <iostream>
#include <string>

namespace Exceptions
{
	class SyntaxError : public std::exception
	{
	public:
		SyntaxError(std::string damaged_command);

		std::string get_info();

	private:
		std::string damaged_command;

	};

	class NameError : public std::exception
	{
	public:
		NameError(std::string damaged_name);

		std::string get_info();

	private:
		std::string damaged_name;

	};

	class InterpreterError : public std::exception
	{
	public:

		InterpreterError(std::string error_msg);

		std::string get_info();

	private:
		std::string error_msg;
	};

}
