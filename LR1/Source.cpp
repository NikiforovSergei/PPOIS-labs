#include "Source.h"

string findFirstFraction(const string& inputExpression)
{
	string output;
	if (inputExpression[0] == '+' || inputExpression[0] == '-')
	{
		int j = 2;
		string buffer;
		while (inputExpression[j] != '\0')
		{
			buffer.push_back(inputExpression[j]);
			j++;
		}
		output = buffer;
	}
	else
	{
		int i = 0;
		string firstFraction;
		while (inputExpression[i] != '*' && inputExpression[i] != '+' && inputExpression[i] != '-' && inputExpression[i] != '/' && inputExpression[i] != '\0' && inputExpression[i] != '>' && inputExpression[i] != '<')
		{
			firstFraction.push_back(inputExpression[i]);
			i++;
		}
		output = firstFraction;
	}

	return output;
}

string findSecondFraction(const string& inputExpression)
{
	int i = 0;
	string secondFraction = "";
	while (inputExpression[i] != '*' && inputExpression[i] != '+' && inputExpression[i] != '-' && inputExpression[i] != '/' && inputExpression[i] != '>' && inputExpression[i] != '<' && inputExpression[i] != ' ' && inputExpression[i] != '\0')
	{
		i++;
	}

	if (inputExpression[i] == '\0')
	{
		return secondFraction;
	}
	else
	{
		i++;
		secondFraction.clear();
		while (inputExpression[i] != '\0')
		{
			secondFraction.push_back(inputExpression[i]);
			i++;
		}
	}
	return secondFraction;
}

bool isInteger(string inputFraction)
{
	int i = 0;
	while (inputFraction[i] != '\0')
	{
		if (inputFraction[i] == '|')return false;
		i++;
	}
	return true;
}

bool hasWholePart(const string& inputFraction)
{
	int i = 0, counter = 0;
	while (inputFraction[i] != '\0')
	{
		if (inputFraction[i] == '(') counter++;
		i++;
	}
	if (counter > 0) return 1;
	else return 0;

}

string findWholePart(const string& inputFraction)
{
	int i = 0;
	string wholePart;
	if (hasWholePart(inputFraction))
	{
		while (inputFraction[i] != '(')
		{
			wholePart.push_back(inputFraction[i]);
			i++;
		}
	}
	else  wholePart = "";
	return wholePart;
}

string findDenominator(const string& inputFraction)
{
	string output;
	if (hasWholePart(inputFraction))
	{
		int i = 0;
		string output;
		while (inputFraction[i] != '|')i++;
		i++;
		while (inputFraction[i] != ')')
		{
			output.push_back(inputFraction[i]);
			i++;
		}
		return output;
	}
	else
	{
		int i = 0;
		while (inputFraction[i] != '|')i++;
		i++;
		while (inputFraction[i] != '\0')
		{
			output.push_back(inputFraction[i]);
			i++;
		}
		return output;
	}
}

string findNumerator(const string& inputFraction)
{
	int i = 0;
	string output, Num;
	if (hasWholePart(inputFraction))
	{
		int i = 0;
		while (inputFraction[i] != '(')i++;
		i++;
		while (inputFraction[i] != '|')
		{
			Num.push_back(inputFraction[i]);
			i++;
		}
		int wholePart = atoi(findWholePart(inputFraction).c_str());
		int Den = atoi(findDenominator(inputFraction).c_str());
		output = (to_string(wholePart * Den + atoi(Num.c_str())));
	}
	else
	{
		string buffer;
		while (inputFraction[i] != '|')
		{
			buffer.push_back(inputFraction[i]);
			i++;
		}
		output = buffer;
	}
	return output;
}

string translateFraction(const string& inputFraction)
{
	string output;
	if (hasWholePart(inputFraction))
	{
		output = findNumerator(inputFraction) + '|' + findDenominator(inputFraction);
	}
	else
	{
		output = inputFraction;
	}
	return output;
}

string reduceFraction(const string& inputFraction)
{
	int buffer;
	string output;
	int Numerator = atoi(findNumerator(inputFraction).c_str());
	int Denominator = atoi(findDenominator(inputFraction).c_str());
	int num = Numerator, den = Denominator;
	while (num > 0 && den > 0)
	{
		if (num > den) num %= den;
		else den %= num;
	}
	buffer = num + den;
	output = to_string(Numerator / buffer) + '|' + to_string(Denominator / buffer);
	return output;
}

double castingToDouble(const string& inputFraction)
{
	double output;
	double Numerator = atoi(findNumerator(inputFraction).c_str());
	double Denominator = atoi(findDenominator(inputFraction).c_str());
	output = Numerator / Denominator;
	return output;
}

