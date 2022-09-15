//
// Created by Глеб on 1.09.22.
//

#ifndef PPOIS_LABS_MATRIX_H
#define PPOIS_LABS_MATRIX_H

#include <fstream>
#include <iostream>

/**
 * @brief Класс матрицы.
 * @details Класс, реализует тип данных "Вещественная матрица". Класс реализует
 * следующие возможности:
 * 1. изменение числа строк и числа столбцов;
 * 2. загрузка матрицы из файла;
 * 3. извлечение подматрицы заданного размера;
 * 4. проверка типа матрицы (квадратная, диагональная, нулевая, единичная,
 * симметрическая, верхняя треугольная, нижняя треугольная);
 * 5. транспонированние матрицы;
 * @author Левков Глеб
 * @date 2022-09-10
 */

class Matrix {
 public:
  /**
   * @brief Конструктор без параметров, инициализирует размеры матрицы нулями.
   * @arg @c rows = 0;
   * @arg @c columns = 0;
   */
  Matrix();

  /**
   * @brief Конструктор инициализирующий матрицу переданными значениями строк и
   * колонок.
   * @param rows - количество строк
   * @param columns - количество столбцов
   */
  Matrix(int rows, int columns);

  /**
   * @brief Конструктор копирования. Он вызывается когда новый объект создаётся
   * на основе существующего.
   * @param other - копируемая матрица
   */
  Matrix(const Matrix& other);

  /**
   * @brief В деструкторе высвобождается задействованная память.
   */
  ~Matrix();

  /**
   * @brief Возвращает значение из i строки j столбца матрицы, если такового
   * нет, возвращает 0.
   * @param i - строка матрицы (i>0)
   * @param j - столбец матрицы (j>0)
   * @return double - значение ячейки матрицы или 0
   */
  double getValue(int i, int j);

  /**
   * @brief Устанавливает переданное значение в i строке j столбце матрицы.
   * @param i - строка матрицы (i>0)
   * @param j - столбец матрицы (j>0)
   * @param value - значение
   */
  void setValue(int i, int j, double value);

  /**
   * @brief Возвращает количество строк матрицы.
   * @return int - количество строк матрицы.
   */
  int getRows();

  /**
   * @brief Возвращает количество столбцов матрицы.
   * @return int - количество столбцов матрицы.
   */
  int getColumns();

  /**
   * @brief Изменяет количество строк на переданное значение.
   * @details Матрица или обрезается, или пустые ячейки заполняются нулями.
   * @param changed_rows - новое значение количества строк матрицы.
   */
  void changeRows(int changed_rows);

  /**
   * @brief Изменяет количество столбцов на переданное значение,
   * @details Матрица или обрезается, или пустые ячейки заполняются нулями.
   * @param changed_columns - новое значение количества столбцов матрицы.
   */
  void changeColumns(int changed_columns);

  /**
   * @brief Возвращает транспонированную матрицу.
   * @throw out_of_range Если невозможно получить подматрицу матрицы.
   * @return Matrix<T> - новая транспонированная матрица.
   */
  Matrix getTransMatrix();

  /**
   * @brief Возвращает под матрицу заданного размера начиная с x1 строки y1
   * столбца, по x2 строки y2 столбца.
   * @param x1 - начальная строка
   * @param y1 - начальный столбец
   * @param x2 - конечная строка
   * @param y2 - конечный столбец
   * @throw out_of_range Если невозможно получить транспонированную матрицу.
   * @return Matrix<T> - сабматрица основной матрицы.
   */
  Matrix getSubMatrix(int x1, int y1, int x2, int y2);

  /**
   * @brief Является ли эта матрица квадратной.
   * @return true - если является, в противном случае false
   */
  bool isSquareMatrix();

  /**
   * @brief Является ли эта матрица диагональной.
   * @return true - если является, в противном случае false
   */
  bool isDiagonalMatrix();

  /**
   * @brief Является ли эта матрица нулевой.
   * @return true - если является, в противном случае false
   */
  bool isZeroMatrix();

  /**
   * @brief Является ли эта матрица единичной.
   * @return true - если является, в противном случае false
   */
  bool isUnitMatrix();

  /**
   * @brief Является ли эта матрица симметричной.
   * @return true - если является, в противном случае false
   */
  bool isSymmetricalMatrix();

  /**
   * @brief Является ли эта матрица верхней треугольной.
   * @return true - если является, в противном случае false
   */
  bool isUpperTriangularMatrix();

  /**
   * @brief Является ли эта матрица нижней треугольной.
   * @return true - если является, в противном случае false
   */
  bool isLowerTriangularMatrix();

  /**
   * @brief Загружает матрицу из файла.
   * @param fileName - имя файла или путь к файлу
   */
  void loadFromFile(std::string fileName);

  /**
   * @brief Переопределяет оператор присваивания.
   * @return Matrix<T>
   */
  Matrix& operator=(Matrix other) noexcept;

  /**
   * @brief Увеличивает количество строк и столбцов матрицы
   * @return Matrix<T> - матрица с изменённым размером.
   */
  Matrix& operator++();

  /**
   * @brief Уменьшает количество строк и столбцов матрицы на 1
   * @return Matrix<T> - матрица с изменённым размером.
   */
  Matrix& operator--();

 private:
  double** M = nullptr;

  int rows;
  int columns;
};

#endif  // PPOIS_LABS_MATRIX_H
