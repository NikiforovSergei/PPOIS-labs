#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Long {
    ///\param _value - значение длинного целого числа.
///\param _isNegative - параметр, отвечающий за знак числа.
///\param l1 - длинное целое, которое находится слева в выражении
///\param l2 - длинное целое, которое находится справа в выражении
    vector <int> _value;
    mutable bool _isNegative;
    void _removeZeros();
public:
    //базовые конструкторы
    Long();
    Long(int number);
    Long to_long(int number);
    Long(string str);
    //
    const Long operator ++();
    const Long operator ++(int);
    const Long operator --();
    const Long operator --(int);
    friend Long operator+ (const Long& l);
    friend Long operator- (const Long& l);
    //вывод типа
    friend ostream& operator << (ostream& os, Long& l);
    //ввод типа
    friend istream& operator >> (istream& in, Long& l);
    //перегрузка операторов сравнения
    friend bool operator == (Long l1, Long l2);
    friend bool operator > (Long l1, Long l2);
    friend bool operator < (Long l1, Long l2);
    friend bool operator >= (Long l1, Long l2);
    friend bool operator <= (Long l1, Long l2);
    friend bool operator > (Long l, int i);
    friend bool operator < (Long l, int i);
    friend bool operator >= (Long l, int i);
    friend bool operator <= (Long l, int i);
    //арифметические операции для длинных целых
    friend Long operator + (Long l1, Long l2);
    friend Long& operator+=(Long& l1, const Long& l2);
    friend Long operator - (Long l1, Long l2);
    friend Long& operator-=(Long& l1, const Long& l2);

    friend Long operator * (Long l1, Long l2);
    friend Long& operator*=(Long& l1, const Long& l2);
    friend Long operator / (Long l1, Long l2);
    friend Long& operator/=(Long& l1, const Long& l2);

    //арифметичексие операции для длинного целого и целого
    friend Long operator + (Long l1, int i);
    friend Long& operator+=(Long& l1, const int& i);
    friend Long operator - (Long l1, int i);
    friend Long& operator-=(Long& l1, const int& i);

    friend Long operator * (Long l1, int i);
    friend Long& operator*=(Long& l1, const int& i);
    friend Long operator / (Long l1, int i);
    friend Long& operator/=(Long& l1, const int& i);

    friend Long division(Long l1, Long l2, int i, Long temp, Long res);
};