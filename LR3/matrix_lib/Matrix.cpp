//
// Created by Глеб on 2.09.22.
//

#include "Matrix.h"

Matrix::Matrix() {
  rows = columns = 0;
}

Matrix::Matrix(const Matrix &other) {
  this->~Matrix();
  this->M = other.M;
  this->rows = other.rows;
  this->columns = other.columns;
}

int Matrix::getValue(int i, int j) {
  return M[i][j];
}

void Matrix::setValue(int i, int j, int value) {
  M[i][j] = value;
}

void Matrix::addRows() {
  M.emplace_back(columns, 0);
  rows++;
}

void Matrix::addColumns() {
  for (auto &rows_ : this->M) {
    rows_.push_back(0);
  }
  columns++;
}

int Matrix::getRows() const { return rows; }

int Matrix::getColumns() const { return columns; }

std::vector<int> *Matrix::getColumn(int n) {
  std::vector<int> result;
  for (int i = 0; i < M.size(); i++) {
    result.push_back(M[i][n]);
  }
  return new std::vector<int>(result);
}

std::vector<int> &Matrix::getRow(int n) {
  return M[n];
}

void Matrix::clear() {
  for (auto &i : M) {
    i.clear();
  }
  M.clear();
  columns = 0;
  rows = 0;
}
void Matrix::removeRows(int n) {
  if (n<=rows) {
    M.erase(M.begin() + n);
    rows--;
  }
}
void Matrix::removeColumns(int n) {
  if (n<=columns) {
    for (auto &i : M) {
      i.erase(i.begin() + n);
    }
    columns--;
  }
}
