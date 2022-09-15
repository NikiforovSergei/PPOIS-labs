//
// Created by Глеб on 2.09.22.
//

#include "Matrix.h"
#include "gtest/gtest.h"

TEST(matrixTypeCheck, diagonalMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/diagonal_matrix.txt");
  EXPECT_EQ(m.isDiagonalMatrix(), true);
}

TEST(matrixTypeCheck, notDiagonalMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/big_matrix.txt");
  EXPECT_EQ(m.isDiagonalMatrix(), false);
}

TEST(matrixTypeCheck, SquareMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/square_matrix.txt");
  EXPECT_EQ(m.isSquareMatrix(), true);
}

TEST(matrixTypeCheck, notSquareMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/not_square_matrix.txt");
  EXPECT_EQ(m.isSquareMatrix(), false);
}

TEST(matrixTypeCheck, ZeroMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/zero_matrix.txt");
  EXPECT_EQ(m.isZeroMatrix(), true);
}

TEST(matrixTypeCheck, notZeroMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/big_matrix.txt");
  EXPECT_EQ(m.isZeroMatrix(), false);
}

TEST(matrixTypeCheck, UnitMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/unit_matrix.txt");
  EXPECT_EQ(m.isUnitMatrix(), true);
}

TEST(matrixTypeCheck, SymmetricalMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/sym_matrix.txt");
  EXPECT_EQ(m.isSymmetricalMatrix(), true);
}

TEST(matrixTypeCheck, LowerTriangularMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/upper_matrix.txt");
  EXPECT_EQ(m.isLowerTriangularMatrix(), true);
}

TEST(matrixTypeCheck, UpperTriangularMatrix) {
  Matrix m = Matrix();

  m.loadFromFile("resources/lower_matrix.txt");
  EXPECT_EQ(m.isUpperTriangularMatrix(), true);
}

TEST(matrixGetTransponentMatrixCheck, x3matrix) {
  Matrix m = Matrix();
  m.loadFromFile("resources/matrixToBeTransp.txt");

  Matrix T = m.getTransMatrix();

  for (int i = 0; i < T.getRows(); i++)
    for (int j = 0; j < T.getColumns(); j++)
      EXPECT_EQ(T.getValue(i, j), m.getValue(j, i));
}

TEST(matrixGetSubMatrixCheck, x5matrix) {
  Matrix m = Matrix();
  m.loadFromFile("resources/big_matrix.txt");

  Matrix correct_sub = Matrix();
  correct_sub.loadFromFile("resources/sub_matrix_of_big_matrix.txt");

  Matrix sub_m = m.getSubMatrix(1, 1, 3, 3);

  for (int i = 0; i < correct_sub.getRows(); i++)
    for (int j = 0; j < correct_sub.getColumns(); j++)
      EXPECT_EQ(sub_m.getValue(i, j), correct_sub.getValue(i, j));
}

TEST(matrixGetSubMatrixCheck, x3matrix) {
  Matrix m = Matrix();
  m.loadFromFile("resources/midle_matrix.txt");

  Matrix correct_sub = Matrix();
  correct_sub.loadFromFile("resources/sub_matrix_of_big_matrix.txt");

  Matrix sub_m = m.getSubMatrix(0, 0, 3, 3);

  for (int i = 0; i < correct_sub.getRows(); i++)
    for (int j = 0; j < correct_sub.getColumns(); j++)
      EXPECT_EQ(sub_m.getValue(i, j), correct_sub.getValue(i, j));
}

TEST(matrixConstructorCheck, withoutArgumens) {
  Matrix m = Matrix();
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getColumns(), 0);
}

TEST(matrixConstructorCheck, with2Argumens3x4) {
  Matrix m = Matrix(3, 4);
  EXPECT_EQ(m.getRows(), 3);
  EXPECT_EQ(m.getColumns(), 4);
}

TEST(matrixConstructorCheck, with2Argumens10x15) {
  Matrix m = Matrix(10, 15);
  EXPECT_EQ(m.getRows(), 10);
  EXPECT_EQ(m.getColumns(), 15);
}

TEST(matrixConstructorCheck, with2Argumens100x200) {
  Matrix m = Matrix(100, 200);
  EXPECT_EQ(m.getRows(), 100);
  EXPECT_EQ(m.getColumns(), 200);
}

TEST(matrixOperatorCheck, increment1) {
  Matrix m = Matrix(10, 10);
  ++m;
  EXPECT_EQ(m.getRows(), 11);
  EXPECT_EQ(m.getColumns(), 11);
}

TEST(matrixOperatorCheck, increment15) {
  Matrix m = Matrix(10, 10);

  for (int i = 0; i < 15; i++) ++m;

  EXPECT_EQ(m.getRows(), 25);
  EXPECT_EQ(m.getColumns(), 25);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}