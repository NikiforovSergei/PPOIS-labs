//
// Created by Глеб on 1.09.22.
//

#ifndef PPOIS_LABS_MATRIX_H
#define PPOIS_LABS_MATRIX_H


#include <iostream>
#include <fstream>

template <typename T>
class Matrix {
private:
    T** M;
    int rows;
    int columns;

public:
    Matrix();
    Matrix(int rows, int columns);
    ~Matrix();

    void print();
    void printMatrixType();

    T getValue(int i, int j);
    void setValue(int i, int j, T value);
    int getRows();
    int getColumns();

    void changeRows(int changed_rows);
    void changeColumns(int changed_columns);

    Matrix<T> getTransMatrix();
    Matrix<T> getSubMatrix(int x1, int y1, int x2, int y2);

    bool isSquareMatrix();
    bool isDiagonalMatrix();
    bool isZeroMatrix();
    bool isUnitMatrix();
    bool isSymmetricalMatrix();
    bool isUpperTriangularMatrix();
    bool isLowerTriangularMatrix();

    void loadFromFile(std::string fileName);
    void removeMatrix();

    Matrix<T>& operator=(Matrix<T> other) noexcept;
    Matrix<T>& operator++();
    Matrix<T>& operator--();
};



template<typename T>
Matrix<T>::Matrix() {
    rows = columns = 0;
    M = nullptr;
}

template<typename T>
Matrix<T>::Matrix(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;

    M = (T**) new T*[rows];

    for (int i = 0; i < rows; i++) {
        M[i] = (T*) new T[columns];
    }

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<columns; j++) {
            M[i][j] = 0;
        }
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    removeMatrix();
}

template<typename T>
void Matrix<T>::print() {
    if (M!= nullptr) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j<columns; j++) {
                std::cout << M[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "matrix empty" << std::endl;
    }

}

template<typename T>
T Matrix<T>::getValue(int i, int j) {
    if( (i>=0 && j>=0) and (i < rows && j < columns) )
        return M[i][j];
    else
        return 0;
}

template<typename T>
void Matrix<T>::setValue(int i, int j, T value) {
    if( (i>=0 && j>=0) and (i <= rows && j <= columns) )
        M[i][j] = value;
    else
        return;
}

template<typename T>
void Matrix<T>::changeRows(int changed_rows) {
    T** changedM = new T*[changed_rows];
    for (int i = 0; i < changed_rows; i++) {
        changedM[i] = (T*) new T[columns];
    }

    for (int i = 0; i<changed_rows; i++) {
        for (int j = 0; j<columns; j++) {
            changedM[i][j] = this->getValue(i,j);
        }
    }

    this->removeMatrix();
    this->rows = changed_rows;
    this->M = changedM;
}

template<typename T>
void Matrix<T>::changeColumns(int changed_columns) {
    T** changedM = new T*[rows];
    for (int i = 0; i < rows; i++) {
        changedM[i] = (T*) new T[changed_columns];
    }

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<changed_columns; j++) {
            changedM[i][j] = this->getValue(i,j);
        }
    }

    this->removeMatrix();
    this->columns = changed_columns;
    this->M = changedM;
}

template<typename T>
void Matrix<T>::loadFromFile(std::string fileName) {
    std::string buff;
    std::ifstream file(fileName);
    if (file.is_open()) {
        removeMatrix();
        file >> this->rows;
        file >> this->columns;

        T** newM = new T*[rows];
        for (int i = 0; i < rows; i++) {
            newM[i] = (T*) new T[columns];
        }

        for (int i=0; i<rows; i++)
            for (int j=0; j<columns; j++)
                file >> newM[i][j];

        this->M = newM;
    }
    else {
        std::cout << "file not founded";
    }
}

template<typename T>
Matrix<T> Matrix<T>::getTransMatrix() {
    if (this->M!= nullptr and this->isSquareMatrix()) {
        Matrix<T> transMatrix = Matrix<T>(rows, columns);

        for(int i = 0; i<rows; i++){
            for(int j = 0; j<columns; j++){
                transMatrix.setValue(i,j,this->getValue(j,i));
            }
        }

        return  transMatrix;
    }
    else
        throw std::out_of_range("impossible to get transparent matrix");
}

template<typename T>
Matrix<T> Matrix<T>::getSubMatrix(int x1, int y1, int x2, int y2) {

    if (
        (x1>=0 && y1>=0) && (x2>=x1 && y2>=y1)
        &&
        (x2<=rows && y2<=columns)
            ) {

        x2++; //не включая столбцы с пересечением на x2 y2
        y2++; //

        int new_rows = x2 - x1;
        int new_columns = y2 - y1;

        Matrix<T> subMatrix = Matrix<T>(new_rows, new_columns);

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
    }
    else
        throw std::out_of_range("impossible to get sub matrix");
}

template<typename T>
bool Matrix<T>::isSquareMatrix() {
    return M != nullptr && rows == columns;
}

template<typename T>
bool Matrix<T>::isDiagonalMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if ( i!=j and this->getValue(i,j) != 0 )
                return false;
        }
    }
    return this->isSquareMatrix();
}

template<typename T>
bool Matrix<T>::isZeroMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if ( this->getValue(i,j) != 0 )
                return false;
        }
    }
    return true;
}

template<typename T>
bool Matrix<T>::isUnitMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if ( (i!=j and this->getValue(i,j) != 0) or (i==j and this->getValue(i,j) != 1))
                return false;
        }
    }
    return this->isSquareMatrix();
}

template<typename T>
bool Matrix<T>::isSymmetricalMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if (this->getValue(i,j) != this->getValue(j,i))
                return false;
        }
    }
    return this->isSquareMatrix();
}

template<typename T>
bool Matrix<T>::isUpperTriangularMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if (i>j and this->getValue(i,j)!=0)
                return false;
        }
    }
    return this->isSquareMatrix();
}

template<typename T>
bool Matrix<T>::isLowerTriangularMatrix() {
    for (int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if (i<j and this->getValue(i,j)!=0)
                return false;
        }
    }
    return this->isSquareMatrix();
}

template<typename T>
void Matrix<T>::printMatrixType() {
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

template<typename T>
void Matrix<T>::removeMatrix() {
    if (rows > 0) {
        for (int i = 0; i < rows; i++) {
            delete[] M[i];
        }
    }

    if (columns > 0) {
        delete[] M;
    }
}

template<typename T>
int Matrix<T>::getRows() {
    return rows;
}

template<typename T>
int Matrix<T>::getColumns() {
    return columns;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> other)  noexcept {
    if (this == &other)
        return *this;

    this->removeMatrix();
    this->M=other.M;
    this->rows=other.rows;
    this->columns=other.columns;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator++() {
    this->changeRows(this->rows+1);
    this->changeColumns(this->columns+1);
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator--() {
    this->changeRows(this->rows-1);
    this->changeColumns(this->columns-1);
    return *this;
}

#endif //PPOIS_LABS_MATRIX_H
