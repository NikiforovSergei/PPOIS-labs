#pragma once

#include <exception>
#include <string>
#include <iostream>

class MyException : public std::exception {
protected:
	std::string exception_text;
public:
	std::string what() {
		return exception_text;
	}
};

class InputException : public MyException {
public:
	InputException() {
		exception_text = "Error. Wrong input.";
	}
};

class VariablesException : public MyException {
public:
	VariablesException() {
		exception_text = "Error. Variable error.";
	}
	VariablesException(std::string exception_text) {
		this->exception_text = "Error. Variable error. " + exception_text;
	}
};

class VariableAlreadyExists final : public VariablesException {
public:
	VariableAlreadyExists(std::string var_name) {
		exception_text = "Error. You've tried to add variable " + var_name + " which is protected. Try other name for variable.";
	}
};

class VariableDoesntExist final : public VariablesException {
public:
	VariableDoesntExist(std::string var_name) {
		exception_text = "Error. You've tried to get " + var_name + " value. That variable doesn't exist. Create new one with that name.";
	}
};

class FunctionException : public MyException {
public:
	FunctionException() {
		exception_text = "Error. Function error.";
	}
	FunctionException(std::string exception_text) {
		this->exception_text = "Error. Function error. " + exception_text;
	}
};

class FunctionDoesntExist : public FunctionException {
public:
	FunctionDoesntExist(std::string func_name) {
		exception_text = "Error. You've tried to use function " + func_name + " which doesn't exist.";
	}
};

class FunctionWrongArgumentAmount final : public FunctionException {
public:
	FunctionWrongArgumentAmount(std::string func_name, int user_argument_amount, int argument_amount) {
		exception_text = "Error. Function " + func_name + " takes " + std::to_string(argument_amount) + " arguments, but you've passed " + std::to_string(user_argument_amount);
	}
};

class FunctionNoCloseParenthesis final : public FunctionException {
public:
	FunctionNoCloseParenthesis() {
		exception_text = "Error. No close parenthesis for function";
	}
};

class NoCloseParenthesis final : public MyException {
public:
	NoCloseParenthesis() {
		exception_text = "Error. Not enough closing or opening parenthesises";
	}
};

class TokenException : public MyException {
public:
	TokenException() {
		exception_text = "Error. Token error.";
	}
	TokenException(std::string exception_text) {
		this->exception_text = "Error. Token error. " + exception_text;
	}
};

class TokenUnresolvedException final : public TokenException {
public:
	TokenUnresolvedException() {
		exception_text = "Unresolved token type.";
	}
};

class BinaryOperatorError final : public MyException {
public:
	BinaryOperatorError() {
		exception_text = "Operator error. Expected expression, variable, number or function call.";
	}
};

class AssignmentError final :public MyException {
public:
	AssignmentError() {
		exception_text = "Assignment error. Can only assign a variable.";
	}
};

class NoArgumentError final : public MyException {
public:
	NoArgumentError() {
		exception_text = "Error. Waited for argument, but hasn't found one.";
	}
};


extern void pointerPrint(int space_amount) {
	std::string spaces;
	spaces.assign(space_amount, ' ');
	spaces += '^';
	std::cout << spaces << std::endl;
}
