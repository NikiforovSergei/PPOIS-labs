#pragma once

#include <string>
#include <map>
#include <iostream>


class Variables {
private:
    static const std::map<std::string, double> CONST_VARS;
    static std::map<std::string, double> vars;
public:
    void addOrChangeVar(std::string var_name, double var_value);
    double callVariable(std::string var_name);
};
