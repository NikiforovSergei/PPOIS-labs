#include "Tokens.hpp"
#include "Exceptions.hpp"


Lexeme::Lexeme(std::string token_value, TokenType token_type, unsigned int index, int priority) {
    this->token_type = token_type;
    this->token_value = token_value;
    this->index = index;
    this->priority = priority;
}

std::string Lexeme::getTokenValue() {
    return this->token_value;
}

TokenType Lexeme::getTokenType() {
    return this->token_type;
}

unsigned int Lexeme::getIndex() {
    return this->index;
}

int Lexeme::getPriority() {
    return this->priority;
}

void Lexeme::setTokenValue(std::string token_value) {
    this->token_value = token_value;
}

void Lexeme::setTokenType(TokenType token_type) {
    this->token_type = token_type;
}

void Lexeme::setIndex(unsigned int index) {
    this->index = index;
}

void Lexeme::setPriority(int priority) {
    this->priority = priority;
}

TokenBuffer::TokenBuffer(std::string buffer) {
    this->buffer = buffer;
}

void TokenBuffer::tokenDivider() {
    std::string token_value = "";
    unsigned int index = 0;
    for (auto sym : this->buffer) {
        index++;
        if (std::find(SEPS.begin(), SEPS.end(), sym) != SEPS.end()) {
            Lexeme to_push(token_value, TokenType::other, index - 1, 0);
            if (token_value != "") {
                readyTokens.push_back(to_push);
            }
            token_value.assign(1, sym);
            to_push.setTokenValue(token_value);
            to_push.setIndex(index);
            readyTokens.push_back(to_push);
            token_value = "";
        }
        else if (std::find(SEPS.begin(), SEPS.end(), sym) == SEPS.end() && sym != ' ' && sym != '\0') {
            token_value += sym;
        }
    }
    Lexeme to_push(token_value, TokenType::other, index, 0);
    if (to_push.getTokenValue() != "") {
        readyTokens.push_back(to_push);
    }
}

std::vector <Lexeme> TokenBuffer::GetReadyTokens() {
    return this->readyTokens;
}

TokenAnalyzer::TokenAnalyzer(std::vector<Lexeme>& raw_tokens) {
    this->raw_tokens = raw_tokens;
}

void TokenAnalyzer::analyzeTokens() {
    std::vector <Lexeme>::iterator it = raw_tokens.begin();
    const std::regex name_regex(R"([a-zA-Z]+[a-zA-Z0-9_]*)");
    while (it != raw_tokens.end()) {
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
            if (check_func_iter != raw_tokens.end() && check_func_iter->getTokenValue() == "(") {
                it->setTokenType(TokenType::function);
            }
            else {
                it->setTokenType(TokenType::variable);
            }
            
        }
        else {
            it->setTokenType(TokenType::other);
            pointer_print(it->getIndex());
            throw TokenUnresolvedException();
        }
        ++it;
    }
}

std::vector <Lexeme> TokenAnalyzer::GetTokenInfo() {
    return this->raw_tokens;
}
