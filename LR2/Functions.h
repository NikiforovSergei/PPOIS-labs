#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdarg.h>
#include "Exceptions.h"


class Functions {
private:
	const std::vector<std::string> UNARY_FUNCS{ "sin", "cos", "abs", "ln", "log", "sqrt" };
	const std::vector<std::string> BINARY_FUNCS{ "pow", "max", "min" };
public:
	double countFunc(std::string func_name, std::vector <double> func_args) {
		if ((std::find(BINARY_FUNCS.begin(), BINARY_FUNCS.end(), func_name) == BINARY_FUNCS.end()) && (std::find(UNARY_FUNCS.begin(), UNARY_FUNCS.end(), func_name) == UNARY_FUNCS.end())) {
			throw FunctionDoesntExist(func_name);
		}
		if (std::find(BINARY_FUNCS.begin(), BINARY_FUNCS.end(), func_name) != BINARY_FUNCS.end()) {
			if (func_args.size() != 2) {
				throw FunctionWrongArgumentAmount(func_name, func_args.size(), 2);
			}
			if (func_name == "pow") {
				return pow(func_args[1], func_args[0]);
			}
			else if (func_name == "min") {
				return func_args[0] < func_args[1] ? func_args[0] : func_args[1];
			}
			else if (func_name == "max") {
				return func_args[0] > func_args[1] ? func_args[0] : func_args[1];
			}
		}
		else {
			if (func_args.size() != 1) {
				throw FunctionWrongArgumentAmount(func_name, func_args.size(), 1);
			}
			if (func_name == "sin") {
				return sin(func_args[0]);
			}
			else if (func_name == "cos") {
				return cos(func_args[0]);
			}
			else if (func_name == "abs") {
				return abs(func_args[0]);
			}
			else if (func_name == "ln") {
				return log(func_args[0]);
			}
			else if (func_name == "log") {
				return log10(func_args[0]);
			}
			else if (func_name == "sqrt") {
				return sqrt(func_args[0]);
			}
		}
		throw FunctionException();
	}
	std::string funcType(std::string func_name) {
		if (std::find(BINARY_FUNCS.begin(), BINARY_FUNCS.end(), func_name) != BINARY_FUNCS.end()) {
			return "Binary";
		}
		else if (std::find(UNARY_FUNCS.begin(), UNARY_FUNCS.end(), func_name) != UNARY_FUNCS.end()) {
			return "Unary";
		}
		else {
			return "NotFunction";
		}
	}
};