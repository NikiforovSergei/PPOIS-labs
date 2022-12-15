#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdarg.h>


class Functions {
private:
    const std::vector<std::string> UNARY_FUNCS{"sin", "cos", "abs", "ln", "log", "sqrt"};
    const std::vector<std::string> BINARY_FUNCS{ "pow", "max", "min" };
public:
    double count_func(std::string func_name, std::vector <double> func_args);
    std::string func_type(std::string func_name);
};
