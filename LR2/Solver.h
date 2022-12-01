#pragma once

#include "Functions.h"
#include "Lexeme.h"
#include "Variables.h"
#include "Exceptions.h"
#include "Tree.h"
#include <stack>

class ExpressionAnalyzer {
private:
	std::vector <Lexeme> rawTokens;
	const std::map <std::string, int> OPERATOR_PRIORITY{ {"=", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"-u", 3}, {"^", 4}, {"func", 5}, {"(", 0}, {")", 0} };
public:
	ExpressionAnalyzer(std::vector <Lexeme>& rawTokens) {
		this->rawTokens = rawTokens;
	}
	void analyzePrioritize() {
		try {
			if ((rawTokens[1].getTokenType() == TokenType::assignment) && (rawTokens[0].getTokenType() != TokenType::variable)) {
				pointerPrint(rawTokens[1].getIndex());
				throw AssignmentError();
			}
		}
		catch (...) {

		}
		int additionalPriority = 0;
		int unclosedParenthesis = 0;
		std::vector <Lexeme>::iterator it = rawTokens.begin();
		bool unaryMinusPossible = true;
		bool operationPossible = true;
		while (it != rawTokens.end()) {
			if (it->getTokenType() == assignment) {
				if (it != ++rawTokens.begin()) {
					pointerPrint(it->getIndex());
					throw AssignmentError();
				}
				unaryMinusPossible = true;
				it->setPriority(OPERATOR_PRIORITY.at("=") + additionalPriority);
			}
			else if (it->getTokenType() == l_parenthesis) {
				additionalPriority += OPERATOR_PRIORITY.at("(");
				unclosedParenthesis++;
				unaryMinusPossible = true;
				operationPossible = false;
			}
			else if (it->getTokenType() == r_parenthesis) {
				additionalPriority += OPERATOR_PRIORITY.at(")");
				unclosedParenthesis--;
				unaryMinusPossible = false;
				operationPossible = true;
			}
			else if (it->getTokenType() == TokenType::function_delimiter) {
				unaryMinusPossible = true;
				operationPossible = false;
			}
			else if (it->getTokenType() == operation) {
				if ((++it) == rawTokens.end()) {
					pointerPrint((--it)->getIndex() + 2);
					throw BinaryOperatorError();
				}
				else {
					--it;
				}
				if (it->getTokenValue() == "-") {
					if (it == rawTokens.begin()) {
						if ((++it)->getTokenType() == TokenType::operation) {
							pointerPrint((--it)->getIndex() + 2);
							throw BinaryOperatorError();
						}
						--it;
						it->setPriority(OPERATOR_PRIORITY.at("-u") + additionalPriority);
						it->setTokenValue("-u");
					}
					else {
						if (unaryMinusPossible) {
							if ((++it)->getTokenType() == TokenType::operation) {
								pointerPrint((--it)->getIndex() + 2);
								throw BinaryOperatorError();
							}
							--it;
							it->setTokenValue("-u");
							it->setPriority(OPERATOR_PRIORITY.at("-u") + additionalPriority);
						}
						else {
							if (!operationPossible) {
								pointerPrint(it->getIndex() + 2);
								throw BinaryOperatorError();
							}
							it->setPriority(OPERATOR_PRIORITY.at("-") + additionalPriority);
						}
					}
					unaryMinusPossible = false;
				}
				else {
					if (!operationPossible) {
						pointerPrint(it->getIndex() + 2);
						throw BinaryOperatorError();
					}
					it->setPriority(OPERATOR_PRIORITY.at(it->getTokenValue()) + additionalPriority);
					unaryMinusPossible = true;
				}
				operationPossible = false;
			}
			else if (it->getTokenType() == TokenType::function) {
				operationPossible = true;
				Functions checkFunction;
				std::string functionType = checkFunction.funcType(it->getTokenValue());
				if (functionType == "NotFunction") {
					pointerPrint(it->getIndex());
					throw FunctionDoesntExist(it->getTokenValue());
				}
				else {
					auto current_it = it;
					int arg_count = 0;
					while (current_it != rawTokens.end()) {
						if (current_it->getTokenType() == TokenType::r_parenthesis) break;
						if (arg_count == 0 && current_it->getTokenType() != TokenType::r_parenthesis) arg_count++;
						else if (current_it->getTokenType() == TokenType::function_delimiter) arg_count++;
						current_it++;
					}
					if (functionType == "Binary" && arg_count != 2) {
						pointerPrint(it->getIndex());
						throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
					}
					else if (functionType == "Unary" && arg_count != 1) {
						pointerPrint(it->getIndex());
						throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
					}
					current_it++;
				}
				it->setPriority(OPERATOR_PRIORITY.at("func") + additionalPriority);
			}
			else if (it->getTokenType() == TokenType::other) {
				pointerPrint(it->getIndex());
				throw TokenUnresolvedException();
			}
			else {
				unaryMinusPossible = false;
				operationPossible = true;
			}
			it++;
		}
		if (unclosedParenthesis != 0) {
			throw NoCloseParenthesis();
		}
	}
	std::vector <Lexeme> getTokens() {
		return this->rawTokens;
	}
};

class ExpressionSolver {
private:

	std::stack<Lexeme> operatorsTree;
	std::stack<Lexeme> valuesTree;
	std::vector<Lexeme> tokens;
	Node root();

	void solveOperator() {
		if (operatorsTree.top().getTokenType() == TokenType::operation) {
			if (operatorsTree.top().getTokenValue() == "-u") {
				double result = (-1) * getTopValue();
				Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
				valuesTree.push(new_value);
				operatorsTree.pop();
			}
			else {
				std::vector<double> args;
				for (int i = 0; i < 2; i++) {
					args.push_back(getTopValue());
				}
				double result = 0;
				if (operatorsTree.top().getTokenValue() == "-") {
					result = args[1] - args[0];
				}
				else if (operatorsTree.top().getTokenValue() == "+") {
					result = args[1] + args[0];
				}
				else if (operatorsTree.top().getTokenValue() == "/") {
					result = args[1] / args[0];
				}
				else if (operatorsTree.top().getTokenValue() == "*") {
					result = args[1] * args[0];
				}
				else if (operatorsTree.top().getTokenValue() == "^") {
					result = pow(args[1], args[0]);
				}
				operatorsTree.pop();
				Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
				valuesTree.push(new_value);
			}
		}
		else if (operatorsTree.top().getTokenType() == TokenType::function) {
			Functions func_solver;
			std::vector<double> args;
			if (func_solver.funcType(operatorsTree.top().getTokenValue()) == "Binary") {
				for (int i = 0; i < 2; i++) {
					args.push_back(getTopValue());
				}
			}
			else {
				args.push_back(getTopValue());
			}
			double result = func_solver.countFunc(operatorsTree.top().getTokenValue(), args);
			operatorsTree.pop();
			Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
			valuesTree.push(new_value);
		}
	}

public:
	ExpressionSolver(std::vector<Lexeme> tokens) {
		this->tokens = tokens;
	}

	double getTopValue() {
		Lexeme top_value = valuesTree.top();
		valuesTree.pop();
		if (top_value.getTokenType() == TokenType::number) {
			return std::stod(top_value.getTokenValue());
		}
		else if (top_value.getTokenType() == TokenType::variable) {
			Variables variables;
			return variables.callVariable(top_value.getTokenValue());
		}
		else {
			throw std::exception("Value can either number or variable!");
		}
	}

	double solve() {
		std::vector<Lexeme>::iterator it = tokens.begin();
		double value = 0;
		while (it != tokens.end()) {
			if (it->getTokenType() == TokenType::number || it->getTokenType() == TokenType::variable) {
				valuesTree.push(*it);
				it++;
			}
			else if (it->getTokenType() == TokenType::l_parenthesis) {
				operatorsTree.push(*it);
				it++;
			}
			else if (it->getTokenType() == TokenType::r_parenthesis) {
				while (operatorsTree.top().getTokenType() != TokenType::l_parenthesis) {
					ExpressionSolver::solveOperator();
				}
				operatorsTree.pop();
				it++;
			}
			else if (it->getTokenType() == TokenType::operation || it->getTokenType() == TokenType::function) {
				if (operatorsTree.empty()) {
					operatorsTree.push(*it);
					it++;
				}
				else {
					if (operatorsTree.top().getTokenType() == TokenType::l_parenthesis || (it->getPriority() > operatorsTree.top().getPriority())) {
						operatorsTree.push(*it);
						it++;
					}
					else {
						ExpressionSolver::solveOperator();
					}
				}
			}
			else if (it->getTokenType() == TokenType::assignment) {
				operatorsTree.push(*it);
				it++;
			}
			else if (it->getTokenType() == TokenType::function_delimiter) {
				it++;
			}
		}
		while (!operatorsTree.empty()) {
			if (operatorsTree.top().getTokenType() == TokenType::assignment) {
				Variables variables_finder;
				double value = std::stod(valuesTree.top().getTokenValue());
				valuesTree.pop();
				variables_finder.addOrChangeVar(valuesTree.top().getTokenValue(), value);
			}
			ExpressionSolver::solveOperator();
		}
		return getTopValue();
	}
};