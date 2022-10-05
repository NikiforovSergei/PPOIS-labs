#include "Header.h"
#include <iostream>
using namespace std;


int Fraction::GetNumerator()
{
    return numerator;
}

int Fraction::GetDenominator()
{
    return denominator;
}

int Fraction::GetWhole()
{
    return whole;
}

void Fraction::SetDenominator(int a)
{
    denominator = a;
}

void Fraction::SetNumerator(int a)
{
    numerator = a;
}

void Fraction::SetWhole(int a)
{
    whole = a;
}

void Fraction::Add()
{
    cin >> whole >> numerator >> denominator;
    if (denominator == 0)
    {
        denominator = 1;
    }
}

void Fraction::Long()
{
    numerator = whole * denominator + numerator;
    whole = 0;
}

void Fraction::Short()
{
    Long();

    if (numerator % denominator == 0)
    {
        whole += numerator / denominator;            //Если числ. кратен знаменателю
        numerator = 0;
        denominator = 1;
    }

    if (abs(numerator) > abs(denominator))
    {

        whole += numerator / denominator;                //Выделение целой части
        numerator = numerator - denominator * whole;

    }

    for (int i = 1; i <= numerator; i++)
    {
        if (denominator % i == 0 && numerator % i == 0)
        {
            numerator = numerator / i;
            denominator = denominator / i;          //Сокращение дроби
            i = 1;
        }
    }
}

void Fraction::Show()
{
    cout << "(" << whole << ") " << numerator << "/" << denominator << endl;
}


