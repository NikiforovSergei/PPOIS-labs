#pragma once
#include <string>
using namespace std;
class Rect {
public:

	Rect(int x, int y, int x1, int y1);

	Rect();

	~Rect();

	void def(int x, int y, int x1, int y1);

	void show();

	int* get();

	void move(int x, int y);

	void change(int x, int y);

	Rect& operator ++();

	Rect& operator ++(int v);

	Rect& operator --();

	Rect& operator --(int v);

	Rect operator +(const Rect& other);

	Rect operator -(const Rect& other);

	Rect operator +=(const Rect& other);

	Rect operator -=(const Rect& other);

	void operator =(const Rect& other);

private:

	int x;
	int y;
	int x1;
	int y1;

	int max(int, int);

	int min(int, int);
};
