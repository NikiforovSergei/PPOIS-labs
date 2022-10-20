/** \file Matrix.h
* Объявляется класс
* Объявляются переменные класса
* Объявляются методы класса
* */
#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Matrix{

private:
	vector<vector<double>> b;
	vector<vector<double>> vec;

public:
	int rows = 0, cols = 0;
	double numb = 0, det = 0;
	vector<vector<double>> a;

	///  \brief Этот метод реализует содание одной матрицы 
    void create_one(Matrix &, int, int);

	///  \brief Этот метод реализует просмотр одной матрицы
	static void show_one(vector<vector<double>>&, int, int);

	///  \brief Этот метод реализует нахождение определителя матрицы 
	static void deter(vector<vector<double>>&, int, double);

	///  \brief Этот метод реализует нахождение определителя матрицы 
	static double cadet(vector<vector<double>>&, int);

	///  \brief Этот метод реализует нахождение определителя матрицы 
	static void new_matr(vector<vector<double>>&, vector<vector<double>>& help, int, int, int);

	///  \brief Этот метод реализует нахождение M-нормы матрицы 
	static void m_norm(vector<vector<double>>&, int, int);

	///  \brief Этот метод реализует нахождение L-нормы матрицы 
	static void l_norm(vector<vector<double>>&, int, int);

	///  \brief Этот метод реализует нахождение K-нормы матрицы 
	static void k_norm(vector<vector<double>>&, int, int);

	///  \brief Данная перегрузка оператора служит для суммы матриц 
	Matrix& operator + (Matrix& right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] + right.a[i][j];
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для суммы матриц
	Matrix& operator += (Matrix& right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] += right.a[i][j];
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для разности матриц
	Matrix& operator - (Matrix& right) {

		//Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] - right.a[i][j];
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для разности матриц
	Matrix& operator -= (Matrix& right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] -= right.a[i][j];
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для суммы матрицы и числа
	Matrix& operator + (double& right) {

		//Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] + right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для суммы матрицы и числа
	Matrix& operator += (double right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] += right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для разности матрицы и числа
	Matrix& operator - (double& right) {

		//Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] - right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для разности матрицы и числа
	Matrix& operator -= (double right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] -= right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для частного матрицы и числа
	Matrix& operator / (double& right) {

		//Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] / right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для частного матрицы и числа
	Matrix& operator /= (double right) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] /= right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для произведения матрицы и числа
	Matrix& operator * (double& right) {

		Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] = a[i][j] * right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для произведения матрицы и числа
	Matrix& operator *= (double& right) {

		Matrix tmp = *this;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->a[i][j] *= right;
			}
		}
		return *(this);
	}

	///  \brief Данная перегрузка оператора служит для произведения матриц
	Matrix& operator * (Matrix& right) {

		b.resize(rows);
		for (int i = 0; i < rows; i++) {
			b[i].resize(cols);
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{

				for (int x = 0; x < cols; x++) {
					b[i][j] += a[i][x] * right.a[x][j];
				}
			}
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				a[i][j] = b[i][j];
			}
		}
		return *this;

	}

	///  \brief Данная перегрузка оператора служит для возведения матрицы в степень
	Matrix& operator ^ (double right) {

		b.resize(rows);
		for (int i = 0; i < rows; i++) {
			b[i].resize(cols);
		}

		vec.resize(rows);
		for (int i = 0; i < rows; i++) {
			vec[i].resize(cols);
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				vec[i][j] = a[i][j];
			}
		}

		for (int k = 0; k < right - 1; k++)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{

					for (int x = 0; x < cols; x++) {
						b[i][j] += vec[i][x] * a[x][j];
					}
					
				}
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					a[i][j] = b[i][j];
					b[i][j] = 0;
				}
			}
		}
		return *this;

	}

	///  \brief Данная перегрузка оператора служит для возведения матрицы в степень
	Matrix& operator ^= (double right) {

		b.resize(rows);
		for (int i = 0; i < rows; i++) {
			b[i].resize(cols);
		}

		vec.resize(rows);
		for (int i = 0; i < rows; i++) {
			vec[i].resize(cols);
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				vec[i][j] = a[i][j];
			}
		}

		for (int k = 0; k < right - 1; k++)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{

					for (int x = 0; x < cols; x++) {
						b[i][j] += vec[i][x] * a[x][j];
					}

				}
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					a[i][j] = b[i] [j];
					b[i][j] = 0;
				}
			}
		}
		return *this;

	}

	Matrix& operator ++ (int) {
		this->a.resize(this->rows + 1);
		for (int i = 0; i < this->rows + 1; i++) {
			this->a[i].resize(this->cols + 1);
		}
		for (int i = 0; i < this->rows + 1; i++) {
			for (int j = 0; j < this->cols + 1; j++) {
				double d;
				cin >> d;
				this->a[i][j] = d;
			}
		}
		return *this;
	}

	Matrix& operator -- (int) {
		this->a.resize(this->rows - 1);
		for (int i = 0; i < this->rows - 1; i++) {
			this->a[i].resize(cols - 1);
		}
		for (int i = 0; i < this->rows - 1; i++) {
			for (int j = 0; j < this->cols - 1; j++) {
				double d;
				cin >> d;
				this->a[i][j] = d;
			}
		}
		return *this;
	}

	/// \brief Данный метод служит для вывода матрицы
	void ShowMatrix()
	{
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < a[i].size(); j++)
			{
				cout << a[i][j] << '\t';
			}
			cout << '\n';
		}
	}
};



