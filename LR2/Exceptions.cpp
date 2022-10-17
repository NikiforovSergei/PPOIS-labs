#include "Exceptions.h"

Exceptions::SyntaxError::SyntaxError(std::string damaged_command) : exception(damaged_command.c_str())
{
	this->damaged_command = damaged_command;
}

std::string Exceptions::SyntaxError::get_info()
{
	std::string info = "No such command: " + std::string(damaged_command);
	return info;
}

Exceptions::NameError::NameError(std::string damaged_name) : exception(damaged_name.c_str())
{
	this->damaged_name = damaged_name;
}

std::string Exceptions::NameError::get_info()
{
	std::string info = "No such name: " + std::string(damaged_name);
	return info;
}

Exceptions::InterpreterError::InterpreterError(std::string error_msg) : exception(error_msg.c_str())
{
	this->error_msg = error_msg;
}

std::string Exceptions::InterpreterError::get_info()
{
	return error_msg;
}
