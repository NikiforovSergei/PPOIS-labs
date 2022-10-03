#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//! Direction - various carriage directions
/*
R - movement to the right
L - move to the left
S - carriage stop
Q - stop the program
*/
enum Direction { L, R, S, Q };   

//! State - rule structure
/*
name - state number
input_symbol - replacement character
next_state - next state number
output_symbol - character to replace
dir - carriage movement
*/
struct State
{
    std::string name;                        
    char input_symbol;                       
    std::string next_state;                  
    char output_symbol;                      
    Direction dir;                          
};

//! Tape class
/*
This class implements the tape of a Turing machine
*/  
class Tape {
public:
    //! Method creat_line 
    /*
    This method creates a ribbon. When calling this method,
    We enter a string that will be our tape (the input goes without spaces)
    */
    void creat_line();
    //! Method change_elem
    /*
     This method replaces the selected character with another one.
     The method takes two parameters. Index of character to be replaced
     And the character we want to replace the desired one with
    */
    void change_elem(const int& num, const char& new_el);
    std::vector<char>tape;
};

//! TuringMachine class
/*
 The main class in which the Turing machine is implemented
 The class has methods that implement the rules necessary for the operation of the Turing machine.
 And side methods to simplify the work with the program
*/
class TuringMachine 
{
public:
    //! Ñonstructor TuringMachine
    /*
    This constructor takes an element of type Tape as a parameter.
    For further use of this tape during the program
    */
    TuringMachine(const Tape &line);


    //! Method create_states
    /*
    This method reads machine states from a file
    The method takes as a parameter the path to the file
    In which the states of the machine are described. And reads them into the states vector
    */
    void create_states(const char* path);


    //! Method add_state
    /*
    This method is used to add a new state
    The method takes as a parameter an element of type State
    And adds it to the vector of all states states
    */
    void add_state(const State& state);


    //! Method del_state
    /*
    This method is used to remove the state
    The method takes as a parameter the state index in the states vector
    And removes it from the vector of all states states
    */
    void del_state(const int &num);


    //! Method show_states
    /*
    This method is used to output all states to the console
    */
    void show_states();

    //! Method run
    /*
    This method is used to start the operation of the Turing machine
    The method takes as parameters
    The starting index of the element on which the caret is located (default 0)
    Boolean variable that serves as a flag for implementing the program step by step (default is false)
    If set to false, the program outputs the final result of the tape
    If set to true, the program is implemented step by step (for each step execution, a ribbon and the corresponding state are displayed)
    */
    void run(unsigned point = 0, bool make_step = false);

private:


    //! Method print_tape
    /*
    This method is used to display the tape
    */
    void print_tape();


    //! Method print_state
    /*
    This method is used to display the tape
    The method takes as a parameter an element of type State
    */
    void print_state(const State &st);


    //! Method _make_step
    /*
    This method is used to output the program step by step.
    The method takes as parameters the state of the feed, the index of the element in the feed
    And the next tape state
    */
    bool _make_step(State &st, unsigned &point, std::string &name_needed);

    Tape line;
    std::vector<State>states;
};

 


