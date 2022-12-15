#pragma once


#include "Functions.hpp"
#include "Exceptions.hpp"
#include <regex>
#include <vector>
#include <string>
#include <algorithm>

enum TokenType {
    number,
    operation,
    variable,
    function,
    function_delimiter,
    assignment,
    r_parenthesis,
    l_parenthesis,
    other,
};

enum ExpressionType {
    var_assignment,
    solution_for_num,
};

class Lexeme {
private:
    std::string token_value;
    TokenType token_type;
    unsigned int index;
    int priority;
public:
    Lexeme(std::string token_value, TokenType token_type, unsigned int index, int priority);
    std::string getTokenValue();
    TokenType getTokenType();
    unsigned int getIndex();
    int getPriority();
    void setTokenValue(std::string token_value);
    void setTokenType(TokenType token_type);
    void setIndex(unsigned int index);
    void setPriority(int priority);
};

class TokenBuffer {
private:
    std::string buffer;
    std::vector <char> SEPS{ '+', '-', '*', '/', '^', '(', ')', ',', '=' };
    std::vector <Lexeme> readyTokens;
public:
    TokenBuffer(std::string buffer);
    void tokenDivider();
    std::vector <Lexeme> GetReadyTokens();
};


class TokenAnalyzer {
public:
    TokenAnalyzer(std::vector<Lexeme>& raw_tokens);
    void analyzeTokens();
    std::vector <Lexeme> GetTokenInfo();
private:
    std::vector <Lexeme> raw_tokens;
    const std::vector <std::string> OPERATORS{ "+", "-", "*", "/", "^", "(", ")", ",", "=" };
};
