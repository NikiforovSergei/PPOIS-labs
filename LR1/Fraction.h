/*!
\file
\brief Заголовочный файл с описанием класса

Данный файл содержит в себе определение класса натуральных дробей со знаком
*/
#ifndef FRACTION_H
#define FRACTION_H
/*!
	\brief Класс натуральной дроби со знаком

	\param numeration Числитель дроби. Если дробь отрицательная, то числитель  должен быть отрицательным.
	\param denominator Знаменатель дроби.
	\param integer Целая часть дроби.
	\warning denominator не может быть отрицательным или нулем. integer не может быть отрицательным. При введении дроби при нарушении 
	условий дробь будет исправлена.

	Число 0 представлено так:
	\code
		numeration = 0;
		denominator = n;
		integer = 0;
	\endcode
	где n - любое целое число.
*/
class Fraction
{

private:
	int numeration;
	int denominator;
	int integer;

	Fraction WithoutInt();
	void WithoutInt(int n);
	int GetGCD(int a, int b);
	void NormalForm();
	void Simplify();
	void MinusDenominator();
	void MinusInteger();
	int compareTo(const Fraction& other);
	int compareTo(const int& other);
	
public:
	
	Fraction();
	Fraction(int numeration, int denominator, int integer);
	Fraction(const Fraction& other);

	void SetNumeration(int numeration);
	void SetDenominator(int denominator);
	void SetInteger(int integer);

	int GetNumeration();
	int GetDenominator();
	int GetInteger();

	Fraction operator +(const Fraction& other);
	Fraction operator -(const Fraction& other);
	Fraction& operator +=(const Fraction& other);
	Fraction& operator -=(const Fraction& other);
	Fraction operator *(const Fraction& other);
	Fraction& operator *=(const Fraction& other);
	Fraction operator /(const Fraction& other);
	Fraction& operator /=(const Fraction& other);
	Fraction operator +(const int& other);
	Fraction operator -(const int& other);
	Fraction& operator +=(const int& other);
	Fraction& operator -=(const int& other);
	Fraction operator *(const int& other);
	Fraction& operator *=(const int& other);
	Fraction operator /(const int& other);
	Fraction& operator /=(const int& other);
	Fraction& operator ++();
	Fraction& operator ++(int other);
	Fraction& operator --();
	Fraction& operator --(int other);
	bool operator <(const Fraction& other);
	bool operator <=(const Fraction& other);
	bool operator >(const Fraction& other);
	bool operator >=(const Fraction& other);
	bool operator ==(const Fraction& other);
	bool operator !=(const Fraction& other);
	bool operator <(const int& other);
	bool operator <=(const int& other);
	bool operator >(const int& other);
	bool operator >=(const int& other);
	bool operator ==(const int& other);
	bool operator !=(const int& other);

	double ToDouble();

};
#endif //FRACTION_H