#pragma once

#include <string>
#include <map>
#include <iostream>
#include "Exceptions.h"

static std::map<std::string, double> vars;

class Variables {
private:
	static const std::map<std::string, double> CONST_VARS;
public:
	void addOrChangeVar(std::string var_name, double var_value) {
		if (CONST_VARS.find(var_name) != CONST_VARS.end()) {
			throw VariableAlreadyExists(var_name);
			return;
		}
		if (vars.find(var_name) == vars.end()) {
			std::cout << "Variable " << var_name << " with value " << var_value << " was created!" << std::endl;
		}
		else {
			std::cout << "Value of variable " << var_name << " was changed to " << var_value << std::endl;
		}
		vars[var_name] = var_value;
	}
	double callVariable(std::string var_name) {
		try {
			return CONST_VARS.at(var_name);
		}
		catch (std::out_of_range e) {
			throw VariablesException();
		}
		try {
			return vars.at(var_name);
		}
		catch (std::out_of_range e) {
			throw VariableDoesntExist(var_name);
		}
	}
};