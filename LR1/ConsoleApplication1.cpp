#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <math.h>
#include "Header.h"

using namespace std;

void AddUp(Fraction a, Fraction  b)
{
    
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();
    Fraction  c=a+b;
    
    c.Short();
    c.Show();
}

void Difference(Fraction a, Fraction b)
{
    Fraction  c;
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();

    c = a - b;
    c.Short();
    c.Show();
}

void Multiplication(Fraction a, Fraction b)
{
    Fraction  c;
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();

    c = a * b;
    c.Short();
    c.Show();
}

void Dividing(Fraction a, Fraction b)
{
    Fraction  c;
    int bb;
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();
    
    c = a / b;

    c.Short();
    c.Show();
}

void IncrementDecrement(Fraction a)
{
    int ch;
    cout << "1--to Increment" << "\t2--to Decrement\n";
    cin >> ch;
    if (ch == 1)
    {
        Fraction c;
        a.Show();
        ++a;
        a.Show();
    }
    else
    {
        a.Show();
        a.Long();
        a.Show();
        --a;
        a.Short();
        a.Show();
    }
}

void Comparison(Fraction a, Fraction b)
{
    cout <<  "1-- >" << "\t2-- <" << "\t3-- ==\n";
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();
    int ch;
    cin>>ch;
    switch (ch)
    {
        case 1:
            if (a > b)
            {
                cout << "Yes";
            }
            else
            {
                cout << "No";
            };
        case 2:
            if (a < b)
            {
                cout << "Yes";
            }
            else
            {
                cout << "No";
            };
        case 3:
            if (a == b)
            {
                cout << "Yes";
            }
            else
            {
                cout << "No";
            };
    }
}


int main()
{
    int ch;
    Fraction a, b;
    cout << "0--to Exit" << "\t1--to Add Up" << "\t2--to Substract" << "\t3--to Multiply" << "\t4--to Divide\n" << "5--to Increment/Decrement" << "\t6--to Compare" << "\t7--to Double\n";
    cin >> ch;
    system("cls");
    switch (ch)
    {
    case 0:
        return 0;
    case 1:
        a.Add();
        b.Add();
        a.Short();
        b.Short();

        AddUp(a, b);
    case 2:

        a.Add();
        b.Add();
        a.Short();
        b.Short();

        Difference(a, b);
    case 3:

        a.Add();
        b.Add();
        a.Short();
        b.Short();

        Multiplication(a, b);
    case 4:

        a.Add();
        b.Add();
        a.Short();
        b.Short();

        Dividing(a, b);
    case 5:
        cout << "Enter a fraction\n";
        a.Add();
        a.Short();
        
        IncrementDecrement(a);
    case 6:
        a.Add();
        b.Add();
        a.Short();
        b.Short();

        Comparison(a, b);
    case 7:
        double aa;
        a.Add();
        a.Short();
        a.Long();
        aa = double(a.GetNumerator()) / (a.GetDenominator());
        cout << aa;
    }

}
        

            
    


