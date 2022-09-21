#include "object.h"
#include <iostream>
#include <vector>
using namespace std;

RECT::RECT(int x, int y, int x1, int y1)
{
	this->x = x;
	this->x1 = x1;
	this->y = y;
	this->y1 = y1;
}

RECT::RECT()
{
	this->x = 0;
	this->x1 = 0;
	this->y = 0;
	this->y1 = 0;
}

RECT::~RECT()
{
}

void RECT::define(int x, int y, int x1, int y1)
{
	this->x = x;
	this->x1 = x1;
	this->y = y;
	this->y1 = y1;
}

void RECT::show_xy()
{
	cout << this->x << " " << this->y << "\t"; 
	cout << this->x1 << " " << this->y << endl;
	cout << this->x << " " << this->y1 << "\t";
	cout << this->x1 << " " << this->y1 << endl << endl;
}

int* RECT::get_xy()
{
	int* xy = new int[4];

	xy[0] = this->x;
	xy[2] = this->x1;
	xy[1] = this->y; 
	xy[3] = this->y1;

	return xy;
}

void RECT::move(int x, int y)
{
	this->x += x;
	this->x1 += x;
	this->y += y;
	this->y1 += y;
}

void RECT::change_size(int x, int y)
{
	this->x1 += x;
	this->y1 += y;
}

RECT& RECT::operator++()
{
	this->x++;
	this->x1++;
	this->y++;
	this->y1++;

	return *this;
}

RECT& RECT::operator ++ (int v)
{
	RECT temp(*this);

	this->x++;
	this->x1++;
	this->y++;
	this->y1++;

	return temp;
}

RECT& RECT::operator -- ()
{
	this->x--;
	this->x1--;
	this->y--;
	this->y1--;

	return *this;
}

RECT& RECT::operator -- (int v)
{
	RECT temp(*this);

	this->x--;
	this->x1--;
	this->y--;
	this->y1--;

	return temp;
}

RECT RECT::operator + (const RECT &other)
{
	int y_max;
	int y_min;
	int x_max;
	int x_min;
	
	if (this->y1 <= other.y1) {
		y_max = other.y1;
	}
	else {
		y_max = this->y1;
	}
	
	if (this->y <= other.y) {
		y_min = this->y;
	}
	else {
		y_min = other.y;
	}
	
	if (other.x1 <= this->x1) {
		x_max = this->x1;
	}
	else {
		x_max = other.x1;
	}
	
	if (other.x <= this->x) {
		x_min = other.x;
	}
	else {
		x_min = this->x;
	}

	RECT temp(x_min, y_min, x_max, y_max);

	return temp;
}

RECT RECT::operator-(const RECT& other)
{
	RECT T(0,0,0,0);

	vector <int> temp(0);

	int X1;
	int Y1;
	int X2; 
	int Y2;

	for (int x = this->x; x <= this->x1; x++){
		for (int y = this->y; y <= this->y1; y++){
			for (int xx = other.x; xx <= other.x1; xx++){
				for (int yy = other.y; yy <= other.y1; yy++){
					X1 = x;
					X2 = xx;
					Y1 = y;
					Y2 = yy;

					if (X1 == X2 && Y1 == Y2) {
						temp.push_back(X1);
						temp.push_back(Y1);
					}
				}
			}
		}
	}

	X1 = temp[0];
	Y1 = temp[1];
	X2 = temp[2];
	Y2 = temp[3];

	for (int i = 0; i < temp.size(); i = i + 2) {

		if (X1 > temp[i]) {
			X1 = temp[i];
		}

		if (X2 < temp[i]) {
			X2 = temp[i];
		}
	}

	for (int j = 1; j < temp.size(); j = j + 2) {

		if (Y1 > temp[j]) {
			Y1 = temp[j];
		}

		if (Y2 < temp[j]) {
			Y2 = temp[j];
		}
	}
	
	if (X1 == X2 || Y1 == Y2) {
		return T;
	}
	else {
		T.define(X1, Y1, X2, Y2);
		return T;
	}
}

RECT RECT::operator += (const RECT& other)
{
	int y_max;
	int y_min;
	int x_max;
	int x_min;
	
	if (this->y1 <= other.y1) {
		y_max = other.y1;
	}
	else {
		y_max = this->y1;
	}

	if (this->y <= other.y) {
		y_min = this->y;
	}
	else {
		y_min = other.y;
	}

	if (other.x1 <= this->x1) {
		x_max = this->x1;
	}
	else {
		x_max = other.x1;
	}

	if (other.x <= this->x) {
		x_min = other.x;
	}
	else {
		x_min = this->x;
	}

	this->x = x_min;
	this->x1 = x_max;
	this->y = y_min;
	this->y1 = y_max;

	return *this;
}

RECT RECT::operator-=(const RECT& other)
{
	RECT T(0, 0, 0, 0);

	vector <int> temp(0);

	int X1;
	int Y1;
	int X2;
	int Y2;

	for (int x = this->x; x <= this->x1; x++) {
		for (int y = this->y; y <= this->y1; y++) {
			for (int xx = other.x; xx <= other.x1; xx++) {
				for (int yy = other.y; yy <= other.y1; yy++) {
					X1 = x;
					X2 = xx;
					Y1 = y;
					Y2 = yy;

					if (X1 == X2 && Y1 == Y2) {
						temp.push_back(X1);
						temp.push_back(Y1);
					}
				}
			}
		}
	}

	X1 = temp[0];
	Y1 = temp[1];
	X2 = temp[2];
	Y2 = temp[3];

	for (int i = 0; i < temp.size(); i = i + 2) {

		if (X1 > temp[i]) {
			X1 = temp[i];
		}

		if (X2 < temp[i]) {
			X2 = temp[i];
		}
	}

	for (int j = 1; j < temp.size(); j = j + 2) {

		if (Y1 > temp[j]) {
			Y1 = temp[j];
		}

		if (Y2 < temp[j]) {
			Y2 = temp[j];
		}
	}
	if (X1 == X2 || Y1 == Y2) {
		return *this;
	}
	else {
		this->x = X1;
		this->y = Y1;
		this->x1 = X2;
		this->y1 = Y2;

		return *this;
	}
}

void RECT::operator=(const RECT& other)
{
	this->x = other.x;
	this->x1 = other.x1;
	this->y = other.y;
	this->y1 = other.y1;
}

int RECT::max(int a, int b)
{
	if (a > b) {
		return a;
	}
	else{
		return b;
	}
		
	return 0;
}

int RECT::min(int a, int b)
{
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
		
	return 0;
}


