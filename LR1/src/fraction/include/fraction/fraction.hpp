#pragma once

#ifndef LAB1_HPP
#define LAB1_HPP

#include <stdexcept>
#include <memory>


// !Fraction class
/*
 * Implementation of a fraction
 */
class Fraction {
private:
	// numerator
	int numerator;
	// denominator
	int denominator;

	// !Utils functions
	/*
	 *	Utils for operator overloading
	 */	
  Fraction __division_of_fractions(const Fraction& other_fraction);
	Fraction __multiplication_of_fractions(const Fraction& other_fraction);
	Fraction __sum_of_fractions(Fraction other_fraction);
	
  void __reduce_fraction(int& numerator, int& denominator);

	// !Utils	
  void __to_common_denominator(Fraction& other_fraction);
	int __get_gcd(int first_number, int second_number);
  int __get_lcm(int first_number, int second_number);
	
  bool __validate_data(int& numerator, int& denominator);
public:
	// Base constructor
	Fraction(int numerator, int denominator);

	// !Getters	
  int get_numerator();
	int get_denominator();
	int get_integer_part();
	double to_double() const;
	
  Fraction operator + (Fraction& other_fraction);
	Fraction operator + (const int other_int);
	Fraction& operator += (Fraction& other_fraction);
	Fraction& operator += (const int other_int);
	Fraction operator - (Fraction& other_fraction);
	Fraction operator - (const int other_int);
	Fraction& operator -= (Fraction& other_fraction);
	Fraction& operator -= (const int other_int);
	Fraction operator * (Fraction& other_fraction);
	Fraction operator * (const int other_int);
	Fraction& operator *= (Fraction& other_fraction);
	Fraction& operator *= (const int other_int);
	Fraction operator / (Fraction& other_fraction);
	Fraction operator / (const int other_int);
	Fraction& operator /= (Fraction& other_fraction);
	Fraction& operator /= (const int other_int);
	
  bool operator == (const Fraction& other_fraction) const;
	bool operator == (int other_int) const;
	bool operator > (const Fraction& other_fraction) const;
	bool operator < (const Fraction& other_fraction) const;
	bool operator >= (const Fraction& other_fraction) const;
	bool operator <= (const Fraction& other_fraction) const;
	bool operator > (int other_int) const;
	bool operator < (int other_int) const;
	bool operator >= (int other_int) const;
  bool operator <= (int other_int) const;
};

#endif
