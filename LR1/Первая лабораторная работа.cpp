#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;
//!Деление для отрицательных чисел
int my_div(int num, int diver) {
    if ((num < 0) && (num % diver))
        return num / diver - 1;
    else
        return num / diver;
}
//!Взятие по модулю для отрицательных чисел
int my_mod(int num, int diver) {
    if ((num < 0) && (num % diver))
        return num % diver + diver;
    else
        return num % diver;
}
/**Класс "большое число", описывает способ хранения большого числа и
длинную арифметику
*/
class BigNumber {
private:
    vector<int> chunks;
    int sign;
    //!Настроиваемые параметры хранения большого числа
    //!Количество символов в строке, которые станут одной "чанкой"
    static const int BASE = 2;
    //!Зависит от BASE (BASE10 = 10^BASE), используется при нормализации
    static const int BASE10 = 100;
    //!Служебные функции
    BigNumber _plus(BigNumber& a);
    BigNumber _minus(BigNumber& a);
    BigNumber _multi(BigNumber&);
    BigNumber _simplemulti(BigNumber&);
    BigNumber _division(BigNumber&);
    BigNumber division1(BigNumber&);
    BigNumber division2(BigNumber&, BigNumber&);
    void _normalizationSigns();
    void _normalizationChunks();
    void _resize(int newsize);
public:
    BigNumber operator + (BigNumber& num);
    BigNumber operator += (BigNumber& num);
    BigNumber operator ++ ();
    BigNumber operator - (BigNumber& num);
    BigNumber operator -= (BigNumber& num);
    BigNumber operator -- ();
    BigNumber operator / (BigNumber&);
    BigNumber operator /= (BigNumber&);
    bool operator != (BigNumber);
    bool operator == (BigNumber);
    bool operator <= (BigNumber);
    bool operator >= (BigNumber);
    bool operator < (BigNumber);
    bool operator > (BigNumber);
    BigNumber operator * (BigNumber);
    BigNumber operator *= (BigNumber);
    friend ostream& operator << (ostream& os, BigNumber& num);
    int getBASE() {
        return this->BASE;
    }
    //!Конструктор, строку конвертирует в большое число
    BigNumber(string str) {
        int i;
        if (BASE != 1) {
            //!Записываем с конца по BASE символов строки в чанки
            for (i = str.size() - BASE; i >= BASE - 1; i -= BASE) {
                chunks.push_back(stoi(str.substr(i, BASE)));
            }
        }
        else {
            for (i = str.size() - BASE; i >= BASE; i -= BASE) {
                chunks.push_back(stoi(str.substr(i, BASE)));
            }
        }
        //!Дошли до начала строки, тут ищем знак и записываем последнюю чанку
        if (str[0] == '-') {
            sign = -1;
            if (i + BASE - 1 != 0) {
                chunks.push_back(stoi(str.substr(1, i + BASE - 1)));
            }
        }
        else {
            sign = 1;
            chunks.push_back(stoi(str.substr(0, i + BASE)));
        }
    }
    //!Конструктор без аргументов - "пустое" положительное число
    BigNumber() {
        sign = 1;
    }
};
//!Изменение размера массива с чанками
void BigNumber::_resize(int newSize) {
    chunks.resize(newSize);
}
/**
* @brief Функция нормализует большое число так, чтобы во всех чанках лежали BASE-разрядные числа
*/
void BigNumber::_normalizationChunks() {
    int over = 0; //!"Лишнее", которое будет кочевать в следующие чанки
    for (int i = 0; i < chunks.size() - 1; i++) {
        chunks[i] += over; //!Прибавляем привесок от прошлых чанок
        over = my_div(chunks[i], BASE10); //!Считаем перевес в текущей чанке
        chunks[i] = my_mod(chunks[i], BASE10); //!Выравниваем чанку по базе
    }
    //!Прибавляем перевес к последней чанке
    chunks[chunks.size() - 1] += over;
    //!Обрабатываем перевес в последней чанке
    if (chunks[chunks.size() - 1] / BASE10) {
        over = my_div(chunks[chunks.size() - 1], BASE10);
        chunks[chunks.size() - 1] = my_mod(chunks[chunks.size() - 1], BASE10);
        chunks.push_back(over); //!Создаем нову чанку с остатками
    }
    return;
}
//!Функция нормализует большое число для печати так, чтобы все чанки были положительными, но sign = -1(если число отрицательное)
void BigNumber::_normalizationSigns() {
    //!Если в последней чанке отрицательное число
    if (chunks[chunks.size() - 1] < 0) {
        sign = -sign; //!Меняем знак числа
        chunks[0] = BASE10 - chunks[0]; //!Нормализуем первую чанку
        for (int i = 1; i < chunks.size(); i++) {
            chunks[i] = (BASE10 - chunks[i] - 1) % BASE10; //!Нормализуем ост. чанки
        }
    }
    //!Убираем из числа нулевые чанки
    int i = chunks.size() - 1;
    while (chunks[i] == 0) {
        if (i == 0) {
            sign = 1;
            return;
        }
        chunks.pop_back();
        i--;
    }
    return;
}
/**
* @brief Функция сложения
*/
BigNumber BigNumber::_plus(BigNumber& num) {
    BigNumber res;
    res.sign = this->sign;
    for (int i = 0; i < this->chunks.size(); i++) {
        res.chunks.push_back(this->chunks[i] + num.chunks[i]);
    }
    return res;
}
/**
* @brief Функция вычитания
*/
BigNumber BigNumber::_minus(BigNumber& num) {
    BigNumber res;
    res.sign = this->sign;
    for (int i = 0; i < this->chunks.size(); i++) {
        res.chunks.push_back(this->chunks[i] - num.chunks[i]);
    }
    return res;
}
//!Оператор +, выполняет корректное сложение больших чисел
BigNumber BigNumber::operator + (BigNumber& num) {
    BigNumber res;
    //!Приводим размер чанок обоих чисел
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!Выполняем операцию в зависимости от знаков чисел
    if (sign == num.sign) {
        res = (*this)._plus(num);
    }
    else {
        res = (*this)._minus(num);
    }
    //!Нормализуем результат
    res._normalizationChunks();
    return res;
}
//!Оператор +=
BigNumber BigNumber::operator += (BigNumber& num) {
    //!Приводим размер чанок обоих чисел
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!Выполняем операцию в зависимости от знаков чисел
    if (sign == num.sign) {
        *this = (*this)._plus(num);
    }
    else {
        *this = (*this)._minus(num);
    }
    //!Нормализуем результат
    (*this)._normalizationChunks();
    return *this;
}
BigNumber BigNumber::operator ++ () {
    BigNumber num("1");
    //!Приводим размер чанок обоих чисел
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!Выполняем операцию в зависимости от знаков чисел
    if (sign == num.sign) {
        *this = (*this)._plus(num);
    }
    else {
        *this = (*this)._minus(num);
    }
    //!Нормализуем результат
    (*this)._normalizationChunks();
    return *this;
}
//!Оператор -, выполняет корректное вычитание
BigNumber BigNumber::operator - (BigNumber& num) {
    BigNumber res;
    //!Приводим размер чанок
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!В зависимости от знаков, выполняем нужное действие
    if (sign != num.sign) {
        res = (*this)._plus(num);
    }
    else {
        res = (*this)._minus(num);
    }
    //!Нормализуем результат
    res._normalizationChunks();
    return res;
}

BigNumber BigNumber::operator -= (BigNumber& num) {
    //!Приводим размер чанок
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!В зависимости от знаков, выполняем нужное действие
    if (sign != num.sign) {
        *this = (*this)._plus(num);
    }
    else {
        *this = (*this)._minus(num);
    }
    //!Нормализуем результат
    (*this)._normalizationChunks();
    return *this;
}
BigNumber BigNumber::operator -- () {
    BigNumber num("1");
    //!Приводим размер чанок
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //!В зависимости от знаков, выполняем нужное действие
    if (sign != num.sign) {
        *this = (*this)._plus(num);
    }
    else {
        *this = (*this)._minus(num);
    }
    //!Нормализуем результат
    (*this)._normalizationChunks();
    return *this;
}
//!Перегрузка оператора << для вывода в поток
ostream& operator << (ostream& os, BigNumber& num) {
    num._normalizationSigns();
    if (num.sign == -1) {
        os << '-';
    }
    os << num.chunks[num.chunks.size() - 1];
    for (int i = num.chunks.size() - 2; i >= 0; i--) {
        os << setw(num.getBASE()) << setfill('0') << num.chunks[i];
    }
    return os;
}

bool BigNumber::operator == (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    if (this->sign == num.sign) {
        //!Если числа разного размера, то они не равны
        if (this->chunks.size() != num.chunks.size()) {
            return false;
        }

        //!Сравнить почанково
        for (int i = this->chunks.size() - 1; i >= 0; i--) {
            if (this->chunks[i] != num.chunks[i]) {
                return false;
            }
        }
        return true;
    }
    //!Если знаки не равны, то и числа не равны
    else {
        return false;
    }
}

bool BigNumber::operator != (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    if (this->sign == num.sign) {
        //!Если числа разного размера, то они не равны
        if (this->chunks.size() != num.chunks.size()) {
            return true;
        }

        //!Сравнить почанково
        for (int i = this->chunks.size() - 1; i >= 0; i--) {
            if (this->chunks[i] != num.chunks[i]) {
                return true;
            }
        }
        return false;
    }
    //!Если знаки не равны, то и числа не равны
    else {
        return true;
    }
}

bool BigNumber::operator < (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    //!Если знаки не равны, то сразу делаем вывод
    if (this->sign != num.sign) {
        if (this->sign == -1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        //!Если можно сделать вывод по длине числа
        if (this->chunks.size() < num.chunks.size()) {
            return true;
        }
        if (this->chunks.size() > num.chunks.size()) {
            return false;
        }

        //!Если одинаковой длины, сравниваем значения
        if (this->sign != -1) {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] > num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] < num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] >= num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
        //!Если первое число отрицательное
        else {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] < num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] > num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] <= num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
    }

    return false;
}

bool BigNumber::operator <= (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    if (this->sign != num.sign) {
        if (sign == -1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (this->chunks.size() < num.chunks.size()) {
            return true;
        }
        if (this->chunks.size() > num.chunks.size()) {
            return false;
        }

        if (sign != -1) {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] > num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] < num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] > num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] < num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] > num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] < num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
    }

    return false;
}

bool BigNumber::operator > (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    if (this->sign != num.sign) {
        if (this->sign == -1) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        if (this->chunks.size() > num.chunks.size()) {
            return true;
        }
        if (this->chunks.size() < num.chunks.size()) {
            return false;
        }

        if (sign == -1) {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] > num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] < num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] >= num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] < num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] > num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] <= num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
    }

    return false;
}

bool BigNumber::operator >= (BigNumber num) {
    num._normalizationChunks();
    num._normalizationSigns();
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();

    if (this->sign != num.sign) {
        if (sign == -1) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        if (this->chunks.size() > num.chunks.size()) {
            return true;
        }
        if (this->chunks.size() < num.chunks.size()) {
            return false;
        }

        if (sign == -1) {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] > num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] < num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] > num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            for (int i = this->chunks.size() - 1; i >= 0; i--) {
                if (this->chunks[i] < num.chunks[i]) {
                    return false;
                }
                if (this->chunks[i] > num.chunks[i]) {
                    return true;
                }
            }

            if (this->chunks[0] < num.chunks[0]) {
                return false;
            }
            else {
                return true;
            }
        }
    }

    return false;
}
/**
* @brief Функция division2 увеличивает частное за счет умножения на числа меньше десяти
*/
BigNumber BigNumber::division2(BigNumber& num, BigNumber& result) {
    BigNumber increase("9");
    BigNumber decrease("1");
    BigNumber result3 = num * result;
    result3._normalizationChunks();
    result3._normalizationSigns();
    BigNumber result2;
    for (; result3 == *this;) {
        if (result3 > *this) {
            result = result2;
            increase = increase - decrease;
        }
        else {
            result2 = result;
            result = result * increase;
            result3 = num * result;
            if (increase == decrease) {
                return result;
            }
        }
    }
    return result;
}
/**
* @brief Данная функция увеличивает размер частного,домнажая на 10, до размеров делимого
*/
BigNumber BigNumber::division1(BigNumber& num) {
    BigNumber result("1");
    BigNumber result2;
    BigNumber increase("10");
    for (;;) {
        if ((result * num) < *this) {
            result2 = result;
            result = result * increase;
            result._normalizationSigns();
        }
        else {
            result = result * increase;
            return division2(num, result);
        }
    }
}
/**
* @brief Функция _division это основная функция для деления больших чисел. Она вызывает другую функцию division1,а division1 вызывает функцию division2.
* Основную работу _division выполняет в конце, прибавляя к частному 1.
*/
BigNumber BigNumber::_division(BigNumber& num) {
    (*this)._normalizationChunks();
    (*this)._normalizationSigns();
    BigNumber decrease("1");
    BigNumber result = division1(num);
    BigNumber result2 = num * result;
    result2._normalizationChunks();
    result2._normalizationSigns();
    for (;;) {
        if (result2 != (*this)) {
            result = result + decrease;
            result2 = num * result;
            result2._normalizationSigns();
            result2._normalizationChunks();
        }
        else {
            return result;
        }

    }
}
/**
* @brief Функция умножения больших чисел
*/
BigNumber BigNumber::_simplemulti(BigNumber& num) {
    BigNumber result;
    result._resize(2 * this->chunks.size());
    result.sign = this->sign;

    for (int i = 0; i < this->chunks.size(); i++) {
        for (int j = 0; j < num.chunks.size(); j++) {
            result.chunks[i + j] += this->chunks[i] * num.chunks[j];
        }
    }

    result._normalizationChunks();
    return result;
}
/**
* @brief Функция приводит большие числа к нужному размеру
*/
BigNumber BigNumber::_multi(BigNumber& num) {
    auto maxSize = max(this->chunks.size(), num.chunks.size());

    int newSize = 1;
    while (newSize < maxSize) {
        newSize *= 2;
    }

    (*this)._resize(newSize);
    num._resize(newSize);

    //return (*this)._fastmulti(num);
    return (*this)._simplemulti(num);
}

BigNumber BigNumber::operator * (BigNumber num) {
    BigNumber result;

    result = (*this)._multi(num);
    result._normalizationChunks();

    if (this->sign == num.sign) {
        result.sign = 1;
    }
    else {
        result.sign = -1;
    }

    return result;
}

BigNumber BigNumber::operator *= (BigNumber num) {
    *this = (*this)._multi(num);
    (*this)._normalizationChunks();

    if (this->sign == num.sign) {
        (*this).sign = 1;
    }
    else {
        (*this).sign = -1;
    }

    return *this;
}

BigNumber BigNumber::operator / (BigNumber& num) {
    BigNumber result;

    result = (*this)._division(num);
    result._normalizationChunks();

    if (this->sign == num.sign) {
        result.sign = 1;
    }
    else {
        result.sign = -1;
    }

    return result;
}

BigNumber BigNumber::operator /= (BigNumber& num) {

    *this = (*this)._division(num);
    (*this)._normalizationChunks();

    if (this->sign == num.sign) {
        (*this).sign = 1;
    }
    else {
        (*this).sign = -1;
    }

    return (*this);
}

void main() {
    ifstream enter;
    enter.open("Vvod1.txt", ios::in);
    string num1, num2;
    enter >> num1;
    enter >> num2;
    enter.close();
    cout << "Number 1: " << num1 << endl;
    cout << "Number 2: " << num2 << endl;
    BigNumber n1(num1);
    BigNumber n2(num2);
    BigNumber n3 = n1 - n2;
    BigNumber n4 = n1 + n2;
    BigNumber n5 = n1 * n2;
    BigNumber n6 = n1 / n2;
    bool n7 = n1 > n2;
    bool n8 = n1 < n2;
    bool n9 = n1 >= n2;
    bool n10 = n1 <= n2;
    n1 -= n2;
    BigNumber n11 = n1;
    n1 += n2;
    BigNumber n12 = n1;
    n1 /= n2;
    BigNumber n13 = n1;
    n1 *= n2;
    BigNumber n14 = n1;
    ++n1;
    BigNumber n15 = n1;
    ++n2;
    BigNumber n16 = n2;
    --n1;
    BigNumber n17 = n1;
    --n2;
    BigNumber n18 = n2;

    cout << "n1 - n2 = " << n3 << endl;
    cout << "n1 + n2 = " << n4 << endl;
    cout << "n1 * n2 = " << n5 << endl;
    cout << "n1 / n2 = " << n6 << endl;
    cout << "n1 > n2 : " << n7 << endl;
    cout << "n1 < n2 : " << n8 << endl;
    cout << "n1 >= n2 : " << n9 << endl;
    cout << "n1 <= n2 : " << n10 << endl;
    cout << "n1 -= n2 : " << n11 << endl;
    cout << "n1 += n2 : " << n12 << endl;
    cout << "n1 /= n2 : " << n13 << endl;
    cout << "n1 *= n2 : " << n14 << endl;
    cout << "++n1 : " << n15 << endl;
    cout << "++n2 : " << n16 << endl;
    cout << "--n1 : " << n17 << endl;
    cout << "--n2 : " << n18 << endl;
}