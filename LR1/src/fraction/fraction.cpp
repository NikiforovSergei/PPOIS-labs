#include "include/fraction/fraction.hpp"
#include "utils/fraction/fraction_utils.cpp"

Fraction::Fraction(int numerator, int denominator) {
  if (!__validate_data(numerator, denominator)) {
    throw std::invalid_argument("check inputed data");
  }
  this->numerator = numerator;
  this->denominator = denominator;

  __reduce_fraction(this->numerator, this->denominator);
}

// getters
int Fraction::get_numerator() { return numerator; }
int Fraction::get_denominator() { return denominator; }
int Fraction::get_integer_part() { return numerator / denominator; }

// cast
double Fraction::to_double() const { return (double)numerator / (double)denominator; }

// private operations
Fraction Fraction::__division_of_fractions(const Fraction& other_fraction) {
  Fraction result(this->numerator * other_fraction.denominator, this->denominator * other_fraction.numerator);
  __reduce_fraction(result.numerator, result.denominator);

  return result;
}

Fraction Fraction::__multiplication_of_fractions(const Fraction& other_fraction) {
	Fraction result(this->numerator * other_fraction.numerator, this->denominator * other_fraction.denominator);
	__reduce_fraction(result.numerator, result.denominator);

	return result;
}

Fraction Fraction::__sum_of_fractions(Fraction other_fraction) {
	__to_common_denominator(other_fraction);


  Fraction result(this->numerator + other_fraction.numerator, this->denominator);
	__reduce_fraction(result.numerator, result.denominator);

	return result;
}

// operator overloading
Fraction Fraction::operator+(Fraction& other_fraction) { return __sum_of_fractions(other_fraction); }
Fraction Fraction::operator+(const int other_int) { return __sum_of_fractions(Fraction(other_int, 1)); }
Fraction& Fraction::operator+=(Fraction& other_fraction) { return *this = *this + other_fraction; }
Fraction& Fraction::operator+=(const int other_int) { return *this = *this + other_int; }

Fraction Fraction::operator-(Fraction& other_fraction) { return __sum_of_fractions(other_fraction * -1); }
Fraction Fraction::operator-(const int other_int) { return __sum_of_fractions(Fraction(other_int, 1) * -1); }
Fraction& Fraction::operator-=(Fraction& other_fraction) { return *this = *this - other_fraction; }
Fraction& Fraction::operator-=(const int other_int) { return *this = *this - other_int; }

Fraction Fraction::operator*(Fraction& other_fraction) { return __multiplication_of_fractions(other_fraction); }
Fraction Fraction::operator*(const int other_int) { return __multiplication_of_fractions(Fraction(other_int, 1)); }
Fraction& Fraction::operator*=(Fraction& other_fraction) { return *this = *this * other_fraction; }
Fraction& Fraction::operator*=(const int other_int) { return *this = *this * other_int; }

Fraction Fraction::operator/(Fraction& other_fraction) { return __division_of_fractions(other_fraction); }
Fraction Fraction::operator/(const int other_int) { return __division_of_fractions(Fraction(other_int, 1));}
Fraction& Fraction::operator/=(Fraction& other_fraction) { return *this = *this / other_fraction; }
Fraction& Fraction::operator/=(const int other_int) { return *this = *this / other_int; }

bool Fraction::operator==(const Fraction& other_fraction) const { return (this->numerator == other_fraction.numerator && this->denominator == other_fraction.denominator); } 
bool Fraction::operator>(const Fraction& other_fraction) const { return this->to_double() > other_fraction.to_double(); }
bool Fraction::operator<(const Fraction& other_fraction) const { return this->to_double() < other_fraction.to_double(); }
bool Fraction::operator>=(const Fraction& other_fraction) const { return this->to_double() >= other_fraction.to_double(); }
bool Fraction::operator<=(const Fraction& other_fraction) const { return this->to_double() <= other_fraction.to_double(); }
bool Fraction::operator==(int other_int) const { return false; }
bool Fraction::operator>(int other_int) const { return this->to_double() > double(other_int); }
bool Fraction::operator<(int other_int) const { return this->to_double() < double(other_int); }
bool Fraction::operator>=(int other_int) const { return this->to_double() >= double(other_int); }
bool Fraction::operator<=(int other_int) const { return this->to_double() <= double(other_int); }

