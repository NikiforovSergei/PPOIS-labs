#pragma once
//#include <string>
using namespace std;

class Rect {
private:
	int x1_;
	int x2_;
	int y1_;
	int y2_;
public:
	Rect();
	Rect(int, int, int, int);
	~Rect();

	void def(int, int, int, int);

	void SetCoor(int, int, int, int);

	//получение координат вершин
	void Show();

	//перемещение
	void Move(int, int);

	//изменение размера
	void Change(int, int);

	//увелечение размера на единицу по каждой из осей
	void More(int);

	//уменьшение размера на единицу по каждой из осей
	void Less(int);

	//построение наименьшего прямоугольника, содержащего два заданных прямоугольника
	void Twosmall(Rect, Rect);

	//построение наименьшего прямоугольника, содержащего два заданных прямоугольника, с присваиванием
	void Twosmallass(Rect, Rect);

	//построение прямоугольника, являющегося общей частью (пересечением) двух прямоугольников
	void Twounif(Rect, Rect);

	//построение прямоугольника, являющегося общей частью (пересечением) двух прямоугольников, с присванием
	void Twounifass(Rect, Rect);

	Rect& operator ++();

	Rect& operator --();

	Rect operator +(const Rect& other);

	Rect operator +=(const Rect& other);

	Rect operator -(const Rect& other);

	Rect operator -=(const Rect& other);

	void operator =(const Rect& other);

};