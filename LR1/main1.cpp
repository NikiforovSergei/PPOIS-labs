#include <iostream>
#include "MatrixClass.h"
#include <string>


void reset(Matrix& matrix);
void console_enter(Matrix& matrix);
void print(Matrix& matrix);
void load(Matrix& matrix);
void extract_submatrix(Matrix& matrix);
void transpose(Matrix& matrix);
void resize(Matrix& matrix);
void plus(Matrix& matrix);
void minus(Matrix& matrix);
void type(Matrix& matrix);


int main() {
	Matrix matrix = {{1,2,3},{4,6,7.1}};
	while (true) {
		int choice;
		std::cout << "Choose an option:\n"
			<< "1 - Reset matrix\n"
			<< "2 - Enter matrix from console\n"
			<< "3 - Print matrix in console\n"
			<< "4 - Load matrix from file\n"
			<< "5 - Extract submatrix\n"
			<< "6 - Transpose matrix\n"
			<< "7 - Resize matrix\n"
			<< "8 - Matrix++\n"
			<< "9 - Matrix--\n"
			<< "10 - Matrix type\n"
			<< "0 - exit\n"
			<< "Enter choise: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			reset(matrix);
			break;
		case 2:
			console_enter(matrix);
			break;
		case 3:
			print(matrix);
			break;
		case 4:
			load(matrix);
			break;
		case 5:
			extract_submatrix(matrix);
			break;
		case 6:
			transpose(matrix);
			break;
		case 7:
			resize(matrix);
			break;
		case 8:
			plus(matrix);
			break;
		case 9:
			minus(matrix);
			break;
		case 10:
			type(matrix);
			break;
		case 0:
			return 0;
		default:
			std::cout << "No such option\n";
			break;
		}
	}
	return 0;
}


void reset(Matrix& matrix) {
	matrix = Matrix();
}

void console_enter(Matrix& matrix) {
	std::cin >> matrix;
}

void print(Matrix& matrix) {
	std::cout << matrix;
}

void load(Matrix& matrix) {
	std::string path;
	std::cout << "Enter file path: ";
	std::cin >> path;
	matrix.load_matrix(path);
}


void extract_submatrix(Matrix& matrix) {
	int row_amount, col_amount, start_row, start_col;
	std::cout << "Enter row and column amount and start row, start column: ";
	std::cin >> row_amount >> col_amount >> start_row >> start_col;
	Matrix sub = matrix.submatrix(row_amount, col_amount, start_row, start_col);
	std::cout << "Your submatrix:\n" << sub;
}

void transpose(Matrix& matrix) {
	matrix.transpose();
}

void resize(Matrix& matrix) {
	int row, col;
	std::cout << "Enter row and column number: ";
	std::cin >> row >> col;
	matrix.matrix_resize(row, col);
}

void plus(Matrix& matrix) {
	matrix++;
}

void minus(Matrix& matrix) {
	matrix--;
}


void type(Matrix& matrix) {
	std::cout << matrix.matrix_type() << "\n";
}