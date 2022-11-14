//
// Created by Глеб on 1.09.22.
//

#ifndef PPOIS_LABS_MATRIX_H
#define PPOIS_LABS_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>

class Matrix {
 public:
  /**
   * @brief Конструктор без параметров, инициализирует размеры матрицы нулями.
   * @arg @c rows = 0;
   * @arg @c columns = 0;
   */
  Matrix();

  /**
   * @brief Конструктор копирования. Он вызывается когда новый объект создаётся
   * на основе существующего.
   * @param other - копируемая матрица
   */
  Matrix(const Matrix &other);

  /**
   * @brief В деструкторе высвобождается задействованная память.
   */
//  ~Matrix();

  /**
   * @brief Возвращает значение из i строки j столбца матрицы, если такового
   * нет, возвращает 0.
   * @param i - строка матрицы (i>0)
   * @param j - столбец матрицы (j>0)
   * @return int - значение ячейки матрицы или 0
   */
  int getValue(int i, int j);

  /**
   * @brief Устанавливает переданное значение в i строке j столбце матрицы.
   * @param i - строка матрицы (i>0)
   * @param j - столбец матрицы (j>0)
   * @param value - значение
   */
  void setValue(int i, int j, int value);

  /**
   * @brief Возвращает количество строк матрицы.
   * @return int - количество строк матрицы.
   */
  int getRows() const;

  std::vector<int> &getRow(int n);

  /**
   * @brief Возвращает количество столбцов матрицы.
   * @return int - количество столбцов матрицы.
   */
  int getColumns() const;

  std::vector<int> *getColumn(int n);

  /**
   * @brief Изменяет количество строк на переданное значение.
   * @details Матрица или обрезается, или пустые ячейки заполняются нулями.
   * @param changed_rows - новое значение количества строк матрицы.
   */
  void addRows();

  void removeRows(int n);

  /**
   * @brief Изменяет количество столбцов на переданное значение,
   * @details Матрица или обрезается, или пустые ячейки заполняются нулями.
   * @param changed_columns - новое значение количества столбцов матрицы.
   */
  void addColumns();

  void removeColumns(int n);

  void clear();

  bool operator!=(Matrix const &other) const {
    return this->M != other.M;
  }
  bool operator==(Matrix const &other) const {
    return this->M == other.M;
  }
  friend bool operator==(const Matrix &it1, const Matrix &it2) {
    return it1.M == it2.M;
  }

  friend bool operator!=(const Matrix &it1, const Matrix &it2) {
    return it1.M != it2.M;
  }

 private:
  std::vector<std::vector<int>> M;

  int rows;
  int columns;
};

#endif  // PPOIS_LABS_MATRIX_H
