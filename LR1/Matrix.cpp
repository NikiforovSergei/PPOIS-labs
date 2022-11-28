#include "Matrix.h"

Matrix::Matrix()
{


	ifstream file("UnitMatrix.txt");

	if (file)
	{
		char temp;
		int N;
		int M;
		file >> temp;
		N = temp - '0';
		file >> temp;
		M = temp - '0';
		this->n = N;
		this->m = M;
		int** mas = new int* [N];
		for (int i = 0; i < N; i++)
		{
			mas[i] = new int[M];
		}
		this->ARR = mas;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				file >> temp;
				this->ARR[i][j] = temp - '0';
			}
		}
		file.close();
	}

}
void Matrix::readMatrix(ifstream& file)
{
	string line;
	getline(file, line);
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->m; j++)
		{
			file >> this->ARR[i][j];
		}
	}
}
void Matrix::print()
{
	for (int i = 0; i < this->n; i++)
	{
		cout << "\n";
		for (int j = 0; j < this->m; j++)
		{
			cout << this->ARR[i][j] << " ";
		}
	}
	cout << endl;
	
}



Matrix& Matrix::operator =(const Matrix& other)
{
	this->n = other.n;
	this->m = other.m;

	if (this->ARR != nullptr)
	{
		delete this->ARR;
	}

	int** mas = new int* [this->n];
	for (int i = 0; i < this->n; i++)
	{
		mas[i] = new int[this->m];
	}
	this->ARR = mas;
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->m; j++)
		{
			this->ARR[i][j] = other.ARR[i][j];
		}
	}
	return *this;
}

int Matrix::getValue(int i, int j)
{
	if ((i >= 0 && j >= 0) and (i < n && j < m))
		return ARR[i][j];
	else
		return 0;
}

bool Matrix::isSquareMatrix()
{
	return ARR != nullptr && n == m;
}

bool Matrix::isDiagonalMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i != j and this->getValue(i, j) != 0) return false;
		}
	}
	return this->isSquareMatrix();
}
bool Matrix::isZeroMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (this->getValue(i, j) != 0) return false;
		}
	}
	return true;
}

bool Matrix::isUnitMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if ((i != j and this->getValue(i, j) != 0) or
				(i == j and this->getValue(i, j) != 1))
				return false;
		}
	}
	return this->isSquareMatrix();
}

bool Matrix::isSymmetricalMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (this->getValue(i, j) != this->getValue(j, i)) return false;
		}
	}
	return this->isSquareMatrix();
}

bool Matrix::isUpperTriangularMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i > j and this->getValue(i, j) != 0) return false;
		}
	}
	return this->isSquareMatrix();
}

bool Matrix::isLowerTriangularMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i < j and this->getValue(i, j) != 0) return false;
		}
	}
	return this->isSquareMatrix();
}
Matrix::Matrix(int N, int M)
{
	this->n = N;
	this->m = M;
	int** mas = new int* [N];
	for (int i = 0; i < N; i++)
	{
		mas[i] = new int[M];
	}
	this->ARR = mas;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{

			this->ARR[i][j] = 0;
		}
	}

}

void Matrix::ChangeString(int number)

{
	Matrix New(number, this->m);
	int q;
	if (number < this->n)
	{
		q = number;
	}
	else
	{
		q = this->n;
	}
	for (int i = 0; i < q; i++)
	{
		for (int j = 0; j < this->m; j++)
		{
			New.ARR[i][j] = this->ARR[i][j];
		}
	}
	New.print();
}

void Matrix::ChangeColumn(int number)

{
	Matrix New(this->n, number);
	int q;
	if (number < this->m)
	{
		q = number;
	}
	else
	{
		q = this->m;
	}
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < q; j++)
		{
			New.ARR[i][j] = this->ARR[i][j];
		}
	}
	New.print();
}

void Matrix::Submatrix(int N, int M)

{
	Matrix New(N, M);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			New.ARR[i][j] = this->ARR[i][j];
		}
	}
	New.print();
}

void Matrix::Trans()

{
	Matrix New(this->m, this->n);
	for (int i = 0; i < this->m; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			New.ARR[i][j] = this->ARR[j][i];
		}
	}
	New.print();
	
}
Matrix::~Matrix()
{
	for (int i = 0; i < n; i++)
		delete[] ARR[i];
	delete[] ARR;

}