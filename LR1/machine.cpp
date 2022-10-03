//
// Created by alexey_t on 19/09/22.
//

#include "machine.h"

//private functions

std::string machine::string_replacer(std::string &inputStr, std::string &src, std::string &dst) {
    std::string result(inputStr);

    size_t pos = result.find(src);
    if(pos != std::string::npos) {
        result.replace(pos, src.size(), dst);
    }

    return result;
}

bool machine::replace(std::string &str, const bool &print_ribbon) {
    patterns::node* curr = rules.begin;
    while(curr){
        if(str.find(curr->take) != std::string::npos){
            if (print_ribbon) std::cout << str << " -> ";
            if (curr->ret.at(curr->ret.length()-1) == '|') {
                if (curr->ret.length()>1){
                    std::string s = curr->ret.substr(0, curr->ret.length()-1);
                    str = string_replacer(str, curr->take, s);
                }
                else{
                    std::string s;
                    str = string_replacer(str, curr->take, s);
                }
                if (print_ribbon) std::cout << str << std::endl;
                return false;
            }
            str = string_replacer(str, curr->take, curr->ret);
            if (print_ribbon) std::cout<<str<<std::endl;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

//public functions

machine::machine(){}

machine::machine(std::string ribbon, std::string rules) {
    this->ribbon = ribbon;
    this->rules = patterns(rules);
}
machine::machine(std::string ribbon, patterns rules) {
    this->ribbon = ribbon;
    this->rules = rules;
}

void machine::set_patterns(patterns patterns){
    this->rules = patterns;
};

patterns machine::get_patterns(){
    return(this->rules);
};

void machine::set_ribbon(std::string ribbon){
    this->ribbon = ribbon;
}

std::string machine::get_ribbon(){
    return(this->ribbon);
}

void machine::step(){
    replace(ribbon, true);
}
void machine::start(const bool print_ribbon) {
    while(replace(ribbon, print_ribbon));
}
//operators functions

bool operator == (const machine& a, const machine& b){
    if (a.ribbon == b.ribbon && a.rules == b.rules) return true;
    else return false;
}
bool operator != (const machine &a, const machine &b) {
    if (a.ribbon == b.ribbon && a.rules == b.rules) return false;
    else return true;
}
