#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

Vector::Vector(double a, double b, double v)
{
	x = a;
	y = b;
	z = v;
}

Cos::Cos(double s)
{
	p = s;
}

void Vector::view_vector()
{
	cout << " V = (" << x << " " << y << " " << z << ")\n";
}

void Cos::prosmotrcos()
{
	cout << "Cos = " << p << "\n";
}


double Vector::length_v(double rez)
{
	rez = ceil(abs(sqrt(x * x + y * y + z * z)));
	return rez;
}

Vector Vector::operator+(Vector v)
{
	return Vector(x + v.x, y + v.y, z + v.z);

}

Vector Vector::operator+=(Vector v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}


Vector Vector::operator-(Vector v)
{
	return Vector(x - v.x, y - v.y, z - v.z);

}

Vector Vector::operator-=(Vector v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;

}

Vector Vector::operator*(Vector v)
{
	return Vector(x * v.x, y * v.y, z * v.z);

}

Vector Vector::operator*=(Vector v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;

}

Vector Vector::operator*(double value)
{
	return Vector(x * value, y * value, z * value);

}

Vector Vector::operator*=(double value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;

}

Vector Vector::operator/(Vector v)
{
	return Vector(x / v.x, y / v.y, z / v.z);

}

Vector Vector::operator/=(Vector v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;

}

double Vector::operator^(Vector v)
{
	double cos;
	cos = ceil((x * v.x + y * v.y + z * v.z)/(abs(sqrt(x * x + y * y + z * z))*(abs(sqrt(v.x * v.x + v.y * v.y+ v.z * v.z)))));
	return cos;
}

bool Vector:: operator > (Vector v)
{
	if (x > v.x)
		if (y > v.y)
			if (z > v.z)
				return true;
	return false;
}

bool Vector:: operator >= (Vector v)
{
	if (x >= v.x)
		if (y >= v.y)
			if (z >= v.z)
				return true;
	return false;
}

bool Vector:: operator <= (Vector v)
{
	if (x <= v.x)
		if (y <= v.y)
			if (z <= v.z)
				return true;
	return false;
}


bool Vector:: operator == (Vector v)
{
	if (x == v.x)
		if (y == v.y)
			if (z == v.z)
				return true;
	return false;
}

bool Cos:: operator == (Cos v)
{
	if (p == v.p)
				return true;
	return false;
}

bool Vector:: operator < (Vector & other)
{
	if (this->x < other.x && this->y < other.y && this->z < other.z)
				return true;
			else return false;
}