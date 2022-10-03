//
// Created by artur on 10/2/22.
//

#ifndef MATRIXLIB__NUMERIC_MATRIX_H_
#define MATRIXLIB__NUMERIC_MATRIX_H_

#include <type_traits>
#include <set>
#include "matrix.h"

enum class NumericMatrixType {
  kSquare,
  kDiagonal,
  kZero,
  kIdentity,
  kSymmetrical,
  kUpperTriangular,
  kLowerTriangular,
};


/**
 * @brief Numeric matrix class.
 * @details This class extends the base Matrix class and provides the following functions specifically
 * for a numeric matrix:
 * 1. determine types of the matrix.
 * @author Artur Sharapov
 * @date 09/17/2022
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class NumericMatrix : public Matrix<T> {
 public:
  using Matrix<T>::Matrix;

  /**
   * @brief Determines types of the numeric matrix.
   * @details Numeric matrix types: - Square - matrix with the same number of rows and columns;
   * - Diagonal - square matrix in which the entries outside the main diagonal are all zero;
   * - Zero - matrix all of whose entries are zero;
   * - Identity - square matrix with ones on the main diagonal and zeros elsewhere;
   * - Symmetrical - square matrix all of whose entries are symmetric with respect to the main diagonal;
   * - Upper Triangular - square matrix which has zero entries below the main diagonal;
   * - Lower Triangular - square matrix which has zero entries above the main diagonal.
   * @result set<NumericMatrixType> - set of types
   */
  std::set<NumericMatrixType> Types() {
	auto result = std::set<NumericMatrixType>();
	if (IsSquare()) result.insert(NumericMatrixType::kSquare);
	if (IsDiagonal()) result.insert(NumericMatrixType::kDiagonal);
	if (IsZero()) result.insert(NumericMatrixType::kZero);
	if (IsIdentity()) result.insert(NumericMatrixType::kIdentity);
	if (IsSymmetrical()) result.insert(NumericMatrixType::kSymmetrical);
	if (IsUpperTriangular()) result.insert(NumericMatrixType::kUpperTriangular);
	if (IsLowerTriangular()) result.insert(NumericMatrixType::kLowerTriangular);
	return result;
  }

 private:
  bool IsSquare() {
	return this->columns_count_ == this->rows_count_;
  }

  bool IsDiagonal() {
	if (!IsSquare()) return false;
	for (int row_index = 0; row_index < this->columns_count_; row_index++) {
	  for (int column_index = row_index + 1; column_index < this->rows_count_; column_index++) {
		if (this->values_[row_index][column_index] != this->default_value_) return false;
		if (this->values_[column_index][row_index] != this->default_value_) return false;
	  }
	}
	return true;
  }

  bool IsZero() {
	for (int row_index = 0; row_index < this->columns_count_; row_index++) {
	  for (int column_index = 0; column_index < this->rows_count_; column_index++) {
		if (this->values_[row_index][column_index] != this->default_value_) return false;
	  }
	}
	return true;
  }

  bool IsIdentity() {
	if (!IsDiagonal()) return false;
	for (int diagonalIndex = 0; diagonalIndex < this->columns_count_; diagonalIndex++) {
	  if (this->values_[diagonalIndex][diagonalIndex] != 1) return false;
	}
	return true;
  }

  bool IsSymmetrical() {
	if (!IsSquare()) return false;
	for (int row_index = 0; row_index < this->columns_count_; row_index++) {
	  for (int column_index = row_index + 1; column_index < this->rows_count_; column_index++) {
		if (this->values_[row_index][column_index] != this->values_[column_index][row_index]) return false;
	  }
	}
	return true;
  }

  bool IsUpperTriangular() {
	if (!IsSquare()) return false;
	for (int row_index = 0; row_index < this->columns_count_; row_index++) {
	  for (int column_index = row_index + 1; column_index < this->rows_count_; column_index++) {
		if (this->values_[column_index][row_index] != this->default_value_) return false;
	  }
	}
	return true;
  }

  bool IsLowerTriangular() {
	if (!IsSquare()) return false;
	for (int row_index = 0; row_index < this->columns_count_; row_index++) {
	  for (int column_index = row_index + 1; column_index < this->rows_count_; column_index++) {
		if (this->values_[row_index][column_index] != this->default_value_) return false;
	  }
	}
	return true;
  }
};

#endif //MATRIXLIB__NUMERIC_MATRIX_H_
