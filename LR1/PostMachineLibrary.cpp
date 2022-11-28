
/**
* @file
* Definition of PostMachineLibrary with of the algorithm of actions of Post machine
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#include "PostMachineLibrary.h"


void PostMachine::Tape::putMark(const int index) {
    this->cells[index] = 1;
}

void PostMachine::Tape::deleteMark(const int index) {
    this->cells[index] = 0;
}

bool PostMachine::Tape::checkMark(const int index) {
    return this->cells[index] != 0;
}

void PostMachine::Tape::changeMark(const int index) {
    if (this->cells[index]) this->deleteMark(index);
    else this->putMark(index);
}

bool PostMachine::changeMarkOnTape(const int index) {
    if (index <= this->rules.getSizeOfTape() && index > 0) {
        this->tape.changeMark(index);
        return true;
    } else {
        return false;
    }
}

bool PostMachine::setNewTape(vector<int> &newTape) {
    this->tape.cells.clear();
    this->tape.cells.push_back(0);
    int size = newTape.size();
    for (int i = 0; i < size; i++) {
        if (newTape[i] != 0 && newTape[i] != 1) {
            return false;
        }
        this->tape.cells.push_back(newTape[i]);
    }
    return true;
}

void PostMachine::Carriage::moveToTheRight() {
    this->index++;
}

void PostMachine::Carriage::moveToTheLeft() {
    this->index--;
}

void PostMachine::showTheRules() {
    Rules::showTheInputRequirements();
    int size = Rules::getNumberOfCommands();
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << this->rules.getActionOfCommand(i) << ' ';
        if (this->rules.getActionOfCommand(i) == BRANCHING) {
            cout << this->rules.getIndexOfNextCommand(i) / 100 << ' ' << this->rules.getIndexOfNextCommand(i) % 100;
        } else {
            if (this->rules.getActionOfCommand(i) != STOP)
                cout << this->rules.getIndexOfNextCommand(i) + 1;
        }
        cout << endl;
    }
}


/**
* Edits a rule with no branching
* @param index Contains an index of a current command
* @param action Contains a command, that needs to be changed
*/
bool PostMachine::editTheRule(const int index, char action) {
    if (!(Rules::commandCorrectnessChecking(index, action))) {
        return false;
    }
    this->rules.setCommand(index - 1, action);
    return true;
}

/**
* Edits a rule with branching
* @param index Contains an index of a current command
* @param action Contains a command, that needs to be changed
* @param indexOfNextCommandIfThereIsTheMark Contains a pointer to the next command
* @param indexOfNextCommandIfThereIsNotTheMark Contains a pointer to the next command
*/
bool PostMachine::editTheRule(const int index, char action, int indexOfNextCommandIfThereIsTheMark,
                              int indexOfNextCommandIfThereIsNotTheMark) {
    if (!(Rules::commandCorrectnessChecking(indexOfNextCommandIfThereIsTheMark,
                                            indexOfNextCommandIfThereIsNotTheMark, action))) {
        return false;
    }
    this->rules.setCommand(index - 1, action, indexOfNextCommandIfThereIsTheMark,
                           indexOfNextCommandIfThereIsNotTheMark);
    return true;
}

/**
* Adds a rule in a case of no branching
* @param index Contains an index of a new command
* @param i Contains a current index of new command
* @param action Contains a command, that needs to be changed
*/
bool PostMachine::addTheRule(const int index, char action) {
    int i = Rules::getNumberOfCommands();
    if (!(Rules::commandCorrectnessChecking(index, action))) {
        return false;
    }
    this->rules.newCommand(action);
    while (index <= i) {
        this->rules.swapTheRules(i, i - 1);
        i--;
    }
    return true;
}

/**
* Adds a rule in a case of branching
* @param index Contains an index of a current command
* @param action Contains a command, that needs to be changed
* @param indexOfNextCommandIfThereIsTheMark Contains a pointer to the next command
* @param indexOfNextCommandIfThereIsNotTheMark Contains a pointer to the next command
*/
bool PostMachine::addTheRule(const int index, char action, int indexOfNextCommandIfThereIsTheMark,
                             int indexOfNextCommandIfThereIsNotTheMark) {
    int i = Rules::getNumberOfCommands();
    if (!(Rules::commandCorrectnessChecking(index, action))) {
        return false;
    }
    this->rules.newCommand(action, indexOfNextCommandIfThereIsTheMark, indexOfNextCommandIfThereIsNotTheMark);
    while (index <= i) {
        this->rules.swapTheRules(i, i - 1);
        i--;
    }
    return true;
}

bool PostMachine::deleteTheRule(int index) {
    int i = Rules::getNumberOfCommands();
    if (index > i) {
        return false;
    }
    while (index < i) {
        this->rules.swapTheRules(index - 1, index);
        index++;
    }
    this->rules.deleteTheLastCommand();
    return true;
}


bool PostMachine::Tape::inputTapeFromFile(const char *path) {
    ifstream F;
    F.open(path);
    if (!F.is_open()) {
        return false;
    }
    string buffer;
    /**First element of Tape is an artificially created empty cell, which is needed for the correct work of Post machine
     * Carriage points on null cell by default
     */
    this->cells.push_back(0);
    getline(F, buffer);
    for (char i : buffer) {
        if (i != '0' && i != '1') {
            F.close();
            return false;
        }
        this->cells.push_back(i - '0');

    }
    F.close();
    return true;
}


bool PostMachine::inputFromFile(const char *path) {
    ifstream F;
    F.open(path);
    if (!F.is_open()) {
        return false;
    }
    if (!this->tape.inputTapeFromFile(path)) {
        return false;
    }
    if (!this->rules.inputRulesFromFile(path)) {
        return false;
    }
    F.close();
    return true;
}

void PostMachine::Tape::outputTapeToConsole() {
    for (int i = 1; i < this->cells.size(); i++) {
        cout << this->cells[i];
    }
    cout << endl;
}

void PostMachine::printState() {
    this->tape.outputTapeToConsole();
    for (int i = 0; i < this->carriage.index - 1; i++)
        cout << ' ';
    cout << "T \n\n";
}

void PostMachine::outputToFile(const char *path) {
    ofstream F;
    F.open(path);
    if (!F.is_open()) {
        cout << "Error" << endl;
        return;
    }
    for (int i = 1; i < this->tape.cells.size(); i++) {
        F << this->tape.cells[i];
    }
    F.close();
}
/**
* Contains the definition of actions, available for the Post machine
*/
bool PostMachine::realizeTheAlgorithm() {
    int index = 0;

    while (true) {
        switch (this->rules.getActionOfCommand(index)) {
            case MOVE_TO_THE_RIGHT: {
                this->carriage.moveToTheRight();
                index++;
                break;
            }
            case MOVE_TO_THE_LEFT: {
                this->carriage.moveToTheLeft();
                index++;
                break;
            }
            case DELETE_MARK: {
                this->tape.deleteMark(this->carriage.index);
                index++;
                break;
            }
            case PUT_MARK: {
                this->tape.putMark(this->carriage.index);
                index++;
                break;
            }
            case BRANCHING: {
                if (this->tape.checkMark(this->carriage.index))
                    index = this->rules.getIndexOfNextCommand(index) / 100 - 1;
                else
                    index = this->rules.getIndexOfNextCommand(index) % 100 - 1;
                break;
            }
            case STOP: {
                return true;
            }

            default: {
                return false;
            }
        }
    }
}

/**
* Contains the definition of actions, available for the Post machine, and step-by-step demonstration of realization
*/
bool PostMachine::realizeTheAlgorithmWithTheStepByStepDemonstration(bool flag) {
    int index = 0;
    while (true) {
        if (flag){
            printState();
        }
        switch (this->rules.getActionOfCommand(index)) {
            case MOVE_TO_THE_RIGHT: {
                this->carriage.moveToTheRight();
                index++;
                break;
            }
            case MOVE_TO_THE_LEFT: {
                this->carriage.moveToTheLeft();
                index++;
                break;
            }
            case DELETE_MARK: {
                this->tape.deleteMark(this->carriage.index);
                index++;
                break;
            }
            case PUT_MARK: {
                this->tape.putMark(this->carriage.index);
                index++;
                break;
            }
            case BRANCHING: {
                if (this->tape.checkMark(this->carriage.index))
                    index = this->rules.getIndexOfNextCommand(index) / 100 - 1;
                else
                    index = this->rules.getIndexOfNextCommand(index) % 100 - 1;
                break;
            }
            case STOP: {
                return true;
            }
            default: {
                return false;
            }
        }
    }
}


bool PostMachine::run(const char *path) {
    return (this->inputFromFile(path) && this->realizeTheAlgorithm());
}

bool PostMachine::runWithTheStepByStepDemonstration(bool flag, const char *path) {
    return (this->inputFromFile(path) && this->realizeTheAlgorithmWithTheStepByStepDemonstration(flag));
}

/**
 * Works with an artificially created cell
 * @return Tape with changed cells
 */
vector<int> PostMachine::getTape() {
    vector<int> resultTape = this->tape.cells;
    resultTape.erase(resultTape.begin());
    return resultTape;
}

char PostMachine::getActionOfCommand(const int index) {
    if (index > Rules::getNumberOfCommands() || index < 1) {
        return NULL_ACTION;
    } else {
        return this->rules.getActionOfCommand(index - 1);
    }
}

int PostMachine::getIndexOfNextCommand(const int index) {
    if (index > Rules::getNumberOfCommands() || index < 1) {
        return NULL_ACTION;
    } else {
        return this->rules.getIndexOfNextCommand(index - 1);
    }
}

