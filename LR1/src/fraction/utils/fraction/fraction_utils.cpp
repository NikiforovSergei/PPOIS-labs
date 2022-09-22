#include "../../include/fraction/fraction.hpp"


bool Fraction::__validate_data(int& numerator, int& denominator) {
	if (denominator == 0) {
		return false;
	}

	if (numerator > 0 && denominator < 0) {
		numerator = -1 * numerator;
		denominator = abs(denominator);

		return true;
	}

	if (numerator < 0 && denominator < 0) {
		numerator = abs(numerator);
		denominator = abs(denominator);
return true;
	}

	return true;
}

void Fraction::__reduce_fraction(int& numerator, int& denominator) {
  auto gcd = __get_gcd(numerator, denominator);
  if (gcd != 1) {
    numerator /= gcd;
    denominator /= gcd;
  } 
}

int Fraction::__get_gcd(int num_1, int num_2) {
  num_1 = abs(num_1);
  num_2 = abs(num_2);
  
  while (num_1 != 0 && num_2 != 0) {
		if (num_1 > num_2) {
			num_1  %= num_2;
		}
		else {
			num_2 %= num_2;
		}
	}

	return num_1 + num_2;
}

void Fraction::__to_common_denominator(Fraction& other_fraction)
{
	int lcm = __get_lcm(this->denominator, other_fraction.denominator);
	if (lcm / this->denominator != 1) {
		this->numerator *= (lcm / this->denominator);
		this->denominator = lcm;
	}
	if (lcm / other_fraction.denominator != 1) {
		other_fraction.numerator *= (lcm / other_fraction.denominator);
		other_fraction.denominator = lcm;
	}
}

int Fraction::__get_lcm(int first_number, int second_number)
{
	first_number = abs(first_number);
	second_number = abs(second_number);

	return (first_number * second_number) / __get_gcd(first_number, second_number);
}
