/*!
\file
\brief Исходный файл реализацией метдов класса натуральных дробей

Данный файл содержит в себе реализацию методов класса натуральных дробей со знаком
*/

#include "Fraction.h"
#include <iostream>
#include <cmath>
using namespace std;
/*!
	\brief Конструктор дроби по умолчанию
	Конструктор по умолчанию создает следующую дробь:
	\code
	 Fraction::Fraction()
	{
		this->numeration = 1;
		this->denominator = 1;
		this->integer = 0;
	}
	\endcode
	 т.е. число 1.

*/

Fraction::Fraction()
{
	this->numeration = 1;
	this->denominator = 1;
	this->integer = 0;
}

/*!
	\brief Конструктор дроби

	\param numeration	числитель дроби
	\param denominator знаменатель дроби
	\param integer целая часть дроби

	В конце вызывает метод NormalForm.
*/

Fraction::Fraction(int numeration, int denominator, int integer)
{
	this->numeration = numeration;
	this->denominator = denominator;
	this->integer = integer;
	this->NormalForm();
}
/*!
	\brief Конструктор копирования дроби

	\param other копируемая дробь
*/
Fraction::Fraction(const Fraction& other)
{
	this->numeration = other.numeration;
	this->denominator = other.denominator;
	this->integer = other.integer;
}
/*!
	\brief Сеттер числителя

	\param numeration устанавливаемое значение
*/
void Fraction::SetNumeration(int numeration)
{
	this->numeration = numeration;
}
/*!
	\brief Сеттер знаменателя

	\param denominator устанавливаемое значение
*/
void Fraction::SetDenominator(int denominator)
{
	this->denominator = denominator;
}
/*!
	\brief Сеттер целой части

	\param integer устанавливаемое значение
*/
void Fraction::SetInteger(int integer)
{
	this->integer = integer;
}
/*!
	\brief Геттер числителя

	\return значение числителя
*/
int Fraction::GetNumeration()
{
	return this->numeration;
}
/*!
	\brief Геттер знаменателя

	\return значение знаменателя
*/
int Fraction::GetDenominator()
{
	return this->denominator;
}
/*!
	\brief Геттер целой части

	\return значение целой части
*/
int Fraction::GetInteger()
{
	return this->integer;
}
/*! \brief Функция сложения двух натуральных дробей
	\param other второе слогаемое
	\return дробь - результат сложения двух дробей
*/
Fraction Fraction::operator+(const Fraction& other)
{
	Fraction temp_1(this->WithoutInt()), temp_2(other);
	temp_2.WithoutInt(1);
	temp_1.numeration = temp_1.numeration * temp_2.denominator + temp_2.numeration * temp_1.denominator;
	temp_1.denominator *= temp_2.denominator;
	temp_1.NormalForm();
	return temp_1;
}
/*! \brief Функция вычитания двух натуральных дробей
		\param other вычитаемое
		 \return дробь - результат вычитания двух дробей
*/
Fraction Fraction::operator-(const Fraction& other)
{
	Fraction temp_1(this->WithoutInt()), temp_2(other);
	temp_2.WithoutInt(1);
	temp_1.numeration = temp_1.numeration * temp_2.denominator - temp_2.numeration * temp_1.denominator;
	temp_1.denominator *= temp_2.denominator;
	temp_1.NormalForm();
	return temp_1;
}
/*! \brief Функция сложения с присваением дроби
	\param other второе слогаемое
*/
Fraction& Fraction::operator+=(const Fraction& other)
{
	this->WithoutInt(1);
	Fraction temp(other);
	temp.WithoutInt(1);
	this->numeration = this->numeration * temp.denominator + temp.numeration * this->denominator;
	this->denominator *= temp.denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция вычитания с присваением дроби
		\param other вычитаемое
*/
Fraction& Fraction::operator-=(const Fraction& other)
{
	this->WithoutInt(1);
	Fraction temp(other);
	temp.WithoutInt(1);
	this->numeration = this->numeration * temp.denominator - temp.numeration * this->denominator;
	this->denominator *= temp.denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция умножения двух натуральных дробей
		\param other второй множитель
		 \return дробь - результат умножения двух дробей
*/
Fraction Fraction::operator*(const Fraction& other)
{
	Fraction temp_1(this->WithoutInt()), temp_2(other);
	temp_2.WithoutInt(1);
	temp_1.numeration *= temp_2.numeration;
	temp_1.denominator *= temp_2.denominator;
	temp_1.NormalForm();
	return temp_1;
}
/*! \brief Функция умножения с присваением дроби
		\param other второй множитель
*/
Fraction& Fraction::operator*=(const Fraction& other)
{
	this->WithoutInt(1);
	Fraction temp(other);
	temp.WithoutInt(1);
	this->numeration *= temp.numeration;
	this->denominator *= temp.denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция деления двух натуральных дробей
	\param other делитель
	\return дробь - результат деления двух дробей
	\warning при делении на 0 возвращает исходную дробь
*/
Fraction Fraction::operator/(const Fraction& other)
{
	if (other.numeration == 0)
	{
		cout << "ERROR:DENOMINATOR IS ZERO" << endl;
		return *this;
	}
	Fraction temp_1(this->WithoutInt()), temp_2(other);
	temp_2 = temp_2.WithoutInt();
	temp_1.numeration *= temp_2.denominator;
	temp_1.denominator *= temp_2.numeration;
	temp_1.NormalForm();
	return temp_1;
}
/*! \brief Функция проверки целой части

	Функция проверяет, отрицательна ли целая часть, если да, то меняет ее знак. Применяется для внутренних операций.
*/
void Fraction::MinusInteger()
{
	if (this->integer<0)
	{
		this->integer *= -1;
	}
}
/*! \brief Функция деления с присваением дроби
	\param other делитель
	\warning при делении на 0 возвращает исходную дробь
*/
Fraction& Fraction::operator/=(const Fraction& other)
{
	if (other.numeration == 0)
	{
		cout << "ERROR:DENOMINATOR IS ZERO" << endl;
		return *this;
	}
	this->WithoutInt(1);
	Fraction temp(other);
	temp.WithoutInt(1);
	this->numeration *= temp.denominator;
	this->denominator *= temp.numeration;
	this->NormalForm();
	return *this;
}
/*! \brief Функция сложения натуральной дроби с целым числом
		\param other второе слогаемое
		 \return дробь - результат сложения дроби с целым числом
*/
Fraction Fraction::operator+(const int& other)
{
	Fraction temp(this->WithoutInt());
	temp.numeration += other * temp.denominator;
	temp.NormalForm();
	return temp;
}
/*! \brief Функция вычитания натуральной дроби и целого числа
		\param other вычитаемое
		 \return дробь - результат вычитания дроби и целого числа
*/
Fraction Fraction::operator-(const int& other)
{
	Fraction temp(this->WithoutInt());
	temp.numeration -= other * temp.denominator;
	temp.NormalForm();
	return temp;
}
/*! \brief Функция сложения с присваением дроби и целого числа
	\param other второе слогаемое
*/
Fraction& Fraction::operator+=(const int& other)
{
	this->WithoutInt(1);
	this->numeration += other * this->denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция вычитания с присваением дроби и целого числа
		\param other вычитаемое
*/
Fraction& Fraction::operator-=(const int& other)
{
	this->WithoutInt(1);
	this->numeration -= other * this->denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция умножения натуральной дроби и целого числа
		\param other второй множитель
		 \return дробь - результат умножения натуральной дроби и целого числа
*/
Fraction Fraction::operator*(const int& other)
{
	if (other == 0)
	{
		return Fraction(0, 1, 0);
	}
	Fraction temp(this->WithoutInt());
	temp.numeration *= other;
	temp.NormalForm();
	return temp;
}
/*! \brief Функция умножения с присваением дроби и целого числа
		\param other второй множитель

*/
Fraction& Fraction::operator*=(const int& other)
{
	if (other == 0)
	{
		this->numeration = 0;
		this->denominator = 1;
		this->integer = 0;
		return *this;
	}
	this->WithoutInt(1);
	this->numeration *= other;
	this->NormalForm();
	return *this;
}
/*! \brief Функция деления дроби на целое число
		\param other делитель
		 \return дробь - результат деления дроби на целое число
		 \warning при делении на 0 возвращает исходную дробь
*/
Fraction Fraction::operator/(const int& other)
{
	if (other == 0)
	{
		cout << "ERROR:DENOMINATOR IS ZERO" << endl;
		return *this;
	}
	Fraction temp(this->WithoutInt());
	temp.denominator *= other;
	temp.NormalForm();
	return temp;
}
/*! \brief Функция деления дроби на целое число
		\param other делитель
		\warning при делении на 0 возвращает исходную дробь
*/
Fraction& Fraction::operator/=(const int& other)
{
	if (other == 0)
	{
		cout << "ERROR:DENOMINATOR IS ZERO" << endl;
		return *this;
	}
	this->WithoutInt(1);
	this->denominator *= other;
	this->NormalForm();
	return *this;
}
/*! \brief Функция преинкремент
	
	Прибавляет единицу и возвращет значение  
*/
Fraction& Fraction::operator++()
{
	this->WithoutInt(1);
	this->numeration += this->denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция предекремент
	
	Отнимает единицу и возвращет значение
*/
Fraction& Fraction::operator--()
{
	this->WithoutInt(1);
	this->numeration -= this->denominator;
	this->NormalForm();
	return *this;
}
/*! \brief Функция постинкремент
	
	Возвращет значение и прибавляет единицу
*/
Fraction& Fraction::operator++(int other)
{
	Fraction temp(*this);
	this->WithoutInt(1);
	this->numeration += this->denominator;
	this->NormalForm();
	return temp;
}
/*! \brief Функция постдекремент
		
	Возвращет значение и отнимает единицу
*/
Fraction& Fraction::operator--(int other)
{
	Fraction temp(*this);
	this->WithoutInt(1);
	this->numeration -= this->denominator;
	this->NormalForm();
	return temp;
}
/*! \brief Функция сравнения < двух натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь меньше other, false во всех остальных случаях
*/
bool Fraction::operator<(const Fraction& other)
{
	return this->compareTo(other) < 0;
}
/*! \brief Функция сравнения <= двух натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь меньше либо равна other, false во всех остальных случаях
*/
bool Fraction::operator<=(const Fraction& other)
{
	return this->compareTo(other) <= 0;
}
/*! \brief Функция сравнения двух > натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь больше other, false во всех остальных случаях
*/
bool Fraction::operator>(const Fraction& other)
{
	return this->compareTo(other) > 0;
}
/*! \brief Функция сравнения двух >= натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь больше либо равна other, false во всех остальных случаях
*/
bool Fraction::operator>=(const Fraction& other)
{
	return this->compareTo(other) >= 0;
}
/*! \brief Функция сравнения двух == натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь равна other, false во всех остальных случаях
*/
bool Fraction::operator ==(const Fraction& other)
{
	return this->compareTo(other) == 0;
}
/*! \brief Функция сравнения двух != натуральных дробей
	\param other дробь, с которой сравнивают
	\return true, если дробь не равна other, false во всех остальных случаях
*/
bool Fraction::operator !=(const Fraction& other)
{
	return this->compareTo(other) != 0;
}
/*! \brief Функция приведения натуральной дроби к типу double
	\return дробь, приведенную к double
*/
double Fraction::ToDouble()
{
	double denominator = this->denominator;
	double integer = this->integer;
	double numeration = this->numeration + denominator * integer;
	return numeration/this->denominator;
}
/*! \brief Функция сравнения < двух натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь меньше other, false во всех остальных случаях
*/
bool Fraction::operator<(const int& other)
{
	return this->compareTo(other) < 0;
}
/*! \brief Функция сравнения <= двух натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь меньше либо равна other, false во всех остальных случаях
*/
bool Fraction::operator<=(const int& other)
{
	return this->compareTo(other) <= 0;
}
/*! \brief Функция сравнения двух > натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь больше other, false во всех остальных случаях
*/
bool Fraction::operator>(const int& other)
{
	return this->compareTo(other) > 0;
}
/*! \brief Функция сравнения двух >= натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь больше либо равна other, false во всех остальных случаях
*/
bool Fraction::operator>=(const int& other)
{
	return this->compareTo(other) >= 0;
}
/*! \brief Функция сравнения двух == натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь равна other, false во всех остальных случаях
*/
bool Fraction::operator ==(const int& other)
{
	return this->compareTo(other) == 0;
}
/*! \brief Функция сравнения двух != натуральных дробей
	\param other число, с которым сравнивают
	\return true, если дробь не равна other, false во всех остальных случаях
*/
bool Fraction::operator !=(const int& other)
{
	return this->compareTo(other) != 0;
}
/*! \brief Функция изменения вида дроби
	\return временную дробь, без целой части

	Функция создает новую дробь, переводя целую часть в числитель. Не изменяет текущую дробь. Упрощает дробь. Применяется для внутренних операций.
*/
Fraction Fraction::WithoutInt()
{
	Fraction temp;
	this->numeration > 0 ? temp.numeration = this->numeration + this->integer * this->denominator : temp.numeration = this->numeration - this->integer * this->denominator;
	temp.denominator = this->denominator;
	temp.integer = 0;
	temp.Simplify();
	return temp;
}
/*! \brief Функция изменения вида дроби

	Функция изменяет текущую дробь, переводя целую часть в числитель. Упрощает дробь. Применяется для внутренних операций.
*/
void Fraction::WithoutInt(int n)
{
	this->numeration > 0 ? this->numeration += this->integer * this->denominator : this->numeration -= this->integer * this->denominator;
	this->integer = 0;
	this->Simplify();
}
/*! \brief Функция упрощения дроби

	Функция упрощает текущую дробь. Применяется для внутренних операций.
*/
void Fraction::Simplify()
{
	this->MinusDenominator();
	if (abs(this->numeration) < 2) return;
	int gcd = GetGCD(abs(this->numeration), this->denominator);
	this->numeration /= gcd;
	this->denominator /= gcd;
}
/*! \brief Функция проверки знаменателя

	Функция проверяет, отрицателен ли знаменател, если да, то меняет знаки знаменателя и числителя. Применяется для внутренних операций.
*/
void Fraction::MinusDenominator()
{
	if (this->denominator < 0)
	{
		this->denominator *= -1;
		this->numeration *= -1;
	}
}
/*! \brief Функция изменения вида дроби

	Функция изменяет текущую дробь, выделяя целую часть, если это возможно. Упрощает дробь. Применяется для внутренних операций.
*/
void Fraction::NormalForm()
{
	this->Simplify();
	this->integer += this->numeration / this->denominator;
	this->MinusInteger();
	this->numeration = this->numeration % this->denominator;
}
/*! \brief Функция вычисления НОД
	\param	a,b числа, для которых надо вычислить НОД

	Функция вычисляет НОД a и b, используя алгоритм вычитания. Применяется для упрощения дроби.
*/
int Fraction::GetGCD(int a, int b) {
	while (a != b)
		a > b ? a -= b : b -= a;
	return a;
}
/*! \brief Функция сравнения двух дробей
	\param	other дробь, с которой сравнивают
	\return разность двух дробей

	Функция вычисляет разность двух дробей. Применяется для операций сравнения.
*/
int Fraction::compareTo(const Fraction& other)
{
	Fraction temp_1(this->WithoutInt()), temp_2(other);
	temp_2 = temp_2.WithoutInt();
	return temp_1.numeration * temp_2.denominator - temp_1.denominator * temp_2.numeration;
}
/*! \brief Функция сравнения дроби и целого числа
	\param	other число, с которым сравнивают
	\return дроби и целого числа

	Функция вычисляет разность дроби и целого числа. Применяется для операций сравнения.
*/
int Fraction::compareTo(const int& other)
{
	Fraction temp_1(this->WithoutInt());
	return temp_1.numeration - temp_1.denominator * other;
}