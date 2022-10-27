#pragma once
#pragma once
#include <fstream>
#include <string>

class Copy_Class
{
public:
	void copy_class(std::ostream& out);
};

class Copy_Operators
{
public:
	void copy_push(std::ostream& out, std::string num);
	void copy_peek(std::ostream& out, std::string num);
	void copy_dup(std::ostream& out);
	void copy_add(std::ostream& out);
	void copy_sub(std::ostream& out);
	void copy_mul(std::ostream& out);
	void copy_div(std::ostream& out);
	void copy_print(std::ostream& out);
};

class CopySource :public Copy_Operators, public Copy_Class
{

};
