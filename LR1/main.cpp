#include "Matrix.h"

using namespace std;

// void print(Matrix m);
// void printMatrixType(Matrix m);
void print(Matrix& m) {
  if (m.getRows() > 0 && m.getColumns() > 0)
    for (int i = 0; i < m.getRows(); i++) {
      for (int j = 0; j < m.getColumns(); j++) {
        std::cout << m.getValue(i, j) << "  ";
      }
      std::cout << std::endl;
    }
  else {
    std::cout << "matrix is empty" << std::endl;
  }
}

void printMatrixType(Matrix& m) {
  std::cout << "Матрица:" << std::endl;
  int counter = 1;
  if (m.isSquareMatrix()) {
    std::cout << counter << ". квадратная" << std::endl;
    counter++;
  }
  if (m.isSymmetricalMatrix()) {
    std::cout << counter << ". симметричная" << std::endl;
    counter++;
  }
  if (m.isUnitMatrix()) {
    std::cout << counter << ". единичная" << std::endl;
    counter++;
  }
  if (m.isZeroMatrix()) {
    std::cout << counter << ". нулевая" << std::endl;
    counter++;
  }
  if (m.isDiagonalMatrix()) {
    std::cout << counter << ". диагональная" << std::endl;
    counter++;
  }
  if (m.isUpperTriangularMatrix()) {
    std::cout << counter << ". верхняя треугольная" << std::endl;
    counter++;
  }
  if (m.isLowerTriangularMatrix()) {
    std::cout << counter << ". нижняя треугольная" << std::endl;
    counter++;
  }
}

int main() {
  Matrix m;
  print(m);
  m.loadFromFile("resources/matrix1.txt");
  cout << endl;
  print(m);
  cout << endl;

  m.changeColumns(5);
  m.changeRows(5);
  m.setValue(3, 3, 1);
  m.setValue(4, 4, 1);
  print(m);

  printMatrixType(m);
  return 0;
}