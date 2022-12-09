/// \file game.h
/// \brief заголовочный файл классов, используемых в этой программе.
/// содержит классы Puzzle, Menu
///
/// \authors DominikFurs
/// \date 29.10.2022

#include <string>
#include <vector>

using  namespace std;

/// \brief класс Puzzle
/// \details класс Puzzle реализует игру "Пятнашки"
class Puzzle
{
private:
	//! вектор векторов, являющий собой пройденную игру
	vector<vector<int>> solution = { {1,2,3,4},
										 {5,6,7,8},
										 {9,10,11,12},
										 {13,14,15,0} };

	//! вектор, содержащий значения от 0 до 15
	vector<int> list;
	//! вектор векторов, содержащий игровое поле
	vector<vector<int>> board{ 4,vector<int>(4) };

	//! переменные - координаты "нулевой" клетки
	int X, Y;
	//! переменная - размер игрового поля
	static const int board_size = 4;
	//! переменная - размер списка значений
	static const int list_size = 16;

public:
	/// \brief конструктор
	Puzzle();

	/// \brief функция рандомной сортировки списка значений
	/// \see vector<int> list
	void random_sort();

	/// \brief функция проверки победы
	/// \see vector<vector<int>> game
	/// \see vector<vector<int>> solved_puzzle
	/// \return true, если вектора равны
	/// \return false, в ином случае
	bool checker();

	/// \brief заполнение списка значений элементами
	/// \see static const int list_size
	/// \see vector<int> list
	void list_filling();

	/// \brief проверка расстановки элементов на возможность решения
	/// \see vector<int> list
	/// \see static const list_size
	/// \see int res
	/// \see int e 
	/// \return true, если победа возможна
	/// \return false, в ином случае
	bool solve();

	/// \brief заполнение игрового поля
	/// \see vector<int> list
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see static const list_size
	void board_filling();

	/// \brief поиск координат "нулевой" клетки
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see int X_x
	/// \see int Y_x
	/// 
	void coordinate();
	/// \brief функция перемещения нулевой клетки
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see int X_x
	/// \see int Y_x
	/// \see char ch
	void move();
	/// \brief перегрузка оператора индекса
	/// \param n, размер вектора
	/// \throw exception при несоблюдении границ вектора list
	int& operator[ ](int);
	/// перегрузка оператора <<
	friend ostream& operator<< (ostream&, Puzzle&);
	/// деструктор
	~Puzzle();
};

/// класс Menu
/// \details класс Menu реализует игровое поле
class Menu
{
private:
	//! переменная выбора пользователя в меню
	int ch;
public:
	/// \brief сеттер для переменной ch
	/// \param ch - выбор пользователя
	void set_choice(int ch);
	/// \brief функция, выводящая меню
	void start();
	/// \brief функция, выводящая сообщение об условиях игры
	void conditions();
	/// \brief функция, выводящая сообщение о прохождении игры
	void end();
};