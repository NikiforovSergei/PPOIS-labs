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

    if (a.GetDenominator() == b.GetDenominator())
    {
        c.SetWhole(0);
        c.SetNumerator (a.GetNumerator() - b.GetNumerator());        //вычитаем числитель, если знаминатели одинаковы
        c.SetDenominator(a.GetDenominator());
    }
    else
    {
        int t;
        c.SetDenominator(a.GetDenominator ()* b.GetDenominator());
        t = c.GetDenominator() / a.GetDenominator();
        a.SetNumerator(t * a.GetNumerator());
        t = c.GetDenominator() / b.GetDenominator();                   //приводим к общему знаменателю и вычитаем   
        b.SetNumerator ( t * b.GetNumerator());
        c.SetNumerator ( a.GetNumerator() - b.GetNumerator());
    }
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

    c.SetNumerator ( a.GetNumerator() * b.GetNumerator());
    c.SetDenominator( a.GetDenominator ()* b.GetDenominator());

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
    
    bb = b.GetNumerator();
    b.SetNumerator ( b.GetDenominator());
    b.SetDenominator( bb);

    c.SetNumerator ( a.GetNumerator ()* b.GetNumerator());
    c.SetDenominator ( a.GetDenominator() * b.GetDenominator());

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
        a.Show();
        a.SetWhole(a.GetWhole()+1);
        a.Show();
    }
    else
    {
        a.Show();
        a.Long();
        a.Show();
        a.SetNumerator(a.GetNumerator()-a.GetDenominator());
        a.Short();
        a.Show();
    }
}

void Comparison(Fraction a, Fraction b)
{
    a.Show();
    b.Show();
    a.Long();
    b.Long();
    a.Show();
    b.Show();

    if (a.GetNumerator() == b.GetNumerator())
    {
        a.Short();
        b.Short();
        cout << "(" << a.GetWhole ()<< ") " << a.GetNumerator ()<< "/" << a.GetDenominator ()<<" = " << "(" << b.GetWhole ()<< ") " << b.GetNumerator ()<< "/" << b.GetDenominator();
    }
    if (a.GetNumerator ()> b.GetNumerator())
    {
        a.Short();
        b.Short();
        cout << "(" << a.GetWhole ()<< ") " << a.GetNumerator ()<< "/" << a.GetDenominator ()<< " > " << "(" << b.GetWhole ()<< ") " << b.GetNumerator ()<< "/" << b.GetDenominator();
    }if (a.GetNumerator ()< b.GetNumerator())
    {
        a.Short();
        b.Short();
        cout << "(" << a.GetWhole ()<< ") " << a.GetNumerator ()<< "/" << a.GetDenominator ()<< " < " << "(" << b.GetWhole ()<< ") " << b.GetNumerator ()<< "/" << b.GetDenominator();
    }
}

int main()
{
    int ch;
    Fraction a, b;
    cout << "0--to Exit" << "\t1--to Add Up" << "\t2--to Substract" << "\t3--to Multiply" << "\t4--to Divide\n" << "5--to Increment/Decrement" << "\t6--to Compare"<< "\t7--to Double\n";
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
        

            
    


