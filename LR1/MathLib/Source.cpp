#include <iostream>
#include <cmath>
#include "Header.h"

using namespace std;

class Vector {
private:
	double x, y, z, x1, y1, z1, x2, y2, z2, lenght;

public:
	void vector(double x1_input, double y1_input, double z1_input, double x2_input, double y2_input, double z2_input) {
		x1 = x1_input;
		y1 = y1_input;
		z1 = z1_input;
		x2 = x2_input;
		y2 = y2_input;
		z2 = z2_input;
		x = x2 - x1;
		y = y2 - y1;
		z = z2 - z1;
		lenght = sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2) + pow(abs(z1 - z2), 2));
	}
	Vector plus(Vector b) {
		//the windblood coordinates and the coordinates of the end of the vector are summed up in turn.
		//a new object is returned, with new end coordinates.
		Vector result;
		result.vector(x1, y1, z1, x2 + b.x2, y2 + b.y2, z2 + b.z2);
		return result;
	}
	void add(Vector b) {
		// the coordinates of the vectors and the coordinates of the ends of the vectors are adjusted
		// noting returns
		x += b.x;
		y += b.y;
		z += b.z;
		x2 = x2 + b.x2;
		y2 = y2 + b.y2;
		z2 = z2 + b.z2;

	}
	Vector mines(Vector b) {
		//a new object is created, with the end coordinates obtained by subtracting the corresponding coordinates of the second vector from the first
		Vector result;
		result.vector(x1, y1, z1, x2 - b.x2, y2 - b.y2, z2 - b.z2);
		return result;
	}
	void decrease(Vector b) {
		//the corresponding coordinates of the second vector are subtracted from the coordinates of the first vector, the same with the coordinates of the ends of the vectors
		// nothing returns
		x2 -= b.x2;
		y2 -= b.y2;
		z2 -= b.z2;
		x -= b.x;
		y -= b.y;
		z -= b.z;
	}
	Vector vect_num_multiplication(double number) {
		// returns a new object obtained as a result of multiplying the coordinates of the ends of the vector by the passed number
		Vector result;
		result.vector(x1 * number, y2 * number, z2 * number, x2 * number, y2 * number, z2 * number);
		return result;
	}
	double skal_multiplication(Vector b) { return ((x * b.x) + (y * b.y) + (z * b.z)); }
	//	count scalar multiplication
	double cos_between_vects(Vector b) {
		if (lenght != 0 && b.lenght != 0) {
			return (skal_multiplication(b) / (lenght * b.lenght));
		}
		else {
			cout << "0-vector";
			return 1;
		}
	}
	// find cos betwee vectors
	Vector multiplication(Vector b) {
		// calculate the multiplication of vectors
		Vector result;
		result.vector(x1, y1, z1, x1 + ((y * b.z) - (z * b.y)), -y1 - ((x * b.z) - (b.x * z)), z1 + ((x * b.y) - (y * b.x)));
		return result;
	}
	bool comparison(Vector b, bool strog = true) {
		// camparison
		if (lenght > b.lenght) {
			return true;
		}
		if ((lenght == b.lenght) and (strog == true)) { return false; }
		if ((lenght == b.lenght) and (strog == false)) { return true; }
		if (lenght < b.lenght) {
			return false;
		}
	}
	void cout_vector() {
		// just out all parameters of vector
		cout << '(' << x << ", " << y << ", " << z << "); [" << x1 << ", " << y1 << ", " << z1 << "][" << x2 << ", " << y2 << ", " << z2 << ']';
	}
};

double operator ^ (Vector a, Vector b) { return a.cos_between_vects(b); }
Vector operator + (Vector a, Vector b) { return a.plus(b); }
void operator += (Vector& a, Vector& b) { a.add(b); }
Vector operator - (Vector a, Vector b) { return a.mines(b); }
void operator -= (Vector& a, Vector& b) { a = a.mines(b); }
Vector operator * (Vector a, Vector b) { return a.multiplication(b); }
void operator *= (Vector& a, Vector& b) { a = a.multiplication(b); }
Vector operator * (Vector a, double num) { return a.vect_num_multiplication(num); }
Vector operator *= (Vector a, double num) { return a = a.vect_num_multiplication(num); }
bool operator > (Vector a, Vector b) { return a.comparison(b); }
bool operator >= (Vector a, Vector b) { return a.comparison(b, true); }
bool operator < (Vector a, Vector b) { return not a.comparison(b); }
bool operator <= (Vector a, Vector b) { return not a.comparison(b, true); }
Vector operator / (Vector a, Vector b) { return a.multiplication(b).vect_num_multiplication(-1); }
void operator /= (Vector& a, Vector& b) { a = a.multiplication(b).vect_num_multiplication(-1); }

void main() {
	double x, y, z, x1, y1, z1, x2, y2, z2;
	Vector vector1, vector2;
	cout << "Enter the coordinates of the ends of the first vector: ";
	cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
	vector1.vector(x1, y1, z1, x2, y2, z2);
	cout << "Enter the coordinates of the ends of the second vector: ";
	cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
	vector2.vector(x1, y1, z1, x2, y2, z2);

	vector1.cout_vector();
	vector2.cout_vector();


	cout << "1. +\n2. +=\n3. -\n4 -=\n5. ^\n6. * (vectors)\n7. *= (vectors)\n8. * (number)\n9. *= (number)\n10. <\n11. >\n12. <=\n13. >=\n14. /\n15. /=\n Choose one: ";
	int action;
	cin >> action;
	if (action == 1) {
		Vector result;
		result = vector1 + vector2;
		result.cout_vector();
	}
	else if (action == 2) {
		vector1 += vector2;
		vector1.cout_vector();
	}
	else if (action == 3) {
		Vector result;
		result = vector1 - vector2;
		result.cout_vector();
	}
	else if (action == 4) {
		vector1 -= vector2;
		vector1.cout_vector();
	}
	else if (action == 5) {
		double result;
		result = vector1 ^ vector2;
		cout << result;
	}
	else if (action == 6) {
		Vector result;
		result = vector1 * vector2;
		result.cout_vector();
	}
	else if (action == 7) {
		vector1 *= vector2;
		vector1.cout_vector();
	}
	else if (action == 8) {
		Vector result;
		double n;
		cout << "Enter the number.";
		cin >> n;
		result = vector1 * n;
		result.cout_vector();
	}
	else if (action == 9) {
		double n;
		cin >> n;
		vector1 *= n;
		vector1.cout_vector();
	}
	else if (action == 10) {
		bool result = vector1 < vector2;
		if (result == false) { cout << false; }
		else { cout << true; }
		cout << result;
	}
	else if (action == 11) {
		bool result = vector1 > vector2;
		cout << result;
	}
	else if (action == 12) {
		bool result = vector1 <= vector2;
		cout << result;
	}
	else if (action == 13) {
		bool result = vector1 >= vector2;
		cout << result;
	}
	else if (action == 14) {
		Vector result;
		result = vector1 / vector2;
		result.cout_vector();
	}
	else if (action == 15) {
		vector1 /= vector2;
		vector1.cout_vector();
	}
}