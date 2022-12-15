#pragma once

/**
* @author Kuleshov Ilya
* @brief This file contain all necessary definitions
* @date 20.10.2022
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

class Menu
{
public:

    Menu(bool log_check);
    void menu_choose();

};


/**
* @brief Here we describe our class
*/
class PostMachine
{
public:
    /**
    * @brief Constructor
    */
    PostMachine();
    /**
    * @brief Destructor
    */
    ~PostMachine();
    /**
    * @brief Function for reading our tape
    */
    void readTape();
    /**
    * @brief Function for reading our file with commands
    */
    void readInputFile(string);
    string start(string tape, string rules);
    /**
    * @brief Function for saving file before the action
    */
    void saveStateBefore();
    /**
    * @brief Function for saving file after the action
    */
    void saveStateAfter(string);
    void coutStateBefore();
    void coutStateAfter();
    string start();
    string start2();
private:
    string tape;
    vector<string> rules;
    unsigned long long tapeIndex;

};