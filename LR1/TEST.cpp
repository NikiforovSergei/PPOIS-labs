#include <iostream>
#include <ostream>
#include "Header.h"

using namespace std;

/// \file
/// \brief Файл TEST с реализацией консольног меню для пользователя и разными действиями над матрицами.

int main()
{
    Matrix A, B, C;
    Solution Way;

    while (true)
    {
        switch (Way.Get_1())
        {
        case 1:
        {
            cin >> A;
            cout << A;
        }
        break;

        case 2:
        {
            cin >> B;
            cout << B;
        }
        break;

        case 3:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                ++A;
                cout << A;
            }
            break;

            case 2:
            {
                ++B;
                cout << B;
            }
            break;
            }
        }
        break;

        case 4:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                --A;
                cout << A;
            }
            break;

            case 2:
            {
                --B;
                cout << B;
            }
            break;
            }
        }
        break;

        case 5:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                C = A + B;
                cout << C;
            }
            break;

            case 2:
            {
                C = A - B;
                cout << C;
            }
            break;
            }
        }
        break;

        case 6:
        {
            C = A * B;
            cout << C;
        }
        break;

        case 7:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                C = A * 2;
                cout << C;
            }
            break;

            case 2:
            {
                C = B * 2;
                cout << C;
            }
            break;
            }
        }
        break;

        case 8:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                C = A / 2;
                cout << C;
            }
            break;

            case 2:
            {
                C = B / 2;
                cout << C;
            }
            break;
            }
        }
        break;

        case 9:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                C = A ^ 2;
                cout << C;
            }
            break;

            case 2:
            {
                C = B ^ 2;
                cout << C;
            }
            break;
            }
        }
        break;

        case 10:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                cout << A;
                cout << A.DeterminantOfMatrix();
            }
            break;

            case 2:
            {
                cout << B;
                cout << B.DeterminantOfMatrix();
            }
            break;
            }
        }
        break;

        case 11:
        {
            switch (Way.Get_2())
            {
            case 1:
            {
                cout << A;
                A.NormOfMatrix();
            }
            break;

            case 2:
            {
                cout << A;
                B.NormOfMatrix();
            }
            break;
            }
        }
        break;

        default:
            break;
        }
    }

    return 0;
}