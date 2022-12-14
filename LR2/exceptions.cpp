#include "exceptions.h"
	using namespace std;

exceptions::syntax_err::syntax_err(string command) : exception(command.c_str())
{
	this->command = command;
}

string exceptions::syntax_err::info()
{
	string info = "Command not found: " + string(command);
	return info;
}

exceptions::name_err::name_err(string name) : exception(name.c_str())
{
	this->name = name;
}

string exceptions::name_err::info()
{
	string info = "Name not found: " + string(name);
	return info;
}

exceptions::interpret_err::interpret_err(string message) : exception(message.c_str())
{
	this->message = message;
}

string exceptions::interpret_err::info()
{
	return message;
}
