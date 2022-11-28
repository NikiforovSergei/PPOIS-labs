#include "Matrix.h"
#include <iostream>


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream file;
	Matrix S;
	

	int kod, n, m,h;
	do
	{
		cout << endl << "0-Выберите матрицу" << endl << "1-характеристика матрицв" << endl << "2-транспонирование матрицы" << endl;
		cout << "3-изменение числа строк" << endl << "4-изменение числа столбцов" << endl << "5-извлечение подматрицы" << endl;
		cin >> kod;
		switch (kod)
		{
		case 0:
		{
			cout << endl << "Выберите матрицу:" << endl << "1-Квадратная матрица" << endl << "2-Симметричная матрица" << endl << "3-Единичная матрица"
				<< endl << "4-Нулевая матрица" << endl << "5-Диагональная матрица" << endl << "6-Верхняя треугольная матрица"
				<< endl << "7-Нижняя треугольная матрица" << endl;
			cin >> h;

			switch (h)
			{
			case 1:
			{
				file.open("SquareMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 2:
			{
				file.open("SymmetricalMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 3:
			{
				file.open("UnitMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 4:
			{
				file.open("ZeroMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 5:
			{
				file.open("DiagonalMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 6:
			{
				file.open("UpperTriangularMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			case 7:
			{
				file.open("LowerTriangularMatrix.txt");
				S.readMatrix(file);
				S.print();
				break;
			}
			}
			break;
		}
		case 1:
		{
			cout << "Матрица:" << std::endl;
			int counter = 1;
			if (S.isSquareMatrix())
			{
				std::cout << counter << ". квадратная" << std::endl;
				counter++;
			}
			if (S.isSymmetricalMatrix()) {
				std::cout << counter << ". симметричная" << std::endl;
				counter++;
			}
			if (S.isUnitMatrix()) {
				std::cout << counter << ". единичная" << std::endl;
				counter++;
			}
			if (S.isZeroMatrix()) {
				std::cout << counter << ". нулевая" << std::endl;
				counter++;
			}
			if (S.isDiagonalMatrix()) {
				std::cout << counter << ". диагональная" << std::endl;
				counter++;
			}
			if (S.isUpperTriangularMatrix()) {
				std::cout << counter << ". верхняя треугольная" << std::endl;
				counter++;
			}
			if (S.isLowerTriangularMatrix()) {
				std::cout << counter << ". нижняя треугольная" << std::endl;
				counter++;
			}
			cout << endl;
			break;
		}
		case 2:
		{
			S.Trans();
			break;
		}
		case 3:
		{
			cout << "введите число строк" << endl;
			cin >> n;
			S.ChangeString(n);
			
			break;
		}
		case 4:
		{
			cout << "введите число столбцов" << endl;
			cin >> n;
			S.ChangeColumn(n);
	
			break;
		}
		case 5:
		{
			cout << "введите число строк и столбцов" << endl;
			cin >> n >> m;
			S.Submatrix(n, m);
			
			break;
		}
		}
	} while (kod <= 5 && kod != -1);
}
