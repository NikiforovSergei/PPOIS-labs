//
// Created by artur on 9/19/22.
//
#include "../numeric_matrix.h"

#include "gtest/gtest.h"

TEST(MatrixConstructor, NoArguments) {
  NumericMatrix<double> matrix;
  EXPECT_EQ(matrix.columns_count(), 0);
  EXPECT_EQ(matrix.rows_count(), 0);
}

TEST(MatrixConstructor, SizeArguments) {
  NumericMatrix<double> matrix (13, 27);
  EXPECT_EQ(matrix.columns_count(), 13);
  EXPECT_EQ(matrix.rows_count(), 27);
}

TEST(MatrixConstructor, FullArguments) {
  auto values = new double*[1];
  values[0] = new double[2] {1.5, -2.7};
  NumericMatrix<double> matrix (2, 1, values, 55);
  EXPECT_EQ(matrix.columns_count(), 2);
  EXPECT_EQ(matrix.rows_count(), 1);
  EXPECT_EQ(matrix.operator[]({0, 0}), 1.5);
  EXPECT_EQ(matrix.operator[]({1, 0}), -2.7);
  matrix.Resize(3, 1);
  EXPECT_EQ(matrix.operator[]({2, 0}), 55);
}

TEST(MatrixConstructor, VectorArguments) {
  NumericMatrix<double> matrix ({
	{-5, -9},
	{4.2, 8},
  });
  EXPECT_EQ(matrix.operator[]({0, 0}), -5);
  EXPECT_EQ(matrix.operator[]({1, 0}), -9);
  EXPECT_EQ(matrix.operator[]({0, 1}), 4.2);
  EXPECT_EQ(matrix.operator[]({1, 1}), 8);
}






TEST(MatrixOperator, MatrixIndexing) {
  NumericMatrix<double> matrix ({
	{1, 2, 3},
	{4, 5, 6},
  });
  Index top_right {-1, 0};
  Index bottom_left {0, -1};
  EXPECT_EQ(matrix[top_right], 3);
  EXPECT_EQ(matrix[bottom_left], 4);
  matrix[{2, 0}] = 8;
  EXPECT_EQ(matrix[top_right], 8);
}

TEST(MatrixOperator, InvalidMatrixIndexing) {
  NumericMatrix<double> matrix ({
	{1, 2},
	{3, 4},
  });
  Index out_of_range_index {-3, 0};
  EXPECT_THROW(matrix[out_of_range_index], std::out_of_range);
}

TEST(MatrixOperator, MatrixEquality) {
  NumericMatrix<double> matrix_1 ({
	{1, 2, 3},
	{4, 5, 6},
  });
  NumericMatrix<double> matrix_2 ({
	{1, 0, 3},
	{4, 5, 6},
  });
  EXPECT_FALSE(matrix_1 == matrix_2);
  matrix_2[{1, 0}] = 2;
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(MatrixOperator, MatrixAssignment) {
  NumericMatrix<double> matrix_1 (2, 2);
  auto matrix_2 = NumericMatrix<double>(2, 2);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(MatrixOperator, MatrixIncrement) {
  NumericMatrix<double> matrix (2, 3);
  EXPECT_EQ((++matrix).columns_count(), 3);
  EXPECT_EQ((++matrix).rows_count(), 5);
}

TEST(MatrixOperator, MatrixDecrement) {
  NumericMatrix<double> matrix (4, 3);
  EXPECT_EQ((--matrix).columns_count(), 3);
  EXPECT_EQ((--matrix).rows_count(), 1);
}




TEST(MatrixType, SquareMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/square-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kSquare));
}

TEST(MatrixType, NonSquareMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/non-square-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kSquare));
}

TEST(MatrixType, DiagonalMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/diagonal-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kDiagonal));
}

TEST(MatrixType, NonDiagonalMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/non-diagonal-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kDiagonal));
}

TEST(MatrixType, LowerTriangularMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/lower-triangular-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kLowerTriangular));
}

TEST(MatrixType, NonLowerTriangularMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/upper-triangular-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kLowerTriangular));
}

TEST(MatrixType, UpperTriangularMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/upper-triangular-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kUpperTriangular));
}

TEST(MatrixType, NonUpperTriangularMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/lower-triangular-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kUpperTriangular));
}

TEST(MatrixType, ZeroMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/zero-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kZero));
}

TEST(MatrixType, NonZeroMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/non-diagonal-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kZero));
}

TEST(MatrixType, SingleMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/single-matrix.txt");
  EXPECT_TRUE(matrix.Types().contains(NumericMatrixType::kIdentity));
}

TEST(MatrixType, NonSingleMatrix) {
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/non-single-matrix.txt");
  EXPECT_FALSE(matrix.Types().contains(NumericMatrixType::kIdentity));
}




TEST(MatrixFile, LoadMatrix) {
  auto expected = NumericMatrix<double>({
	{1.1, 2.2, 3.3, 8.4},
	{4.9, 5.1, 6.2, 9.0},
	{9.2, 9.5, 5.9, 3.4},
  });
  auto matrix = NumericMatrix<double>();
  matrix.Load("../tests/assets/valid-matrix.txt");
  EXPECT_TRUE(matrix == expected);
}

TEST(MatrixFile, LoadInvalidMatrix) {
  auto matrix = NumericMatrix<double>();
  EXPECT_THROW(matrix.Load("../tests/assets/invalid-matrix.txt"), std::out_of_range);
}

TEST(MatrixFile, LoadSavedMatrix) {
  auto saved = NumericMatrix<double>();
  saved.Save("../tests/assets/saved-matrix.txt");
  auto loaded = NumericMatrix<double>();
  loaded.Load("../tests/assets/saved-matrix.txt");
  EXPECT_TRUE(saved == loaded);
}




TEST(MatrixMethod, ResizeMatrix) {
  NumericMatrix<double> matrix (2, 3);
  matrix.Resize(4, 8);
  EXPECT_EQ(matrix.columns_count(), 4);
  EXPECT_EQ(matrix.rows_count(), 8);
}

TEST(MatrixMethod, SliceMatrix) {
  auto matrix = NumericMatrix<double>(20, 20);
  matrix[{9, 3}] = 78;
  auto slice = matrix.Slice(10, 5);
  EXPECT_EQ(slice.operator[]({-1, -2}), 78);
}

TEST(MatrixMethod, CopyMatrix) {
  auto matrix = NumericMatrix<double>(2, 3);
  auto copy = matrix.Copy();
  EXPECT_TRUE(matrix == copy);
  matrix[{1, 1}] = 99;
  EXPECT_FALSE(matrix == copy);
}

TEST(MatrixMethod, SetDefaultValueOfMatrix) {
  auto matrix = NumericMatrix<double>(2, 3);
  matrix.set_default_value(-123.45);
  EXPECT_EQ(matrix.operator[]({1, 2}), 0);
  matrix.Resize(2, 2);
  matrix.Resize(2, 3);
  EXPECT_EQ(matrix.operator[]({1, 2}), -123.45);
}

TEST(MatrixMethod, TransposeMatrix) {
  auto matrix = NumericMatrix<double>({
	{1.1, 2.2, 3.3, 8.4},
  	{9.2, 9.5, 5.9, 3.4},
  });
  auto transposed = NumericMatrix<double>({
	{1.1, 9.2},
	{2.2, 9.5},
	{3.3, 5.9},
	{8.4, 3.4},
  });
  EXPECT_TRUE(matrix.Transpose() == transposed);
}

//TEST(MatrixOther, NonNumericMatrix) {
//  NumericMatrix<char> matrix;
//  EXPECT_TRUE(true);
//}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
