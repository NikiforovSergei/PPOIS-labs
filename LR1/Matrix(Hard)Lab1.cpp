#include <iostream>
#include "MatrixLMAO.h"

using namespace std;

/// \file Matrix(Hard)Lab1.cpp
/// \brief Главный Файл.


typedef int int32_t;

/// \brief Содержит вызовы функций и "меню" для управления программой.

int main() {
    setlocale(LC_ALL, "RUS");
    int choice, result;
    RealMatrix Matrix1;
    RealMatrix Matrix2;
    RealMatrix Matrix3;
    bool flag = false;
    while (flag == false)
    {
        cout << "1 - Create Matrix1." << endl;
        cout << "2 - Create Matrix2." << endl;
        cout << "3 - ++Matrix1." << endl;
        cout << "4 - ++Matrix2." << endl;
        cout << "5 - --Matrix1." << endl;
        cout << "6 - --Matrix2." << endl;
        cout << "7 - Matrix1 + Matrix2" << endl;
        cout << "8 - Matrix1 - Matrix2" << endl;
        cout << "9 - Matrix1 * Matrix2" << endl;
        cout << "10 - Matrix1 * Указанное вами число" << endl;
        cout << "11 - Matrix2 * Указанное вами число" << endl;
        cout << "12 - Matrix1 / Указанное вами число" << endl;
        cout << "13 - Matrix2 / Указанное вами число" << endl;
        cout << "14 - Matrix1 ^ Указанное вами число" << endl;
        cout << "15 - Matrix2 ^ Указанное вами число" << endl;
        cout << "16 - Matrix1 Determinant " << endl;
        cout << "17 - Matrix2 Determinant" << endl;
        cout << "18 - Matrix1 Norm" << endl;
        cout << "19 - Matrix2 Norm" << endl;
        cin >> choice;
        switch (choice) {

        case 1:
        {
            cin >> Matrix1;
            cout << Matrix1;
        }
        break;
        case 2:
        {
            cin >> Matrix2;
            cout << Matrix2;
        }
        break;
        case 3:
        {
            ++Matrix1;
            cout << Matrix1;
        }
        break;
        case 4:
        {
            ++Matrix2;
            cout << Matrix2;
        }
        break;
        case 5:
        {
            --Matrix1;
            cout << Matrix1;
        }
        break;
        case 6:
        {
            --Matrix2;
            cout << Matrix2;
        }
        break;
        case 7:
        {
            Matrix3 = Matrix1 + Matrix2;
            cout << Matrix3;
        }
        break;
        case 8:
        {
            Matrix3 = Matrix1 - Matrix2;
            cout << Matrix3;
        }
        break;
        case 9:
        {
            Matrix3 = Matrix1 * Matrix2;
            cout << Matrix3;
        }
        break;
        case 10:
        {
            Matrix3 = Matrix1 * 2;
            cout << Matrix3;
        }
        break;
        case 11:
        {
            Matrix3 = Matrix2 * 2;
            cout << Matrix3;
        }
        break;
        case 12:
        {
            Matrix3 = Matrix1 / 2;
            cout << Matrix3;
        }
        break;
        case 13:
        {
            Matrix3 = Matrix1 / 2;
            cout << Matrix3;
        }
        break;
        case 14:
        {
            Matrix3 = Matrix1 ^ 2;
            cout << Matrix3;
        }
        break;
        case 15:
        {
            Matrix3 = Matrix2 ^ 2;
            cout << Matrix3;
        }
        break;
        case 16:
        {
            cout << Matrix1;
            cout << Matrix1.MatrixDeterminant() << endl;
        }
        break;
        case 17:
        {
            cout << Matrix2;
            cout << Matrix2.MatrixDeterminant() << endl;
        }
        break;
        case 18:
        {
            cout << Matrix1;
            cout << Matrix1.MatrixNorm() << endl;
        }
        break;
        case 19:
        {
            cout << Matrix2;
            cout << Matrix2.MatrixNorm() << endl;
        }
        break;

        }
    }
}