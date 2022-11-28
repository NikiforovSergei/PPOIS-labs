
/**
* @file
* Contains declaration of functions, such as constituent parts and custom functions of the Post machine
*/

#ifndef POSTMACHINE_POSTMACHINELIBRARY_H
#define POSTMACHINE_POSTMACHINELIBRARY_H

#include <string>
#include <vector>
#include "Rules.h"

using namespace std;

/**
*\brief Defines constituent parts and custom functions of the Post machine
*
*Post machine works according to the algorithm specified by the user.
*
* The private section contains the classes Tape (with methods for setting / removing labels) and Carriage (with methods for moving it along the tape).
* Tape is an ordered set of cells, which have two conditions: with/without a mark.
*The public section contains methods for user to control the process.
*/
class PostMachine {
private:
    class Tape {
    private:
        vector<int> cells;
    public:
        bool inputTapeFromFile(const char *path);

        void outputTapeToConsole();

        void putMark(int index);

        void deleteMark(int index);

        bool checkMark(int index);

        /**
         * Deletes the mark, if it exists, puts the mark, if there is none.
         */
        void changeMark(int index);

        friend PostMachine;
    } tape;

    class Carriage {
    private:
        /**
         * @param index Contains the index of the cell on tape, that the carriage is currently pointing to
         */
        int index = 0;
    public:
        /**
          * Moves carriage to the right along the tape
          */
        void moveToTheRight();

        /**
         * Moves carriage to the left along the tape
         */
        void moveToTheLeft();

        friend PostMachine;
    } carriage;

    /**
     * @param rules Contains a set of commands, that are specified by user
     */
    Rules rules;

public:
    /**
* When creating an object of the Post Machine class, the command counter needs to be reset, because the relaunched Post machine has no commands
*/
    PostMachine() {
        Rules::resetTheCounter();
    }

    bool inputFromFile(const char *path);

    /**
     * Implementation of the algorithm according to the rules entered by the user
     */
    bool realizeTheAlgorithm();

    bool realizeTheAlgorithmWithTheStepByStepDemonstration(bool);

    /**
     * \brief Shows the state of the Post machine.
     * The state of machine is described by the state of cells on tape and by the position of carriage.
     */
    void printState();

    void outputToFile(const char *path);

    /**
     * Replaces the mark on tape.
     * @param index Contains the index of the cell, where a change of mark is needed
     */
    bool changeMarkOnTape(int index);

    bool setNewTape(vector<int> &new_tape);

    /**
* Shows which rules are already entered / edited by user.
*/
    void showTheRules();

    char getActionOfCommand(int index);

    int getIndexOfNextCommand(int index);

    /**
* Implements the addition of single-variant rule.
* @param index An integer containing the serial number of action
* @param action Contains an action, which correlates with the rules
*/
    bool addTheRule(int index, char action);

    bool addTheRule(int index, char action, int indexOfNextCommandIfThereIsTheMark,
                    int indexOfNextCommandIfThereIsNotTheMark);

    bool editTheRule(int index, char action);

    bool editTheRule(int index, char action, int indexOfNextCommandIfThereIsTheMark,
                     int indexOfNextCommandIfThereIsNotTheMark);

    bool deleteTheRule(int index);

/**
* \brief Starts the Post machine
* Reads from file and realizes the algorithm.
*/
    bool run(const char *path);

    bool runWithTheStepByStepDemonstration(bool flag, const char *path);

    vector<int> getTape();

};

#endif //POSTMACHINE_POSTMACHINELIBRARY_H


