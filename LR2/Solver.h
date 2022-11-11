#pragma once


#include "Functions.h"
#include "Tokens.h"
#include "Variables.h"
#include "Exceptions.h"
#include <stack>



class ExpressionAnalyzer {
public:
	ExpressionAnalyzer(std::vector <Lexeme>& raw_tokens);
	void analyze_prioritize();	
	std::vector <Lexeme> getTokens();	
private:
	std::vector <Lexeme> raw_tokens;	
	const std::map <std::string, int> OPERATOR_PRIORITY{ {"=", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"-u", 3}, {"^", 4}, {"func", 5}, {"(", 0}, {")", 0}};	
};

class ExpressionSolver {
private:
	std::stack<Lexeme> operators_stack;
	std::stack<Lexeme> values_stack;
	std::vector<Lexeme> tokens;
	void solve_operator();
	double get_top_value();
public:
	ExpressionSolver(std::vector<Lexeme> tokens);
	double solve();
};