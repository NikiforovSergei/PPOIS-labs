///\file
///INPUT_ENCODING ANSI CP1251
/**
*    \brief Заголовочный файл с описанием игры "Кубик рубика"
*    \author Admin (Савицкий И.В.)
*    \version 1.0
*    \date 11.09.2022
*    \warning Создано в рамках задач варианта 1.5.3. лабораторной работы 1.1 по учебному предмету ППОИС
*
*    Реализация игры "Кубик рубика" на языке С++. Данный файл содержит в себе определение основных классов, функий и т.д.
*/
#pragma once
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
class Cube;
std::istream& operator>>(std::istream& is, Cube& cube);
std::ostream& operator>>(std::ostream& os, const Cube& cube);
class Cube
{
private:
	/**
	*   \brief Edge граней куба
	*   \author Admin (Савицкий И.В.)
	*   \date 04.09.2022.
	*   \warning Данный Edge вложен в класс Cube. Модификатор доступа private.
	*
	*   
	*/
	class Edge 
	{
	private:
		/**
	*   \brief cells клетки грани
	*   \author Admin (Савицкий И.В.)
	*   \date 04.09.2022.
	*   \warning Данный cells вложен в класс Edge. Модификатор доступа private.
	*
	*	хранит цвета клеток
	*/
		std::vector<char> cells;
	public:
		/**
	*   конструктор создания грани
	*	\param data Цвета клеток, которые должны иметь клетки после создания
	*/
		Edge(std::vector<char> data);
		/**
	*   конструктор копирования грани
	*	\param other ссылка на грань от которой копируем 
	*/
		Edge(const Edge& other);
		/**
	*   оператор сравнения 
	* \param other ссылка на грань с которой сравниваем
	*/
		bool operator ==(const Edge& other); 
		/**   оператор сравнения 
	* \param other ссылка на грань с которой сравниваем
	*/
		bool operator !=(const Edge& other); 
		/**
	*   геттер 
	*	берёт вектор цветов клеток
	*/
		std::vector<char> getCells(); 
		std::vector<char> getCells() const;
		/**
	*   геттер
	*	\param номер клетки которую берём
	*/
		char getOneCell(int counter); 
		/**
	*   сеттер всех клеток
	*	\param вектор цветов клеток
	*/
		void setCells(const std::vector<char> & data);
		/**
	*   сеттер верхней строки
	*	\param вектор цветов клеток
	*/
		void setTopRove(const std::vector<char>& data); 
		/**
	*   сеттер нижней строки
	*	\param вектор цветов клеток
	*/
		void setBotRove(const std::vector<char>& data); 
		/**
	*   сеттер левого столбца
	*	\param вектор цветов клеток
	*/
		void setLeftColumn(const std::vector<char>& data); 
		/**
	*   сеттер правого столбца
	*/
		void setRightColumn(const std::vector<char>& data); 
		/**
	*   геттер верхней строки
	*/
		std::vector<char> getTopRove();
		/**
	*   геттер нижней строки
	*/
		std::vector<char> getBotRove(); 
		/**
	*   геттер левого столбца
	*/
		std::vector<char> getLeftColumn(); 
		/**
	*   геттер правого столбца
	*/
		std::vector<char> getRightColumn(); 
		/**
	*   поворачивает по часовой стрелке клетки
	*/
		void rotateClocwise(); 
	};
	/**
	*   \brief edges грани
	*   \author Admin (Савицкий И.В.)
	*   \date 04.09.2022.
	*   \warning Данный edges вложен в класс Cube. Модификатор доступа private.
	*
	*	хранит состояния граней
	* 0- front, 1- back, 2- left, 3- right, 4- top, 5- bot.
	*/
	std::vector<Edge> edges;
	/**
	*   оператор потока ввода
	* \param other ссылка на грань с которой сравниваем
	*/
	friend std::istream& operator>>(std::istream& is, Cube& cube);
	/**
	*   оператор потока вывода
	* \param other ссылка на грань с которой сравниваем
	*/
	friend std::ostream& operator>>(std::ostream& os, const Cube& cube);
public:
	/**
	*   конструктор создания куба
	*/
	Cube(); 
	/**
	*   конструктор копирования грани
	*	\param other ссылка на куб от которого копируем
	*/
	Cube(const Cube& other); 
	/**
	*   оператор присваивания
	* \param other ссылка на куб значения которого призваиваем
	*/
	void operator = (const Cube& other); 
	/**
	*   оператор сравнения
	* \param other ссылка на куб с которым сравниваем
	*/
	bool operator ==(const Cube& other); 
	/**
	*   оператор сравнения
	* \param other ссылка на куб с которым сравниваем
	*/
	bool operator !=(const Cube& other); 
	/**
	*   геттер
	*	берёт вектор цветов всех клеток
	*/
	std::vector<char> getCube(); 
	/**
	*   геттер
	*	берёт вектор цветов всех клеток
	*/
	std::vector<char> getCube() const; 
	/**
	*   Загружает куб по данному вектору цветов
	*	
	*/
	void loadCube(std::vector<char> data);
	/**
	*   Поворачивает фронтальную грань по часовой стрелке
	*	
	*/
	void rotateClockwiseFrontEdge();
	/**
	*   Поворачивает заднюю грань по часовой стрелке
	*
	*/
	void rotateClockwiseBackEdge();
	/**
	*   Поворачивает левую грань по часовой стрелке
	*
	*/
	void rotateClockwiseLeftEdge();
	/**
	*   Поворачивает правую грань по часовой стрелке
	*
	*/
	void rotateClockwiseRightEdge();
	/**
	*   Поворачивает верхнюю грань по часовой стрелке
	*
	*/
	void rotateClockwiseTopEdge();
	/**
	*   Поворачивает нижнюю грань по часовой стрелке
	*
	*/
	void rotateClockwiseBotEdge();
	/**
	*   Проверяет собранность куба
	*
	*/
	bool checkForWin(); 
};

