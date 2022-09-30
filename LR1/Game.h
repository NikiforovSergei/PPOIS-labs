#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
/*!
	\brief Класс, представляющий реализацию игры "Крестики-нолики"

	Данный класс обладает полным набором функций необходимых для полноценной и комфортной игры: выбор размеров поля, возможность постановки символа,
	проверка ввода всех значений, которые задаются пользователем, а также проверка победы одной из сторон
*/
class krestiki_noliki {
private:
	vector <vector<string>> field_p;
	vector<string> temp;
	string position;
	char x;
	int x_length_p, y_length_p, position_x, position_y;
public:
	void SetLength(int x_length_, int y_length_);
	/*! Задаёт размер игрового поля
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	int GetLength(int x_length, int y_length);
	/*! Получение значений размеров игрового поля
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void init(int x_length, int y_length);
	/*! Инициализация матча, создание игрового поля
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void print(int x_length, int y_length);
	/*! Вывод текущего состояния игрового поля на экран
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void check_win(bool* check, int x_length, int y_length);
	/*! Проверка на победу одной из сторон
	*   \param[check] check индикатор состояния победы (0-ни одна из сторон не победила, 1-победа одной из сторон)
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	int turn_cross(int x_length, int y_length);
	/*! Проверки хода крестиков
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void place_cross(int position_y, int position_x, int x_length, int y_length);
	/*! Установка крестика в указанную позицию
	*   \param[position_y] position_y Координаты клетки по горизонтали в которую необходимо установить крестик
	*	\param[position_x] position_x Координаты клетки по вертикали в которую необходимо установить крестик
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	int turn_zero(int x_length, int y_length);
	/*! Проверки хода ноликов
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void place_zero(int position_y, int position_x, int x_length, int y_length);
	/*! Установка нолика в указанную позицию
	*   \param[position_y] position_y Координаты клетки по горизонтали в которую необходимо установить нолик
	*	\param[position_x] position_x Координаты клетки по вертикали в которую необходимо установить нолик
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void input_error(int* y_pos, int* x_pos, int x_length, int y_length);
	/*! Вывод ошибки о неправильном вводе и запрос повторного ввода
	*   \param[y_pos] position_y Координаты клетки по горизонтали в которую необходимо установить крестик
	*	\param[x_pos] position_x Координаты клетки по вертикали в которую необходимо установить крестик
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
	void InputTypeCheck(int* y_pos, int* x_pos);
	/*! Проверка вводимого типа данных
	*   \param[y_pos] position_y Координаты клетки по горизонтали в которую необходимо установить крестик
	*	\param[x_pos] position_x Координаты клетки по вертикали в которую необходимо установить крестик
	*/
	void correct_input(int* y_pos, int* x_pos, int x_length, int y_length);
	/*! Получение данных от пользователя и проверка клетки
	*   \param[y_pos] position_y Координаты клетки по горизонтали в которую необходимо установить крестик
	*	\param[x_pos] position_x Координаты клетки по вертикали в которую необходимо установить крестик
		\param[x_length] x_length Размер игрового поля по горизонтали
		\param[y_length] y_length Размер игрового поля по вертикали
	*/
};
