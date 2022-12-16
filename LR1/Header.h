/**
 * @file Header.h
 * @author A. Yahya-zada (aylin.yakhyazade@gmail.com)
 * @brief This file is the header file created to work with numeric matrices.
 * @version 0.1
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Matrix
{
  public:

    Matrix(int n);
    /**
    * @brief Find the sum of matrixes.
    * @details Sums all correspondings elements of a matrix.
    * 
    * @param Matrix is another matrix
    * 
    * @author A. Yahya-zada
    */
    Matrix operator + (Matrix &);
    /**
    * @brief Find the sum of a matrix and a number.
    * @details Adds a number to all the elements of a matrix.
    * 
    * @param number is the number
    * 
    * @author A. Yahya-zada
    */
    Matrix operator + (int number);
    /**
    * @brief Substract another matrix from the matrix.
    * @details Substracts all the correspoiding elenemts of another matrix from the matrix.
    * 
    * @param Matrix is another matrix
    * 
    * @author A. Yahya-zada
    */
    Matrix operator - (Matrix &);
    /**
    * @brief Substract a number from the matrix.
    * @details Substracts a number from all the elements of the matrix.
    * 
    * @param number is the number
    * 
    * @author A. Yahya-zada
    */
    Matrix operator - (int number);
    /**
    * @brief Multiplies matrixes.
    * @details Multiplies every element fo a matrix by every corresponding element of another matrix.
    * 
    * @param Matrix is another matrix
    * 
    * @author A. Yahya-zada
    */
    Matrix operator * (Matrix &);
    /**
    * @brief Multiplies a matrix by a number.
    * @details Multiplies every element fo a matrix by a number.
    * 
    * @param number is the number
    * 
    * @author A. Yahya-zada
    */
    Matrix operator * (int number);
    /**
    * @brief Divides a matrix by a number.
    * @details Divides every element of a matrix by a number.
    * 
    * @param number is the number
    * 
    * @author A. Yahya-zada
    */
    Matrix operator / (int number);
    /**
    * @brief Raising a matrix to a power of a number.
    * @details Raises every element of a matrix to a power of a number.
    * 
    * @param number is the number
    * 
    * @author A. Yahya-zada
    */
    Matrix operator ^ (int number);
    /**
    * @brief Finds the minor of a matrix.
    * @details Finds the line with the biggets sum of the elements.
    * 
    * @author A. Yahya-zada
    */
    void Minor();
    /**
    * @brief Finds the determinant of a matrix.
    * @details Finds the determinant of any matrix.
    * 
    * @author A. Yahya-zada
    */
    void Determinant();
    /**
    * @brief Constructor by default
    * @details Frees the memory set for ARR.
    * 
    * @author A. Yahya-zada
    */
    ~Matrix()
    {
	    for (int i = 0; i < n; i++)
	      delete[] ARR[i];
    	delete[] ARR;
    }  
    /**
    * @brief Matrix print.
    * @details Prints a matrix.
    * 
    * @author A. Yahya-zada
    */
    void print_matrix();

  private:

    int n;

    int** ARR;


};

 