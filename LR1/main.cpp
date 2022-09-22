
#include <iostream>
#include "vector"
#include "cmath"
#include <algorithm>
//#include "gtest.h"
//#include "gmock.h"
using namespace::std;


class Polynomial{
    
private:
    int elem, j;
    vector<int> koef;
public:
    /*!
         \brief количество коэффициентов в многочлене

     */
    int size;
    /*!
         \brief Конструктор класса который принимает вектор коэфициентов

     */
    Polynomial(vector<int> s){ // констурктор
        koef = s;
        size = s.size();
    }
    

    friend ostream &operator<< (ostream &s, Polynomial &c); // перегруженный оператор вывода
    friend istream &operator >> (istream &s, Polynomial &c); // перегруженный оператор ввода
        
    
    int i,n;
    /*!
         \brief метод  получения коэффициента по индексу

     */
    int& operator[](int n){
        if (n<0 or  n > size) {
            cout << "Wrong index";
            exit(1);
        }
        return koef[n];
    }
    
    /*!
         \brief метод вычисления многочлена по заданному аргументу

     */
    double &operator()(int argument)
    {
        double value = 0;
        int degree = size - 1;
        for (i =0 ; i < size; i++) {
            if (i == size - 1 ) {
                value += koef[i];
            } else {
                value += pow(argument, degree) * koef[i];
                degree -= 1;
            }
        }
        return value;
    }
    
    
    /*!
         \brief метод вычитание двух многочленов

     */
    Polynomial operator-(const Polynomial &B) //оператор вычитания А-В
    {
        int i;
        int degree_A = size, degree_B = B.size;
        int j = 0;
        if (size >= B.size)//А>B
        {
            Polynomial Z = *this;
            for (i = 0; i < size; i++) {
                if (degree_A == degree_B) {
                    Z.koef[i] = koef[i] - B.koef[j];
                    j++;
                } else{
                    degree_A--;
                    Z.koef[i] = koef[i];
                }
            }
            return Z;
        }
        else//B>A
        {
            Polynomial Z(B.koef);
            for (i = 0; i < B.size; i++) {
                if (degree_A == degree_B) {
                    Z.koef[i] = koef[j] - B.koef[i];
                    j++;
                } else{
                    degree_B--;
                    Z.koef[i] = -B.koef[i];
                }
            }
            return Z;
        }
    }
    
    
    /*!
         \brief Метод складывает коэффициенты двух многочленов


     */
    
    Polynomial operator+( Polynomial &B){ //оператор  сложения А-В
        int i;
        int degree_A = size, degree_B = B.size;
        int j = 0;
        if (size >= B.size)//А>B
        {
            Polynomial Z = *this;
            for (i = 0; i < size; i++) {
                if (degree_A == degree_B) {
                    Z.koef[i] = koef[i] + B.koef[j];
                    j++;
                } else{
                    degree_A--;
                    Z.koef[i] = koef[i];
                }
            }
            return Z;
        }
        else//B>A
        {
            Polynomial Z(B.koef);
            for (i = 0; i < B.size; i++) {
                if (degree_A == degree_B) {
                    Z.koef[i] = koef[j] + B.koef[i];
                    j++;
                } else{
                    degree_B--;
                    Z.koef[i] = B.koef[i];
                }
            }
            return Z;
        }
    }
    
    /*!
         \brief Метод складывает коэффициенты двух многочленов


     */
    Polynomial operator+=(Polynomial &B){ //оператор  +=
        Polynomial A = *this;
        Polynomial C = A + B;
        vector<int> vec = C.koef;
        return Polynomial(koef = vec);
    }
    
    /*!
         \brief метод вычитание двух многочленов

     */
    Polynomial operator-=(Polynomial &B){ //оператор  -=
        Polynomial A = *this;
        Polynomial C = A - B;
        vector<int> vec = C.koef;
        return Polynomial(koef = vec);
    }
    /*!
         \brief метод умножения двух многочленов

     */
    Polynomial operator*=(Polynomial &B){ //оператор  *=
        Polynomial A = *this;
        Polynomial C = A * B;
        vector<int> vec = C.koef;
        return Polynomial(koef = vec);
    }
    
    /*!
         \brief метод умножения двух многочленов

     */
    Polynomial operator*( Polynomial& B)
    {
        
        reverse(koef.rbegin(), koef.rend());
        reverse(B.koef.rbegin(), B.koef.rend());
        vector<int> Result;
        
        for (int i =0; i <size + B.size -1;i++)
            Result.push_back(0);

        Polynomial temp(Result);

        for (int i = 0; i< size; i++){
            for (int j = 0 ;j < B.size; j++){
                if (j==0 or j==1 or i==1 or i==0){
                    temp.koef[i+j] += koef[i] * B.koef[j];
                } else{
                    temp.koef[i*j] += koef[i] * B.koef[j];
                }
            }
        }
        reverse(koef.rbegin(), koef.rend());
        reverse(B.koef.rbegin(), B.koef.rend());
        reverse(temp.koef.rbegin(), temp.koef.rend());
        return temp;
    }
    
    /*!
         \brief метод деления двух многочленов

     */
    Polynomial operator / ( Polynomial &B) {
        Polynomial A = *this;
        reverse(A.koef.rbegin(), A.koef.rend());
        reverse(B.koef.rbegin(), B.koef.rend());
        if (B.size == 0 or (B.size == 1 and B.koef[0] == 0)){
            cout << "Divison by zero";
            exit(1);
        }
        vector<int> temp;
        int max_degree = B.size - 1;
        int degree_now, result_degree;
        for (int i = 0; i < size- max_degree; i++) {
            temp.push_back(0);
        }
        Polynomial result( temp);
        Polynomial temporary( temp);
        for (int i = 0; i < size; i++) {
            degree_now = size - 1 - i; // какая сейчас степень
            result_degree = degree_now - max_degree; // степень для ответа
            result[result_degree] = A.koef[degree_now] / B.koef[max_degree]; // ответ
            temporary[result_degree] = A.koef[degree_now] / B.koef[max_degree]; // для умножения временный
            A = A - (B * temporary); // вычисление
            
            temporary[result_degree] = 0; // обнуление временного
        }
        // остаток в А
        reverse(result.koef.rbegin(), result.koef.rend());
        return result;
    }
    
    /*!
         \brief метод деления двух многочленов

     */
    Polynomial operator/=(Polynomial &B){ //оператор  +=
        Polynomial A = *this;
        Polynomial C = A / B;
        vector<int> vec = C.koef;
        return Polynomial(koef = vec);
    }
    /*!
         \brief метод сравнения двух многочленов

     */
    bool operator==(Polynomial &B){
        Polynomial A= *this;
        if (A.size != B.size) {
            return false;
        }
        for (int i =0; i < A.size; i++) {
            if (A.koef[i] != B.koef[i])
                return false;
        }
        return true;
    }
    
    /*!
         \brief метод сравнения на неравенство двух многочленов

     */
    bool operator!=(Polynomial &B){
        Polynomial A= *this;
        if (A.size != B.size) {
            return true;
        }
        for (int i =0; i < A.size; i++) {
            if (A.koef[i] == B.koef[i])
                continue;
            else
                return true;
        }
        return false;
    }
    
 
};

/*!
     \brief вывод многочленов

 */
ostream& operator<<(ostream &os, Polynomial &poly)
{
    int degree = poly.size-1;
    for (int i = 0; i < poly.size; i++) {
        if(poly.koef[i] == 0)
            continue;
        else {
            if (i == 0){
                os << poly.koef[i] << "X^" << degree - i;
            }
            else if ((degree - i) == 0) {
                if (poly.koef[i] > 0) {
                    os << '+' << poly.koef[i];
                } else
                    os << poly.koef[i];
            }
            else if (poly.koef[i] > 0){
                os << '+';
                os << poly.koef[i] << "X^" << degree - i;
            }
            else
                os << poly.koef[i] << "X^" << degree - i;
        }
    }
return os;
}

/*!
     \brief ввод многочлена

 */
istream &operator>>(istream &s, Polynomial &c)// перегруженный оператор ввода
    {
        int i;
        for (i = 0; i < c.size; i++)
        {
            s >> c.koef[i];
        }
        return s;
    }




int main(int argc, const char * argv[]) {
    int n;
    vector<int> s= {1,0,6,-9};
    vector<int> k= {1,-3};
    Polynomial one(s), two(k);
    while (true) {
        cout << endl;
        cout << "1 +" << endl;
        cout << "2 -" << endl;
        cout << "3 *" << endl;
        cout << "4 /" << endl;
        cout << "5 ==" << endl;
        cout << "6 != " << endl;
        cout << "7 +=" << endl;
        cout << "8 -= " << endl;
        cout << "9 *=" << endl;
        cout << "10 /=" << endl;
        cout << "11 >>" << endl;
        cout << "12 <<" << endl;
        cout << "13 ()" << endl;
        cout << "Input number ";
        cin >> n;
        if (n == 1) {
            Polynomial C = one + two;
            cout << C;
        } else if (n == 2){
            Polynomial C = one - two;
            cout << C;
        } else if (n == 3){
            Polynomial C = one * two;
            cout << C;
        } else if (n == 4){
            Polynomial C = one / two;
            cout << C;
        } else if (n == 5){
            bool C = one == two;
            cout << C;
        } else if (n == 6){
            bool C = one != two;
            cout << C;
        } else if (n == 7){
            Polynomial C = one;
            C += two;
            cout << C;
        } else if (n == 8){
            Polynomial C = one;
            C -= two;
            cout << C;
        } else if (n == 9){
            Polynomial C = one;
            C *= two;
            cout << C;
        } else if (n == 10){
            Polynomial C = one;
            C /= two;
            cout << C;
        } else if (n == 11){
            int k;
            cout << "1 - one" << endl;
            cout << "2 - two" << endl;
            cin >> k;
            if (k == 1) {
                cin >> one;
            } else
                cin >> two;
        } else if (n == 12){
            cout << "One - " << one << endl;
            cout << "Two - " << two << endl;
        } else if (n == 13){
            int arg;
            cout << "Input argument" << endl;
            cin >> arg;
            cout << "One - " << one(arg) << endl;
            cout << "Two - " << two(arg) << endl;
        }
    }
        return 0;
}

