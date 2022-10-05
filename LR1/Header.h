#pragma once
using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;
    int whole = 0;
    double number;
public:
    ///<summary>
    /// Display a fraction
    ///<summary>
    void Show();
    ///<summary>
    /// Add a fraction
    ///<summary>
    void Add();
    ///<summary>
    /// Reduce fraction
    ///<summary>
    void Short();
    ///<summary>
    /// Without an integer, only numerator
    ///<summary>
    void Long();
    ///<summary>
    /// To get a numerator
    ///<summary>
    int GetNumerator();
    ///<summary>
    /// To get a denominator
    ///<summary>
    int GetDenominator();
    ///<summary>
    /// To get a whole
    ///<summary>
    int GetWhole();
    ///<summary>
    /// Output a numerator
    ///<summary
    void SetNumerator(int a);
    ///<summary>
    /// Output a denominator
    ///<summary>
    void SetDenominator(int a);
    ///<summary>
    /// Output a whole
    ///<summary>
    void SetWhole(int a);
};