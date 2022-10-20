#pragma once
#include <iostream>
#include <string>
using namespace std;

class Fraction
{

public:

	string value;

	friend Fraction operator+(Fraction first, Fraction second);

	friend Fraction operator-(Fraction first, Fraction second);

	friend Fraction operator*(Fraction first, Fraction second);

	friend Fraction operator/(Fraction first, Fraction second);

	friend Fraction operator++(Fraction first, int);

	friend Fraction operator--(Fraction first, int);

	friend bool operator >(Fraction first, Fraction second);

	friend bool operator <(Fraction first, Fraction second);

	friend bool operator>= (Fraction first, Fraction second);

	friend bool operator <= (Fraction first, Fraction second);

	friend Fraction operator++(Fraction first);

	friend Fraction operator--(Fraction first);

};