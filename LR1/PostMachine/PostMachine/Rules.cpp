/**
* @file Rules.cpp
* @author Daniil Halushka
* @brief This file contain all necessary definitions
*/

#include "Rules.h"
#include <iostream>

PostMachine::PostMachine()
{
    /** 
    * @brief Label start position
    */
    tapeIndex = 0;
}

PostMachine::~PostMachine()
{
}

/** 
 * @brief The user enters the input tape until it turns out to be correct (it means from 0 and 1).
*/
void PostMachine::readTape()
{
    int check = -1;
    while (check < 0)
    {
        check = -1;
        cout << "������� �����: \n";
        cin >> tape;
        for (unsigned long long i = 0; i < tape.size(); i++)
            if (tape[i] == '0' || tape[i] == '1')
                check = 1;
            else
            {
                check = INT_MIN;
                cout << "������ ������, �� �������� � �������\n";
                break;
            }
    }
}
/**
 * @brief Reading from input data from a file in which
 * A - own alphabet
 * X � set of variables
 * A1 - set of axioms
 * R is a finite set of inference rules
*/
void PostMachine::readInputFile(string path)
{
    ifstream file(path);
    if (!file)
    {
        cout << "������, ���� ����� �� ������\n";
        exit(-1);
    }
    bool foundRules = false;
    while (!file.eof())
    {
        string str;
        getline(file, str);

        if (str == "}") foundRules = false;
        if (foundRules) rules.push_back(str.substr(0, str.find(",")));
        if (str == "R = {") foundRules = true;
    }
    file.close();
}

/**
 * @brief In a loop, we walk along the tape and apply the rules to the cell, to which the label points.
*/
string PostMachine::start()
{
    unsigned long long currentRule = 0;
    while (true)
    {
        // Getting the current command
        string command;
        if (currentRule < rules.size())
            command = rules.at(currentRule);
        else
            return("������ ����������, ��������� ��������� 1");

        /**
         * @brief We execute a command from 6 available.
         * If you cannot find a command from the list, then we return a response with an error.
        */

        if (command.find("<-") != string::npos)
        {
            saveStateBefore();
            coutStateBefore();
            tapeIndex--;

            if (tapeIndex < 0)
            {
                tape.insert(0, "0");
                tapeIndex++;
            }
            saveStateAfter(command);
            coutStateAfter();
            currentRule = stoi(command.substr(command.find("<-") + 2)) - 1;
        }
        else if (command.find("->") != string::npos)
        {
            saveStateBefore();
            coutStateBefore();
            tapeIndex++;

            if (tapeIndex > tape.length())
            {
                tape.insert(tape.length(), "0");
            }
            saveStateAfter(command);
            coutStateAfter();
            currentRule = stoi(command.substr(command.find("->") + 2)) - 1;
        }
        else if (command.find("?") != string::npos)
        {
            saveStateBefore();
            coutStateBefore();
            if (tape[tapeIndex] == '0')
            {
                saveStateAfter(command);
                coutStateAfter();
                currentRule = stoi(command.substr(command.find("?") + 1, command.find(";"))) - 1;
                continue;
            }
            else
            {
                saveStateAfter(command);
                coutStateAfter();
                currentRule = stoi(command.substr(command.find(";") + 1)) - 1;
                continue;
            }
        }
        else if (command.find("V") != string::npos)
        {
            saveStateBefore();
            coutStateBefore();
            if (tape[tapeIndex] == '0')
                tape[tapeIndex] = '1';
            else
                return("������ ����������, ��������� ��������� 2");

            saveStateAfter(command);
            coutStateAfter();
            currentRule = stoi(command.substr(command.find("V") + 1)) - 1;
        }
        else if (command.find("X") != string::npos)
        {
            saveStateBefore();
            coutStateBefore();
            if (tape[tapeIndex] == '1')
                tape[tapeIndex] = '0';
            else
                return("������ ����������, ��������� ��������� 3");

            saveStateAfter(command);
            coutStateAfter();
            currentRule = stoi(command.substr(command.find("X") + 1)) - 1;
        }
        else if (command.find("!") != string::npos)
        {
            return("��������� ������� ��������� ");
        }
        else
        {
            return("������ ����������, ��������� ��������� 4");
        }
    }

    return("������ ����������, ��������� ��������� 5");
}

/**
 * @brief Write to the tape state file before the rule is applied.
 * If the file is not found, it is created
*/
void PostMachine::saveStateBefore()
{
    ofstream file_out;
    file_out.open("result.txt", std::ios::app);
    file_out << tape << "\n";
    string carriage;
    for (unsigned long long i = 0; i < tape.length(); i++) if (i != tapeIndex) carriage += ' '; else carriage += '^';
    file_out << carriage << "\n";
    file_out.close();
}

/**
 * @brief Writing to file the current action and state of the tape (after applying the rule).
*/
void PostMachine::saveStateAfter(string command)
{
    ofstream file_out;
    file_out.open("result.txt", std::ios::app);
    file_out << command << "\n";
    file_out << tape << "\n";
    string carriage;
    for (unsigned long long i = 0; i < tape.length(); i++) if (i != tapeIndex) carriage += ' '; else carriage += '^';
    file_out << carriage << "\n";
    file_out << "**************************************************************\n";
    file_out.close();
}

void PostMachine::coutStateBefore()
{
    cout << tape << "\n";
    string carriage;
    for (unsigned long long i = 0; i < tape.length(); i++) if (i != tapeIndex) carriage += ' '; else carriage += '^';
    cout << carriage << "\n";
}

/**
 * @brief Writing to file the current action and state of the tape (after applying the rule).
*/
void PostMachine::coutStateAfter()
{
    /*cout << command << "\n";*/
    cout << tape << "\n";
    string carriage;
    for (unsigned long long i = 0; i < tape.length(); i++) if (i != tapeIndex) carriage += ' '; else carriage += '^';
    cout << carriage << "\n";
    cout << "**************************************************************\n";
}