/**
 * @file Normal_matrix.h
 * @author Yakavinich Hleb (gleb.yakovinich1990@gmail.com)
 * @brief declaration of class Normal_matrix 
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#ifndef _NORMAL_MATRIX_H_
#define _NORMAL_MATRIX_H_

#include "includes.h"
using namespace std;

/**
 * @brief declaration of class Normal_matrix
 * 
 */
class Normal_matrix
{
private:
    /// @brief matrix represent as 2-dimensions vector
    vector<vector<double>> matrix;

public:

    /// @brief typical setter
    /// @param matrix 
    void set(const vector<vector<double>>& matrix);

    /// @brief typical getter
    /// @return private field - matrix
    vector<vector<double>> get();
    
    /**
     * @brief checking if this Normal_matrix IS anyone custom _type
     * 
     * @param _type 
     * @return true if Normal_matrix IS _type
     * @return false in other cases
     */
    bool type( bool(*_type)(Normal_matrix forCheck) )
    { return _type(*this); }

    /**
     * @brief Construct a new Normal_matrix object
     * 
     * @param colsNum number of columns for matrix 
     * @param rowsNum number of rows for matrix
     * @param fillWith number to fill all cells of matrix. Default is 0
     */
    Normal_matrix(cu_int colsNum, cu_int rowsNum, const double fillWith = 0);

    
    /**
     * @brief Construct a new Normal_matrix object
     * 
     * @param newMatrix
     */
    Normal_matrix(const vector<vector<double>>& newMatrix);
    
    /**
     * @brief Destroy the Normal_matrix object
     * 
     */
    ~Normal_matrix();

    Normal_matrix();

    /**
     * @brief overloading of operator stream input
     * 
     * @param in first operand - input stream
     * @param to second operand - where to input 
     * @return istream& reference to input stream
     */
    friend istream& operator>>(istream& in, Normal_matrix& to);
    
    /**
     * @brief overloading of operator stream output
     * 
     * @param out first operand - output stream
     * @param from second operand - what to output 
     * @return ostream& reference to output stream
     */
    friend ostream& operator<<(ostream& out, const Normal_matrix& from);
   
    /**
     * @brief overloading of operator stream input to file
     * 
     * @param in first operand - input stream from file
     * @param to second operand - where to input
     * @return ifstream& reference to input stream from file
     */
    friend ifstream& operator>>(ifstream& in, Normal_matrix& to);
    
    /**
     * @brief overloading of operator pre increment
     * 
     * @return const Normal_matrix 
     */
    const Normal_matrix operator++();
    
    /**
     * @brief overloading of operator post increment
     * 
     * @return readable const Normal_matrix 
     */
    const Normal_matrix operator++(int);
    
    /**
     * @brief overloading of operator pre decrement
     * 
     * @return readable const Normal_matrix 
     */
    const Normal_matrix operator--();
    
    /**
     * @brief overloading of operator post decrement
     * 
     * @return readable const Normal_matrix 
     */
    const Normal_matrix operator--(int);
    
    
    /**
     * @brief overloading of operator +
     * 
     * @param fst first operand 
     * @param snd second operand
     * @return readable const Normal_matrix 
     */
    friend const Normal_matrix
    operator+(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator -
     * 
     * @param fst first operand 
     * @param snd second operand
     * @return readable const Normal_matrix 
     */
    friend const Normal_matrix
    operator-(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator +=
     * 
     * @param fst first operand
     * @param snd second operand
     */
    friend void
    operator+=(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator -=
     * 
     * @param fst first operand
     * @param snd second operand
     */
    friend void
    operator-=(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator -=
     * 
     * @param fst first operand
     * @param snd second operand
     * @return const Normal_matrix 
     */
    friend const Normal_matrix
    operator*(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator /
     * 
     * @param fst first operand
     * @param snd second operand
     * @return readable const Normal_matrix 
     */
    friend const Normal_matrix
    operator/(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator *=
     * 
     * @param fst first operand
     * @param snd second operand
     */
    friend void
    operator*=(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading of operator /=
     * 
     * @param fst first operand
     * @param snd second operand
     */
    friend void
    operator/=(const Normal_matrix& fst, const Normal_matrix& snd);

    /**
     * @brief overloading /
     * 
     * @param fst first operand
     * @param num second operand
     * @return const Normal_matrix 
     */
    friend const Normal_matrix
    operator/(const Normal_matrix& fst, long long num);

    /**
     * @brief overloading *
     * 
     * @param fst first operand
     * @param num secodn operand
     * @return const Normal_matrix 
     */
    friend const Normal_matrix
    operator*(const Normal_matrix& fst, long long num);

    /**
     * @brief overloading /=
     * 
     * @param fst first operand
     * @param num second operand
     */
    friend void
    operator/=(Normal_matrix& fst, long long num);
    
    /**
     * @brief overloading *=
     * 
     * @param fst first operand
     * @param num second operand
     */
    friend void
    operator*=(Normal_matrix& fst, long long num);
    
    /**
     * @brief overloading of operator ==
     * 
     * @param fst first operand
     * @param snd second operand
     * @return true if fst is equal to snd
     * @return false if fst isn't equal to snd 
     */
    friend bool
    operator==(const Normal_matrix& fst, const Normal_matrix& snd)
    { return fst.matrix == snd.matrix; }

    /**
     * @brief overloading of operator !=
     * 
     * @param fst first operand
     * @param snd second operand
     * @return true if fst isn't equal to snd
     * @return false if fst is equal to snd
     */
    friend bool
    operator!=(const Normal_matrix& fst, const Normal_matrix& snd)
    { return fst.matrix != snd.matrix; }
    
    /**
     * @brief change number of columns of matrix
     * 
     * @param colsNum positive or negative number to increase of decrease number of columns
     * @param fillWith number to fill with empty cells, if colsNum bigger then zero
     */
    void resizeCols(const int colsNum, const double fillWith = 0);
    
    /**
     * @brief change number of columns of matrix
     * 
     * @param rowsNum positive or negative number to increase of decrease number of rows
     * @param fillWith number to fill with empty cells, if rowsNum bigger then zero
     */
    void resizeRows(const int rowsNum, const double fillWith = 0);
    
    /**
     * @brief get reference to cell
     * 
     * @param row row of choosen cell
     * @param col column of choosen cell
     * @return double& read/write reference to data
     */
    double& at(cu_int row, cu_int col);
    
    /**
     * @brief get copy of data in cell
     * 
     * @param row row of choosen cell
     * @param col column of choosen cell
     * @return double readable copy of data
     */
    double at(cu_int row, cu_int col) const;
    
    /**
     * @brief transpose this matrix
     * 
     * @return Normal_matrix& read/write reference to transposed matrix
     */
    Normal_matrix& transpose();
    
    /**
     * @brief calculate determinant of matrix
     * 
     * @return double 
     */
    const double determinant() const;
    
    /**
     * @brief get smaller size matrix(sub matrix)
     * 
     * @param _Angle1 top-left angle of sub matrix
     * @param _Angle2 bottom-right angle of sub matrix
     * @return Normal_matrix 
     */
    Normal_matrix sub
    (pair<cu_int, cu_int> _Angle1, pair<cu_int, cu_int> _Angle2);


private:
    
    /**
     * @brief check is angles are relevant
     * 
     * @param angl1 top-left angle 
     * @param angl2 bottom-right angle
     * @return true if angles are relevant to get sub matrix
     * @return false if angles aren't relevant to get sub matrix
     */
    bool isTrueAngle(pair<cu_int, cu_int> angl1, pair<cu_int, cu_int> angl2);
    
    /**
     * @brief check matrix is it valid
     * 
     * @return true if matrix is valid
     * @return false if matrix isn't valid
     */
    bool isValid() const;

    /**
     * @brief check if matrix is compatible - with 
     * 
     * @param with second matrix
     * @return true if matrix are with the same size
     * @return false if matrix aren't with the same size
     */
    bool isCompatible(const Normal_matrix& with) const;

};

#endif
