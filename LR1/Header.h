#pragma once

using namespace std;

/// \file
/// \brief ���� Header � ����������� �������, ����������, �������, �������������, ������������, ���������� ����������.

/*!
	\brief �����, ����������� �������.
	\authors Miroshnichenko Kostya
	\version 1.0
	\date 9/16/2022
*/
class Matrix
{
private:
	/// \brief ��������� ����������� ������ ������� �� ��� X.
	int size_x;

	/// \brief ��������� ����������� ������ ������� �� ��� Y.
	int size_y;

	/// \brief ��������� ������ ��� ������������� ���������� �������.
	int** Content;
	
	/// \brief ���������, ����������� �������� true ��� false, � ����������� �� ����, ���������� �� ������� ������ ������� ��� ���.
	bool ReturnExistTemp;

	/// \brief ����������, ����������� �������� true ��� false, � ����������� �� ����, ����� �� ������ ������ ����������� ������� ��� ���.
	bool MatrixExist;

public:
	/// \brief �����������, � ������� ������ ������� �� ��������� [0]x[0].
	Matrix();

	/// \brief �����������, ������� ������� ������� � ����������� �� ��������, ������� ���� ������������ ����� �������.
	/// \param ���������� ����������, ������������ ������ ������� �� ���� X � Y.
	Matrix(int, int);

	/// \brief ����������, ��� �������� ������������� ���������� �������.
	~Matrix();

	/// \brief �������, ������� ������� ������� (������������ ��������� ������).
	void DynamicArray();

	/// \brief �������, ������� ��������� 3 ����� �������.
	void NormOfMatrix();

	/// \brief �������, ������� ��������� ����������� �������.
	double DeterminantOfMatrix();

	/// \brief ���������� ��������� ������, ��� ������ ���� ��������� �������.
	/// \param ���������� ������ �� �������.
	friend ostream& operator<< (ostream&, Matrix&);

	/// \brief ���������� ��������� �����, ��� ����� ��������� �������.
	/// \param ���������� ������ �� �������.
	friend istream& operator>> (istream&, Matrix&);

	/// \brief ���������� ��������� ��������, ��� ��������� ����� ���� ������.
	/// \param ���������� ������ �� �������.
	Matrix operator+ (Matrix&);

	/// \brief ���������� ��������� ��������, ��� ��������� �������� ���� ������.
	/// \param ���������� ������ �� �������.
	Matrix operator- (Matrix&);

	/// \brief ���������� ��������� ������������, ��� ��������� ������������ ���� ������.
	/// \param ���������� ������ �� �������.
	Matrix operator* (Matrix&);

	/// \brief ���������� ��������� ������������, ��� ��������� ������������ ������� c ������.
	/// \param ���������� ����������, ������� �������� ������ ��� ������������ � ��������.
	Matrix operator* (int);

	/// \brief ���������� ��������� �������, ��� ��������� ������� ������� �� ������.
	/// \param ���������� ����������, ������� �������� ������ ��� ������� � ��������.
	Matrix operator/ (int);

	/// \brief ���������� ��������� �������, ��� ��������� ������� � ����������� �������.
	/// \param ���������� ����������, ������� �������� �������� �������.
	Matrix operator^ (int);

	/// \brief ���������� ��������� ����������, ��� ����, ���� ����� ������� ��������� ������.
	/// \param ���������� ������ �� ����������� �������.
	Matrix& operator= (const Matrix&);

	/// \brief ���������� ��������� ����������, ��� ���������� �������.
	Matrix& operator++ ();

	/// \brief ���������� ��������� �����������, ��� ���������� �������.
	Matrix& operator-- ();
};


/*!
	\brief ����� ��� ������ �������� ��� ��������.
	\authors Miroshnichenko Kostya
	\version 1.0
	\date 9/16/2022
*/ 
class Solution
{
private:
	/// \brief ��������� ����������� ����� �������� ��� ��������.
	int way;

public:
	/// \brief ������� ��� ���������� �������� ���� ���������.
	int Get_1();

	/// \brief ������� ��� ���������� �������� ���� ���������.
	int Get_2();
};