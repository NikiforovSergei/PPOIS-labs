#include <iostream>
#include <cmath>
#include "Header.h"

using namespace std;

/// \file
/// \brief ‘айл Source с реализацией всего, что было объ€влено в Header.

void Solution::Menu()
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
}

int Solution::Get_1()
{
    cout << "\n\n Create Matrix A - 1\n Create Matrix B - 2\n ++A or ++B - 3\n --A or --B - 4\n A+B or A-B - 5\n A*B - 6\n A*2 or B*2 - 7\n A/2 or B/2 - 8\n A^2 or B^2 - 9\n Determinant of matrix A or B - 10\n Norm of matrix A or B - 11\n\n";
    cout << "Enter way -> ";

    cin >> way;

    cout << "\n";

    return way;
}

int Solution::Get_2()
{
    cout << "";
    cout << "Enter way (1 or 2) -> ";
    cin >> way;
    cout << "\n";
    return way;
}

Matrix::Matrix()
{
    this->size_x = 0;
    this->size_y = 0;

    this->ReturnExistTemp = false;
    this->MatrixExist = false;
}

Matrix::Matrix(int size_x, int size_y)
{
    this->size_x = size_x;
    this->size_y = size_y;

    this->Content = new int* [this->size_x];
    for (int i = 0; i < this->size_x; i++)
    {
        this->Content[i] = new int [this->size_y];
    }

    this->ReturnExistTemp = false;
    this->MatrixExist = true;
}

Matrix::~Matrix()
{
    if (!this->ReturnExistTemp && this->MatrixExist)
    {
        for (int i = 0; i < this->size_x; i++)
        {
            delete[] this->Content[i];
        }

        delete[] this->Content;

        this->MatrixExist = false;
    }
}

void Matrix::DynamicArray()
{
    this->~Matrix();

    this->Content = new int* [this->size_x];
    for (int i = 0; i < this->size_x; i++)
    {
        this->Content[i] = new int[this->size_y];
    }

    this->MatrixExist = true;
}

double Matrix::DeterminantOfMatrix()
{
    if (this->size_x == this->size_y)
    {
        if (this->size_x < 1)
        {
            cout << "The determinant cannot be calculated\n";
            cout << "Matrix size is smaller than [1]x[1]\n";
            exit(0);
        }

        if (this->size_x == 1)
        {
            return this->Content[0][0];
        }

        if (this->size_x == 2)
        {
            return this->Content[0][0] * this->Content[1][1] - this->Content[1][0] * this->Content[0][1];
        }

        if (this->size_x > 2)
        {
            Matrix Temp(this->size_x - 1, this->size_x - 1);

            double determinant = 0;
            int a, b;

            for (int i = 0; i < this->size_x; i++)
            {
                a = 0;

                for (int j = 1; j < this->size_x; j++)
                {
                    b = 0;

                    for (int k = 0; k < this->size_x; k++)
                    {
                        if (k != i)
                        {
                            Temp.Content[a][b] = this->Content[j][k];

                            b++;
                        }
                    }

                    a++;
                }

                Temp.size_x = this->size_x - 1;
                Temp.size_y = this->size_x - 1;

                determinant += pow(-1, (double)i + 2) * this->Content[0][i] * Temp.DeterminantOfMatrix();
            } 

            return determinant;
        }
    }
    else
    {
        cout << "The determinant cannot be calculated\n";
        cout << "The width and height of the matrix is different\n";
        exit(0);
    }
}

void Matrix::NormOfMatrix()
{
    if (this->size_x > 0 && this->size_y > 0)
    {
        int NormNumber = 1;
        double amount = 0, max;

        if (NormNumber == 1)
        {
            double* Temp = new double [size_x];

            for (int i = 0; i < this->size_x; i++)
            {
                for (int j = 0; j < this->size_y; j++)
                {
                    amount += abs(this->Content[i][j]);
                }

                Temp[i] = amount;
                amount = 0;
            }

            max = Temp[0];
            for (int i = 0; i < this->size_x; i++)
            {
                if (Temp[i] > max)
                {
                    max = Temp[i];
                }
            }

            cout << "Norm #1 -> " << max;
            NormNumber = 2;

            delete[] Temp;
        }

        if (NormNumber == 2)
        {
            double* Temp = new double [size_y];

            for (int i = 0; i < this->size_y; i++)
            {
                for (int j = 0; j < this->size_x; j++)
                {
                    amount += abs(this->Content[j][i]);
                }

                Temp[i] = amount;
                amount = 0;
            }

            max = Temp[0];
            for (int i = 0; i < this->size_y; i++)
            {
                if (Temp[i] > max)
                {
                    max = Temp[i];
                }
            }

            cout << "\nNorm #2 -> " << max;
            NormNumber = 3;

            delete[] Temp;
        }

        if (NormNumber == 3)
        {
            for (int i = 0; i < this->size_x; i++)
            {
                for (int j = 0; j < this->size_y; j++)
                {
                    amount += pow(abs(this->Content[i][j]), 2);
                }
            }

            max = sqrt(amount);

            cout << "\nNorm #3 -> " << max;
        }
    }
    else
    {
        cout << "The norm cannot be calculated\n";
        cout << "Matrix size is smaller than [1]x[1]\n";
        exit(0);
    }
}

ostream& operator<< (ostream& cout, Matrix& Name)
{
    for (int i = 0; i < Name.size_x; i++)
    {
        for (int j = 0; j < Name.size_y; j++)
        {
            cout << "[ " << Name.Content[i][j] << " ]";
        }

        cout << endl;
    }

    cout << endl;

    return cout;
}

istream& operator>> (istream& cin, Matrix& Name)
{
    Name.~Matrix();

    cout << "Enter the length of the matrix-> ";
    cin >> Name.size_y;

    cout << "Enter the width of the matrix-> ";
    cin >> Name.size_x;

    cout << endl;

    Matrix Temp(Name.size_x, Name.size_y);

    Name = Temp;
    for (int i = 0; i < Name.size_x; i++)
    {
        for (int j = 0; j < Name.size_y; j++)
        {
            Name.Content[i][j] = rand() % 4;
        }
    }

    return cin;
}

Matrix& Matrix::operator= (const Matrix& Name)
{
    this->~Matrix();

    this->size_x = Name.size_x;
    this->size_y = Name.size_y;

    this->DynamicArray();

    for (int i = 0; i < this->size_x; i++)
    {
        for (int j = 0; j < this->size_y; j++)
        {
            this->Content[i][j] = Name.Content[i][j];
        }
    }

    this->MatrixExist = Name.MatrixExist;

    return *this;
}

Matrix Matrix::operator+ (Matrix& Name)
{
    if (this->size_x == Name.size_x && this->size_y == Name.size_y)
    {
        Matrix Temp(this->size_x, this->size_y);
        for (int i = 0; i < Temp.size_x; i++)
        {
            for (int j = 0; j < Temp.size_y; j++)
            {
                Temp.Content[i][j] = this->Content[i][j] + Name.Content[i][j];
            }
        }

        Temp.ReturnExistTemp = true;

        return Temp;
    }
    else
    {
        cout << "The amount cannot be calculated\n";
        cout << "Matrixes have different sizes\n";
        exit(0);
    }
}

Matrix Matrix::operator- (Matrix& Name)
{
    if (this->size_x == Name.size_x && this->size_y == Name.size_y)
    {
        Matrix Temp(this->size_x, this->size_y);
        for (int i = 0; i < Temp.size_x; i++)
        {
            for (int j = 0; j < Temp.size_y; j++)
            {
                Temp.Content[i][j] = this->Content[i][j] - Name.Content[i][j];
            }
        }

        Temp.ReturnExistTemp = true;

        return Temp;
    }
    else
    {
        cout << "The difference cannot be calculated\n";
        cout << "Matrixes have different sizes\n";
        exit(0);
    }
}

Matrix& Matrix::operator++ ()
{
    Matrix Temp(this->size_x + 1, this->size_y + 1);

    for (int i = 0; i < Temp.size_x; i++)
    {
        for (int j = 0; j < Temp.size_y; j++)
        {
            if (i + 1 == Temp.size_x || j + 1 == Temp.size_y)
            {
                Temp.Content[i][j] = 0;
                continue;
            }

            Temp.Content[i][j] = this->Content[i][j];
        }
    }

    *this = Temp;

    return *this;
}

Matrix& Matrix::operator-- ()
{
    Matrix Temp(this->size_x - 1, this->size_y - 1);

    for (int i = 0; i < Temp.size_x; i++)
    {
        for (int j = 0; j < Temp.size_y; j++)
        {
            Temp.Content[i][j] = this->Content[i][j];
        }
    }

    *this = Temp;

    return *this;
}

Matrix Matrix::operator* (int value)
{
    Matrix Temp(this->size_x, this->size_y);
    for (int i = 0; i < Temp.size_x; i++)
    {
        for (int j = 0; j < Temp.size_y; j++)
        {
            Temp.Content[i][j] = this->Content[i][j] * value;
        }
    }

    Temp.ReturnExistTemp = true;

    return Temp;
}

Matrix Matrix::operator/ (int value)
{
    Matrix Temp(this->size_x, this->size_y);
    for (int i = 0; i < Temp.size_x; i++)
    {
        for (int j = 0; j < Temp.size_y; j++)
        {
            Temp.Content[i][j] = this->Content[i][j] / value;
        }
    }

    Temp.ReturnExistTemp = true;

    return Temp;
}

Matrix Matrix::operator* (Matrix& Name)
{
    if (this->size_x == Name.size_y)
    {
        Matrix Temp(this->size_x, this->size_y);
        for (int i = 0; i < this->size_x; i++)
        {
            for (int j = 0; j < Name.size_y; j++)
            {
                Temp.Content[i][j] = 0;

                for (int k = 0; k < this->size_y; k++)
                {
                    Temp.Content[i][j] += this->Content[i][k] * Name.Content[k][j];
                }
            }
        }

        Temp.ReturnExistTemp = true;

        return Temp;
    }
    else
    {
        cout << "The product cannot be calculated\n";
        cout << "Matrixes have inappropriate sizes\n";
        exit(0);
    }
}

Matrix Matrix::operator^ (int value)
{
    int i = 0;
    Matrix Temp;

    Temp = *this;

    do {
        Temp = Temp * *this;

        i++;
    } while (i + 1 < value);

    Temp.ReturnExistTemp = true;

    return Temp;
}
