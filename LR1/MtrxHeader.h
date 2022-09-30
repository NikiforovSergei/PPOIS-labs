/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определение класса и основных методов класса, используемых в программе.
*/
#pragma once
#include <iostream>
#include <vector>
using std::vector;
/*!
\brief Класс вещественной матрицы

Данный класс содержит методы по сложению, вычитанию, умножению, делению матриц, также вычисления детермината и
норм матрицы.
*/
class Mtrx
{
private: 
	vector<vector<float>> mtrx;
	float determinant_utility(vector<vector<float>>& mtrx, int mtrx_size);
	void subMatrix(vector<vector<float>>& mtrx, vector<vector<float>>& temp, int p, int q, int n);
	int get_y_size();
	int get_x_size();
	float get_elm_by_index(int x_index, int y_index);
	void set_elm_by_index(int& x_index, int& y_index, float& elm);
	vector<vector<float>> get_current_mtrx();
	vector<float> get_line_by_index(int y_index);
	vector<float> get_column_by_index(int x_index);
public:
	/// <summary>
	/// Метод предназначен для инициализации матрицы.
	/// </summary>
	/// <param name="input_values">Массив вещественных чисел для заполнения матрицы.</param>
	/// <param name="size_y">Количество строк матрицы.</param>
	/// <param name="size_x">Количество столбцов матрицы.</param>
	void init(const vector<float>& input_values, const int& size_y, const int& size_x);
	/// <summary>
	/// Вывод матрицы на экран.
	/// </summary>
	void print_mtrx();
	/// <summary>
	/// Очистка текущей матрицы.
	/// </summary>
	void clear_current_mtrx();
	/// <summary>
	/// Перегрузка оператора(+). Выполнение операции сложения 2ух матриц.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат). 
	/// </summary>
	/// <param name="right">Передача в метод, второй матрицы для выполнения операции сложения. </param>
	/// <returns>Mtrx sum_res</returns>
	const Mtrx operator+(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(+=). Выполнение операции сложения 2ух матриц.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="right">Передача в метод, второй матрицы для выполнения операции сложения.</param>
	const void operator+=(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(-). Выполнение операции вычитания 2ух матриц.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат). 
	/// </summary>
	/// <param name="right">Передача в метод, второй матрицы для выполнения операции вычитания.</param>
	/// <returns>Mtrx difference_res</returns>
	const Mtrx operator-(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(-=). Выполнение операции вычитания 2ух матриц.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="right">Передача в метод, второй матрицы для выполнения операции вычитания.</param>
	const void operator-=(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(+). Выполнение операции сложения матрицы и вещественного числа.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат).
	/// </summary>
	/// <param name="addition_value">Передача в метод,вещественного числа для выполнения операции сложения.</param>
	/// <returns>Mtrx addition_res</returns>
	const Mtrx operator+(float addition_value);
	/// <summary>
	/// Перегрузка оператора(+). Выполнение операции сложения матрицы и вещественного числа.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="addition_value">Передача в метод,вещественного числа для выполнения операции сложения.</param>
	const void operator+=(float addition_value);
	/// <summary>
	/// Перегрузка оператора(-). Выполнение операации вычитания из матрицы вещественного числа.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат). 
	/// </summary>
	/// <param name="difference_value">Передача в метод,вещественного числа для выполнения операции вычитания</param>
	/// <returns>Mtrx difference_res</returns>
	const Mtrx operator-(float difference_value);
	/// <summary>
	/// Перегрузка оператора(-=). Выполнение операации сложения матрицы и вещественного числа.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="difference_value">Передача в метод,вещественного числа для выполнения операции вычитания</param>
	const void operator-=(float difference_value);
	bool check_multiplication_possibility(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(*). Выполнение операции умножения 2ух матриц.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат). 
	/// </summary>
	/// <param name="right">Передача в метод, второй матрицы для выполнения операции произведения. </param>
	/// <returns>Mtrx multiplication_res</returns>
	const Mtrx operator*(Mtrx& right);
	/// <summary>
	/// Перегрузка оператора(*). Выполнение операции умножения матрицы на вещественное число.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат). 
	/// </summary>
	/// <param name="multiplication_value">Передача в метод,вещественного числа для выполнения операции произведения.</param>
	/// <returns>Mtrx multiplication_res</returns>
	const Mtrx operator*(float multiplication_value);
	/// <summary>
	/// Перегрузка оператора(*=). Выполнение операции сложения матрицы и вещественного числа.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="multiplication_value">Передача в метод,вещественного числа для выполнения операции произведения.</param>
	const void operator*=(float multiplication_value);
	/// <summary>
	/// Перегрузка оператора(/). Выполнение операции деления матрицы на вещественное число.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат).
	/// </summary>
	/// <param name="division_value">Передача в метод,вещественного числа для выполнения операции деления.</param>
	/// <returns>Mtrx division_res</returns>
	const Mtrx operator/(float division_value);
	/// <summary>
	/// Перегрузка оператора(/=). Выполнение операции сложения матрицы и вещественного числа.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="division_value">Передача в метод,вещественного числа для выполнения операции деления.</param>
	const void operator/=(float division_value);
	/// <summary>
	/// Перегрузка оператора(^). Выполнение операции возведения в степень матрицы.
	/// Результатом выполнения станет новый объект класса Mtrx, матрица С(результат).
	/// </summary>
	/// <param name="involution_value">Передача в метод,целого числа для выполнения операции возведения в степень</param>
	/// <returns>Mtrx res_mtrx</returns>
	const Mtrx operator^(int involution_value);
	/// <summary>
	/// Перегрузка оператора(^=). Выполнение операции возведения в степень матрицы.
	/// Результат выполения записывается в текущую матрицу.  
	/// </summary>
	/// <param name="involution_value">Передача в метод,вещественного числа для выполнения операции возведения в степень.</param>
	const void operator^=(int involution_value);
	/// <summary>
	/// Метод по вычислению определителя(детерминанта) матрицы.
	/// Результатом станет вещественное число.
	/// </summary>
	/// <returns>float determinant</returns>
	float determinant();
	/// <summary>
	/// Метод по вычислению M-нормы матрицы.
	/// Результатом станет вещественное число.
	/// </summary>
	/// <returns>float M_norm</returns>
	float M_normal_mtrx();
	/// <summary>
	/// Метод по вычислению L-нормы матрицы.
	/// Результатом станет вещественное число.
	/// </summary>
	/// <returns>float L_norm</returns>
	float L_normal_mtrx();
	/// <summary>
	/// Метод по вычислению K-нормы матрицы.
	/// Результатом станет вещественное число.
	/// </summary>
	/// <returns>float K_norm</returns>
	float K_normal_mtrx();
};