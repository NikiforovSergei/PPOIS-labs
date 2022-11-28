#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

class Matrix
{
public:
	/// <summary>
	/// brief constructor
	/// </summary>
	Matrix();
	void readMatrix(ifstream&);
	/// <summary>
	/// brief function of output
	/// </summary>
	void print();
	/// <summary>
	/// brief copy constructor
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Matrix& operator =(const Matrix& other);
	/// <summary>
	/// brief function for getting of matrix member
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <returns></returns>
	int getValue(int i, int j);
	/// <summary>
	/// brief check matrix for squareness
	/// </summary>
	/// <returns></returns>
	bool isSquareMatrix();
	/// <summary>
	/// brief check matrix for diagonality
	/// </summary>
	/// <returns></returns>
	bool isDiagonalMatrix();
	/// <summary>
	/// brief check matrix for zeroness
	/// </summary>
	/// <returns></returns>
	bool isZeroMatrix();
	/// <summary>
	/// brief check matrix for unity
	/// </summary>
	/// <returns></returns>
	bool isUnitMatrix();
	/// <summary>
	/// check matrix for symmetry
	/// </summary>
	/// <returns></returns>
	bool isSymmetricalMatrix();
	/// <summary>
	/// check matrix for upper tringularity
	/// </summary>
	/// <returns></returns>
	bool isUpperTriangularMatrix();
	/// <summary>
	/// check matrix for lower tringularity
	/// </summary>
	/// <returns></returns>
	bool isLowerTriangularMatrix();
	/// <summary>
	/// brief cconstructor of matrix with given size
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	Matrix(int, int);
	/// <summary>
	/// brief change string number
	/// </summary>
	/// <param name=""></param>
	void ChangeString(int);
	/// <summary>
	/// brief change column number
	/// </summary>
	/// <param name=""></param>
	void ChangeColumn(int);
	/// <summary>
	/// brief getting submatrix of given size
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	void Submatrix(int, int);
	/// <summary>
	/// brief transposition of matrix
	/// </summary>
	void Trans();
	///<summary>
	///brief destructor
	/// </summary>
	~Matrix();
private:
	/// <summary>
	/// brief number of columns
	/// </summary>
	int m;//столбцы
	/// <summary>
	/// brief number for strings
	/// </summary>
	int n;//строки
	/// <summary>
	/// brief array of matrix
	/// </summary>
	int** ARR;

};