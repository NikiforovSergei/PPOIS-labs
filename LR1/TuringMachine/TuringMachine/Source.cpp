#include "Header.h"


TuringMachine::TuringMachine(const Tape& line) {
    this->line = line;
}

void TuringMachine::add_state(const State& state) {
    states.push_back(state);
}

void TuringMachine::show_states() {
    for (int i = 0; i < states.size(); i++) {
        std::cout << i + 1 << ") " << states[i].name << " " << states[i].input_symbol << " " << states[i].output_symbol << " ";
        switch (states[i].dir)
        {
        case L: std::cout << "L" << " "; break;
        case R: std::cout << "R" << " "; break;
        case S: std::cout << "S" << " "; break;
        case Q: std::cout << "Q" << " "; break;
        }
        std::cout << states[i].next_state << std::endl;
    }
}

void TuringMachine::del_state(const int& num) {
    states.erase(states.begin() + (num - 1));
}

void TuringMachine::create_states(const char* path) {
    std::ifstream from(path);
    State state;
    char move;
    if (from.is_open()) {
        while (!from.eof()) {
            bool fail = false;
            from >> state.name >> state.input_symbol >> state.output_symbol >> move >> state.next_state;
            switch (move)
            {
            case 'L': state.dir = L; break;
            case 'R': state.dir = R; break;
            case 'S': state.dir = S; break;
            case 'Q': state.dir = Q; break;
            default: fail = true; break;
            }
            if (fail) break;
            add_state(state);
        }
        from.close();
    }
    else
        std::cout << "ERROR!: File open error" << std::endl;
}


void Tape::creat_line() {
    tape.clear();
    std::string tape_1;
    std::cout << "Input tape:";
    std::cin >> tape_1;
    for (int i = 0; i < tape_1.size(); i++) {
        tape.push_back(tape_1[i]);
    }
}

void Tape::change_elem(const int& num, const char& new_el) {
    tape.erase(tape.begin() + num - 1);
    if (num == tape.size() + 1)
        tape.push_back(new_el);
    else
        tape.insert(tape.begin() + num - 1, new_el);
}

void TuringMachine::print_tape() {
    for (int i = 0; i < line.tape.size(); i++) 
        std::cout << line.tape[i] << " ";
    std::cout << std::endl;
    
}
void TuringMachine::print_state(const State& st) {
    std::cout << st.name << " " << st.input_symbol << " " << st.output_symbol << " ";
    switch (st.dir)
    {
    case L: std::cout << "L" << " "; break;
    case R: std::cout << "R" << " "; break;
    case S: std::cout << "S" << " "; break;
    case Q: std::cout << "Q" << " "; break;
    }
    std::cout << st.next_state << std::endl;
}

bool TuringMachine::_make_step(State& st, unsigned &point, std::string &name_needed) {
    bool end = false;
    unsigned i = 0;
    bool fail = true;
    if (point >= line.tape.size()) {
        std::cout << "ERROR!: Tape out of bounds (Check if machine states are correct)" << std::endl;
        end = true;
        return end;
    }
    while (i < states.size())
    {
        if (states[i].name == name_needed)
        {
            if (states[i].input_symbol == line.tape[point])
            {
                 st = states[i];
                 fail = false;
                 break;
            }
        }
            ++i;
    }
    if (fail) {
         std::cout << "ERROR!: There is no suitable state for the graceful termination of the program " << std::endl;
         end = true;
         return end;
    }

    line.tape[point] = st.output_symbol;
    name_needed = st.next_state;
    switch (st.dir)
    {
     case L: --point; break;
     case R: ++point; break;
     case S: break;
     case Q: end = true; break;
    }
    return end;
}

void TuringMachine::run(unsigned point, bool make_step) {
    if (states.size() == 0) {
        std::cout << "ERROR!: The rules of the machine are not described" << std::endl;
        return;
    }
    State st = states[0];
    std::string name_needed = st.name;
    bool end = false;
    while (!end) {
        end = _make_step(st, point, name_needed);
        if (make_step) {
            std::cout << "--------------------------------" << std::endl;
            print_tape();
            print_state(st);
        }
    }
    if (!make_step) {
        print_tape();
    }
}

