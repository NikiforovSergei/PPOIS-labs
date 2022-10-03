#pragma once
#include "Source.h"
#include "Fraction.h"
#include <iostream>
#include <string>
using namespace std;


string value;

Fraction operator+ (Fraction first, Fraction second)
{
	int newNumerator;
	Fraction output;
	translateFraction(first.value);
	translateFraction(second.value);
	if (isInteger(second.value))
	{
		int integerDigit = atoi(second.value.c_str());
		newNumerator = integerDigit * atoi(findDenominator(first.value).c_str());
		second.value = to_string(newNumerator) + '|' + findDenominator(first.value);
	}

	if (findDenominator(first.value) == findDenominator(second.value))
	{
		int firstNumerator = atoi(findNumerator(first.value).c_str());
		int secondNumerator = atoi(findNumerator(second.value).c_str());
		int numeratorSum = firstNumerator + secondNumerator;
		output.value = to_string(numeratorSum) + '|' + findDenominator(first.value);
	}
	else
	{
		int firstDenominator = atoi(findDenominator(first.value).c_str());
		int secondDenominator = atoi(findDenominator(second.value).c_str());
		int firstNumerator = atoi(findNumerator(first.value).c_str());
		int secondNumerator = atoi(findNumerator(second.value).c_str());
		int newDenominator = firstDenominator * secondDenominator;
		int newNumerator = (firstNumerator * secondDenominator) + (secondNumerator * firstDenominator);
		output.value = to_string(newNumerator) + '|' + to_string(newDenominator);
	}
	output.value = reduceFraction(output.value);
	return output;
}

Fraction operator-(Fraction first, Fraction second)
{
	int newNumerator;
	Fraction output;
	translateFraction(first.value);
	translateFraction(second.value);

	if (isInteger(second.value))
	{
		int integerDigit = atoi(second.value.c_str());
		newNumerator = integerDigit * atoi(findDenominator(first.value).c_str());
		second.value = to_string(newNumerator) + '|' + findDenominator(first.value);
	}

	if (findDenominator(first.value) == findDenominator(second.value))
	{
		int firstNumerator = atoi(findNumerator(first.value).c_str());
		int secondNumerator = atoi(findNumerator(second.value).c_str());
		int numeratorSum = firstNumerator - secondNumerator;
		output.value = to_string(numeratorSum) + '|' + findDenominator(first.value);
	}
	else
	{
		int firstDenominator = atoi(findDenominator(first.value).c_str());
		int secondDenominator = atoi(findDenominator(second.value).c_str());
		int firstNumerator = atoi(findNumerator(first.value).c_str());
		int secondNumerator = atoi(findNumerator(second.value).c_str());
		int newDenominator = firstDenominator * secondDenominator;
		int newNumerator = (firstNumerator * secondDenominator) - (secondNumerator * firstDenominator);
		output.value = to_string(newNumerator) + '|' + to_string(newDenominator);
	}
	output.value = reduceFraction(output.value);
	return output;
}

Fraction operator*(Fraction first, Fraction second)
{
	int newNumerator;
	Fraction output;

	translateFraction(first.value);
	translateFraction(second.value);

	if (isInteger(second.value))
	{
		int integerDigit = atoi(second.value.c_str());
		newNumerator = integerDigit * atoi(findDenominator(first.value).c_str());
		second.value = to_string(newNumerator) + '|' + findDenominator(first.value);
	}

	int firstDenominator = atoi(findDenominator(first.value).c_str());
	int secondDenominator = atoi(findDenominator(second.value).c_str());
	int firstNumerator = atoi(findNumerator(first.value).c_str());
	int secondNumerator = atoi(findNumerator(second.value).c_str());
	newNumerator = firstNumerator * secondNumerator;
	int newDenominator = firstDenominator * secondDenominator;
	output.value = to_string(newNumerator) + '|' + to_string(newDenominator);
	output.value = reduceFraction(output.value);
	return output;
}

Fraction operator/(Fraction first, Fraction second)
{
	int newNumerator;
	Fraction output;
	translateFraction(first.value);
	translateFraction(second.value);

	if (isInteger(second.value))
	{
		int integerDigit = atoi(second.value.c_str());
		newNumerator = integerDigit * atoi(findDenominator(first.value).c_str());
		second.value = to_string(newNumerator) + '|' + findDenominator(first.value);
	}

	int firstDenominator = atoi(findDenominator(first.value).c_str());
	int secondDenominator = atoi(findDenominator(second.value).c_str());
	int firstNumerator = atoi(findNumerator(first.value).c_str());
	int secondNumerator = atoi(findNumerator(second.value).c_str());
	newNumerator = firstNumerator * secondDenominator;
	int newDenominator = firstDenominator * secondNumerator;
	output.value = to_string(newNumerator) + '|' + to_string(newDenominator);
	output.value = reduceFraction(output.value);
	return output;
}

Fraction operator++(Fraction first, int)
{

	Fraction output;
	Fraction newExpression;
	newExpression.value = "1|1";
	output = first + newExpression;
	return output;
}

Fraction operator--(Fraction first, int)
{
	Fraction output;
	Fraction newExpression;
	newExpression.value = "1|1";
	output = first - newExpression;
	return output;
}

bool operator >(Fraction first, Fraction second)
{
	double largestFraction;
	bool output;
	double firstDouble = castingToDouble(first.value);
	double secondtDouble = castingToDouble(second.value);
	largestFraction = max(firstDouble, secondtDouble);
	if (largestFraction == firstDouble)output = true;
	else output = false;
	return output;
}

bool operator <(Fraction first, Fraction second)
{
	double largestFraction;
	bool output;
	double firstDouble = castingToDouble(first.value);
	double secondtDouble = castingToDouble(second.value);
	largestFraction = max(firstDouble, secondtDouble);
	if (largestFraction == secondtDouble)output = true;
	else output = false;
	return output;
}

bool operator>= (Fraction first, Fraction second)
{
	double largestFraction;
	bool output;
	double firstDouble = castingToDouble(first.value);
	double secondtDouble = castingToDouble(second.value);
	if (firstDouble != secondtDouble)
	{
		largestFraction = max(firstDouble, secondtDouble);
		if (largestFraction == firstDouble)output = true;
		else output = false;
	}
	else output = true;
	return output;
}

bool operator <= (Fraction first, Fraction second)
{
	double largestFraction;
	bool output;
	double firstDouble = castingToDouble(first.value);
	double secondtDouble = castingToDouble(second.value);
	if (firstDouble != secondtDouble)
	{
		largestFraction = max(firstDouble, secondtDouble);
		if (largestFraction == secondtDouble)output = true;
		else output = false;
	}
	else output = true;
	return output;
}

Fraction operator--(Fraction first)
{
	return first;
}

Fraction operator ++(Fraction first)
{
	return first;
}


