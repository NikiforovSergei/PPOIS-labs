

/**
* @file
* Definition of Rules with a description of the algorithm of actions of Post machine
*/

#include <iostream>
#include <fstream>

using namespace std;


#include "Rules.h"

void Rules::Command::setAction(char action) {
    this->action = action;
}

char Rules::Command::getAction() {
    return this->action;
}

void Rules::Command::setNext(int next) {
    this->next = next;
}

/**
* Since branching has two pointers to the next command,
 * two pointers are stored in the same memory area by adding the first pointer (if there is a mark) multiplied by 100,
 * and the second pointer (if the mark is absent)
*/
void Rules::Command::setNext(int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark) {
    this->next = indexOfNextCommandIfThereIsTheMark * 100 + indexOfNextCommandIfThereIsNotTheMark;
}

int Rules::Command::getNext() {
    return this->next;
}

int Rules::getSizeOfTape() {
    return this->commands.size();
}

void Rules::resetTheCounter() {
    Rules::counter = 0;
}

void Rules::showTheInputRequirements() {
    cout << "There are several requirements for the input: "
            "\n1. 0 < index <= " << counter + 1 << ";"
                                                   "\n2. The command must match the following alphabet:"
                                                   "\n! - Stop the program "
                                                   "\nV - Put a mark "
                                                   "\nX - Delete a mark "
                                                   "\n> - Move to the right"
                                                   "\n< - Move to the left "
                                                   "\n? next1 next2 - If there is a mark, go to the next1 command, else go the next2 command\n\n";
}

/**
* Reads the list of rules from file and creates a list of commands for Post machine
*
* @param path Contains the file address
*/
bool Rules::inputRulesFromFile(const char *path) {
    ifstream F;
    F.open(path);
    if (!F.is_open()) {
        return false;
    }
    string buffer;
    /**
    * According to input from file rules, the first string in file is the content of Tape of the Post machine.
    * Therefore, the first line is skipped and the commands get processed from the second line.
    */
    getline(F, buffer);

    while (!(F.eof())) {
        getline(F, buffer);
        /**All commands of the Post machine, except branching, are represented by one symbol according to the alphabet.
        *In case of branching, there is a symbol of command '?' and 2 spaces and 2 pointers to the next command depending on the availability of a mark in a cell.
        *There are 3 variants of the amount of symbols in a line with the branching command: 5 (both pointers - single digit), 6 (one is single digit, other one is two-digit), 7 (both pointers are two-digit)
        *Case with the amount of commands greater or equal to 100 is not considered in this library
         */

        switch (buffer.length()) {
            case 1: {
                this->newCommand(buffer[0]);
                break;
            }
            case 5: {
                this->newCommand(buffer[0], buffer[2] - '0', buffer[4] - '0');
                break;
            }
            case 6: {
                if (buffer[3] != ' ') {
                    this->newCommand(buffer[0], (buffer[2] - '0') * 10 + buffer[3] - '0', buffer[5] - '0');
                } else {
                    this->newCommand(buffer[0], buffer[2] - '0', (buffer[4] - '0') * 10 + buffer[5] - '0');
                }
                break;
            }
            case 7: {
                this->newCommand(buffer[0], (buffer[2] - '0') * 10 + buffer[3] - '0',
                                 (buffer[5] - '0') * 10 + buffer[6] - '0');
                break;
            }
            default: {
                F.close();
                return "";
            }
        }
    }
    F.close();
    return "true";
}

bool Rules::setCommand(const int index, char action) {
    if (!(commandCorrectnessChecking(index, action))) {
        return false;
    }
    this->commands[index].setAction(action);
    return true;
}

bool Rules::setCommand(const int index, char action, int indexOfNextCommandIfThereIsTheMark,
                       int indexOfNextCommandIfThereIsNotTheMark) {

    if (!(commandCorrectnessChecking(index, action))) {
        return false;
    }
    this->commands[index - 1].setAction(action);
    this->commands[index - 1].setNext(indexOfNextCommandIfThereIsTheMark, indexOfNextCommandIfThereIsNotTheMark);
    return true;
}

bool Rules::newCommand(char action) {
    if (!(commandActionChecking(action))) {
        return false;
    }
    Command newCommand(action);
    commands.push_back(newCommand);
    return true;
}

bool Rules::newCommand(char action, int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark) {
    if (!(commandActionChecking(action))) {
        return false;
    }
    Command newCommand(action, indexOfNextCommandIfThereIsTheMark, indexOfNextCommandIfThereIsNotTheMark);
    commands.push_back(newCommand);
    return true;
}

void Rules::deleteTheLastCommand() {
    counter--;
    commands.pop_back();
}

char Rules::getActionOfCommand(const int index) {
    return this->commands[index].getAction();
}

int Rules::getIndexOfNextCommand(const int index) {
    return this->commands[index].getNext();
}

int Rules::getNumberOfCommands() {
    return Rules::counter;
}

int Rules::counter = 0;

/**
* Changes next pointers to prevent a command referring to itself
* @param index Contains an index of a current command
*/
void Rules::automaticNextChanging(const int index) {
    if (this->commands[index].getAction() == '?') {
        int indexOfNextCommandIfThereIsTheMark = this->commands[index].getNext() / 100;
        int indexOfNextCommandIfThereIsNotTheMark = this->commands[index].getNext() % 100;
        if (indexOfNextCommandIfThereIsTheMark == index + 1)
            this->commands[index].setNext(indexOfNextCommandIfThereIsTheMark + 1,
                                          indexOfNextCommandIfThereIsNotTheMark);
        else if (indexOfNextCommandIfThereIsNotTheMark == index + 1)
            this->commands[index].setNext(indexOfNextCommandIfThereIsTheMark,
                                          indexOfNextCommandIfThereIsNotTheMark + 1);
    } else {
        this->commands[index].setNext(index + 1);
    }
}

/**
* Exchanges the indexes of two commands. If there is branching, it changes next-pointers too.
* @param firstIndex Contains an index of a command that will be swapped
* @param secondIndex Contains an index of a command that changed
*/
void Rules::swapTheRules(const int firstIndex, const int secondIndex) {
    char cbuffer = this->commands[firstIndex].getAction();
    this->commands[firstIndex].setAction(this->commands[secondIndex].getAction());
    this->commands[secondIndex].setAction(cbuffer);
    if (this->commands[firstIndex].getAction() == '?' || this->commands[secondIndex].getAction() == '?') {
        int ibuffer = this->commands[firstIndex].getNext();
        this->commands[firstIndex].setNext(this->commands[secondIndex].getNext());
        this->commands[secondIndex].setNext(ibuffer);
        this->automaticNextChanging(firstIndex);
        this->automaticNextChanging(secondIndex);
    }
}

bool Rules::commandIndexChecking(const int index, const int amountOfCommands) {
    if (index > amountOfCommands + 1) {
        return false;
    } else {
        return index > 0;
    }
}

bool Rules::commandIndexChecking(const int indexOfNextCommandIfThereIsTheMark,
                                 const int indexOfNextCommandIfThereIsNotTheMark, const int amountOfCommands) {
    if (indexOfNextCommandIfThereIsTheMark > amountOfCommands + 1 ||
        indexOfNextCommandIfThereIsNotTheMark > amountOfCommands + 1) {
        return false;
    } else {
        return (indexOfNextCommandIfThereIsTheMark > 0 && indexOfNextCommandIfThereIsNotTheMark > 0);
    }
}

bool Rules::commandActionChecking(const char action) {
    return action == MOVE_TO_THE_RIGHT || action == MOVE_TO_THE_LEFT || action == DELETE_MARK || action == PUT_MARK ||
           action == BRANCHING || action == STOP;
}

bool Rules::commandCorrectnessChecking(const int index, const char action) {
    if (!(commandIndexChecking(index, counter)) || !(commandActionChecking(action))) {
        showTheInputRequirements();
        return false;
    }
    return true;
}

bool Rules::commandCorrectnessChecking(const int indexOfNextCommandIfThereIsTheMark,
                                       const int indexOfNextCommandIfThereIsNotTheMark, const char action) {
    if (!(commandIndexChecking(indexOfNextCommandIfThereIsTheMark, indexOfNextCommandIfThereIsNotTheMark, counter)) ||
        !(commandActionChecking(action))) {
        showTheInputRequirements();
        return false;
    }
    return true;
}