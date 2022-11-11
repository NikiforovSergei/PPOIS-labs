#include "Exceptions.h"


std::string BaseException::what() {
	return exception_text;
}

VariablesException::VariablesException() {
	exception_text = "Error. Variable error.";
}

VariablesException::VariablesException(std::string exception_text) {
	this->exception_text = "Error. Variable error. " + exception_text;
}

VariableAlreadyExists::VariableAlreadyExists(std::string var_name) {
	exception_text = "Error. You've tried to add variable " + var_name + " which is protected. Try other name for variable.";
}

VariableDoesntExist::VariableDoesntExist(std::string var_name) {
	exception_text = "Error. You've tried to get " + var_name + " value. That variable doesn't exist. Create new one with that name.";
}

FunctionException::FunctionException() {
	exception_text = "Error. Function error.";
}

FunctionException::FunctionException(std::string exception_text) {
	this->exception_text = "Error. Function error. " + exception_text;
}

FunctionDoesntExist::FunctionDoesntExist(std::string func_name) {
	exception_text = "Error. You've tried to use function " + func_name + " which doesn't exist.";
}

FunctionWrongArgumentAmount::FunctionWrongArgumentAmount(std::string func_name, int user_argument_amount, int argument_amount) {
	exception_text = "Error. Function " + func_name + " takes " + std::to_string(argument_amount) + " arguments, but you've passed " + std::to_string(user_argument_amount);
}

FunctionNoCloseParenthesis::FunctionNoCloseParenthesis() {
	exception_text = "Error. No close parenthesis for function";
}

TokenException::TokenException() {
	exception_text = "Error. Token error.";
}

TokenException::TokenException(std::string exception_text) {
	this->exception_text = "Error. Token error. " + exception_text;
}

TokenUnresolvedException::TokenUnresolvedException() {
	exception_text = "Unresolved token type.";
}

BinaryOperatorError::BinaryOperatorError() {
	exception_text = "Operator error. Expected expression, variable, number or function call.";
}

AssignmentError::AssignmentError() {
	exception_text = "Assignment error. Can only assign a variable.";
}

NoCloseParenthesis::NoCloseParenthesis() {
	exception_text = "Error. Not enough closing or opening parenthesises";
}

NoArgumentError::NoArgumentError() {
	exception_text = "Error. Waited for argument, but hasn't found one.";
}


extern void pointer_print(int space_amount) {
	std::string spaces;
	spaces.assign(space_amount, ' ');
	spaces += '^';
	std::cout << spaces << std::endl;
}



