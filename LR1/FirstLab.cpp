#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	Matrix mat1;
	Matrix mat2;
	Matrix result;
	double num;
	int degree;
	bool k = true;
	bool kt = true;
	bool ktk = true;

	while (ktk == true){
		int n;
		cout << "Выберете знаки:" << endl;
		cout << "1 - +,-,*,/,^ :" << endl << "2 - +=, -=, *=, /=, ^= :" << endl << "3 - выход:" << endl;// "3 - ++ или --:" << endl <<
		cin >> n;
		switch(n){

		case 1:

	    while (k == true) {
		kt = true;
		cout << "1 - редактирование матрицы:" << endl << "2 - просмотр матрицы:" << endl << "3 - сумма матрицы A и матрицы B:" << endl << "4 - сумма матрицы с числом:" << endl << "5 - разность двух матриц:" << endl << "6 - разность матрицы с числом:" << endl;
		cout << "7 - произведение матрицы A и матрицы B:" << endl << "8 - произведение матрицы с числом:" << endl << "9 - деление матрицы на число:" << endl << "10 - возведение матрицы в степень:" << endl;
		cout << "11 - детерминант(определитель) матрицы:" << endl << "12 - норма матрицы:" << endl << "13 - выход:" << endl;
		cin >> n;
		switch (n) {

		case 1:

			system("cls");
			while (kt) {
				cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
				cin >> n;
				switch (n) {

				
				case 1:

					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					break;

				case 2:

					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
					break;
						
				case 3:

					system("cls");
					kt = false;
					break;

				}

			}
			break;

		case 2:

			system("cls");
			while (kt) {
				cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
				cin >> n;
				switch (n) {

					case 1:

						mat1.ShowMatrix();
						break;

					case 2:

						mat2.ShowMatrix();
						break;

					case 3:

						system("cls");
						kt = false;
						break;

				}

			}
			break;

		case 3:


			system("cls");
			if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
				result = mat1 + mat2;
				result.ShowMatrix();
				result.a.clear();
			}
			else {
				cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
				cout << "Введите количество строк матрицы A:" << endl;
				cin >> mat1.rows;
				cout << "Введите количество столбцов матрицы A:" << endl;
				cin >> mat1.cols;
				cout << "Введите количество строк матрицы B:" << endl;
				cin >> mat2.rows;
				cout << "Введите количество столбцов матрицы B:" << endl;
				cin >> mat2.cols;
				while (kt) {
					cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
					cin >> n;
					switch (n) {

					case 1:

						cout << "Введите количество строк матрицы A:" << endl;
						cin >> mat1.rows;
						cout << "Введите количество столбцов матрицы A:" << endl;
						cin >> mat1.cols;
						mat1.create_one(mat1, mat1.rows, mat1.cols);
						break;

					case 2:

						cout << "Введите количество строк матрицы B:" << endl;
						cin >> mat2.rows;
						cout << "Введите количество столбцов матрицы B:" << endl;
						cin >> mat2.cols;
						mat2.create_one(mat2, mat2.rows, mat2.cols);
						break;

					case 3:

						kt = false;
						system("cls");
						break;

					}

				}
			}
			break;

		case 4:

			system("cls");
			cout << "1 - сумма числа с матрицей A:" << endl << "2 - сумма числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat1 + num;
				result.ShowMatrix();
				result.a.clear();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat2 + num;
				result.ShowMatrix();
				result.a.clear();
				break;

			}
			break;

		case 5:

			system("cls");
			cout << "1 - A-B" << endl << "2 - B-A" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
					result = mat1 - mat2;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					system("cls");
					cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			case 2:

				if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
					result = mat2 - mat1;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					system("cls");
					cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 6:

			system("cls");
			cout << "1 - разность числа с матрицей A:" << endl << "2 - разность числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat1 - num;
				result.ShowMatrix();
				result.a.clear();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat2 - num;
				result.ShowMatrix();
				result.a.clear();
				break;

			}
			break;

		case 7:

			system("cls");
			cout << "1 - A*B:" << endl << "2 - B*A:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.cols == mat2.rows) {
					result = mat1 * mat2;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Количество столбцов матрицы A должно совпадать с количеством строк матрицы B !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			case 2:

				if (mat2.cols == mat1.rows) {
					result = mat2 * mat1;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Количество столбцов матрицы B должно совпадать с количеством строк матрицы A !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 8:

			system("cls");
			cout << "1 - произведение числа с матрицей A:" << endl << "2 - произведение числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat1 * num;
				result.ShowMatrix();
				result.a.clear();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat2 * num;
				result.ShowMatrix();
				result.a.clear();
				break;

			}
			break;

		case 9:

			system("cls");
			cout << "1 - частное матрицы A и числа:" << endl << "2 - частное матрицы B и числа:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat1 / num;
				result.ShowMatrix();
				result.a.clear();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				result = mat2 / num;
				result.ShowMatrix();
				result.a.clear();
				break;

			}
			break;

		case 10:

			system("cls");
			cout << "1 - возведение матрицы A в степень:" << endl << "2 - возведение матрицы B в степень:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat1.cols) {
					cout << "Введите степень:" << endl;
					cin >> degree;
					result = mat1 ^ degree;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat1.ShowMatrix();
					result.a.clear();
				}
				break;

			case 2:

				if (mat2.rows == mat2.cols) {
					cout << "Введите степень:" << endl;
					cin >> degree;
					result = mat2 ^ degree;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
					mat2.ShowMatrix();
				}
				break;

			}
			break;

		case 11:

			system("cls");
			cout << "1 - определитель матрицы A:" << endl << "2 - определитель матрицы B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat1.cols) {
					Matrix::deter(mat1.a, mat1.rows, mat1.det);
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);

				}
				break;

			case 2:

				if (mat2.rows == mat2.cols) {
					Matrix::deter(mat2.a, mat2.rows, mat2.det);
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 12:

			system("cls");
			cout << "1 - норма матрицы A:" << endl << "2 - норма матрицы B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "1 - M-норма матрицы A:" << endl << "2 - L-норма матрицы A:" << endl << "3 - K-норма матрицы A:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					Matrix::m_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				case 2:

					Matrix::l_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				case 3:

					Matrix::k_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				}
				break;

			case 2:

				cout << "1 - M-норма матрицы B:" << endl << "2 - L-норма матрицы B:" << endl << "3 - K-норма матрицы B:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					Matrix::m_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				case 2:

					Matrix::l_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				case 3:

					Matrix::k_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				}
				break;

			}
			break;

		case 13:

			system("cls");
			k = false;
			break;

		}

	}
	
	break;

	case 2:

	while (k == true) {
		int n;
		kt = true;
		cout << "1 - редактирование матрицы:" << endl << "2 - просмотр матрицы:" << endl << "3 - сумма матрицы A и матрицы B:" << endl << "4 - сумма матрицы с числом:" << endl << "5 - разность двух матриц:" << endl << "6 - разность матрицы с числом:" << endl;
		cout << "7 - произведение матрицы A и матрицы B:" << endl << "8 - произведение матрицы с числом:" << endl << "9 - деление матрицы на число:" << endl << "10 - возведение матрицы в степень:" << endl;
		cout << "11 - детерминант(определитель) матрицы:" << endl << "12 - норма матрицы:" << endl << "13 - выход:" << endl;
		cin >> n;
		switch (n) {

		case 1:

			system("cls");
			while (kt) {
				cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					break;

				case 2:

					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
					break;

				case 3:

					system("cls");
					kt = false;
					break;

				}

			}
			break;

		case 2:

			system("cls");
			while (kt) {
				cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					mat1.ShowMatrix();
					break;

				case 2:

					mat2.ShowMatrix();
					break;

				case 3:

					system("cls");
					kt = false;
					break;

				}

			}
			break;

		case 3:


			system("cls");
			if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
				mat1 += mat2;
				mat1.ShowMatrix();
			}
			else {
				cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
				cout << "Введите количество строк матрицы A:" << endl;
				cin >> mat1.rows;
				cout << "Введите количество столбцов матрицы A:" << endl;
				cin >> mat1.cols;
				cout << "Введите количество строк матрицы B:" << endl;
				cin >> mat2.rows;
				cout << "Введите количество столбцов матрицы B:" << endl;
				cin >> mat2.cols;
				while (kt) {
					cout << "1 - матрица A:" << endl << "2 - матрица B:" << endl << "3 - выход:" << endl;
					cin >> n;
					switch (n) {

					case 1:

						cout << "Введите количество строк матрицы A:" << endl;
						cin >> mat1.rows;
						cout << "Введите количество столбцов матрицы A:" << endl;
						cin >> mat1.cols;
						mat1.create_one(mat1, mat1.rows, mat1.cols);
						break;

					case 2:

						cout << "Введите количество строк матрицы B:" << endl;
						cin >> mat2.rows;
						cout << "Введите количество столбцов матрицы B:" << endl;
						cin >> mat2.cols;
						mat2.create_one(mat2, mat2.rows, mat2.cols);
						break;

					case 3:

						kt = false;
						system("cls");
						break;

					}

				}
			}
			break;

		case 4:

			system("cls");
			cout << "1 - сумма числа с матрицей A:" << endl << "2 - сумма числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				mat1 += num;
				mat1.ShowMatrix();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				mat2 += num;
				mat2.ShowMatrix();
				break;

			}
			break;

		case 5:

			system("cls");
			cout << "1 - A-B" << endl << "2 - B-A" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
					mat1 -= mat2;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					system("cls");
					cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			case 2:

				if (mat1.rows == mat2.rows && mat1.cols == mat2.cols) {
					mat2 -= mat1;
					mat2.ShowMatrix();
				}
				else {
					system("cls");
					cout << "Количество строк и столбцов матриц A и B должно быть одинаково !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 6:

			system("cls");
			cout << "1 - разность числа с матрицей A:" << endl << "2 - разность числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				mat1 -= num;
				mat1.ShowMatrix();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				mat2 -= num;
				mat2.ShowMatrix();
				break;

			}
			break;

		case 7:

			system("cls");
			cout << "1 - A*B:" << endl << "2 - B*A:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.cols == mat2.rows) {
					result = mat1 * mat2;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Количество столбцов матрицы A должно совпадать с количеством строк матрицы B !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			case 2:

				if (mat2.cols == mat1.rows) {
					result = mat2 * mat1;
					result.ShowMatrix();
					result.a.clear();
				}
				else {
					cout << "Количество столбцов матрицы B должно совпадать с количеством строк матрицы A !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 8:

			system("cls");
			cout << "1 - произведение числа с матрицей A:" << endl << "2 - произведение числа с матрицей B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				mat1 *= num;
				mat1.ShowMatrix();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				mat2 *= num;
				mat2.ShowMatrix();
				break;

			}
			break;

		case 9:

			system("cls");
			cout << "1 - частное матрицы A и числа:" << endl << "2 - частное матрицы B и числа:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "Введите число" << endl;
				cin >> num;
				mat1 /= num;
				mat1.ShowMatrix();
				break;

			case 2:

				cout << "Введите число" << endl;
				cin >> num;
				mat2 /= num;
				mat2.ShowMatrix();
				break;

			}
			break;

		case 10:

			system("cls");
			cout << "1 - возведение матрицы A в степень:" << endl << "2 - возведение матрицы B в степень:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat1.cols) {
					cout << "Введите степень:" << endl;
					cin >> degree;
					mat1 ^= degree;
					mat1.ShowMatrix();
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);
					mat1.ShowMatrix();
				}
				break;

			case 2:

				if (mat2.rows == mat2.cols) {
					cout << "Введите степень:" << endl;
					cin >> degree;
					mat2 ^= degree;
					mat2.ShowMatrix();
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
					mat2.ShowMatrix();
				}
				break;

			}
			break;

		case 11:

			system("cls");
			cout << "1 - определитель матрицы A:" << endl << "2 - определитель матрицы B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				if (mat1.rows == mat1.cols) {
					Matrix::deter(mat1.a, mat1.rows, mat1.det);
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы A:" << endl;
					cin >> mat1.rows;
					cout << "Введите количество столбцов матрицы A:" << endl;
					cin >> mat1.cols;
					mat1.create_one(mat1, mat1.rows, mat1.cols);

				}
				break;

			case 2:

				if (mat2.rows == mat2.cols) {
					Matrix::deter(mat2.a, mat2.rows, mat2.det);
				}
				else {
					cout << "Матрица для возведения её в степень должна быть квадратной !!!" << endl;
					cout << "Введите количество строк матрицы B:" << endl;
					cin >> mat2.rows;
					cout << "Введите количество столбцов матрицы B:" << endl;
					cin >> mat2.cols;
					mat2.create_one(mat2, mat2.rows, mat2.cols);
				}
				break;

			}
			break;

		case 12:

			system("cls");
			cout << "1 - норма матрицы A:" << endl << "2 - норма матрицы B:" << endl;
			cin >> n;
			switch (n) {

			case 1:

				cout << "1 - M-норма матрицы A:" << endl << "2 - L-норма матрицы A:" << endl << "3 - K-норма матрицы A:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					Matrix::m_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				case 2:

					Matrix::l_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				case 3:

					Matrix::k_norm(mat1.a, mat1.rows, mat1.cols);
					break;

				}
				break;

			case 2:

				cout << "1 - M-норма матрицы B:" << endl << "2 - L-норма матрицы B:" << endl << "3 - K-норма матрицы B:" << endl;
				cin >> n;
				switch (n) {

				case 1:

					Matrix::m_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				case 2:

					Matrix::l_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				case 3:

					Matrix::k_norm(mat2.a, mat2.rows, mat2.cols);
					break;

				}
				break;

			}
			break;

		case 13:

			system("cls");
			k = false;
			break;

		}

	}
	break;

	/*case 3:
		
		cout << "1 - A++" << endl << "2 - A--" << endl << "3 - B++" << endl << "4 - B--"<< endl;
		cin >> n;
		switch (n) {

		case 1:

			mat1.ShowMatrix();
			mat1++;
			mat1.ShowMatrix();
			break;

		case 2:

			mat1.ShowMatrix();
			mat1--;
			mat1.ShowMatrix();
			break;
		case 3:

			mat2.ShowMatrix();
			mat2++;
			mat2.ShowMatrix();
			break;

		case 4:

			mat2.ShowMatrix();
			mat2--;
			mat2.ShowMatrix();
			break;

		}
		break;*/

	case 3:

		ktk = false;
		system("cls");
		break;

	}
    }

}