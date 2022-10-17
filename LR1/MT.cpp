#include "HeaderMT.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/// <summary>
/// \brief constructor without parametrs
/// </summary>

MT::MT()
{

}

MT::MT(bool StepByStep)
{
	StepByStep = true;
}

/// <summary>
/// \brief copy constructor 
/// </summary>
/// <param name="mt"></param>

void MT::operator= (const MT& mt)
{
	tape = mt.tape;
	head = mt.head;
	ruleset = mt.ruleset;
}

/// <summary>
/// \brief destructor
/// </summary>

MT::~MT()
{

}

/// <summary>
/// \brief fuction for loading tape from stream 
/// </summary>
/// <param name="file"></param>

void MT::LoadTape(ifstream& file)
{
	
	int count = 0;
	char a;
	string line;
	getline(file, line, '\0');
	count = line.length();

	vector<char>mas(count);
	file.clear();
	file.seekg(0);
	for (int i = 0; i < count; i++)
	{
		file >> mas[i];
	}
	this->tape = Tape(mas);
	cout << "Tape is loaded\n";
	file.close();
};

/// <summary>
/// \brief function for loading head state from stream
/// </summary>
/// <param name="file"></param>

void MT::LoadState(ifstream& file)
{
	
	int count = 0;
	string line;
	getline(file, line, '\n');
	count = line.length();

	vector<char>mas(count);
	file.clear();
	file.seekg(0);
	for (int i = 0; i < count; i++)
	{
		file >> mas[i];
	}
	int pos = static_cast<int>(mas[1])-'0';
	this->head = Head(mas[0], pos);
	file.clear();
	file.seekg(0);
};

/// <summary>
/// \brief function for loading rules from stream
/// </summary>
/// <param name="file"></param>

void MT::LoadRules(ifstream& file)
{

	int count = 0;
	string str1;
	getline(file, str1);
	string str2;
	while (!file.eof())
	{
		getline(file, str2);
		this->ruleset.AddRule(str2);
	}
	file.clear();
	file.seekg(0);
};

/// <summary>
/// \brief function for loading a method for showing rules
/// </summary>

void MT::ShowRules()
{

	this->ruleset.ViewRules();
}

/// <summary>
/// \brief function for loading a method for deleting a single rule
/// </summary>

void MT::deleteRule()
{
	this->ruleset.DeleteRule();
}

/// <summary>
/// \brief function for loading a method for changing symbol on the tape
/// </summary>
/// <param name="pos"></param>
/// <param name="symb"></param>

void MT::changeSymb(int pos, char symb)
{
	this->tape.ChangeSimbol(pos, symb);
}

/// <summary>
/// \brief function for loading a method for writing symbol on the tape
/// </summary>
/// <param name="file"></param>
/// <param name="pos"></param>
/// <param name="symb"></param>

void MT::writeSymb(ifstream& file, int pos, char symb)
{
	int count = 0;
	string line1;
	getline(file, line1);
	count = line1.length();

	vector<char>mas(count);
	file.clear();
	file.seekg(0);
	for (int i = 0; i < count; i++)
	{
		file >> mas[i];
	}
	this->tape.WriteSimbol(symb, pos);
	int TapeLength = this->tape.TapeLength();
	int curPos = TapeLength - 1;
	this->head = Head(mas[0], curPos);
	file.close();
}

/// <summary>
/// \brief function for loading a method for print tape
/// </summary>

void MT::PrintTape()
{ 
	this->tape.Print();
}

/// <summary>
/// \brief  function for implementing of the haed step and interpreting the entire program
/// </summary>
void MT::Run(bool log_check)
{
	string rule;
	char curSymb, curState, replacementSymbol, Shift, State;
	do
	{
		int pos = this->head.GetCurPosition();
		curSymb = this->tape.GetCurSymbol(pos);
		curState = this->head.GetCurState();
		rule = this->ruleset.SearchRule(curState, curSymb);

		replacementSymbol = rule[0];
		Shift = rule[2];
		State = rule[4];

		if (replacementSymbol != ' ')
		{
			this->tape.ChangeSimbol(pos, replacementSymbol);
		}

		if (Shift == 'L' || Shift == 'R')
			this->head.Step(Shift);

		if (State != ' ')
		{
			this->head.ChangeState(State);
		}
		if (log_check)
		{
			cout << curState << endl;
			this->tape.Print();
		}
	}while (State != '0');
	 
	
};



/// <summary>
/// \brief function for loading a method for adding a rule to a rule vector
/// </summary>
/// <param name="rule"></param>

void MT::AddRule(string rule)
{
	this->ruleset.AddRule(rule);
}
