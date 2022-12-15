#include "Solver.hpp"
#include "Exceptions.hpp"

ExpressionAnalyzer::ExpressionAnalyzer(std::vector<Lexeme>& raw_tokens) {
    this->raw_tokens = raw_tokens;
}

void ExpressionAnalyzer::analyze_prioritize() {
    int additional_priority = 0;
    int unclosed_parenthesis = 0;
    std::vector <Lexeme>::iterator it = raw_tokens.begin();
    bool unary_minus_possible = true;
    bool operation_possible = false;
    while (it != raw_tokens.end()) {
        if (it->getTokenType() == assignment) {
            unary_minus_possible = true;
            it->setPriority(OPERATOR_PRIORITY.at("=") + additional_priority);
        }
        else if (it->getTokenType() == l_parenthesis) {
            additional_priority += OPERATOR_PRIORITY.at("(");
            unclosed_parenthesis++;
            unary_minus_possible = true;
            operation_possible = false;
        }
        else if (it->getTokenType() == r_parenthesis) {
            additional_priority += OPERATOR_PRIORITY.at(")");
            unclosed_parenthesis--;
            unary_minus_possible = false;
            operation_possible = true;
        }
        else if (it->getTokenType() == TokenType::function_delimiter) {
            unary_minus_possible = true;
            operation_possible = false;
        }
        else if (it->getTokenType() == operation) {
            if ((++it) == raw_tokens.end()) {
                pointer_print((--it)->getIndex()+2);
                throw BinaryOperatorError();
            }
            else {
                --it;
            }
            if (it->getTokenValue() == "-") {
                if (it == raw_tokens.begin()) {
                    if ((++it)->getTokenType() == TokenType::operation) {
                        pointer_print((--it)->getIndex()+2);
                        throw BinaryOperatorError();
                    }
                    --it;
                    it->setPriority(OPERATOR_PRIORITY.at("-u") + additional_priority);
                    it->setTokenValue("-u");
                }
                else {
                    if (unary_minus_possible) {
                        if ((++it)->getTokenType() == TokenType::operation) {
                            pointer_print((--it)->getIndex()+2);
                            throw BinaryOperatorError();
                        }
                        --it;
                        it->setTokenValue("-u");
                        it->setPriority(OPERATOR_PRIORITY.at("-u") + additional_priority);
                    }
                    else {
                        if (!operation_possible) {
                            pointer_print(it->getIndex()+2);
                            throw BinaryOperatorError();
                        }
                        it->setPriority(OPERATOR_PRIORITY.at("-") + additional_priority);
                    }
                }
                unary_minus_possible = false;
            }
            else {
                if (!operation_possible) {
                    pointer_print(it->getIndex()+2);
                    throw BinaryOperatorError();
                }
                it->setPriority(OPERATOR_PRIORITY.at(it->getTokenValue()) + additional_priority);
                unary_minus_possible = true;
            }
            operation_possible = false;
        }
        else if (it->getTokenType() == TokenType::function) {
            operation_possible = true;
            Functions check_func;
            std::string func_type = check_func.func_type(it->getTokenValue());
            if (func_type == "NotFunction") {
                pointer_print(it->getIndex());
                throw FunctionDoesntExist(it->getTokenValue());
            }
            else {
                auto current_it = it;
                int arg_count = 0;
                while (current_it != raw_tokens.end()) {
                    if (current_it->getTokenType() == TokenType::r_parenthesis) break;
                    if (arg_count == 0 && current_it->getTokenType() != TokenType::r_parenthesis) arg_count++;
                    else if (current_it->getTokenType() == TokenType::function_delimiter) arg_count++;
                    current_it++;
                }
                if (func_type == "Binary" && arg_count != 2) {
                    pointer_print(it->getIndex());
                    throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
                }
                else if (func_type == "Unary" && arg_count != 1) {
                    pointer_print(it->getIndex());
                    throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
                }
                current_it++;
            }
            it->setPriority(OPERATOR_PRIORITY.at("func") + additional_priority);
        }
        else if (it->getTokenType() == TokenType::other) {
            pointer_print(it->getIndex());
            throw TokenUnresolvedException();
        }
        else {
            unary_minus_possible = false;
            operation_possible = true;
        }
        it++;
    }
    if (unclosed_parenthesis != 0) {
        throw NoCloseParenthesis();
    }
}


std::vector <Lexeme> ExpressionAnalyzer::getTokens() {
    return this->raw_tokens;
}

ExpressionSolver::ExpressionSolver(std::vector<Lexeme> tokens) {
    this->tokens = tokens;
}

double ExpressionSolver::solve() {
    std::vector<Lexeme>::iterator it = tokens.begin();
    double value = 0;
    while (it != tokens.end()) {
        if (it->getTokenType() == TokenType::number || it->getTokenType() == TokenType::variable) {
            values_stack.push(*it);
            it++;
        }
        else if (it->getTokenType() == TokenType::l_parenthesis) {
            operators_stack.push(*it);
            it++;
        }
        else if (it->getTokenType() == TokenType::r_parenthesis) {
            while (operators_stack.top().getTokenType() != TokenType::l_parenthesis) {
                ExpressionSolver::solve_operator();
            }
            operators_stack.pop();
            it++;
        }
        else if(it->getTokenType() == TokenType::operation || it->getTokenType() == TokenType::function) {
            if (operators_stack.empty()) {
                operators_stack.push(*it);
                it++;
            }
            else {
                if (operators_stack.top().getTokenType() == TokenType::l_parenthesis || (it->getPriority() > operators_stack.top().getPriority())) {
                    operators_stack.push(*it);
                    it++;
                }
                else {
                    ExpressionSolver::solve_operator();
                }
            }
        }
        else if (it->getTokenType() == TokenType::assignment) {
            operators_stack.push(*it);
            it++;
        }
        else if (it->getTokenType() == TokenType::function_delimiter) {
            it++;
        }
    }
    while (!operators_stack.empty()) {
        if (operators_stack.top().getTokenType() == TokenType::assignment) {
            Variables variables_finder;
            double value = get_top_value();
            variables_finder.addOrChangeVar(values_stack.top().getTokenValue(), value);
            operators_stack.pop();
        }
        else{
            ExpressionSolver::solve_operator();
        }
        
    }
    return get_top_value();
}

void ExpressionSolver::solve_operator() {
    if (operators_stack.top().getTokenType() == TokenType::operation) {
        if (operators_stack.top().getTokenValue() == "-u") {
            double result = (-1) * get_top_value();
            Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
            values_stack.push(new_value);
            operators_stack.pop();
        }
        else {
            std::vector<double> args;
            for (int i = 0; i < 2; i++) {
                args.push_back(get_top_value());
            }
            double result = 0;
            if (operators_stack.top().getTokenValue() == "-") {
                result = args[1] - args[0];
            }
            else if (operators_stack.top().getTokenValue() == "+") {
                result = args[1] + args[0];
            }
            else if (operators_stack.top().getTokenValue() == "/") {
                result = args[1] / args[0];
            }
            else if (operators_stack.top().getTokenValue() == "*") {
                result = args[1] * args[0];
            }
            else if (operators_stack.top().getTokenValue() == "^") {
                result = pow(args[1], args[0]);
            }
            operators_stack.pop();
            Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
            values_stack.push(new_value);
        }
    }
    else if (operators_stack.top().getTokenType() == TokenType::function) {
        Functions func_solver;
        std::vector<double> args;
        if (func_solver.func_type(operators_stack.top().getTokenValue()) == "Binary") {
            for (int i = 0; i < 2; i++) {
                args.push_back(get_top_value());
            }
        }
        else {
            args.push_back(get_top_value());
        }
        double result = func_solver.count_func(operators_stack.top().getTokenValue(), args);
        operators_stack.pop();
        Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
        values_stack.push(new_value);
    }
    
}


double ExpressionSolver::get_top_value() {
    Lexeme top_value = values_stack.top();
    values_stack.pop();
    if (top_value.getTokenType() == TokenType::number) {
        return std::stod(top_value.getTokenValue());
    }
    else if (top_value.getTokenType() == TokenType::variable) {
        Variables variables;
        return variables.callVariable(top_value.getTokenValue());
    }
    else {
//        throw std::exception("Value can either number or variable!");
        return 0;
    }
}
