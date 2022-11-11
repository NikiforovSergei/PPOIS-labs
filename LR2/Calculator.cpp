#include "Calculator.h"


void Calculator::start() {
	std::cout << "\n> ";
	std::getline(std::cin, buffer);	
	TokenBuffer token_buffer(buffer);
	try {
		token_buffer.tokenDivider();
		std::vector<Lexeme> ready_tokens = token_buffer.GetReadyTokens();
		TokenAnalyzer token_analyzer(ready_tokens);
		token_analyzer.analyzeTokens();
		ready_tokens = token_analyzer.GetTokenInfo();
		ExpressionAnalyzer expression_analyzer(ready_tokens);
		expression_analyzer.analyze_prioritize();
		ready_tokens = expression_analyzer.getTokens();
		ExpressionSolver expression_solver(ready_tokens);
		double result;
		result = expression_solver.solve();
		std::cout << "Result: " << result << '\n';
	}
	catch (FunctionDoesntExist& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (VariableAlreadyExists& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (VariableDoesntExist& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (FunctionWrongArgumentAmount& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (FunctionNoCloseParenthesis& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (NoCloseParenthesis& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (TokenUnresolvedException& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (BinaryOperatorError& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (AssignmentError& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (NoArgumentError& e) {
		std::cout << e.what() << '\n';
		return;
	}
	catch (...) {

	}
}