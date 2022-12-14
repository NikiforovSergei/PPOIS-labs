#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>
using namespace std;

namespace exceptions
{
	class syntax_err : public exception
	{
	public:

		syntax_err(string command);
		string info();

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


#endif 
