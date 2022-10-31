#include <iostream>
#include <string>
#include <vector>
#include "multiset.h"
#include "parser.h"

using namespace custom_multiset;

ostream& operator << (ostream& os, multiset& obj) {

	return os << obj.get_set_string();

}

istream& operator >> (istream& in, multiset& obj) {

	string output;

	in >> output;

	obj.set_container(set_parser(output));

	return in;

}

int main() {

	string A, B, element;
	vector<string> parsed_set_1, parsed_set_2;
	int choice;

	std::cout << "Enter multiset A: ";
	std::getline(std::cin, A);

	std::cout << "Enter multiset B: ";
	std::getline(std::cin, B);

	std::cout << "\n";

	while (true) {

		multiset set1(set_parser(A)), set2(set_parser(B));

		std::cout << "----------Menu----------: \n";
		std::cout << "1) Multiset union \n";
		std::cout << "2) Multiset intersection \n";
		std::cout << "3) Multiset difference \n";
		std::cout << "4) Add an element to multiset\n";
		std::cout << "5) Remove an element from multiset \n";
		std::cout << "6) Check on inclusion of an element \n";
		std::cout << "7) Get length of a multiset \n";
		std::cout << "8) Check if empty \n";
		std::cout << "9) Check equality \n";
		std::cout << "------------------------: \n";
		std::cout << "Enter an option: ";

		std::cin >> choice;

		system("cls");

		std::cout << "Multiset A:" << set1 << '\n' << "Multiset B:" << set2 << '\n';

		switch (choice) {
		case 1: {

			multiset res = set1 + set2;
			res.print();

			break;
		}
		case 2: {

			multiset res = set1 * set2;
			res.print();

			break;
		}
		case 3: {

			multiset res = set1 - set2;
			res.print();

			break;
		}
		case 4: {

			std::cout << "Choose multiset (1/2): ";
			std::cin >> choice;

			switch (choice) {
			case 1: {

				std::cout << "Enter the element to add: ";
				std::cin >> element;

				set1.set_add(element);
				set1.print();

				break;
			}
			case 2: {

				std::cout << "Enter the element to add: ";
				std::cin >> element;

				set2.set_add(element);
				set2.print();

				break;
			}
			default:
				break;
			}

			break;
		}
		case 5: {

			std::cout << "Choose multiset (1/2): ";
			std::cin >> choice;

			switch (choice) {
			case 1: {

				std::cout << "Enter the element to remove: ";
				std::cin >> element;

				set1.set_remove(element);
				set1.print();

				break;
			}
			case 2: {

				std::cout << "Enter the element to remove: ";
				std::cin >> element;

				set2.set_remove(element);
				set2.print();

				break;
			}
			default:
				break;
			}
			break;
		}
		case 6: {

			std::cout << "Choose multiset (1/2): ";
			std::cin >> choice;

			switch (choice) {
			case 1: {

				std::cout << "Enter the element to check: ";

				std::cin >> element;
				std::cout << set1[element];

				break;
			}
			case 2: {

				std::cout << "Enter the element to check: ";

				std::cin >> element;
				std::cout << set2[element];

				break;
			}
			default:
				break;
			}
			break;
		}
		case 7: {

			std::cout << "Choose multiset (1/2): ";
			std::cin >> choice;

			switch (choice) {
			case 1: {

				std::cout << "The length of multiset 1 is ";

				std::cout << set1.set_length();

				break;
			}
			case 2: {

				std::cout << "The length of multiset 2 is ";

				std::cout << set2.set_length();

				break;
			}
			default:
				break;
			}
			break;
		}
		case 8: {
			
			std::cout << "Choose multiset (1/2): ";
			std::cin >> choice;

			switch (choice) {
			case 1: {

				std::cout << set1.is_empty();

				break;
			}
			case 2: {

				std::cout << set2.is_empty();

				break;
			}
			default:
				break;
			}
			break;
		}
		case 9:

			std::cout << "Multiset A and B are " << (A == B ? "" : "not ") << "equal";

		default:

			break;
		}

		std::cout << "\n";

	}

	return 0;

}
