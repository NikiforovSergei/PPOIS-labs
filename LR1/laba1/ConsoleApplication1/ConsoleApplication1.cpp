
#include <iostream>
#include <fstream>
#include <iomanip>
#include "turingmashine.h"

int main(int argv,char **args)
{   
    Turing turing;
    std::vector<Rule> rules;
    Node* buf = new Node;

    char log[4] = { '-', 'l', 'o', 'g' };
    bool log_bool = false;
    if (argv == 3) {
        log_bool = true;
        for (size_t i = 0; i < 4; i++)
             if (log[i] != args[2][i]) log_bool = false;
    }

    int number, size_of_rules, size_of_mashine;
    while (true) {
        std::cout << std::setw(3) << "1-" << std::setw(25) << "Make tape\n"
            << std::setw(3) << "2-" << std::setw(25) << "Add element\n" 
            << std::setw(3) << "3-" << std::setw(25) << "Show elements\n"
            << std::setw(3) << "4-" << std::setw(25) << "Enter rules\n"
            << std::setw(3) << "5-" << std::setw(25) << "Show rules\n"
            << std::setw(3) << "6-" << std::setw(25) << "Change rules\n"
            << std::setw(3) << "7-" << std::setw(25) << "Breakpoint\n"
            << std::setw(3) << "8-" << std::setw(25) << "Run\n"
            << std::setw(3) << "9-" << std::setw(25) << "Delete rules\n"
            << std::setw(3) << "10-" << std::setw(25) << "Start input in file\n"
            << std::setw(3) << "0-" << std::setw(25) << "Complete the program\n";
        char a;
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 1: {
            std::cout << "Enter size of mashine\n";
            std::cin >> size_of_mashine;
            std::cout << "Enter element\n";
            turing.tape(size_of_mashine);
            break;
        }
        case 2: {
            std::cout << "Enter element\n";
            std::cin >> a;
            turing.add_element(a);
            break;
        }
        case 3: {
            turing.show_element();
            break;
        }
        case 4: {
            std::cout << "Enter size of rules\n";
            std::cin >> size_of_rules;
            std::cout << "Enter rules\n";
            turing.run(rules, size_of_rules);
            break;
        }
        case 5: {
            turing.show_rules(rules, size_of_rules);
            break;
        }
        case 6: {
            int change;
            std::cout << "Enter number of rules\n";
            std::cin >> change;
            std::cout << "Enter new rules\n";
            turing.change_rule(rules, change);
            break;
        }
        case 7: {
            std::cout << "Enter breakpoint\n";
            std::cin >> number;
            turing.breakpoint(number, buf, turing);
            std::cout << buf->value << '\n';
            break;
        }
        case 8: {
            // case 1, case 7, case 4, case 8
            turing.analyze_rule(rules, number, turing, log_bool);
            turing.show_element();
            break;
        }
        case 9: {
            int num;
            std::cout << "Enter the number of rules that you want to delete\n";
            std::cin >> num;
            turing.delete_rule(rules, num);
            size_of_rules--;
            turing.show_rules(rules, size_of_rules);
            break;
        }
        case 10: {
            std::ifstream in("C:/Users/USER/Desktop/2курс/поис/laba1/Debug/input.txt", std::ifstream::in);
            if (in.is_open()) {
                in >> size_of_mashine;
                for (int i = 0; i < size_of_mashine; ++i) {
                    in >> a;
                    turing.add_element(a);
                }
                in >> number;
                turing.breakpoint(number, buf, turing);
                in >> size_of_rules;
                turing.run_in_file(rules, size_of_rules, args[1]);
                turing.analyze_rule(rules, number, turing, log_bool);
                in.close();
            }
            else std::cout << "ERROR";
            turing.show_element();
            system("pause");

            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}