//
// Created by alexey_t on 15/09/22.
//

#include "patterns.h"

//private functions

//public functions
patterns::patterns(){}

patterns::patterns(std::string str) {
    for(const std::string &s:split(str))
        this->push_back(s);
}

void patterns::push_back(const std::string str) {

    std::pair<std::string, std::string>rule = cut(str);
    std::string take = rule.first, ret = rule.second;

    if(!begin) {
        begin = new node(take, ret);
        return;
    }
    node* curr = begin;
    while(curr->next) curr = curr->next;
    curr->next = new node(take, ret);
}

void patterns::delete_pattern(const std::string str) {
    std::pair<std::string, std::string>rule = cut(str);
    node* curr = begin, *prevCurr = nullptr;
    while (curr){
        if (curr->take == rule.first && curr->ret == rule.second){
            if (curr == begin){
                begin = begin->next;
                delete curr;
            }
            else{
                prevCurr->next = curr->next;
                delete curr;
            }
            break;
        }
        prevCurr = curr;
        curr = curr->next;
    }
}

void patterns::view_patterns() {
    std::cout << *this;
}

//operators functions

std::ostream& operator << (std::ostream &os, patterns& con){
    patterns::node* curr = con.begin;
    while(curr){
        os << curr->take << " -> " << curr->ret + "\n";
        curr = curr->next;
    }
    return os;
}

std::istream& operator >> (std::istream& in, patterns& con)
{
    std::string str;
    in >> str;

    for(const std::string &s:split(str))
        con.push_back(s);

    return in;
}

bool operator == (const patterns& a, const patterns& b){

    patterns::node *a_curr = a.begin, *b_curr = b.begin;

    while(true){
        if(!a_curr && !b_curr) return true;
        else if (!a_curr || !b_curr) return false;

        if(a_curr->take != b_curr->take || a_curr->ret != b_curr->ret) return false;

        a_curr = a_curr->next; b_curr = b_curr->next;
    }
}
bool operator != (const patterns &a, const patterns &b) {

    patterns::node *a_curr = a.begin, *b_curr = b.begin;

    while(true){
        if(!a_curr && !b_curr) return false;
        else if (!a_curr || !b_curr) return true;

        if(a_curr->take != b_curr->take || a_curr->ret != b_curr->ret) return true;

        a_curr = a_curr->next; b_curr = b_curr->next;
    }
}


//additional functions

static std::vector<std::string> split(const std::string &str)
{
    std::stringstream ss;

    ss<<str;

    std::vector<std::string> elems;

    std::string item;
    while (std::getline(ss, item, ';')) {
        elems.push_back(item);
    }
    return elems;
}

static std::pair<std::string, std::string>cut(const std::string &str){
    size_t pos = str.find("->");
    std::string f, s;
    if(pos != std::string::npos) {
        f = str.substr(0, pos);
        s = str.substr(pos + 2, str.length() - 1);
    }
    return std::pair<std::string, std::string>{f,s};
}