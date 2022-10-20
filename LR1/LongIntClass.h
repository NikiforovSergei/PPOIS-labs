#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace LongIntSpace {
    class LongInt {
    public:
        int sign;
        vector<int> digits;
    public:
        LongInt();
        LongInt(const LongInt& x);
        LongInt(const string& value);

        friend ostream& operator<<(ostream& os, const LongInt& value);

        bool operator>(const LongInt& x) const;
        bool operator<(const LongInt& x) const;
        bool operator>=(const LongInt& x) const;
        bool operator<=(const LongInt& x) const;
        bool operator==(const LongInt& x) const;
        bool operator!=(const LongInt& x) const;

        LongInt& operator=(const LongInt& x);

        LongInt operator*(const LongInt& x) const;
        LongInt operator*=(const LongInt& x);
        LongInt operator/(const LongInt& x) const;
        LongInt operator/=(const LongInt& x);
        LongInt operator+(const LongInt& x) const;
        LongInt operator+=(const LongInt& x);
        LongInt operator-(const LongInt& x) const;
        LongInt operator-=(const LongInt& x);

        /*LongInt inverse() const;*/
    };
}

