#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Header.h"

/**
* @brief Defoult constructor without parameters
*/
MC::MC() = default;

/**
* @brief Defoult constructor with parameters
* @param[in] i Deegre of Polynom
* @param[in]  arr Array of all coefficients of Polynom
*/
MC::MC(int n, double* arr)                             
{
    deg = n;
    for (int i = 0; i <= deg; i++)
    {
        double num = arr[i];
        coeff.push_back(num);
    }
}        

/**
* @brief Defoult constructor with parameters
* @param[in]  vect Vector of all coefficients of Polynom
*/
MC::MC(vector <double> vect)                                          
{
    for (int i = 0; i < vect.size(); i++)
    {
        coeff.push_back(vect[i]);
    }
    deg = vect.size() - 1;
}


/**
* @brief Return degee and coefficients into console
*/
void MC::out()
{
    cout << this->deg << " | ";
    for (int i = 0; i <= deg; i++)
    {
        cout << this->coeff[i] << " ";
    }
    cout << endl;
}

/**
* @brief Return plynom's degree
* @return degree
*/
int MC::outdeg()
{
    return (this->deg);
}

/**
* @brief calculate polynom whith num
* @param[in]  num Inputed x
* overload of () operator
* @return buff Output number 
*/
const double MC::operator() (const double num)
{
    double buff = 0;
    for (int i = 0; i < deg + 1; i++)
    {
        buff = buff + (coeff[i] * pow(num, i));
    }

    return buff;
}
/**
* @brief return polynom's coefficient by using it's number
* @param[in]  num Inputed number of coefficient
* overload of [] operator
* @return coeff[num] Output element of vector of coefficients
*/
const double MC::operator[] (const double num)
{
    if (num > this->deg) { return 0; }
    return(coeff[num]);
}
/**
* @brief caculate sum of two polynom's
* @param[in]  rv Input of second polynom
* overload of += operator
* @return *this Output this plolynom (sum of this polynom and another polynom)
*/
const MC MC::operator+= (MC& rv)
{
    if(this->deg >= rv.deg)
    {
        for (int i = 0; i < rv.deg + 1; i++)
        {
            this->coeff[i] = this->coeff[i] + rv.coeff[i];
        }
    }
    else
    {
        for (int i = 0; i <= rv.deg; i++)
        {
            if( i <= this->deg )
            {
                this->coeff[i] = this->coeff[i] + rv.coeff[i];
            }
            else
            {
                this->coeff.push_back(rv.coeff[i]);
            }
        }
        this->deg = rv.deg;
    }

    return(*this);
}
/**
* @brief caculate dif of two polynom's
* @param[in]  rv Input of second polynom
* overload of -= operator
* @return *this Output this plolynom (dif of this polynom and another polynom)
*/
const MC MC::operator-= (MC& rv)
{
    if (this->deg >= rv.deg)
    {
        for (int i = 0; i < rv.deg + 1; i++)
        {
            this->coeff[i] = this->coeff[i] - rv.coeff[i];
        }
    }
    else
    {
        for (int i = 0; i <= rv.deg; i++)
        {
            if (i <= this->deg)
            {
                this->coeff[i] = this->coeff[i] - rv.coeff[i];
            }
            else
            {
                this->coeff.push_back(rv.coeff[i]*(-1.0));
            }
        }
        this->deg = rv.deg;
    }

    return(*this);
}
/**
* @brief caculate prod of two polynom's
* @param[in]  rv Input of second polynom
* overload of *= operator
* @return *this Output this plolynom (prod of this polynom and another polynom)
*/
const MC MC::operator*= (MC& rv)
{
    if (this->deg >= rv.deg)
    {
        vector <double> buff;
        for (int i = 0; i < rv.deg + 1; i++)
        {
            for (int j = 0; j < this->deg + 1; j++)
            {
                buff.resize(this->deg + rv.deg + 1);
                
                    buff[j + i] = this->coeff[j] * rv.coeff[i];
                
            }
        }
        this->coeff = buff;
        this->deg = buff.size() - 1;
    }
    else
    {
        vector <double> buff;
        for (int i = 0; i < this->deg + 1; i++)
        {
            for (int j = 0; j < rv.deg + 1; j++)
            {
                buff.resize(this->deg + rv.deg + 1);

                buff[j + i] = this->coeff[i] * rv.coeff[j];

            }
        }
        this->coeff = buff;
        this->deg = buff.size() - 1;
    }

    return(*this);
}
/**
* @brief caculate div of two polynom's
* @param[in]  rv Input of second polynom
* overload of /= operator
* @return *this Output this plolynom (div of this polynom and another polynom)
*/
const MC MC::operator/= (MC& rv)
{
    if (this->deg >= rv.deg)
    {
        for (int i = 0; i < rv.deg + 1; i++)
        {
            this->coeff[i] = this->coeff[i] / rv.coeff[i];
        }
    }
    else
    {
        for (int i = 0; i <= rv.deg; i++)
        {
            if (i <= this->deg)
            {
                this->coeff[i] = this->coeff[i] / rv.coeff[i];
            }
        }
    }

    return(*this);
}
/**
* @brief assignment another polynom to this polynom
* @param[in]  rv Input of second polynom
* overload of = operator
* @return *this Output this modefied plolynom
*/
const MC MC::operator=( const MC& rv)
{
    if (this == &rv) {          
        return *this;
    }

    if (this->deg > rv.deg)
    {
        for (int i = 0; i <= this->deg; i++)
        {
            if (i <= rv.deg) 
            {
            this->coeff[i] = rv.coeff[i];
            }
            else { this->coeff.pop_back(); }
        }
        this->deg = rv.deg;
    }
    else
    {
        if (this->deg > 0)
        {
            for (int i = 0; i < rv.deg + 1; i++)
            {
                if (i < this->deg + 1)
                {
                    this->coeff[i] = rv.coeff[i];
                }
                else
                {
                    this->coeff.push_back(rv.coeff[i]);
                }
            }
            this->deg = rv.deg;
        }
        else
        {
            for (int i = 0; i < rv.deg + 1; i++)
            {
                this->coeff.push_back(rv.coeff[i]);
            }
            this->deg = rv.deg;
        }

    }
    return *this;

}
/**
* @brief  caculate sum of two polynom's
* @param[in]  c1 Input of second polynom
* overload of + operator
* @return tmp Output temporery plolynom (polynom's sum)
*/
MC MC::operator +(const MC& c1)
{
    MC tmp;
    if (c1.deg >= this->deg)
    {
        tmp.deg = c1.deg;

        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= this->deg)
            {
                tmp.coeff.push_back(c1.coeff[i] + this->coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(c1.coeff[i]);
            }
        }
    }
    else
    {
        tmp.deg = this->deg;
        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= c1.deg)
            {
                tmp.coeff.push_back(c1.coeff[i] + this->coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(this->coeff[i]);
            }
        }
    }
    return tmp;
}

/**
* @brief  caculate dif of two polynom's
* @param[in]  c1 Input of second polynom
* overload of - operator
* @return tmp Output temporery plolynom (polynom's dif)
*/
MC MC::operator -(const MC& c1)
{
    MC tmp;
    if (c1.deg >= this->deg)
    {
        tmp.deg = c1.deg;
        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= this->deg)
            {
                tmp.coeff.push_back(this->coeff[i] - c1.coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(c1.coeff[i] * (-1.0));
            }
        }
    }
    else
    {
        tmp.deg = this->deg;
        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= c1.deg)
            {
                tmp.coeff.push_back(this->coeff[i] - c1.coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(this->coeff[i]);
            }
        }
    }
    return tmp;
}
/**
* @brief  caculate prod of two polynom's
* @param[in]  rv Input of second polynom
* overload of * operator
* @return tmp Output temporery plolynom (polynom's prod)
*/
MC MC::operator *(const MC& rv)
{ 
    MC buff;
    if (this->deg >= rv.deg)
    {
        
        for (int i = 0; i < rv.deg + 1; i++)
        {
            for (int j = 0; j < this->deg + 1; j++)
            {
                buff.coeff.resize(this->deg + rv.deg + 1);

                buff.coeff[j + i] = this->coeff[j] * rv.coeff[i];

            }
        }
    }
    else
    {
        
        for (int i = 0; i < this->deg + 1; i++)
        {
            for (int j = 0; j < rv.deg + 1; j++)
            {
                buff.coeff.resize(this->deg + rv.deg + 1);

                buff.coeff[j + i] = this->coeff[i] * rv.coeff[j];

            }
        }
    }
    buff.deg = buff.coeff.size() - 1;
    return(buff);
}

/**
* @brief  caculate div of two polynom's
* @param[in]  c1 Input of second polynom
* overload of / operator
* @return tmp Output temporery plolynom (polynom's div)
*/
MC MC::operator /(const MC& c1)
{
    MC tmp;
    if (c1.deg >= this->deg)
    {
        tmp.deg = c1.deg;

        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= this->deg)
            {
                tmp.coeff.push_back(this->coeff[i] / c1.coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(1.0 / c1.coeff[i]);
            }
        }
    }
    else
    {
        tmp.deg = this->deg;
        for (int i = 0; i <= tmp.deg; i++)
        {
            if (i <= c1.deg)
            {
                tmp.coeff.push_back(this->coeff[i] / c1.coeff[i]);
            }
            else
            {
                tmp.coeff.push_back(this->coeff[i]);
            }
        }
    }
    return tmp;
}