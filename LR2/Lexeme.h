#pragma once

#include "Functions.h"
#include "Exceptions.h"
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
	varAssignment,
	numSolution,
};

class Lexeme {
private:
	std::string tokenValue;
	TokenType tokenType;
	unsigned int index;
	int priority;
public:
	Lexeme(std::string tokenValue, TokenType tokenType, unsigned int index, int priority) {
		this->tokenType = tokenType;
		this->tokenValue = tokenValue;
		this->index = index;
		this->priority = priority;
	}
	std::string getTokenValue() {
		return this->tokenValue;
	}
	TokenType getTokenType() {
		return this->tokenType;
	}
	unsigned int getIndex() {
		return this->index;
	}
	int getPriority() {
		return this->priority;
	}
	void setTokenValue(std::string tokenValue) {
		this->tokenValue = tokenValue;
	}
	void setTokenType(TokenType tokenType) {
		this->tokenType = tokenType;
	}
	void setIndex(unsigned int index) {
		this->index = index;
	}
	void setPriority(int priority) {
		this->priority = priority;
	}
};

class TokenBuffer {
private:
	std::string input;
	std::vector <char> SEPS{ '+', '-', '*', '/', '^', '(', ')', ',', '=' };
	std::vector <Lexeme> readyTokens;
public:
	TokenBuffer(std::string input) {
		this->input = input;
	}
	void tokenDivider() {
		std::string tokenValue = "";
		unsigned int index = 0;
		for (auto sym : this->input) {
			index++;
			if (std::find(SEPS.begin(), SEPS.end(), sym) != SEPS.end()) {
				Lexeme to_push(tokenValue, TokenType::other, index - 1, 0);
				if (tokenValue != "") {
					readyTokens.push_back(to_push);
				}
				tokenValue.assign(1, sym);
				to_push.setTokenValue(tokenValue);
				to_push.setIndex(index);
				readyTokens.push_back(to_push);
				tokenValue = "";
			}
			else if (std::find(SEPS.begin(), SEPS.end(), sym) == SEPS.end() && sym != ' ' && sym != '\0') {
				tokenValue += sym;
			}
		}
		Lexeme to_push(tokenValue, TokenType::other, index, 0);
		if (to_push.getTokenValue() != "") {
			readyTokens.push_back(to_push);
		}
	}
	std::vector <Lexeme> GetReadyTokens() {
		return this->readyTokens;
	}
};


class TokenAnalyzer {
private:
	std::vector <Lexeme> rawTokens;
	const std::vector <std::string> OPERATORS{ "+", "-", "*", "/", "^", "(", ")", ",", "=" };
public:
	TokenAnalyzer(std::vector<Lexeme>& rawTokens) {
		this->rawTokens = rawTokens;
	}
	void analyzeTokens() {
		std::vector <Lexeme>::iterator it = rawTokens.begin();
		const std::regex name_regex(R"([a-zA-Z]+[a-zA-Z0-9_]*)");
		while (it != rawTokens.end()) {
			try {
				auto test_for_number = std::stod(it->getTokenValue());
				it->setTokenType(TokenType::number);
				it++;
				continue;
			}
			catch (...) {

			}
			if (std::find(OPERATORS.begin(), OPERATORS.end(), it->getTokenValue()) != OPERATORS.end()) {
				if (it->getTokenValue() == "=") {
					it->setTokenType(TokenType::assignment);
				}
				else if (it->getTokenValue() == "(") {
					it->setTokenType(TokenType::l_parenthesis);
				}
				else if (it->getTokenValue() == ")") {
					it->setTokenType(TokenType::r_parenthesis);
				}
				else if (it->getTokenValue() == ",") {
					it->setTokenType(TokenType::function_delimiter);
				}
				else {
					it->setTokenType(TokenType::operation);
				}
			}
			else if (std::regex_match(it->getTokenValue(), name_regex)) {
				auto check_func_iter = it;
				check_func_iter++;
				if (check_func_iter != rawTokens.end() && check_func_iter->getTokenValue() == "(") {
					it->setTokenType(TokenType::function);
				}
				else {
					it->setTokenType(TokenType::variable);
				}

			}
			else {
				it->setTokenType(TokenType::other);
				pointerPrint(it->getIndex());
				throw TokenUnresolvedException();
			}
			++it;
		}
	}
	std::vector <Lexeme> GetTokenInfo() {
		return this->rawTokens;
	}
};