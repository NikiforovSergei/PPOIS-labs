#include <gtest/gtest.h>
#include "header.h"

using namespace std;
/// вспомогательная команда, позовляющая убрать нули
void Long::_removeZeros() {
    while (this->_value.size() > 1 && this->_value.back() == 0) {
        this->_value.pop_back();
    }
}


Long::Long(){}

Long::Long(string str){
    if (str[0] == '-') {
        _isNegative = true;
        str.erase(0, 1);
    }
    else
        _isNegative = false;
    for (int i = str.size() - 1; i >= 0; i--)
        _value.push_back(str[i] - '0');
}


Long::Long(int number) {
    if(number < 0)
        _isNegative = true;
    else
        _isNegative = false;
    string str = to_string(number);
    for (int i = str.size() - 1; i >= 0; i--)
        _value.push_back(str[i] - '0');
};
///операторы сравнения для длинных
bool operator == (Long l1, Long l2) {
    if (l1._value.size() == l2._value.size())
        for (int i = 0; i < l1._value.size(); i++)
            if (l1._value[i] == l2._value[i])
                return true;
            else
                return false;
    else return false;
}
bool operator > (Long l1, Long l2)
{
    if (l1._isNegative == l2._isNegative) {
        int n = l1._value.size();
        if (l1._value.size() != l2._value.size())
            if (l1._isNegative == true)
                return l1._value.size() < l2._value.size();
            else
                return l1._value.size() > l2._value.size();
        while (n--)
            if (l1._value[n] != l2._value[n])
                if (l1._isNegative == true)
                    return l1._value[n] < l2._value[n];
                else
                    return l1._value[n] > l2._value[n];
        return false;
    }
    else
    if (l2._isNegative == true)
        return true;
    else
        return false;
}
bool operator < (Long l1, Long l2)
{
    if (l1._isNegative == l2._isNegative) {
        int n = l1._value.size();
        if (l1._value.size() != l2._value.size())
            if (l1._isNegative == true)
                return l1._value.size() > l2._value.size();
            else
                return l1._value.size() < l2._value.size();
        while (n--)
            if (l1._value[n] != l2._value[n])
                if(l1._isNegative == true)
                    return l1._value[n] > l2._value[n];
                else
                    return l1._value[n] < l2._value[n];
        return false;
    }
    else
    if (l2._isNegative == true)
        return false;
    else
        return true;
}
bool operator >= (Long l1, Long l2) {
    return !(l1 < l2);
}
bool operator <= (Long l1, Long l2){
    return !(l1 > l2);
}

///операторы сравнения для длинных и целых
bool operator > (Long l1, int i){
    Long l2(i);
    return l1 > l2;
}
bool operator < (Long l1, int i){
    Long l2(i);
    return l1 < l2;
}
bool operator >= (Long l1, int i) {
    Long l2(i);
    return !(l1 < l2);
}
bool operator <= (Long l1, int i) {
    Long l2(i);
    return !(l1 > l2);
}
///инкремент и декремент
const Long Long::operator++() {
    return (*this += 1);
}

const Long Long::operator ++(int) {
    *this += 1;
    return *this - 1;
}

const Long Long::operator --() {
    return *this -= 1;
}

const Long Long::operator --(int) {
    *this -= 1;
    return *this + 1;
}


///арифметические операции для длинных целых
Long operator+ (const Long& l){
    return l;
}
Long operator- (const Long& l){
    l._isNegative = !l._isNegative;
    return l;
}
Long operator + (Long l1, Long l2) {
    if (l1._isNegative) {
        if (l2._isNegative)
            return -(-l1 + (-l2));
        else
            return l2 - (-l1);
    }
    else
    if (l2._isNegative)
        return l1 - (-l2);
    if (l1._value.size() < l2._value.size()){
        int upper = l2._value.size() - l1._value.size() + 1;
        for (int i = 0; i < upper; i++)
            l1._value.push_back(0);
    }
    else
    if(l1._value.size() > l2._value.size()) {
        int upper = l1._value.size() - l2._value.size() + 1;
        for (int i = 0; i < upper; i++)
            l2._value.push_back(0);
    }
    l1._value.push_back(0);
    l2._value.push_back(0);
    for (int i = 0; i < l1._value.size(); i++)
    {
        l1._value[i] += l2._value[i];
        if (l1._value[i] > 9)
        {
            l1._value[i + 1] += 1;
            l1._value[i] -= 10;
        }
    }
    l1._removeZeros();
    return l1;
}
Long& operator+=(Long& l1, const Long& l2) {
    l1 = l1 + l2;
    return l1;
}
Long operator - (Long l1, Long l2) {
    if (l2._isNegative)
        return l1 + (-l2);
    else
    if (l1._isNegative)
        return -(-l1 + l2);
    else
    if (l1 < l2)
        return -(l2 - l1);
    int z = l1._value.size() - l2._value.size() + 1;
    if (l1._value.size() < l2._value.size())
        for (int i = 0; i < z; i++)
            l1._value.push_back(0);
    else
    if (l1._value.size() > l2._value.size())
        for (int i = 0; i < z; i++)
            l2._value.push_back(0);
    for (int i = 0; i < l1._value.size(); i++)
    {
        l1._value[i] -= l2._value[i];
        if (l1._value[i] <0)
        {
            l1._value[i + 1] -= 1;
            l1._value[i] += 10;
        }
    }
    l1._removeZeros();
    return l1;
}
Long& operator-=(Long& l1, const Long& l2) {
    l1 = l1 - l2;
    return l1;
}

Long operator * (Long l1, Long l2) {
    if(l2 == 0 || l1 == 0)
        return 0;
    Long result;
    for (int i = 0; i < l1._value.size() + l2._value.size(); i++)
        result._value.push_back(0);
    for (size_t i = 0; i < l1._value.size(); ++i) {
        for (size_t j = 0; j < l2._value.size(); ++j) {
            result._value[j + i] += l1._value[i] * l2._value[j];
            while(result._value[i + j] > 9)
            {
                result._value[i + j] -= 10;
                result._value[i + j + 1] +=1;
            }
        }
    }
    /// высчитывание знака
    result._isNegative = l1._isNegative != l2._isNegative;
    result._removeZeros();
    return result;
}
Long& operator*=(Long& l1, const Long& l2) {
    l1 = l1 * l2;
    return l1;
}
Long operator / (Long l1, Long l2) {
    if(l1 == l2)
        return 1;
    if(l2 == 0)
        throw logic_error("Smth wrong!");
    else
    if(l1 == 0)
        return 0;
    Long temp = 0;
    return division(l1, l2, l1._value.size() - 1, temp, 0);
}
Long& operator/=(Long& l1, const Long& l2){
    l1 = l1 / l2;
    return l1;
}


///арифметичексие операции для длинного целого и целого
Long operator + (Long l1, int i){
    Long temp(i);
    return l1 + temp;
}
Long operator - (Long l1, int i){
    Long temp(i);
    return l1 - temp;
}
Long& operator+=(Long& l1, const int& i) {
    Long l2 = i;
    l1 = l1 + l2;
    return l1;
}
Long& operator-=(Long& l1, const int& i) {
    Long l2(i);
    l1 = l1 - l2;
    return l1;
}

Long operator * (Long l1, int i){
    Long temp(i);
    return l1 * temp;
}
Long& operator*=(Long& l1, const int& i){
    Long temp(i), l2;
    l2 = l1 * temp;
    l1 = l2;
    return l1;
}
Long operator / (Long l1, int i){
    Long temp(i);
    return l1 / temp;
}
Long& operator/=(Long& l1, const int& i){
    Long temp(i);
    l1 = l1 / temp;
    return l1;
}


///ввод и вывод
ostream& operator << (ostream& os, Long& l) {
    if (l._isNegative)
        os << '-';
    for (size_t i = l._value.size(); i > 0; i--)
        os << l._value[i - 1];
    return os;
}
istream& operator >> (istream & in, Long & l)
{
    string str;
    in >> str;

    int n = str.size();
    if (str[0] == '-') {
        l._isNegative = true;
        str.erase(0, 1);
    }
    else
        l._isNegative = false;
    for (int i = str.size() - 1; i >= 0; i--)
        l._value.push_back(str[i] - '0');
    return in;
}


///воспомагательные функции
Long division(Long l1, Long l2, int i, Long temp, Long res){
    while (temp < l2) { /// высчитываем число, с которым будут проводиться первые операции
        temp = temp * 10;
        if(i >= 0) {
            temp = temp + l1._value[i];
            i--;
        }
        else {
            if(res == 0)
                res._isNegative = l1._isNegative != l2._isNegative;
            return res;
        }
    }
    int idx = 0;
    while (l2 * idx <= temp)///осуществление подбора для результата
        idx++;
    res = res * 10 + idx - 1;
    temp = temp - l2 * (idx - 1);
    if(i == l1._value.size() - 1){
        res._isNegative = l1._isNegative != l2._isNegative;
        return res;
    }
    return division(l1, l2, i, temp, res);
}
