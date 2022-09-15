//
// Created by Глеб on 2.09.22.
//

#include "Matrix.h"

Matrix::Matrix() {
  rows = columns = 0;
  M = nullptr;
}

Matrix::Matrix(const Matrix& other) {
  this->~Matrix();
  this->M = other.M;
  this->rows = other.rows;
  this->columns = other.columns;
}

Matrix::Matrix(int rows, int columns) {
  this->rows = rows;
  this->columns = columns;

  M = (double**)new double*[rows];

  for (int i = 0; i < rows; i++) {
    M[i] = (double*)new double[columns];
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M[i][j] = 0;
    }
  }
}

Matrix::~Matrix() {
  if (rows > 0) {
    for (int i = 0; i < rows; i++) {
      delete[] M[i];
    }
  }

  if (columns > 0) {
    delete[] M;
  }
}

void Matrix::print() {
  if (M != nullptr) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        std::cout << M[i][j] << "  ";
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "matrix empty" << std::endl;
  }
}

double Matrix::getValue(int i, int j) {
  if ((i >= 0 && j >= 0) and (i < rows && j < columns))
    return M[i][j];
  else
    return 0;
}

void Matrix::setValue(int i, int j, double value) {
  if ((i >= 0 && j >= 0) and (i <= rows && j <= columns))
    M[i][j] = value;
  else
    return;
}

void Matrix::changeRows(int changed_rows) {
  double** changedM = new double*[changed_rows];
  for (int i = 0; i < changed_rows; i++) {
    changedM[i] = (double*)new double[columns];
  }

  for (int i = 0; i < changed_rows; i++) {
    for (int j = 0; j < columns; j++) {
      changedM[i][j] = this->getValue(i, j);
    }
  }

  this->~Matrix();
  this->rows = changed_rows;
  this->M = changedM;
}

void Matrix::changeColumns(int changed_columns) {
  double** changedM = new double*[rows];
  for (int i = 0; i < rows; i++) {
    changedM[i] = (double*)new double[changed_columns];
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < changed_columns; j++) {
      changedM[i][j] = this->getValue(i, j);
    }
  }

  this->~Matrix();
  this->columns = changed_columns;
  this->M = changedM;
}

void Matrix::loadFromFile(std::string fileName) {
  std::string buff;
  std::ifstream file(fileName);
  if (file.is_open()) {
    this->~Matrix();

    file >> this->rows;
    file >> this->columns;

    double** newM = new double*[rows];
    for (int i = 0; i < rows; i++) {
      newM[i] = (double*)new double[columns];
    }

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) file >> newM[i][j];

    this->M = newM;
  } else {
    std::cout << "file not founded";
  }
}

Matrix Matrix::getTransMatrix() {
  if (this->M != nullptr and this->isSquareMatrix()) {
    Matrix transMatrix = Matrix(rows, columns);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        transMatrix.setValue(i, j, this->getValue(j, i));
      }
    }

    return transMatrix;
  } else
    throw std::out_of_range("impossible to get transparent matrix");
}

Matrix Matrix::getSubMatrix(int x1, int y1, int x2, int y2) {
  if ((x1 >= 0 && y1 >= 0) && (x2 >= x1 && y2 >= y1) &&
      (x2 <= rows && y2 <= columns)) {
    x2++;  //не включая столбцы с пересечением на x2 y2
    y2++;  //

    int new_rows = x2 - x1;
    int new_columns = y2 - y1;

    Matrix subMatrix = Matrix(new_rows, new_columns);

    int _i = 0;
    int _j = 0;
    for (int i = x1; i < x2; i++) {
      _j = 0;
      for (int j = y1; j < y2; j++) {
        subMatrix.setValue(_i, _j, this->getValue(i, j));
        _j++;
      }
      _i++;
    }
    return subMatrix;
  } else
    throw std::out_of_range("impossible to get sub matrix");
}

bool Matrix::isSquareMatrix() { return M != nullptr && rows == columns; }

bool Matrix::isDiagonalMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (i != j and this->getValue(i, j) != 0) return false;
    }
  }
  return this->isSquareMatrix();
}

bool Matrix::isZeroMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (this->getValue(i, j) != 0) return false;
    }
  }
  return true;
}

bool Matrix::isUnitMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if ((i != j and this->getValue(i, j) != 0) or
          (i == j and this->getValue(i, j) != 1))
        return false;
    }
  }
  return this->isSquareMatrix();
}

bool Matrix::isSymmetricalMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (this->getValue(i, j) != this->getValue(j, i)) return false;
    }
  }
  return this->isSquareMatrix();
}

bool Matrix::isUpperTriangularMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (i > j and this->getValue(i, j) != 0) return false;
    }
  }
  return this->isSquareMatrix();
}

bool Matrix::isLowerTriangularMatrix() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (i < j and this->getValue(i, j) != 0) return false;
    }
  }
  return this->isSquareMatrix();
}

void Matrix::printMatrixType() {
  std::cout << "Матрица:" << std::endl;
  int counter = 1;
  if (this->isSquareMatrix()) {
    std::cout << counter << ". квадратная" << std::endl;
    counter++;
  }
  if (this->isSymmetricalMatrix()) {
    std::cout << counter << ". симметричная" << std::endl;
    counter++;
  }
  if (this->isUnitMatrix()) {
    std::cout << counter << ". единичная" << std::endl;
    counter++;
  }
  if (this->isZeroMatrix()) {
    std::cout << counter << ". нулевая" << std::endl;
    counter++;
  }
  if (this->isDiagonalMatrix()) {
    std::cout << counter << ". диагональная" << std::endl;
    counter++;
  }
  if (this->isUpperTriangularMatrix()) {
    std::cout << counter << ". верхняя треугольная" << std::endl;
    counter++;
  }
  if (this->isLowerTriangularMatrix()) {
    std::cout << counter << ". нижняя треугольная" << std::endl;
    counter++;
  }
}

int Matrix::getRows() { return rows; }

int Matrix::getColumns() { return columns; }

Matrix& Matrix::operator=(Matrix other) noexcept {
  if (this == &other) return *this;

  this->~Matrix();
  this->M = other.M;
  this->rows = other.rows;
  this->columns = other.columns;
  return *this;
}

Matrix& Matrix::operator++() {
  this->changeRows(this->rows + 1);
  this->changeColumns(this->columns + 1);
  return *this;
}

Matrix& Matrix::operator--() {
  this->changeRows(this->rows - 1);
  this->changeColumns(this->columns - 1);
  return *this;
}