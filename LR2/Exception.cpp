#include "Exception.h"
using namespace std;

Exception::syntax_err::syntax_err(string command) : exception(command.c_str())
{
	this->command = command;
}

Exception::name_err::name_err(string name) : exception(name.c_str())
{
	this->name = name;
}

string Exception::name_err::info()
{
	string info = "No such name: " + string(name);
	return info;
}

Exception::interpret_err::interpret_err(string message) : exception(message.c_str())
{
	this->message = message;
}

string Exception::interpret_err::info()
{
	return message;
}