#include "Calculator.h"

const std::map<std::string, double> Variables::CONST_VARS{ {"PI", 3.141592}, {"pi", 3.141592}, {"E", 2.718281}, {"e", 2.718281} };

int main() {
	Calculator calculator;
	while (true) {
		calculator.start();
	}
	return 0;
}