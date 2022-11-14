#include "polynomial.h"

Polynomial::Polynomial(int power)
{
    this->f = new double[power + 1];
    this->power = power;
    for (int i = 0; i <= power; i++)
    {
        this->f[i] = 0;
    }
}

void Polynomial::set(int index, double num)
{
    this->f[this->power - index] = num;
}

void Polynomial::print()
{
    for (int i = power; i > -1; i--)
    {
        if (this->f[i] != 0)
        {
            if (this->f[i] > 0 && i != power)
                cout << "+";
            cout << this->f[i];
            if (i != 0)
                cout << "x";
            if (i != 0 && i != 1)
                cout << "^" << i;
        }
    }
    cout << endl;
}

Polynomial Polynomial::operator +(const Polynomial& other)
{
    int n;
    if (this->power > other.power)
        n = this->power;
    else
        n = other.power;
    Polynomial a(n);
    a.copy(*this);
    Polynomial b(n);
    b.copy(other);
    Polynomial temp(n);

    for (int i = 0; i <= n; i++)
    {
        temp.f[i] = a.f[i] + b.f[i];
    }
    return temp;
}

Polynomial& Polynomial::operator +=(const Polynomial& other)
{
    *this = *this + other;
    return *this;
}

Polynomial Polynomial::operator -(const Polynomial& other)
{
    int n;
    if (this->power > other.power)
        n = this->power;
    else
        n = other.power;
    Polynomial a(n);
    a.copy(*this);
    Polynomial b(n);
    b.copy(other);
    Polynomial temp(n);

    for (int i = 0; i <= n; i++)
    {
        temp.f[i] = a.f[i] - b.f[i];
    }
    return temp;
}

Polynomial& Polynomial::operator -=(const Polynomial& other)
{
    *this = *this - other;
    return *this;
}

Polynomial Polynomial::operator *(const Polynomial& other)
{
    int i, j, k;
    int n = this->power + other.power;
    Polynomial temp(n);
    for (k = 0; k <= n; k++)
    {
        for (i = 0; i <= this->power; i++)
        {
            for (j = 0; j <= other.power; j++)
            {
                if (i + j == k)
                    temp.f[k] += this->f[i] * other.f[j];
            }
        }
    }
    return temp;
}

Polynomial& Polynomial::operator *=(const Polynomial& other)
{
    *this = *this * other;
    return *this;
}

Polynomial Polynomial::operator /(const Polynomial& other)
{
    if (this->power < other.power)
    {
        cout << "difficult to calculate, because the answer will always be |equal| <= 1" << endl;
        Polynomial temp(0);
        return temp;
    }
    else
    {
        Polynomial a(this->power);
        a.copy(*this);
        int x = a.power;
        int y = other.power;
        int m = this->power - other.power;
        Polynomial temp(m);
        while (m > -1)
        {
            temp.f[m] = a.f[x] / other.f[y];
            for (int k = 0; k <= y; k++)
            {
                a.f[x - k] = a.f[x - k] - other.f[y - k] * temp.f[m];
            }
            m--;
            x--;
        }
        if (!a.Zero()) /*if a false, means != 0*/
        {
            cout << "numerator: ";
            a.print();
        }
        return temp;
    }
}

Polynomial& Polynomial::operator /=(const Polynomial& other)
{
    if (this->power < other.power)
    {
        Polynomial temp(-1);
        *this = temp;
        return temp;
    }
    else
    {
        Polynomial a = *this;
        int x = a.power;
        int y = other.power;
        int m = this->power - other.power;
        Polynomial temp(m);
        while (m > -1)
        {
            temp.f[m] = a.f[x] / other.f[y];
            for (int k = 0; k <= y; k++)
            {
                a.f[x - k] = a.f[x - k] - other.f[y - k] * temp.f[m];
            }
            m--;
            x--;
        }
        *this = temp;
        return *this;
    }
}

Polynomial& Polynomial::operator =(const Polynomial& other)
{
    this->power = other.power;

    if (this->f != nullptr)
    {
        delete this->f;
    }

    this->f = new double[other.power + 1];

    for (int i = 0; i <= other.power; i++)
    {
        this->f[i] = other.f[i];
    }
    return *this;
}

double Polynomial::operator()(double x)
{
    double sum = 0;
    for (int i = 0; i <= this->power; i++)
    {
        sum += this->f[i] * pow(x, i);
    }
    return sum;
}

double Polynomial::operator[](int index)
{
    return this->f[index];
}



Polynomial Polynomial::copy(const Polynomial& other)
{
    for (int i = 0; i <= other.power; i++)
    {
        this->f[i] = other.f[i];
    }
    return *this;
}

bool Polynomial::Zero()
{
    bool t = true;
    for (int i = 0; i <= power; i++)
    {
        if (this->f[i] != 0)
            t = false;
    }
    return t;
}
