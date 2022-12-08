#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;


/// \file lab1(ppopis).cpp
/// 
/// \brief Header-file,содержащий в себе объявление класса,функций,переменных.

/*!
            \brief Класс,реализующий трехмерный вектор
            \authors Абдуллаев Амирхон
            \version the latest one ^_^
            \date 20.11.2022
*/
class Vector
{
private:
    /// \brief Переменные,хранящая в себе координаты векторов.
    double X, Y, Z;

public:
    
    Vector()
    {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

   
    Vector(double x, double y, double z)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }

    /// \brief Функция вычисления длины вектора.
    double GetLength()
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }
    
    /// \brief Функция создания Vector #3(созданный по итогу действий над векторами)
    void Print()
    {
        cout << "Vector #3(" << X << "," << Y << "," << Z << ")" << endl;
    }
    /// \brief Функция перегрузки оператора сложения (используется для сложения 2-х векторов).
    /// \param В параметры получает ссылку на вектор.
    Vector operator +(Vector r)
    {
        return Vector(this->X + r.X, this->Y + r.Y, this->Z + r.Z);
    }
    /// \brief Функция перегрузки оператора разности (используется для разности 2-х векторов).
    /// \param В параметры получает ссылку на вектор.
    Vector operator -(Vector r)
    {
        return Vector(this->X - r.X, this->Y - r.Y, this->Z - r.Z);
    }
    /// \brief Функция перегрузки оператора произведения (используется для произведения 2-х векторов).
    /// \param В параметры получает ссылку на вектор.
    Vector operator *(Vector r)
    {
        return Vector(this->X * r.X , this->Y * r.Y , this->Z * r.Z);
    }
    /// \brief Функция перегрузки оператора деления (используется для деления 2-х векторов).
    /// \param В параметры получает ссылку на вектор.
    Vector operator /(Vector r)
    {
        return Vector(this->X / r.X, this->Y / r.Y, this->Z / r.Z);
    }
    /// \brief Функция перегрузки оператора нахождения cos угла между векторами (используется для нахождения cos угла меду 2-мя векторами).
    /// \param В параметры получает ссылку на вектор.
    double operator ^(Vector r)
    {
        return((this->X * r.X+ this->Y * r.Y+this->Z * r.Z)/(X * X + Y * Y + Z * Z));
    }
};


/// \brief Содержит меню для управления программой

int main()
{
    setlocale(LC_ALL, "rus");

    double  a = 1, cordv1[3], cordv2[3];
    int m = 0, i = 0;

    for (i = 0; i < 3; i++) {
        cout << "Введите " << i + 1 << "-ую координату первого вектора: ";
        cin >> cordv1[i];
    }
    cout << endl;
    for (i = 0; i < 3; i++) {
        cout << "Введите " << i + 1 << "-ую координату второго вектора: ";
        cin >> cordv2[i];
    }
    system("cls");

    Vector V1(cordv1[0], cordv1[1], cordv1[2]);
    Vector V2(cordv2[0], cordv2[1], cordv2[2]);
    Vector V3;

    while (a == 1) {
        cout << "Vector #1(";
        for (i = 0; i < 3; i++) {
            if (i != 2) { cout << cordv1[i] << ", "; }
            else cout << cordv1[i];
        }cout << ") " << endl << endl;

        cout << "Vector #2(";
        for (i = 0; i < 3; i++) {
            if (i != 2) { cout << cordv2[i] << ", "; }
            else cout << cordv2[i];
        }cout << ") " << endl << endl;

        cout << endl << "1. Получить сложение векторов." << endl;
        cout << "2. Получить разность векторов." << endl;
        cout << "3. Получить скалярное произведение векторов." << endl;
        cout << "4. Получить частное двух векторов." << endl;
        cout << "5. Получить вектор умноженный на n." << endl;
        cout << "6. Получить значение косинуса угла между этими векторами." << endl;
        cout << "7. Получение длины векторов" << endl;
        cout << "8. Сравнение длин двух векторов" << endl;
        cout << "9. Выход из программы." << endl << endl;
        cout << "Введите значение -> ";
        cin >> m;
        cout << endl;

        switch (m)
        {
        case 1:
            cout << "Вектор, образовавшийся путём сложения введённых векторов: ";
            V3 = V1 + V2;
            V3.Print();
            _getch();
            system("cls");
            a = 1;
            break;
        case 2:
            cout << "Вектор, образовавшийся путём вычитания введённых векторов: ";
            V3 = V1 - V2;
            V3.Print();
            _getch();
            system("cls");
            a = 1;
            break;
        case 3:
            cout << endl << "Произведение введенных векторов = ";
            V3= V1 * V2;
            V3.Print();
            _getch();
            system("cls");
            a = 1;
            break;
        case 4:
            int dev;
            cout << "Деление двух векторов=";
            cout << "V1/V2"<<endl;
            cout << "V2/V1" << endl;
            cin >> dev;
            switch (dev)
            {
            case 1:
                V3 = V1 / V2;
                V3.Print();
                _getch();
                system("cls");
                a = 1;
                break;
            case 2:
                V3 = V2 / V1;
                V3.Print();
                _getch();
                system("cls");
                a = 1;
                break;
            }
            break;
        case 5:
            int n, v, z1, z2, z3, v1, v2, v3;
            cout << "Введите число n:";
            cin >> n;

            z1 = n * cordv1[0];
            z2 = n * cordv1[1];
            z3 = n * cordv1[2];

            v1 = n * cordv2[0];
            v2 = n * cordv2[1];
            v3 = n * cordv2[2];

            cout << "Первый вектор умноженный на n=(" << z1 << "," << z2 << "," << z3 << ")" << endl;
            cout << "Второй веткор умноженный на n=(" << v1 << "," << v2 << "," << v3 << ")";
            _getch();
            system("cls");
            a = 1;
            break;
        case 6:
            cout << "Косинус угла между векторами = "  << endl;
            double cos;
            cos= V2 ^ V1;
            cout << cos<<endl<<
            _getch();
            system("cls");
            a = 1;
            break;
            _getch();
            system("cls");
            a = 1;
            break;
        case 7:
            cout << "Введите номер вектора: ";
            int b; cin >> b; cout << endl;
            switch (b)
            {
            case 1:

                cout << "Длинна первого вектора: " << V1.GetLength() << endl;
                break;
            case 2:
                cout << "Длинна второго вектора: " << V2.GetLength() << endl;
                break;
            default:
                cout << "Вы ввели неверное значение!" << endl << "Вектора всего два. Введите '1' либо '2'." << endl << endl;
                a = 1;
                break;
            }
            _getch();
            system("cls");
            a = 1;
            break;
        case 8:
    
            if(V1.GetLength() > V2.GetLength()) 
            {
                cout << "Vector1("<< V1.GetLength()<<")>Vector2("<< V2.GetLength()<<")";
            }
            else
            {
                cout << "Vector2(" << V2.GetLength() << ")>Vector1(" << V1.GetLength() << ")";
            }
            _getch();
            system("cls");
            a = 1;
            break;
        case 9:
            cout << "Завершение программы" << endl;
            _getch();
            system("cls");
            a = 0;
            break;
        default:
            cout << "Вы ввели неверное значение!" << endl;
            system("pause");
            system("cls");
            a = 1;
            break;
        }
    }
    return 0;
}