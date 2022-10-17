#include "HeaderRule.h"
#include <string>

/// <summary>
/// \brief constructor without parametrs
/// </summary>

Rule::Rule()
{

}

/// <summary>
/// \brief destructor
/// </summary>

Rule::~Rule()
{

}

/// <summary>
/// \brief constructor withparametrs
/// </summary>
/// <param name="curSymb"></param>
/// <param name="curSt"></param>
/// <param name="textR"></param>

Rule::Rule(char curSymb, char curSt, string textR)
{
	curSymbol = curSymb;
	curState = curSt;
	textRule = textR;
}

/// <summary>
/// \brief function for comparing the current symbol and its position on the head with the symbols and their positions in the rule vector
/// </summary>
/// <param name="curSt"></param>
/// <param name="curSymb"></param>
/// <returns></returns>

bool Rule::Comparison(char curSt, char curSymb)
{
	if (curSymb == curSymbol && curSt == curState)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// \brief function that return the text of the rule
/// </summary>
/// <returns></returns>

string Rule::GetRule()
{
	return this->textRule;
}

