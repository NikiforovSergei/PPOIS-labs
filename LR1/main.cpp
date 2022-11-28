#include <cstdio>
#include <vector>
#include <assert.h>
#include <iostream>
#include "PostMachineLibrary.h"

const char NAME1[] = "Input1.txt"; 
const char NAME2[] = "Input2.txt";
const char NAME3[] = "Input3.txt";

int main(int argc, char *argv[]) {
    {
        PostMachine machine;
        assert(!machine.run(NAME3));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        assert(machine.getActionOfCommand(1) == MOVE_TO_THE_RIGHT);
        assert(machine.getIndexOfNextCommand(2) == 301);
    }

    {
        PostMachine machine;
        machine.run(NAME2);
        vector<int> result = {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
        assert(result == machine.getTape());
    }
    {
        PostMachine machine;
        vector<int> newTape = {0, 0, 11, 1, 0};
        machine.setNewTape(newTape);
        assert(!machine.setNewTape(newTape));
    }
    {
        PostMachine machine;
        vector<int> newTape = {1, 1, 1, 0, 0, 0, 0};
        machine.setNewTape(newTape);
        assert(machine.getTape() == newTape);
    }
    {
        PostMachine machine;
        vector<int> newTape = {1};
        machine.setNewTape(newTape);
        assert(machine.getTape() == newTape);
    }
    {
        PostMachine machine;
        vector<int> newTape = {1, 01, 1};
        machine.setNewTape(newTape);
        assert(machine.getTape() == newTape);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 7;
        assert(!machine.addTheRule(index, STOP));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        assert(!machine.addTheRule(index, '1'));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 4;
        machine.addTheRule(index, BRANCHING, 3, 6);
        assert(machine.getActionOfCommand(index) == BRANCHING);
        assert(machine.getIndexOfNextCommand(index) == 306);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 6;
        machine.addTheRule(index, MOVE_TO_THE_LEFT);
        assert(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        machine.editTheRule(index, MOVE_TO_THE_LEFT);
        assert(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 2;
        machine.editTheRule(index, BRANCHING, 1, 3);
        assert(machine.getActionOfCommand(index) == BRANCHING);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 3;
        assert(!machine.editTheRule(index, 'A'));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 9;
        assert(!machine.editTheRule(index, PUT_MARK));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 4;
        assert(!machine.editTheRule(index, BRANCHING, 0, 11));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 4;
        assert(!machine.editTheRule(index, BRANCHING, 0, 11));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 2;
        machine.deleteTheRule(index);
        assert(machine.getActionOfCommand(index) == MOVE_TO_THE_LEFT);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 1;
        machine.deleteTheRule(index);
        assert(machine.getActionOfCommand(index) == BRANCHING);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 4;
        machine.deleteTheRule(index);
        assert(machine.getActionOfCommand(index) == STOP);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 5;
        machine.deleteTheRule(index);
        assert(machine.getActionOfCommand(index) == NULL_ACTION);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 18;
        assert(!machine.deleteTheRule(index));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 8;
        assert(!machine.changeMarkOnTape(index));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = -1;
        assert(!machine.changeMarkOnTape(index));
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 1;
        machine.changeMarkOnTape(index);
        assert(machine.getTape()[index - 1] == 1);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME1);
        const int index = 5;
        machine.changeMarkOnTape(index);
        assert(machine.getTape()[index - 1] == 1);
    }
    {
        PostMachine machine;
        machine.inputFromFile(NAME2);
        const int index = 7;
        machine.changeMarkOnTape(index);
        assert(machine.getTape()[index - 1] == 0);
    }
    {
        
            PostMachine machine;
            machine.inputFromFile(NAME2);
            const int index = 4;
            machine.showTheRules();
            std::cout << "\nDelete the 4th command.\n\n";
            machine.deleteTheRule(index);
            assert(machine.getActionOfCommand(index) == MOVE_TO_THE_RIGHT);
            machine.showTheRules();
    }
    {
        Rules rules;
        rules.inputRulesFromFile(NAME2);
        PostMachine machine;
        if (argc > 1){
        string s = argv[1];
        if (s == "-log") {
            rules.flag = true;
        } else rules.flag = false;}
        assert(machine.runWithTheStepByStepDemonstration(rules.flag, NAME2));
    }
    
}