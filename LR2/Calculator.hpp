#pragma once

#include "Solver.hpp"
#include "Exceptions.hpp"
#include "Tokens.hpp"
#include "Variables.hpp"
#include <string>


class Calculator {
public:
    std::string buffer;
    void start();
};
