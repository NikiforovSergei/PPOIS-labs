#pragma once

class Vector;

	void vector(double x1_input, double y1_input, double z1_input, double x2_input, double y2_input, double z2_input);
	Vector plus(Vector b);
	void add(Vector b);
	Vector mines(Vector b);
	void decrease(Vector b);
	Vector vect_num_multiplication(double number);
	double skal_multiplication(Vector b);
	//	count scalar multiplication

	double cos_between_vects(Vector b);

	// find cos betwee vectors
	Vector multiplication(Vector b);
	bool comparison(Vector b, bool strog = true);
	void cout_vector();

double operator ^ (Vector a, Vector b);
Vector operator + (Vector a, Vector b);
void operator += (Vector& a, Vector& b);
Vector operator - (Vector a, Vector b);
void operator -= (Vector& a, Vector& b);
Vector operator * (Vector a, Vector b);
void operator *= (Vector& a, Vector& b);
Vector operator * (Vector a, double num);
Vector operator *= (Vector a, double num);
bool operator > (Vector a, Vector b);
bool operator >= (Vector a, Vector b);
bool operator < (Vector a, Vector b);
bool operator <= (Vector a, Vector b);
Vector operator / (Vector a, Vector b);
void operator /= (Vector& a, Vector& b);
