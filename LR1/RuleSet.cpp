#include "HeaderRuleSet.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

/// <summary>
/// \brief constructor without parametrs
/// </summary>
RuleSet::RuleSet()
{

}

/// <summary>
/// \brief constructor with parametrs
/// </summary>
/// <param name="arr"></param>
RuleSet::RuleSet(vector<Rule>arr)
{
	rules = arr;
}


/// <summary>
/// \brief destructor
/// </summary>
RuleSet::~RuleSet()
{

}

/// <summary>
/// \brief function that adds one rule in the vector of rules
/// </summary>
/// <param name="textrule"></param>

void RuleSet::AddRule(string textrule)
{
	char curSymb, curSt;
	string textR;
	Rule rl;
	curSt = textrule.at(0);
	curSymb = textrule.at(2);
	textR = textrule.substr(4);
	rl = Rule(curSymb, curSt, textR);
	this->rules.push_back(rl);
};

/// <summary>
/// \brief function for viewing rules
/// </summary>

void RuleSet::ViewRules()
{
	int size = this->rules.size();
	for (int i =0; i < size; i++)
		cout << i << " " << this->rules[i] <<endl;

};

/// <summary>
/// \brief function for deleting a single rule
/// </summary>

void RuleSet::DeleteRule()
{
	int index;
	cout << "Enter the number of the rule you want to delete\n";
	cin >> index;
	this->rules.erase(this->rules.begin() + index);
}

/// <summary>
/// \brief function for searching relu from the vector of rules
/// </summary>
/// <param name="curState"></param>
/// <param name="curSymbol"></param>
/// <returns></returns>

string RuleSet::SearchRule(char curState, char curSymbol)
{
	for (int i = 0; i < this->rules.size(); i++)
	{
		if (this->rules[i].Comparison(curState, curSymbol))
			return this->rules[i].GetRule();
		else
			continue;
	}
}



