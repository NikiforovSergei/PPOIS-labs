#pragma once
#include <string>
#include "Fraction.h"
using namespace std;

string findFirstFraction(const string& inputExpression);

string findSecondFraction(const string& inputExpression);

bool isInteger(string inputFraction);

bool hasWholePart(const string& inputFraction);

string findWholePart(const string& inputFraction);

string findDenominator(const string& inputFraction);

string findNumerator(const string& inputFraction);

string translateFraction(const string& inputFraction);

string reduceFraction(const string& inputFraction);

double castingToDouble(const string& inputFraction);

