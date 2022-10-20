/** \file Matrix.cpp
* Реализуются методы класса
* */
#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

///  \code 
void Matrix::create_one(Matrix &mat, int row, int col) {
	mat.a.clear();
	mat.a.resize(row);
	for (int i = 0; i < row; i++) {
		mat.a[i].resize(col);
	}

	vector<double> help;
	cout << "Введите элементы матрицы:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double c;
			cin >> c;
			help.push_back(c);
			mat.a[i][j] = help[0];
			help.clear();
		}
	}

}

/// \code
void Matrix::show_one(vector<vector<double>>& a, int row, int col) {

	cout << "Вывод матрицы:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}

}

/// \code
void Matrix::new_matr(vector<vector<double>>& a, vector<vector<double>>& help, int i, int j, int row) {
    int k1, k2, d1, d2;
    d1 = 0;
    for (k1 = 0; k1 < row - 1; k1++) {
		if (k1 == i) {
			d1 = 1;
		}
        d2 = 0;
        for (k2 = 0; k2 < row - 1; k2++) {
			if (k2 == j) {
				d2 = 1;
			}
            help[k1][k2] = a[k1 + d1][k2 + d2];
        }
    }
}

/// \code
double Matrix::cadet(vector<vector<double>>& a, int row) {
    int j, k, n;
	double det;
	vector<vector<double>> help;
    help.resize(row);
    for (int i = 0; i < row; i++)
        help[i].resize(row);
    j = 0; det = 0;
    k = 1; 
    n = row - 1;
    if (row < 1) cout << "Определитель вычислить невозможно!";
    if (row == 1) {
        det = a[0][0];
        return det;
    }
    if (row == 2) {
		det = a[0][0] * a[1][1] - (a[1][0] * a[0][1]);
        return det;
    }
    if (row > 2) {
        for (int i = 0; i < row; i++) {
            Matrix::new_matr(a, help, i, 0, row);
            cout << a[i][j] << endl;
            Matrix::show_one(help, n, n);
            det = det + k * a[i][0] * cadet(help, n);
            k = -k;
        }
    }
    return det;
}

/// \code
void Matrix::deter(vector<vector<double>>& a, int row, double det) {
	det = Matrix::cadet(a, row);
	cout << "Определитель матрицы равен det = " << det << endl;
}

/// \code
void Matrix::m_norm(vector<vector<double>>& a, int row, int col) {

	vector<double> res;
	res.resize(row);
	double cou = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cou += a[i][j] ;
		}
		res[i] = cou;
		cou = 0;
	}

	double max = res[0];
	for (int i = 0; i < row; i++)
	{
		if (max < res[i]) {
			max = res[i];
		}
	}

	cout << "M-норма матрицы:" << endl;
	cout << max << endl;
	show_one(a, row, col);

}

/// \code
void Matrix::l_norm(vector<vector<double>>& a, int row, int col) {

	vector<double> res;
	res.resize(row);
	double cou = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cou += a[j][i];
		}
		res[i] = cou;
		cou = 0;
	}

	double max = res[0];
	for (int i = 0; i < row; i++)
	{
		if (max < res[i]) {
			max = res[i];
		}
	}

	cout << "L-норма матрицы:" << endl;
	cout << max << endl;
	show_one(a, row, col);

}

/// \code
void Matrix::k_norm(vector<vector<double>>& a, int row, int col) {

	double cou = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cou += pow(a[i][j], 2);
		}
	}

	cou = sqrt(cou);

	cout << "K-норма матрицы:" << endl;
	cout << cou << endl;
	show_one(a, row, col);

}
