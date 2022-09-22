/*! 
* \file 
* This file is a header file for the Natural class.
*/
#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
/*!
* \brief This class is a natural fraction with a sign. 
* 
* The declaration and definition of the class is in the files: header.h and realisation.cpp 
*/

class Natural
{
private:
	/*!\privatesection.*/
	int num; ///< stores the numerator and the sign of the fraction
	unsigned int denom; ///< stores the denominator of the fraction 
	void reduce(); 
	int NOD(int x, int y); 
	Natural& reversal(); 
public:
	Natural();///< a default constructor which creates 1/1 fraction 
	Natural(int i);///< a constructor which takes int and returns i/1 fraction
	Natural(int i, int n, int d);///< a constructor which takes a mixed fraction and stores as natural fraction
	Natural(int n, int d);///< a constructor which takes n/d fraction
	~Natural();///< a destructor
	Natural(const Natural& x);///< a copy constructor 
	const int getInt(); 
	const int getNum();
	const int getDenom();
	double ntod();

	friend bool operator ==(Natural& x, Natural& y);
	friend bool operator !=(Natural& x, Natural& y);
	friend ostream& operator <<(ostream& os, Natural& x);
	friend istream& operator >>(istream& is, Natural& x);

	friend Natural operator +(Natural& x, Natural& y);
	friend void operator += (Natural& x, Natural& y);
	friend Natural operator +(int x, Natural& y);
	friend Natural operator +(Natural& y, int x);
	friend void operator +=(Natural& y, int x);

	friend Natural operator -(Natural& x, Natural& y);
	friend void operator -=(Natural& x, Natural& y);
	friend Natural operator -(Natural& y, int x);
	friend void operator -=(Natural& y, int x);

	friend Natural operator *(Natural& x, Natural& y);
	friend void operator *= (Natural& x, Natural& y);
	friend Natural operator *(int x, Natural& y);
	friend Natural operator *(Natural& y, int x);
	friend void operator *=(Natural& y, int x);

	friend Natural operator /(Natural& x, Natural& y);
	friend void operator /=(Natural& x, Natural& y);
	friend Natural operator /(Natural& y, int x);
	friend void operator /=(Natural& y, int x);

	friend Natural operator ++(Natural& x, int);
	friend void operator ++(Natural& x);
	friend Natural operator --(Natural& x, int);
	friend void operator --(Natural& x);

	friend bool operator >(Natural& x, Natural& y);
	friend bool operator >(Natural& x, int y);
	friend bool operator >=(Natural& x, Natural& y);
	friend bool operator >=(Natural& x, int y);
	friend bool operator <(Natural& x, Natural& y);
	friend bool operator <(Natural& x, int y);
	friend bool operator <=(Natural& x, Natural& y);
	friend bool operator <=(Natural& x, int y);




};
