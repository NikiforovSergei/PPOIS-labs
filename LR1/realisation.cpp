/*!\file 
* This file stores the realisation of Natural class.
*/
#include "header.h"
Natural::Natural()
{
	num = 1;
	denom = 1;
}
Natural::Natural(int i)
{
	if (i == 0)
		/*! \throws Throws the exception if int i equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	num = i;
	denom = 1;
}
Natural::Natural(int i, int n, int d)
{
	if (n == 0)
		/*! \throws Throws the exception if int n equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	if (d == 0)
		/*! \throws Throws the exception if int d equals 0. Otherwise division by 0.*/
		throw "Division by zero.\n";
	num = fabs(i) * d + fabs(n); if (i < 0) num = -num; if (n < 0) num = -num;  
	denom = d;
	reduce();
}
Natural::Natural(int n, int d)
{
	if (n == 0)
		/*! \throws Throws the exception if int i equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	if (d == 0)
		/*! \throws Throws the exception if int d equals 0. Otherwise division by 0.*/
		throw "Division by zero.\n";
	num = n; if (n < 0) num = -num;
	denom = d;
	reduce();
}

Natural::~Natural() {};

Natural::Natural(const Natural& x) {
	num = x.num;
	denom = x.denom;
}
/*! Finds NOD to be able to reduce fraction in further calculations 
* \param x, y numerator and denominator of the fraction
* \return NOD 
*/
int Natural::NOD(int x, int y)
{
	x = fabs(x);
	while (y)
	{
		int temp = y;
		y = x % y;
		x = temp;
	}
	return x;
}
/*! Reduces a fraction*/
void Natural::reduce()
{
	int del = NOD(num, denom);
	num /= del;
	denom /= del;
}
/*! Makes fraction upside-down in the operation of division
*\return reversed fraction
*/
Natural& Natural::reversal()
{
	Natural t;
	t.denom = fabs(num);
	t.num = denom;
	if (num < 0) t.num = -t.num;
	return t;
}
/*! 
* \return integer part of the fraction */
const int Natural::getInt()
{
	return num / denom;
}
/*!
\return the numerator of the fraction*/
const int Natural::getNum()
{
	return num;
}
/*! \return the denominator of the fraction*/
const int Natural::getDenom()
{
	return denom;
}
/*! \return natural fraction into double*/
double Natural::ntod()
{
	double n = num, d = denom;
	return n / d;
}

/*! \brief Equality operator 
* Compares 2 natural fractions. 
* \return if fractions are equal returns 1
* \return if fractions aren't equal returns 0
*/
bool operator ==(Natural& x, Natural& y)
{
	return ((x.num == y.num) & (x.denom == y.denom)) ? 1 : 0;
}
/*!  \brief Inequality operator 
* Compares 2 natural fractions.
* \return if fractions aren't equal returns 1
* \return if fractions are equal returns 0
*/
bool operator !=(Natural& x, Natural& y)
{
	return ((x.num != y.num) || (x.denom != y.denom)) ? 1 : 0;
}
/*!  \brief Output operator
* Sends fraction into output stream
* \param os takes output stream
* \param x takes a fraction
* \return output stream
*/
ostream& operator <<(ostream& os, Natural& x)
{
	return os << x.num << "/" << x.denom;
}
/*!  \brief Input operator
* Takes fraction from input stream
* \param is takes input stream
* \param x takes a fraction
* \return a natural fraction
*/
istream& operator >>(istream& is, Natural& x)
{
	if (!is)
		throw "Zero is not natural.\n";
	return is >> x.num >> x.denom;
}
/*!  \brief Addition operator
* Add 2 fractions
* \param x,y natural fractions
* \return another natural fraction - the result of addition
*/
Natural operator +(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.getNum() * y.getDenom() + x.getDenom() * y.getNum();
	t.denom = x.getDenom() * y.getDenom();
	t.reduce();
	return t;
};
/*!  \brief Addition operator
* Add a fraction to another fraction and stores the result in x
* \param x,y natural fractions
*/
void operator +=(Natural& x, Natural& y)
{
	x = operator +(x, y);
};
/*!  \brief Addition operator
* Add a fraction to integer
* \param x,y int, natural fraction
* \return another natural fraction - the result of addition
*/
Natural operator +(int x, Natural& y)
{
	Natural t(x);
	return operator+(t, y);
}
/*!  \brief Addition operator
* Add an integer to natural fraction
* \param x,y natural fraction, int
* \return another natural fraction - the result of addition
*/
Natural operator +(Natural& y, int x) {
	return operator+(x, y);
}
/*!  \brief Addition operator
* Add an integer to a fraction and stores the result in x
* \param x,y natural fraction, int
*/
void operator +=(Natural& x, int y) {
	x = operator+(x, y);
}
/*!  \brief Difference operator
* Calculates the difference of 2 fractions
* \param x,y natural fractions
* \return another natural fraction - the result of difference
*/
Natural operator -(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.getNum() * y.getDenom() - x.getDenom() * y.getNum();
	t.denom = x.getDenom() * y.getDenom();
	t.reduce();
	return t;
}
/*!  \brief Difference operator
* Calculates the difference of 2 fractions and stores the result in x
* \param x,y natural fractions
*/
void operator -=(Natural& x, Natural& y)
{
	x = operator -(x, y);
}
/*!  \brief Difference operator
* Calculates the difference of a fraction and an integer
* \param x,y natural fraction, int
* \return another natural fraction - the result of difference
*/
Natural operator -(Natural& y, int x)
{
	Natural t(x);
	return operator-(y, t);
}
/*!  \brief Difference operator
* Calculates the difference of a fraction and an integer and stores the result in x
* \param x,y natural fraction, int
*/
void operator -=(Natural& y, int x)
{
	y = operator-(y, x);
}
/*!  \brief Multiplication operator
* Calculates the multiplication of 2 fractions
* \param x,y natural fractions
* \return another natural fraction - the result of multiplication
*/
Natural operator *(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.num * y.num;
	t.denom = x.denom * y.denom;
	t.reduce();
	return t;
}
/*!  \brief Multiplication operator
* Calculates the multiplication of 2 fractions and stores the result in x
* \param x,y natural fractions
*/
void operator *=(Natural& x, Natural& y)
{
	x = operator*(x, y);
}
/*!  \brief Multiplication operator
* Calculates the multiplication of an integer and a fraction
* \param x,y int, natural fraction
* \return another natural fraction - the result of multiplication
*/
Natural operator *(int x, Natural& y)
{
	Natural t(x * y.num, y.denom);
	t.reduce();
	return t;
}
/*!  \brief Multiplication operator
* Calculates the multiplication of a fraction and an integer 
* \param y,x natural fraction, int
* \return another natural fraction - the result of multiplication
*/
Natural operator *(Natural& y, int x)
{
	return operator*(x, y);
}
/*!  \brief Multiplication operator
* Calculates the multiplication of a fraction and an integer and stores the result in y
* \param y,x natural fraction, int
*/
void operator *=(Natural& y, int x)
{
	y = operator*(y, x);
}
/*!  \brief Division operator
* Calculates the division of 2 fractions with the help of multiplication of x fraction and reversed y fraction.
* \param x,y natural fractions
* \return another natural fraction - the result of division
*/
Natural operator /(Natural& x, Natural& y)
{
	Natural t = y.reversal();
	return operator*(x, t);
}
/*!  \brief Division operator
* Calculates the division of 2 fractions and stores the result in x
* \param x,y natural fractions
*/
void operator /=(Natural& x, Natural& y)
{
	x = operator /(x, y);
}
/*!  \brief Division operator
* Calculates the division of a fraction and an integer
* \param x,y int, natural fraction
* \return another natural fraction - the result of division
*/
Natural operator /(Natural& y, int x)
{
	if (!x)
		throw "Division by zero.\n";
	Natural t(y.num, y.denom * x);
	t.reduce();
	return t;
}
/*!  \brief Division operator
* Calculates the division of a fraction and an integer and stores the result in y
* \param y,x natural fraction, int
*/
void operator /=(Natural& y, int x)
{
	y = operator /(y, x);
}
/*!  \brief Post-Increment operator
* Increments a fraction by 1 
* \param x natural fraction
* \return a fraction before addition
*/
Natural operator ++(Natural& x, int)
{
	Natural t = x;
	x += 1;
	return t;
}
/*!  \brief Pre-Increment operator
* Increments a fraction by 1
* \param x natural fraction
*/
void operator ++(Natural& x)
{
	x += 1;
}
/*!  \brief Post-Decrement operator
* Decrements a fraction by 1
* \param x natural fraction
* \return a fraction before difference
*/
Natural operator --(Natural& x, int)
{
	Natural t = x;
	x -= 1;
	return t;
}
/*!  \brief Pre-Decrement operator
* Decrements a fraction by 1
* \param x natural fraction
*/
void operator --(Natural& x)
{
	x -= 1;
}
/*!  \brief Comparison operator
* \param x,y natural fractions
* \return if x > y, returns 1
* \return if x <= y, returns 0
*/
bool operator >(Natural& x, Natural& y)
{
	return ((x - y).num > 0) ? 1 : 0;
}
/*!  \brief Comparison operator
* \param x,y natural fraction, int
* \return if x > y, returns 1
* \return if x <= y, returns 0
*/
bool operator >(Natural& x, int y)
{
	Natural t(y);
	return operator>(x, t);
}
/*!  \brief Comparison operator
* \param x,y natural fractions
* \return if x >= y, returns 1
* \return if x < y, returns 0
*/
bool operator >=(Natural& x, Natural& y)
{
	if (operator>(x, y))
		return 1;
	return (x == y) ? 1 : 0;
}
/*!  \brief Comparison operator
* \param x,y natural fraction, int
* \return if x >= y, returns 1
* \return if x < y, returns 0
*/
bool operator >=(Natural& x, int y)
{
	Natural t(y);
	return operator>=(x, t);
}
/*!  \brief Comparison operator
* \param x,y natural fractions
* \return if x < y, returns 1
* \return if x >= y, returns 0
*/
bool operator <(Natural& x, Natural& y)
{
	return ((x - y).num < 0) ? 1 : 0;
}
/*!  \brief Comparison operator
* \param x,y natural fraction, int
* \return if x < y, returns 1
* \return if x >= y, returns 0
*/
bool operator <(Natural& x, int y)
{
	Natural t(y);
	return operator<(x, t);
}
/*!  \brief Comparison operator
* \param x,y natural fractions
* \return if x <= y, returns 1
* \return if x > y, returns 0
*/
bool operator <=(Natural& x, Natural& y)
{
	if (operator<(x, y))
		return 1;
	return (x == y) ? 1 : 0;
}
/*!  \brief Comparison operator
* \param x,y natural fraction, int
* \return if x <= y, returns 1
* \return if x > y, returns 0
*/
bool operator <=(Natural& x, int y)
{
	Natural t(y);
	return operator<=(x, t);
}
