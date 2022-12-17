#include<iostream>
#include<string>
#include"Header.h"

using namespace std;

int main() {
	setlocale(0, "");
	vector<Set> data;
	Solver solver;
	
	cout << "Введите выражение (множества выделяются {} или латинскими буквами верхнего регистра)" << endl;
	cout << "Элементами множества могут служить элементы, выделяемые латинскими буквами нижнего регистра, цифры или други множества" << endl;
	cout << "Предусмотрена функция Bool(), принимающая только 1 аргумент" << endl;

	do {
		string line;
		getline(cin, line);
		Input_Processing input(line);

		if (input.Syntax_check()) {

			vector<Set> new_data = input.Parse(input.line);
			data = Insert(data, new_data);
			data = solver.Solve_post_form(solver.To_post_form(input.line, data));

			data.back().print(); cout << endl;
		}
		

	} while (true);

	return 0;
}
 