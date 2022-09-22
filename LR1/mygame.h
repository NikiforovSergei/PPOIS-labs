///\file game.h
/// \brief заголовочный файл классов, используемых в этой игре
/// содержит классы Puzzle и Menu
///
/// \author ZayatsDmitry
/// \date 21.09.2022

#include <string>
#include <vector>

using  namespace std;

/// \brief класс Puzzle
/// \details Класс Puzzle реализуют игру "15"
class Puzzle
{
private:
	//! вектор векторов, содержащий решенную игра
	vector<vector<int>> solved_puzzle = { {1,2,3,4},
										 {5,6,7,8},
										 {9,10,11,12},
										 {13,14,15,0} };
	//! вектор, содержащий значения от 0 до 15 
	vector<int> list;
	//! вектор векторов, содержащий игровое поле
	vector<vector<int>> game_board{ 4,vector<int>(4) };
	//! размер игрового поля
	static const int board_size = 4;
	//! размер списка значений
	static const int list_size = 16;
	//! координаты пустой клетки
	int X_x, X_y;

public:
	/// \brief конструктор
	Puzzle();
	/// \brief сортировка списка значений
	/// \see vector<int> list
	void shuffling();  
	/// \brief проверка на победу
	/// \see vector<vector<int>> game
	/// \see vector<vector<int>> solved_puzzle
	/// \return true, если вектора равны
	/// \return false, в ином случае
	bool checker();
	/// \brief заполнение списка значений элементами
	/// \see static const int list_size
	/// \see vector<int> list
	void list_filling();
	/// \brief проверка конфигурации на возможность ее решить
	/// \see vector<int> list
	/// \see static const list_size
	/// \see int res
	/// \see int e 
	/// \return true, если конфигурация решаема
	/// \return false, в ином случае
	bool is_it_solvable();
	/// \brief заполнение игрового поля
	/// \see vector<int> list
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see static const list_size
	void board_filling();
	/// \brief поиск координат пустой клетки
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see int X_x
	/// \see int Y_x
	void x_location();
	/// \brief реализация перемещения 
	/// \see vector<vector<int>> game_board
	/// \see static const board_size
	/// \see int X_x
	/// \see int Y_x
	/// \see char ch
	void move();
	/// \brief перегрузка оператора инфексации 
	/// \param n, размер вектора
	/// \throw exception при не соблюдении границ вектора list
	int& operator[ ](int);
	/// перегрузка оператора <<
	friend ostream& operator<< (ostream&, Puzzle&);
	/// деструктор
	~Puzzle();
};

/// класс Menu
/// \details класс Menu реализует игровое меню
class Menu
{
private:
	//! выбор пользователя
	int ch;
public:
	/// \brief сеттер для переменной ch
	/// \param сh, выбор пользователя
	void setCh(int ch);
	/// \brief основные параметры меню
	void start_menu();
	/// \brief условия игры
	void conditions_of_the_game();
	/// \brief сообщение о решении головоломки
	void end_of_the_game();
};