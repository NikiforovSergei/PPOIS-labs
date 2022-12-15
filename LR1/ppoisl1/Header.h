#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class MC 
{
	int deg = 0;
	vector <double> coeff;
public:

	MC();                              
	MC(int n, double* arr);
	MC(vector <double> vect);
	void out();
	int outdeg();
	const double operator() (const double num);
	const double operator[] (const double num);
	const MC operator+= (MC& rv);
	const MC operator-= (MC& rv);
	const MC operator*= (MC& rv);
	const MC operator/= (MC& rv);
	const MC operator=(const MC& rv);
	MC operator +(const MC& c1);
	MC operator -(const MC& c1);
	MC operator *(const MC& rv);
	MC operator /(const MC& c1);

};