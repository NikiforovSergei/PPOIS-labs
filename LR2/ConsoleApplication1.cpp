
#include <iostream>
#include "Set.h"
#include "Error.h"
#include "Function.h"

int main() {
	setlocale(LC_ALL, "ru");
	Set set1;
	Set set2;
	Set empty_set;
	bool n = 0;
	std::string s;
	while (true) {
		try
		{
			getline(std::cin, s);
			Set::check_boolean(s, n);
			if (n) {
				set1 = empty_set;
				set2 = empty_set;
				n = 0;
				continue;
			}
			std::string first_set, second_set, sign;
			Set::split(s, first_set, second_set, sign);
			set1.parse(first_set);
			set2.parse(second_set);
			Set::processing(set1, set2, sign);
			set1 = empty_set;
			set2 = empty_set;
			n = 0;
		}
		catch (Error::ER error)
		{
			std::cout << error.message << '\n';
		}
	}
}
// {1, 2, 3, {1, 5}} + {3, 5}
// {1, 2, 3, {1, 5}} - {3, 5, {1, 2}} 
// {1, 2, 3, {2, 3}} * {1, 5, {2, 3}}
// Boolean({1, 2})