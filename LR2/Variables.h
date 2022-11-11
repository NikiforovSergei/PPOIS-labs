#pragma once

#include <string>
#include <map>
#include <iostream>

static std::map<std::string, double> vars;

class Variables {
private:	
	static const std::map<std::string, double> CONST_VARS;
public:
	void addOrChangeVar(std::string var_name, double var_value);
	double callVariable(std::string var_name);
};