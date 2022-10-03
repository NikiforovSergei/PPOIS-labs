//
// Created by alexey_t on 19/09/22.
//
#include "patterns.h"

#ifndef LAB1_MACHINE_H
#define LAB1_MACHINE_H

/*! The main class in which a machine based on Markov algorithms is implemented.*/
class machine {

    friend bool operator == (const machine&, const machine&);
    friend bool operator != (const machine&, const machine&);

    std::string ribbon;
    patterns rules;

    static std::string string_replacer(std::string&, std::string&, std::string&);

    bool replace(std::string &, const bool&);

public:

    //! A constructor.
    /*!
      A default constructor without arguments.
    */
    machine();

    //! A constructor.
    /*!
      A constructor with 2 string arguments, where first parameter is ribbon, second - rules.
    */
    machine(std::string, std::string);

    //! A constructor.
    /*!
      A constructor with 2 arguments, where first parameter is ribbon (type string), second - rules (type patterns).
    */
    machine(std::string, patterns);

    /*!
      This method sets or replaces the rules of this machine.
    */
    void set_patterns(patterns);

    /*!
      This method returns the rules of this machine.
    */
    patterns get_patterns();

    /*!
      This method sets or replaces the ribbon of this machine.
    */
    void set_ribbon(std::string);

    /*!
      This method returns the ribbon of this machine.
    */
    std::string get_ribbon();

    /*!
      This method does one iteration of this machine.
    */
    void step();

    /*!
      This method makes all possible substitutions in the feed according to the given rules.
    */
    void start(const bool);

};

bool operator == (const machine&, const machine&);
bool operator != (const machine&, const machine&);

#endif //LAB1_MACHINE_H
