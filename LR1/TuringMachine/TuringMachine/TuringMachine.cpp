#include <iostream>
#include "Header.h"

int main(int argv, char** args)
{
    Tape t;
    TuringMachine* tr = nullptr;

    char log[4] = { '-', 'l', 'o', 'g' };
    bool log_flag = false;
    if (argv == 3) {
        log_flag = true;
        for (int i = 0; i < 4; i++)
            if (log[i] != args[2][i]) log_flag = false;
        
    }
   
    bool end = true;
    int choice;
    while (end) {
        std::cout << "1. Creat tape" << std::endl;
        std::cout << "2. Change element in tape" << std::endl;
        std::cout << "3. Put tape into Turing Machine" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            t.creat_line();
            break;
        }
        case 2:
        {
            for (int i = 0; i < t.tape.size(); i++)
                std::cout << i + 1 << ") " << t.tape[i] << std::endl;
            int num;
            std::cout << "Enter the item number" << std::endl;
            std::cin >> num;
            char el;
            std::cout << "Enter a new element" << std::endl;
            std::cin >> el;
            t.change_elem(num, el);
            break;
        }
        case 3:
        {
            tr = new TuringMachine(t);
            end = false;
            break;
        }
        }
    }

    while (true) {

        std::cout << "1. Creat states" << std::endl;
        std::cout << "2. Add state" << std::endl;
        std::cout << "3. Delet state" << std::endl;
        std::cout << "4. Show state" << std::endl;
        std::cout << "5. Run" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            tr->create_states(args[1]);
            break;
        }
        case 2:
        {
            State new_state;
            char dir;
            std::cout << "Enter name ";
            std::cin >> new_state.name;
            std::cout << "Enter input symbol ";
            std::cin >> new_state.input_symbol;
            std::cout << "Enter output symbol ";
            std::cin >> new_state.output_symbol;
            std::cout << "Enter direction ";
            std::cin >> dir;
            std::cout << "Enter next name of state ";
            std::cin >> new_state.next_state;
            switch (dir) {
            case 'L': new_state.dir = L; break;
            case 'R': new_state.dir = R; break;
            case 'S': new_state.dir = S; break;
            case 'Q': new_state.dir = Q; break;
            default: std::cout << "Error input " << std::endl; break;
            }
            tr->add_state(new_state);
            break;
        }
        case 3:
        {
            int num;
            std::cout << "Enter the state number" << std::endl;
            std::cin >> num;
            tr->del_state(num);
            break;
        }
        case 4:
        {
            tr->show_states();
            break;
        }
        case 5:
        {
            tr->run(0, log_flag);
            delete tr;
            system("pause");
            return 0;
        }


        }

    }
}

