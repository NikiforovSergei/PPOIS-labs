#include <iostream>
#include <cmath>
#include "MatrixLMAO.h"

using namespace std;

/// \file MatrixLMAO.cpp
/// \brief Содержит реализацию всех вышеописанных функций в Хеддер-Файле.

RealMatrix::RealMatrix()
{
	this->lines = 0;
	this->columns = 0;

	this->ifmatrixreturns = false;
	this->ismatrixexist = false;
}

RealMatrix::RealMatrix(int lines, int columns)
{
	this->lines = lines;
	this->columns = columns;

	this->Memory = new int* [this->lines];
	for (int i = 0; i < this->lines; i++)
	{
		this->Memory[i] = new int[this->columns];
	}

	this->ifmatrixreturns = false;
	this->ismatrixexist = false;
}

RealMatrix::~RealMatrix()
{
	if (!this->ifmatrixreturns && this->ismatrixexist)
	{
		for (int i = 0; i < this->lines; i++)
			delete[] this->Memory[i];

		delete[] this->Memory;
		this->ismatrixexist = false;
	}
}

void RealMatrix::ArrayWithMemoryCreator()
{
	this->~RealMatrix();

	this->Memory = new int* [this->lines];
	for (int i = 0; i < this->lines; i++)
		this->Memory[i] = new int[this->columns];

	this->ismatrixexist = true;
}

RealMatrix& RealMatrix::operator = (const RealMatrix& Title)
{
	this->~RealMatrix();

	this->lines = Title.lines;
	this->columns = Title.columns;

	this->ArrayWithMemoryCreator();

	for (int i = 0; i < this->lines; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->Memory[i][j] = Title.Memory[i][j];
		}
	}

	this->ismatrixexist = Title.ismatrixexist;

	return *this;

}

RealMatrix RealMatrix::operator+ (RealMatrix& Title)
{
	if (this->lines == Title.lines && this->columns == Title.columns)
	{
		RealMatrix Temp(this->lines, this->columns);
		for (int i = 0; i < Temp.lines; i++)
		{
			for (int j = 0; j < Temp.lines; j++)
			{
				Temp.Memory[i][j] = this->Memory[i][j] + Title.Memory[i][j];
			}
		}

		Temp.ifmatrixreturns = true;

		return Temp;
	}
	else
	{
		cout << "The program can't figure it out\n";
		cout << "Matrixes have different sizes\n";
		exit(0);
	}
}

RealMatrix RealMatrix::operator- (RealMatrix& Name)
{
	if (this->lines == Name.lines && this->columns == Name.columns)
	{
		RealMatrix Temp(this->lines, this->columns);
		for (int i = 0; i < Temp.lines; i++)
		{
			for (int j = 0; j < Temp.columns; j++)
			{
				Temp.Memory[i][j] = this->Memory[i][j] - Name.Memory[i][j];
			}
		}

		Temp.ifmatrixreturns = true;

		return Temp;
	}
	else
	{
		cout << "The program can't figure it out\n";
		cout << "Matrixes have different sizes\n";
		exit(0);
	}
}

RealMatrix& RealMatrix::operator++ ()
{
	RealMatrix Temp(this->lines + 1, this->columns + 1);

	for (int i = 0; i < Temp.lines; i++)
	{
		for (int j = 0; j < Temp.columns; j++)
		{
			if (i + 1 == Temp.lines || j + 1 == Temp.columns)
			{
				Temp.Memory[i][j] = 0;
				continue;
			}

			Temp.Memory[i][j] = this->Memory[i][j];
		}
	}
	*this = Temp;

	return *this;
}

RealMatrix& RealMatrix::operator-- ()
{
	RealMatrix Temp(this->lines - 1, this->columns - 1);

	for (int i = 0; i < Temp.lines; i++)
	{
		for (int j = 0; j < Temp.columns; j++)
		{
			Temp.Memory[i][j] = this->Memory[i][j];
		}
	}
	*this = Temp;

	return *this;
}

RealMatrix RealMatrix::operator* (int value)
{
	RealMatrix Temp(this->lines, this->columns);
	for (int i = 0; i < Temp.lines; i++)
	{
		for (int j = 0; j < Temp.columns; j++)
		{
			Temp.Memory[i][j] = this->Memory[i][j] * value;
		}
	}
	Temp.ifmatrixreturns = true;

	return Temp;
}

RealMatrix RealMatrix::operator/ (int value)
{
	RealMatrix Temp(this->lines, this->columns);
	for (int i = 0; i < Temp.lines; i++)
	{
		for (int j = 0; j < Temp.columns; j++)
		{
			Temp.Memory[i][j] = this->Memory[i][j] / value;
		}
	}

	Temp.ifmatrixreturns = true;

	return Temp;
}

RealMatrix RealMatrix::operator* (RealMatrix& Name)
{
	if (this->lines == Name.lines)
	{
		RealMatrix Temp(this->lines, this->columns);
		for (int i = 0; i < this->lines; i++)
		{
			for (int j = 0; j < Name.columns; j++)
			{
				Temp.Memory[i][j] = 0;

				for (int m = 0; m < this->columns; m++)
				{
					Temp.Memory[i][j] += this->Memory[i][m] * Name.Memory[m][j];
				}
			}
		}

		Temp.ifmatrixreturns = true;

		return Temp;
	}
	else
	{
		cout << "The program can't figure it out\n";
		cout << "Matrixes have inappropriate sizes\n";
		exit(0);
	}
}

RealMatrix RealMatrix::operator^ (int value)
{
	int i = 0;
	RealMatrix Temp;

	Temp = *this;

	do {
		Temp = Temp * *this;

		i++;
	} while (i + 1 < value);

	Temp.ifmatrixreturns = true;

	return Temp;
}

double RealMatrix::MatrixDeterminant()
{
	if (this->lines == this->columns)
	{
		if (this->lines < 1)
		{
			cout << "The determinant cannot be calculated\n";
			cout << "Matrix size is smaller than [1]x[1]\n";
			exit(0);
		}

		if (this->lines == 1)
		{
			return this->Memory[0][0];
		}

		if (this->lines == 2)
		{
			return this->Memory[0][0] * this->Memory[1][1] - this->Memory[1][0] * this->Memory[0][1];
		}

		if (this->lines > 2)
		{
			RealMatrix Temp(this->lines - 1, this->lines - 1);

			double determinant = 0;
			int a, b;

			for (int i = 0; i < this->lines; i++)
			{
				a = 0;

				for (int j = 1; j < this->lines; j++)
				{
					b = 0;

					for (int k = 0; k < this->lines; k++)
					{
						if (k != i)
						{
							Temp.Memory[a][b] = this->Memory[j][k];

							b++;
						}
					}

					a++;
				}

				Temp.lines = this->lines - 1;
				Temp.columns = this->lines - 1;

				determinant += pow(-1, (double)i + 2) * this->Memory[0][i] * Temp.MatrixDeterminant();
			}

			return determinant;
		}
	}
	else
	{
		cout << "The program can't figure it out\n";
		cout << "The matrix must be square\n";
		exit(0);
	}
}

double RealMatrix::MatrixNorm()
{
	if (this->lines > 0 && this->columns > 0)
	{
		int NormNumber = 1;
		double amount = 0, max;

		if (NormNumber == 1)
		{
			double* Temp = new double[lines];

			for (int i = 0; i < this->lines; i++)
			{
				for (int j = 0; j < this->columns; j++)
				{
					amount += abs(this->Memory[i][j]);
				}

				Temp[i] = amount;
				amount = 0;
			}

			max = Temp[0];
			for (int i = 0; i < this->lines; i++)
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
			double* Temp = new double[columns];

			for (int i = 0; i < this->lines; i++)
			{
				for (int j = 0; j < this->lines; j++)
				{
					amount += abs(this->Memory[j][i]);
				}

				Temp[i] = amount;
				amount = 0;
			}

			max = Temp[0];
			for (int i = 0; i < this->columns; i++)
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
			for (int i = 0; i < this->lines; i++)
			{
				for (int j = 0; j < this->columns; j++)
				{
					amount += pow(abs(this->Memory[i][j]), 2);
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

ostream& operator<< (ostream& cout, RealMatrix& Title)
{
	for (int i = 0; i < Title.lines; i++)
	{
		for (int j = 0; j < Title.columns; j++)
		{
			cout << "[ " << Title.Memory[i][j] << " ]";
		}

		cout << endl;
	}

	cout << endl;

	return cout;
}

istream& operator>> (istream& cin, RealMatrix& Title)
{
	Title.~RealMatrix();

	cout << "Enter the columns of the matrix-> ";
	cin >> Title.columns;

	cout << "Enter the lines of the matrix-> ";
	cin >> Title.lines;

	cout << endl;

	RealMatrix Temp(Title.lines, Title.columns);

	Title = Temp;
	for (int i = 0; i < Title.lines; i++)
	{
		for (int j = 0; j < Title.columns; j++)
		{
			Title.Memory[i][j] = rand() % 4;
		}
	}

	return cin;
}
