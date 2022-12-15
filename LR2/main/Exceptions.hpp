#pragma once


#include <exception>
#include <string>
#include <iostream>



class BaseException : public std::exception {
protected:
    std::string exception_text;
public:
    std::string what();
};

class VariablesException : public BaseException {
public:
    VariablesException();
    VariablesException(std::string exception_text);
};

class VariableAlreadyExists final : public VariablesException {
public:
    VariableAlreadyExists(std::string var_name);
};

class VariableDoesntExist final : public VariablesException {
public:
    VariableDoesntExist(std::string var_name);
};

class FunctionException : public BaseException {
public:
    FunctionException();
    FunctionException(std::string exception_text);
};

class FunctionDoesntExist : public FunctionException {
public:
    FunctionDoesntExist(std::string func_name);
};

class FunctionWrongArgumentAmount final : public FunctionException {
public:
    FunctionWrongArgumentAmount(std::string func_name, int user_argument_amount, int argument_amount);
};

class FunctionNoCloseParenthesis final : public FunctionException {
public:
    FunctionNoCloseParenthesis();
};

class NoCloseParenthesis final : public BaseException {
public:
    NoCloseParenthesis();
};

class TokenException : public BaseException {
public:
    TokenException();
    TokenException(std::string exception_text);
};

class TokenUnresolvedException final : public TokenException {
public:
    TokenUnresolvedException();
};

class BinaryOperatorError final : public BaseException {
public:
    BinaryOperatorError();
};

class AssignmentError final :public BaseException {
public:
    AssignmentError();
};

class NoArgumentError final : public BaseException {
public:
    NoArgumentError();
};


extern void pointer_print(int space_amount);
