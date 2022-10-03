//
// Created by alexey_t on 19/09/22.
//
#include <utility>

#include "iostream"
#include "string"
#include "sstream"
#include "vector"
#include "algorithm"

#ifndef UNTITLED_PATTERNS_H
#define UNTITLED_PATTERNS_H

/*!The class in which the rules are implemented.*/
class patterns {
    friend bool operator == (const patterns&, const patterns&);
    friend bool operator != (const patterns&, const patterns&);
    friend std::ostream& operator << (std::ostream &os, patterns&);
    friend std::istream& operator >> (std::istream& in, patterns&);

    friend class machine;

    struct node{
        std::string take, ret;
        node *next = nullptr;

        node(std::string take, std::string ret) : take(std::move(take)), ret(std::move(ret)) {
        };

    }*begin = nullptr;

public:

    //! A constructor.
    /*!
      A default constructor without arguments.
    */
    patterns();

    //! A constructor.
    /*!
      A constructor with a string argument, which sets the rules and should look like this "str1->str2;str3->str4".
    */
    patterns(std::string);

    /*!
      This method adds one rule to the end of the list of rules, the argument should look like this "str1->str2".
    */
    void push_back(const std::string);

    /*!
      This method removes the rule given as an argument from the list of rules, the argument should look like this "str1->str2".
     */
    void delete_pattern(const std::string);

    /*!
      This method displays a list of rules.
     */
    void view_patterns();

};

std::ostream& operator << (std::ostream&, patterns&);

std::istream& operator >> (std::istream&, patterns&);

bool operator == (const patterns&, const patterns&);
bool operator != (const patterns&, const patterns&);


static std::vector<std::string> split(const std::string&);

static std::pair<std::string, std::string>cut(const std::string&);



#endif //UNTITLED_PATTERNS_H
