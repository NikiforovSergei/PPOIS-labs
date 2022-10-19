#include "LongIntClass.h"

/*!
    \brief Is namespace for LongInt class
    \version 1.0.0
*/
namespace LongIntSpace {
    /*!
        \brief 
            overload operator <<, for use this write cout << a
        \version 1.0.0
    */
    ostream& operator<<(ostream& os, const LongInt& value) {
        if (value.sign == -1)
            os << '-';
        int i = 0;
        while (i < value.digits.size())
            os << value.digits[i++];
        return os;
    }

    LongInt::LongInt() {
        sign = 1;
        digits = vector<int>(1, 0);
    }

    LongInt::LongInt(const LongInt& x) {
        sign = x.sign;
        digits = vector<int>(x.digits);
    }

    /*!
        \brief
            To create big int number write this: LongInt("your_number"), where parameter is a string
        \version 1.0.0
    */

    LongInt::LongInt(const string& value) {
        size_t index;

        if (value[0] == '-') {
            sign = -1;
            index = 1;
        }
        else {
            sign = 1;
            index = 0;
        }

        while (index < value.length()) {
            digits.push_back(value[index] - '0');
            index++;
        }
    }
    /*!
        \brief
            overload operator <, for use this write a < b
        \version 1.0.0
    */
    bool LongInt::operator<(const LongInt& x) const {
        return !(*this > x || *this == x);
    }
    /*!
        \brief
            overload operator >=, for use this write a >= b
        \version 1.0.0
    */
    bool LongInt::operator>=(const LongInt& x) const {
        return *this > x || *this == x;
    }

    /*!
        \brief
            overload operator <=, for use this write a <= b
        \version 1.0.0
    */
    bool LongInt::operator<=(const LongInt& x) const {
        return *this < x || *this == x;
    }
    /*!
        \brief
            overload operator ==, for use this write a == b
        \version 1.0.0
    */
    bool LongInt::operator==(const LongInt& x) const {
        if (sign != x.sign)
            return false;

        if (digits.size() != x.digits.size())
            return false;

        for (size_t i = 0; i < digits.size(); i++)
            if (digits[i] != x.digits[i])
                return false;

        return true;
    }
    /*!
        \brief
            overload operator !=, for use this write a != b
        \version 1.0.0
    */
    bool LongInt::operator!=(const LongInt& x) const {
        return !(*this == x);
    }
    /*!
        \brief
            overload operator *, for use this write a * b
        \version 1.0.0
    */
    LongInt LongInt::operator*(const LongInt& x) const {
        size_t len = digits.size() + x.digits.size();
        LongInt res;

        res.sign = sign * x.sign;
        res.digits = vector<int>(len, 0);

        for (size_t i = 0; i < digits.size(); i++)
            for (size_t j = 0; j < x.digits.size(); j++)
                res.digits[i + j + 1] += digits[i] * x.digits[j];
        for (size_t i = len - 1; i > 0; i--) {
            res.digits[i - 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }

        while (res.digits.size() > 1 && res.digits[0] == 0) {
            res.digits.erase(res.digits.begin());
        }

        return res;
    }
    /*!
        \brief
            overload operator >, for use this write a > b
        \version 1.0.0
    */
    bool LongInt::operator>(const LongInt& x) const {
        if (sign != x.sign)
            return sign > x.sign;

        vector<int> d1(digits);
        vector<int> d2(x.digits);
        size_t size = max(d1.size(), d2.size());

        while (d1.size() != size)
            d1.insert(d1.begin(), 0);

        while (d2.size() != size)
            d2.insert(d2.begin(), 0);

        for (size_t i = 0; i < size; i++)
            if (d1[i] != d2[i])
                return (d1[i] > d2[i]) ^ (sign == -1);

        return false;
    }
    /*!
        \brief
            overload operator -, for use this write a - b
        \version 1.0.0
    */
    LongInt LongInt::operator-(const LongInt& x) const {
        if (sign == 1 && x.sign == 1) {
            bool cmp = *this > x;

            vector<int> d1(cmp ? digits : x.digits);
            vector<int> d2(cmp ? x.digits : digits);

            size_t size = max(d1.size(), d2.size());

            while (d1.size() != size)
                d1.insert(d1.begin(), 0);

            while (d2.size() != size)
                d2.insert(d2.begin(), 0);

            size_t len = 1 + size;

            LongInt res;

            res.sign = cmp ? 1 : -1;
            res.digits = vector<int>(len, 0);

            for (size_t i = 0; i < size; i++)
                res.digits[i + 1] = d1[i] - d2[i];

            for (size_t i = len - 1; i > 0; i--) {
                if (res.digits[i] < 0) {
                    res.digits[i] += 10;
                    res.digits[i - 1]--;
                }
            }

            while (res.digits.size() > 1 && res.digits[0] == 0) {
                res.digits.erase(res.digits.begin());
            }

            return res;
        }

        LongInt n("-1");

        if (sign == -1 && x.sign == -1)
            return (n * x) - (n * (*this));

        return *this + (n * x);
    }
    /*!
        \brief
            overload operator -=, for use this write a -= b
        \version 1.0.0
    */
    LongInt LongInt::operator-=(const LongInt& x) {
        LongInt a;
        a = *this - x;
        *this = a;
        return *this;
    }
    /*!
        \brief
            overload operator +, for use this write a + b
        \version 1.0.0
    */
    LongInt LongInt::operator+(const LongInt& x) const {
        if (sign == x.sign) {
            vector<int> d1(digits);
            vector<int> d2(x.digits);

            size_t size = max(d1.size(), d2.size());

            size_t len = 1 + size;

            LongInt res;

            res.sign = sign;
            res.digits = vector<int>(len, 0);

            while (d1.size() != size)
                d1.insert(d1.begin(), 0);

            while (d2.size() != size)
                d2.insert(d2.begin(), 0);

            for (size_t i = 0; i < size; i++)
                res.digits[i + 1] = d1[i] + d2[i];

            for (size_t i = len - 1; i > 0; i--) {
                res.digits[i - 1] += res.digits[i] / 10;
                res.digits[i] %= 10;
            }

            while (res.digits.size() > 1 && res.digits[0] == 0) {
                res.digits.erase(res.digits.begin());
            }


            return res;
        }

        LongInt n("-1");

        if (sign == -1)
            return x - n * (*this);

        return *this - (n * x);
    }
    /*!
        \brief
            overload operator +=, for use this write a += b
        \version 1.0.0
    */
    LongInt LongInt::operator+=(const LongInt& x) {
        LongInt a;
        a = *this + x;
        *this = a;
        return *this;
    }
    /*!
        \brief
            overload operator /, for use this write a /= b
        \version 1.0.0
    */
    LongInt LongInt::operator/(const LongInt& x) const {
        if (x.digits.size() == 1 && x.digits[0] == 0) {
            throw string("Delenie na nol");
        }

        LongInt copy(*this);
        LongInt copyX(x);

        LongInt res;
        res.sign = (sign != x.sign ? -1 : 1);
        res.digits = vector<int>();

        if (copyX.sign == -1)
            copyX = LongInt("-1") * copyX;

        if (sign == -1)
            copy = LongInt("-1") * copy;


        while (copy != LongInt("0") && copy >= copyX) {
            int div = 0;

            while (copy >= copyX) {
                div++;
                copy = copy - copyX;
            }

            while (res.digits.size() > 1 && res.digits[0] == 0) {
                res.digits.erase(res.digits.begin());
            }
            res.digits.push_back(div);
        }

        return res;
    }
    /*!
        \brief
            overload operator =, for use this write a = b
        \version 1.0.0
    */
    LongInt& LongInt::operator=(const LongInt& x) {
        if (this == &x)
            return *this;

        sign = x.sign;
        digits = vector<int>(x.digits.size());

        for (size_t i = 0; i < x.digits.size(); i++)
            digits[i] = x.digits[i];

        return *this;
    }
    /*!
        \brief
            overload operator *=, for use this write a *= b
        \version 1.0.0
    */
    LongInt LongInt::operator*=(const LongInt& x) {
        LongInt a;
        a = *this * x;
        *this = a;
        return *this;
    }
    /*!
        \brief
            overload operator /=, for use this write a /= b
        \version 1.0.0
    */
    LongInt LongInt::operator/=(const LongInt& x) {
        LongInt a;
        a = *this / x;
        *this = a;
        return *this;
    }
}