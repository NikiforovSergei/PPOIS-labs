#pragma once
#include<iostream>
#include <cmath>
using namespace std;

class Mnogochlen
{
public:
	/// <summary>
	///\brief constructor
	/// </summary>
	/// <param name="power"></param>
	Mnogochlen(int);
	/// <summary>
	///\brief setter for coefficients
	/// </summary>
	/// <param name="index"></param>
	/// <param name="num"></param>
	void set(int, double);
	/// <summary>
	///\brief output of polynomial on screen
	/// </summary>
	void print();
	/// <summary>
	///\brief sum
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen operator +(const Mnogochlen& other);
	/// <summary>
	///\brief adding
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen& operator +=(const Mnogochlen& other);
	/// <summary>
	///\brief substruction
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen operator -(const Mnogochlen& other);
	/// <summary>
	///\brief substraction
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen& operator -=(const Mnogochlen& other);
	/// <summary>
	///\brief multiplication
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen operator *(const Mnogochlen& other);
	/// <summary>
	///\brief multiplication
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen& operator *=(const Mnogochlen& other);
	/// <summary>
	///\brief deviding
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen operator /(const Mnogochlen& other);
	/// <summary>
	///\brief deviding
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen& operator /=(const Mnogochlen& other);
	/// <summary>
	///\brief copy constructor
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen& operator =(const Mnogochlen& other);
	/// <summary>
	///\brief calculation
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	double operator()(double x);
	/// <summary>
	///\brief output of coefficient
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	double operator[](int index);
	/// <summary>
	/// \brief comparing
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator ==(const Mnogochlen& other);
	/// <summary>
	/// \brief comparing
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator !=(const Mnogochlen& other);

private:
	/// <summary>
	///\brief power of polynomial
	/// </summary>
	int power;
	/// <summary>
	///\brief array of coefficients
	/// </summary>
	double* f;
	/// <summary>
	///\brief copying coefficients from one polynomial to another
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Mnogochlen copy(const Mnogochlen& other);
	/// <summary>
	///\brief checking if polynomial equals zero
	/// </summary>
	/// <returns></returns>
	bool Zero();
};