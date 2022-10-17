#pragma once
#include "HeaderTape.h"
#include "HeaderRuleSet.h"
#include "HeaderHead.h"
#include <iostream>
using namespace std;
/// <summary>
/// \brief class implementing a turing machine
/// </summary>
class MT
{
private:
	/// <summary>
	/// \brief variable of the tape class type containing the machine tape
	/// </summary>
	/// <param name="tape"></param>
	/// <returns></returns>
	Tape tape;

	/// <summary>
	/// \brief variable of the class head containing the machine head
	/// </summary>
	/// <param name="curState"></param>
	/// <param name="position"></param>
	Head head;
	/// <summary>
	/// \brief variable of the class RuleSet containing the rules for interpretation program
	/// </summary>
	RuleSet ruleset;

	bool StepByStep;
public:
	MT();
	~MT();
	MT(bool);
	void operator= (const MT&);
	void LoadTape(ifstream&);
	void LoadRules(ifstream&);
	void LoadState(ifstream&);
	void ShowRules();
	void deleteRule();
	void changeSymb(int, char);
	void writeSymb(ifstream&, int, char);
	void PrintTape();
	void Run(bool);
	void AddRule(string);
};

