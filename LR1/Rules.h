

/**
* @file
* Contains declaration of functions, which control the Post machine
*/

#ifndef POSTMACHINE_RULES_H
#define POSTMACHINE_RULES_H

#include <string>
#include <vector>

using namespace std;

enum Action {
    MOVE_TO_THE_RIGHT = '>',
    MOVE_TO_THE_LEFT = '<',
    DELETE_MARK = 'X',
    PUT_MARK = 'V',
    BRANCHING = '?',
    STOP = '!',
    NULL_ACTION = 0
};

/**
* \brief Defines rules and available actions of the Post machine
*
* Rules are composed of an ordered set of commands.
*
* The private section contains a class of commands, that are available for Post machine, getters and setters of actions (in private) and machine control functions (in public).
*/
class Rules {  //Algorithm
private:
    /**
* @param counter  An integer containing the number of symbols in tape
*/
    static int counter;

    /**
* \brief Contains an action available for the Post machine and the index of the next action.
*
*/
    class Command {
    private:
        /**
* @param action contains action, that Post machine is performing
* @param next contains index of next command
*/
        char action;
        int next;
    public:
        /**
* \brief For default cases
*/
        Command() {
            this->action = ' ';
            this->next = 0;
        }

        /**
* \brief For all actions, except branching
*/
         explicit Command(char action) {
            this->action = action;
            this->next = ++counter;
        }

        /**
* \brief For branching case
*/
        Command(char action, int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark) {
            this->action = action;
            this->next = indexOfNextCommandIfThereIsTheMark * 100 + indexOfNextCommandIfThereIsNotTheMark;
            counter++;
        }

        void setAction(char action);

        char getAction();

        void setNext(int next);

        void setNext(int next1, int indexOfNextCommandIfThereIsNotTheMark);

        int getNext();
    };

    /**
* @param commands Contains a set of ordered commands.
*/
    vector<Command> commands;
public:
    /**
* Sets to zero the command counter (hereinafter - to create a new object of the "Post machine" class).
*/
    bool flag = false;
    static void resetTheCounter();

    /**
*@return Number of cells in a tape
*/
    int getSizeOfTape();

    static void showTheInputRequirements();

    bool inputRulesFromFile(const char *path);

    bool setCommand(int index, char action);

    bool setCommand(int index, char action, int indexOfNextCommandIfThereIsTheMark,
                    int indexOfNextCommandIfThereIsNotTheMark);

    bool newCommand(char action);

    bool newCommand(char action, int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark);

    void deleteTheLastCommand();

    char getActionOfCommand(int index);

    int getIndexOfNextCommand(int index);

    static int getNumberOfCommands();

    /**
 * Changes next pointers, so that the command does not refer to itself and everything goes sequentially.
 */
    void automaticNextChanging(int index);

    /**
* Swaps commands in an ordered list.
*/
    void swapTheRules(int firstIndex, int secondIndex);

    static bool commandIndexChecking(int index, int amountOfCommands);

    static bool commandIndexChecking(int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark, int amountOfCommands);

    static bool commandActionChecking(char action);

    static bool commandCorrectnessChecking(int index, char action);

    static bool commandCorrectnessChecking(int indexOfNextCommandIfThereIsTheMark, int indexOfNextCommandIfThereIsNotTheMark, char action);
};

#endif //POSTMACHINE_RULES_H
