#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace Exception
{
	class syntax_err : public exception
	{
	public:
		syntax_err(string command);

		string what() {
			return "No such command" + command;
		}

	private:
		string command;
	};

	class name_err : public exception
	{
	public:
		name_err(string name);

		string info();

	private:
		string name;
	};

	class interpret_err : public exception
	{
	public:

		interpret_err(string message);

		string info();

	private:
		string message;
	};
}