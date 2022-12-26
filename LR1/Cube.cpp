//
// Created by Admin on 04.09.2022.
//
#include "Cube.h"

//конструктор куба
Cube::Cube()
{
	
	char allColor[] = {'r', 'o', 'y', 'g', 'b', 'w'};
	srand(time(0));
	for (int i = 0; i < 6; ++i) 
	{
		std::swap(allColor[i], allColor[std::rand() % 6]);
	}
	for (int i = 0; i < 6; i++)
	{
		std::vector<char> bufferEdgeVector;
		for (int j = 0; j < 9; j++)
		{
			bufferEdgeVector.push_back(allColor[i]);
		}
		Edge bufferEdge(bufferEdgeVector);
		this->edges.push_back(bufferEdge);
	}
	for (int i = 0; i < 12; i++)
	{
		for (int bufferCounter1 = rand() % 30 + 20; bufferCounter1 > 0; bufferCounter1--)
		{
			for (int bufferCounter2 = rand() % 6; bufferCounter2 > 0; bufferCounter2--) 
			{
				this->rotateClockwiseBackEdge();
				this->rotateClockwiseFrontEdge();
			}
			for (int bufferCounter2 = rand() % 6; bufferCounter2 > 0; bufferCounter2--)
			{
				this->rotateClockwiseBotEdge();
				this->rotateClockwiseTopEdge();
			}
			for (int bufferCounter2 = rand() % 6; bufferCounter2 > 0; bufferCounter2--)
			{
				this->rotateClockwiseLeftEdge();
				this->rotateClockwiseRightEdge();
			}
		}
	}
}
//конструктор копирования
Cube::Cube(const Cube& other)
{
	this->edges = other.edges;
}
//оператор присваивания
void Cube::operator=(const Cube& other)
{
	this->edges = other.edges;
}
//оператор сравнения
bool Cube::operator==(const Cube& other)
{
	bool buffer = true;
	for (int i = 0; i < this->edges.size(); i++)
	{
		if (this->edges.at(i) != other.edges.at(i)) 
		{
			buffer = false;
		}
	}
	return buffer;
}
//оператор сравнения
bool Cube::operator!=(const Cube& other)
{
	bool buffer = true;
	for (int i = 0; i < this->edges.size(); i++)
	{
		if (this->edges.at(i) == other.edges.at(i))
		{
			buffer = false;
		}
	}
	return buffer;
}
//геттер куба
std::vector<char> Cube::getCube()
{
	std::vector<char> cube;
	for (int i = 0; i < 6; i++) 
	{
		std::vector<char> buffer;
		buffer = this->edges.at(i).getCells();
		for (int j = 0; j < buffer.size(); j++)
		{
			cube.push_back(buffer.at(j));
		}
	}
	return cube;
}
//геттер куба
std::vector<char> Cube::getCube() const
{
	std::vector<char> cube;
	for (int i = 0; i < 6; i++)
	{
		std::vector<char> buffer;
		buffer = edges.at(i).getCells();
		for (int j = 0; j < buffer.size(); j++)
		{
			cube.push_back(buffer.at(j));
		}
	}
	return cube;
}
//загрущка куба от вектора
void Cube::loadCube(std::vector<char> data)
{
	std::vector<char> buffer;
	for (int i = 0; i < this->edges.size(); i++)
	{
		for (int j = 0; j < 8; j++) 
		{
			buffer.at(j) = data.at(j + 9 * i);
		}
		this->edges.at(i).setCells(buffer);
	}
}
//поворот фронтальной грани по часовой
void Cube::rotateClockwiseFrontEdge()
{
	this->edges.at(0).rotateClocwise();
	this->edges.at(0).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(2).getRightColumn();
	std::swap(buffer1.at(0), buffer1.at(2));
	this->edges.at(2).setRightColumn(this->edges.at(5).getTopRove());
	buffer2 = this->edges.at(3).getLeftColumn();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(5).setTopRove(buffer2);
	this->edges.at(3).setLeftColumn(this->edges.at(4).getBotRove());
	this->edges.at(4).setBotRove(buffer1);
}
//поворот задней грани по часовой
void Cube::rotateClockwiseBackEdge()
{
	this->edges.at(1).rotateClocwise();
	this->edges.at(1).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(3).getRightColumn();
	std::swap(buffer1.at(0), buffer1.at(2));
	this->edges.at(3).setRightColumn(this->edges.at(5).getBotRove());
	buffer2 = this->edges.at(2).getLeftColumn();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(5).setBotRove(buffer2);
	this->edges.at(2).setLeftColumn(this->edges.at(4).getTopRove());
	this->edges.at(4).setTopRove(buffer1);
}
//поворот левой грани по часовой
void Cube::rotateClockwiseLeftEdge()
{
	this->edges.at(2).rotateClocwise();
	this->edges.at(2).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(1).getRightColumn();
	buffer2 = this->edges.at(5).getLeftColumn();
	std::swap(buffer1.at(0), buffer1.at(2));
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(1).setRightColumn(buffer2);
	this->edges.at(5).setLeftColumn(this->edges.at(0).getLeftColumn());
	this->edges.at(0).setLeftColumn(this->edges.at(4).getLeftColumn());
	this->edges.at(4).setLeftColumn(buffer1);
}
//поворот правой грани по часовой
void Cube::rotateClockwiseRightEdge()
{
	this->edges.at(3).rotateClocwise();
	this->edges.at(3).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(0).getRightColumn();
	this->edges.at(0).setRightColumn(this->edges.at(5).getRightColumn());
	buffer2 = this->edges.at(1).getLeftColumn();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(5).setRightColumn(buffer2);
	buffer2 = this->edges.at(4).getRightColumn();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(1).setLeftColumn(buffer2);
	this->edges.at(4).setRightColumn(buffer1);
}

//поворот верхней грани по часовой
void Cube::rotateClockwiseTopEdge()
{
	this->edges.at(4).rotateClocwise();
	this->edges.at(4).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(2).getTopRove();
	std::swap(buffer1.at(0), buffer1.at(2));
	this->edges.at(2).setTopRove(this->edges.at(0).getTopRove());
	this->edges.at(0).setTopRove(this->edges.at(3).getTopRove());
	buffer2 = this->edges.at(1).getTopRove();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(3).setTopRove(buffer2);
	this->edges.at(1).setTopRove(buffer1);
}
//поворот нижней грани по часовой
void Cube::rotateClockwiseBotEdge()
{
	this->edges.at(5).rotateClocwise();
	this->edges.at(5).rotateClocwise();
	std::vector<char> buffer1, buffer2;
	buffer1 = this->edges.at(3).getBotRove();
	std::swap(buffer1.at(0), buffer1.at(2));
	this->edges.at(3).setBotRove(this->edges.at(0).getBotRove());
	this->edges.at(0).setBotRove(this->edges.at(2).getBotRove());
	buffer2 = this->edges.at(1).getBotRove();
	std::swap(buffer2.at(0), buffer2.at(2));
	this->edges.at(2).setBotRove(buffer2);
	this->edges.at(1).setBotRove(buffer1);
}
//проверка собранности куба
bool Cube::checkForWin()
{
	bool buffer = true;
	for (int i = 0; i < this->edges.size(); i++)
	{
		std::vector<char> bufferVector = edges.at(i).getCells();
		for (int j = 0; j < bufferVector.size(); j++) 
		{
			if (bufferVector.at(i) != bufferVector.at(1)) 
			{
				buffer = false;
				break;
			}
			
		}
	}
	return buffer;
}
//конструктор грани
Cube::Edge::Edge(std::vector<char> data)
{
	this->cells = data;
}
//конструктор копирования грани
Cube::Edge::Edge(const Edge& other)
{
	this->cells = other.cells;
}
//оператор сравнения грани
bool Cube::Edge::operator==(const Edge& other)
{
	bool buffer = true;
	for (int i = 0; i < this->cells.size(); i++)
	{
		if (this->cells.at(i) != other.cells.at(i))
		{
			buffer = false;
			break;
		}
	}
	return buffer;
}
//оператор сравнения грани
bool Cube::Edge::operator!=(const Edge& other)
{
	bool buffer = true;
	for (int i = 0; i < this->cells.size(); i++)
	{
		if (this->cells.at(i) == other.cells.at(i))
		{
			buffer = false;
			break;
		}
	}
	return buffer;
}
//геттер всех клеток
std::vector<char> Cube::Edge::getCells()
{
	std::vector<char> buffer;
	buffer = this->cells;
	return buffer;
}
//геттер всех клеток
std::vector<char> Cube::Edge::getCells() const
{
	std::vector<char> buffer;
	buffer = cells;
	return buffer;
}
//геттер одной клетки
char Cube::Edge::getOneCell(int counter)
{
	char buffer;
	buffer = this->cells.at(counter);
	return buffer;
}
//сеттер всех клеток
void Cube::Edge::setCells(const std::vector<char> & data)
{
	this->cells = data;
}
//сеттер верхей строки
void Cube::Edge::setTopRove(const std::vector<char>& data)
{
	this->cells.at(0) = data.at(0);
	this->cells.at(1) = data.at(1);
	this->cells.at(2) = data.at(2);
}
//сеттер нижней строки
void Cube::Edge::setBotRove(const std::vector<char>& data)
{
	this->cells.at(6) = data.at(0);
	this->cells.at(7) = data.at(1);
	this->cells.at(8) = data.at(2);
}
//сеттер левой колонки
void Cube::Edge::setLeftColumn(const std::vector<char>& data)
{
	this->cells.at(0) = data.at(0);
	this->cells.at(3) = data.at(1);
	this->cells.at(6) = data.at(2);
}
//сеттер правой колонки
void Cube::Edge::setRightColumn(const std::vector<char>& data)
{
	this->cells.at(2) = data.at(0);
	this->cells.at(5) = data.at(1);
	this->cells.at(8) = data.at(2);
}
//геттер верхей строки
std::vector<char> Cube::Edge::getTopRove()
{
	std::vector<char> buffer;
	for (int i = 0; i < 3; i++)
	{
		buffer.push_back(this->cells.at(i));
	}
	return buffer;
}
//геттер нижней строки
std::vector<char> Cube::Edge::getBotRove()
{
	std::vector<char> buffer;
	for (int i = 0; i < 3; i++)
	{
		buffer.push_back(this->cells.at(i+6));
	}
	return buffer;
}
//геттер левой колонки
std::vector<char> Cube::Edge::getLeftColumn()
{
	std::vector<char> buffer;
	for (int i = 0; i < 3; i++)
	{
		buffer.push_back(this->cells.at(i * 3));
	}
	return buffer;
}
//геттер правой колонки
std::vector<char> Cube::Edge::getRightColumn()
{
	std::vector<char> buffer;
	for (int i = 0; i < 3; i++)
	{
		buffer.push_back(this->cells.at(2 + i * 3));
	}
	return buffer;
}

//поворот грани по часовой
void Cube::Edge::rotateClocwise()
{
	char buffer1 = cells.at(1), buffer2 = cells.at(2);
	cells.at(1) = cells.at(0);
	cells.at(2) = buffer1;
	buffer1 = buffer2;
	buffer2 = cells.at(5);
	cells.at(5) = buffer1;
	buffer1 = buffer2;
	buffer2 = cells.at(8);
	cells.at(8) = buffer1;
	buffer1 = buffer2;
	buffer2 = cells.at(7);
	cells.at(7) = buffer1;
	buffer1 = buffer2;
	buffer2 = cells.at(6);
	cells.at(6) = buffer1;
	buffer1 = buffer2;
	buffer2 = cells.at(3);
	cells.at(3) = buffer1;
	cells.at(0) = buffer2;
}
//оператор потокового ввода
std::istream& operator>>(std::istream& is, Cube& cube)
{
	for (int i = 0; i < 6; i++)
	{
		std::vector<char> buffer;
		for (int j = 0; j < 9; j++)
		{
			char bufferChar;
			is >> bufferChar;
			buffer.push_back(bufferChar);
		}
		cube.edges.at(i) = buffer;
	}
	
	return is;
}
//оператор потокового вывода
std::ostream& operator>>(std::ostream& os, const Cube& cube)
{
	std::vector<char> buffer;
	
	buffer = cube.getCube();
	for (int i = 0; i < buffer.size(); i++)
	{
		os << buffer.at(i);
	}
	return os;
}
