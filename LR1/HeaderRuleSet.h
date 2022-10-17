#pragma once
#include "HeaderRule.h"
#include <vector>
#include <iostream>
using namespace std;
/// <summary>
/// \brief class that implements the vector of rules by which the head interprets the program
/// </summary>
class RuleSet
{
private:
	/// <summary>
	/// vector containing rules 
	/// </summary>
	vector<Rule>rules;
public:
	RuleSet();
	~RuleSet();
	RuleSet(vector<Rule>);
	void AddRule(string);
	void ViewRules();
	void DeleteRule();
	string SearchRule(char, char);
	
};

