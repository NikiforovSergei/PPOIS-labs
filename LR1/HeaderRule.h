#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
/// <summary>
/// \brief class that forms one rule
/// </summary>
class Rule
{
private:
	/// <summary>
	/// \brief variable containing the tape's symbol
	/// </summary>
	char curSymbol;

	/// <summary>
	/// \brief variable containing the state of the head
	/// </summary>
	char curState;

	/// <summary>
	/// string containing the text of the rule
	/// </summary>
	string textRule;
public:
	Rule();
	~Rule();
	Rule(char, char, string);
	/// <summary>
	///  overloading the streaming output operator
	/// </summary>
	/// <param name="os"></param>
	/// <param name="rule"></param>
	/// <returns></returns>
	friend ostream& operator<<(ostream& os, const Rule& rule)
	{
		return os << rule.curState << rule.curSymbol << rule.textRule;
	}
	bool Comparison(char, char);
	string GetRule();
}; 
