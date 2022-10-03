//
// Created by artur on 9/19/22.
//

#ifndef MATRIX__MATRIX_H_
#define MATRIX__MATRIX_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::string;
using std::vector;


/**
 * @brief Matrix index class.
 * @details This class is used to create objects representing the index of a matrix.
 * @author Artur Sharapov
 * @date 09/17/2022
 */
struct Index {
  /**
   * @brief Column index (x-axis)
   */
  int m{};
  /**
   * @brief Row index (y-axis)
   */
  int n{};
  /**
   * @brief If passed true, the default value is returned when index is out of range instead of throwing exception.
   */
  bool safe = false;
};

/**
 * @brief Base matrix class.
 * @details This class implements a base matrix class for values of any
 * type and has the following built-in functions:
 * 1. change the number of rows and columns;
 * 2. save matrix to file;
 * 3. load matrix from file;
 * 4. get matrix slice;
 * 5. transpose matrix;
 * 6. copy matrix;
 * 7. set default value.
 * @author Artur Sharapov
 * @date 09/17/2022
 */
template<typename T>
class Matrix {
 public:
  /**
   * @brief Constructor without arguments. An empty matrix of size zero is created.
   */
  Matrix();
  /**
   * @brief Copy constructor. The copy constructor is used to create a shallow copy an already existing matrix.
   * @param matrix - already existing matrix
   */
  Matrix(const Matrix<T> &matrix);
  /**
   * @brief Constructor with the number of columns and rows specified.
   * @details A matrix of the corresponding size is created and filled with the default values of the matrix type.
   * @param columns_count - number of columns
   * @param rows_count - number of rows
   */
  Matrix(unsigned int columns_count, unsigned int rows_count);
  /**
   * @brief Constructor with the number of columns and rows, values array, and custom default value specified.
   * @details A matrix of the corresponding size is created and filled with the values of provided array.
   * The specified default value will be used when expanding the matrix to fill empty cells.
   * @param columns_count - number of columns
   * @param rows_count - number of rows
   * @param values - pointer to an array of values
   * @param default_value - default value
   */
  Matrix(unsigned int columns_count, unsigned int rows_count, T **values, T default_value);
  /**
   * @brief Constructor with vector of values specified.
   * @details A matrix with the values of provided vector is created.
   * @param vector - provided vector
   */
  explicit Matrix(vector<vector<T>> vector);
  /**
   * @brief Assignment operator.
   * @details The right matrix is assigned to the left one using a deep copy.
   */
  Matrix<T> &operator=(Matrix<T> const &matrix);
  /**
   * @brief Deallocation of using memory
   */
  ~Matrix();

  /**
   * @brief Increment operator.
   * @details Increases the number of rows and columns by 1.
   * @result Matrix<T>& - reference to the mutated matrix
   */
  Matrix<T>& operator++();
  /**
   * @brief Decrement operator.
   * @details Decreases the number of rows and columns by 1.
   * @result Matrix<T>& - reference to the mutated matrix
   */
  Matrix<T>& operator--();
/**
   * @brief Postfix increment operator.
   * @details Increases the number of rows and columns by 1.
   * @result Matrix<T>& - reference to the mutated matrix
   */
  T &operator[](Index index);
  /**
   * @brief Equality operator.
   * @details Determines the equality of two matrices.
   * @result bool
   */
  bool operator==(Matrix<T> &matrix);

  /**
   * @brief Saves matrix to a file at the given address.
   * @param path - given address (including file name and extension)
   */
  void Save(const string &path);
  /**
   * @brief Loads matrix from a file at the given address.
   * @param path - given address (including file name and extension)
   */
  void Load(const string &path);
  /**
   * @brief Creates a slice of the matrix of the given size.
   * @param new_columns_count - the number of columns (must be less than initial)
   * @param new_rows_count - the number of rows (must be less than initial)
   * @result Matrix - matrix slice
   */
  Matrix<T> Slice(unsigned int new_columns_count, unsigned int new_rows_count) const;
  /**
   * @brief Creates a deep copy of the matrix.
   * @result Matrix - matrix copy
   */
  Matrix<T> Copy() const;
  /**
   * @brief Changes the size of the matrix.
   * @details When expanding the matrix, empty cells are filled with the default value
   * (see Matrix::set_default_value).
   * @param new_columns_count - the new number of columns
   * @param new_rows_count - the new number of rows
   */
  void Resize(unsigned int new_columns_count, unsigned int new_rows_count);
  /**
   * @brief Transposes the matrix.
   * @details Flips the matrix over its diagonal.
   * @param Matrix - transposed matrix
   */
  Matrix Transpose();

  /**
   * @brief Returns the number of columns.
   * @result unsigned int - the number of columns
   */
  [[nodiscard]] unsigned int columns_count() const { return columns_count_; }
  /**
   * @brief Returns the number of rows.
   * @result unsigned int - the number of rows
   */
  [[nodiscard]] unsigned int rows_count() const { return rows_count_; }
  /**
   * @brief Sets the default value for the matrix.
   * @param value - new default value
   */
  void set_default_value(T value) { default_value_ = value; }


 protected:
  T **values_ = nullptr;
  unsigned int columns_count_ = 0;
  unsigned int rows_count_ = 0;
  T default_value_;

  bool IsEmpty();

};






template<typename T>
Matrix<T>::Matrix() {
  default_value_ = T();
};

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix) {
  this->~Matrix();
  values_ = matrix.values_;
  rows_count_ = matrix.rows_count_;
  columns_count_ = matrix.columns_count_;
  default_value_ = matrix.default_value_;
}

template<typename T>
Matrix<T>::Matrix(unsigned int columns_count, unsigned int rows_count) {
  default_value_ = T();
  Resize(columns_count, rows_count);
}

template<typename T>
Matrix<T>::Matrix(unsigned int columns_count, unsigned int rows_count, T **values, T default_value) {
  columns_count_ = columns_count;
  rows_count_ = rows_count;
  values_ = values;
  default_value_ = default_value;
}

template<typename T>
Matrix<T>::Matrix(vector<vector<T>> vector) {
  int new_rows_count = vector.size();
  int new_columns_count = vector[0].size();
  auto new_values = new T *[new_rows_count];
  for (int row_index = 0; row_index < new_rows_count; row_index++) {
	new_values[row_index] = new T[new_columns_count];
	for (int column_index = 0; column_index < new_columns_count; column_index++) {
	  new_values[row_index][column_index] = vector[row_index][column_index];
	}
  }
  rows_count_ = new_rows_count;
  if (rows_count_) columns_count_ = new_columns_count;
  default_value_ = T();
  values_ = new_values;
};

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
  if (this == matrix) return *this;
  this->~Matrix();
  columns_count_ = matrix.columns_count_;
  rows_count_ = matrix.rows_count_;
  default_value_ = matrix.default_value_;
  values_ = matrix.values_;
  return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
  if (values_ == nullptr) return;
  for (int row_index = 0; row_index < rows_count_; row_index++) {
	if (values_[row_index])
	  delete[] values_[row_index];
  }
  delete[] values_;
}




template<typename T>
T &Matrix<T>::operator[](Index index) {
  if (index.m < 0) index.m += columns_count_;
  if (index.n < 0) index.n += rows_count_;
  if (index.m >= columns_count_ || index.n >= rows_count_) {
	if (index.safe) return default_value_;
	throw std::out_of_range("Index out of range!");
  }
  return values_[index.n][index.m];
};

template<typename T>
bool Matrix<T>::operator==(Matrix<T> &matrix) {
  if (columns_count_ != matrix.columns_count_) return false;
  if (rows_count_ != matrix.rows_count_) return false;
  if (default_value_ != matrix.default_value_) return false;
  for (int row_index = 0; row_index < rows_count_; row_index++) {
  	for (int column_index = 0; column_index < columns_count_; column_index++) {
	  if (values_[row_index][column_index] != matrix.values_[row_index][column_index]) return false;
	}
  }
  return true;
}

template<typename T>
Matrix<T>& Matrix<T>::operator++() {
  Resize(columns_count_ + 1, rows_count_ + 1);
  return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator--() {
  Resize(columns_count_ - 1, rows_count_ - 1);
  return *this;
}




template<typename T>
void Matrix<T>::Save(const string &path) {
  std::ofstream outputStream(path);
  outputStream << rows_count_ << "\t";
  outputStream << columns_count_ << "\n";
  for (int row_index = 0; row_index < rows_count_; row_index++) {
	for (int column_index = 0; column_index < columns_count_; column_index++) {
	  outputStream << values_[row_index][column_index] << "\t";
	}
	outputStream << "\n";
  }
  outputStream.close();
}

template<typename T>
void Matrix<T>::Load(const string &path) {
  std::ifstream inputStream(path);
  if (!inputStream.is_open()) throw std::out_of_range("File does not exist!");
  auto read_next = [&inputStream](auto &value) {
	if (inputStream) inputStream >> value;
	else inputStream.close();
	if (!inputStream.is_open()) throw std::out_of_range("Invalid file format!");
  };
  read_next(rows_count_);
  read_next(columns_count_);
  this->~Matrix();
  if (!IsEmpty()) {
	auto new_values = new T *[rows_count_];
	for (int row_index = 0; row_index < rows_count_; row_index++) {
	  new_values[row_index] = new T[columns_count_];
	  for (int column_index = 0; column_index < columns_count_; column_index++) {
		read_next(new_values[row_index][column_index]);
	  }
	}
	values_ = new_values;
  } else {
	columns_count_ = 0;
	rows_count_ = 0;
  }
  inputStream.close();
}

template<typename T>
Matrix<T> Matrix<T>::Slice(unsigned int new_columns_count, unsigned int new_rows_count) const {
  if (new_rows_count > rows_count_ || new_columns_count > columns_count_) {
	throw std::out_of_range("Slice size cannot go beyond the original matrix!");
  }
  auto new_values = new T *[new_rows_count];
  for (int row_index = 0; row_index < new_rows_count; row_index++) {
	new_values[row_index] = new T[new_columns_count];
	for (int column_index = 0; column_index < new_columns_count; column_index++) {
	  new_values[row_index][column_index] = values_[row_index][column_index];
	}
  };
  return Matrix<T>(new_columns_count, new_rows_count, new_values, default_value_);
};

template<typename T>
Matrix<T> Matrix<T>::Copy() const {
  return Slice(columns_count_, rows_count_);
}

template<typename T>
void Matrix<T>::Resize(unsigned int new_columns_count, unsigned int new_rows_count) {
  if (new_rows_count == 0 || new_columns_count == 0) {
	columns_count_ = 0;
	rows_count_ = 0;
	this->~Matrix();
	return;
  }
  auto new_values = new T *[new_rows_count];
  for (int row_index = 0; row_index < new_rows_count; row_index++) {
	new_values[row_index] = new T[new_columns_count];
	for (int column_index = 0; column_index < new_columns_count; column_index++) {
	  new_values[row_index][column_index] = operator[]({row_index, column_index, true});
	}
  }
  this->~Matrix();
  columns_count_ = new_columns_count;
  rows_count_ = new_rows_count;
  values_ = new_values;
};

template<typename T>
Matrix<T> Matrix<T>::Transpose() {
  auto values = new T *[columns_count_];
  for (int column_index = 0; column_index < columns_count_; column_index++) {
	values[column_index] = new T[rows_count_];
  	for (int row_index = 0; row_index < rows_count_; row_index++) {
	  values[column_index][row_index] = values_[row_index][column_index];
	}
  }
  return Matrix(rows_count_, columns_count_, values, default_value_);
}

template<typename T>
bool Matrix<T>::IsEmpty() {
  return this->columns_count_ == 0 || this->rows_count_ == 0;
}


#endif //MATRIX__MATRIX_H_
