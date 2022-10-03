//
// Created by User on 04.09.2022.
//

#ifndef SEM3_PPOIS_LAB1_VECTOR_H
#define SEM3_PPOIS_LAB1_VECTOR_H

#include <vector>
#include <string>
#include "Point.h"

namespace std {

    class Vector {
    private:
        Point start;  ///координаты точки начала вектора
        Point finish; ///координаты точки конца вектора
        Point coordinatesOfVector; ///координаты вектора
        const void setCoordinatesOfVector();
    public:
        Vector();
        Vector(vector<double> start, vector<double> finish);

        Vector(vector<double> coordinatesOfVector);

        ~Vector();
        vector<double> getStart() const;
        void setStart(vector<double> start);
        const vector<double> getCoordinatesOfVector() const;
        vector<double> getFinish() const;
        void setFinish(vector<double> finish);
        void setCoordinatesOfVector(vector<double> vectorCoordinates);
        const double getLength();

        const void sum(Vector v1);
        const void subtraction (std::Vector v1);
        const void multiplication(double number);
        const void multiplication(std::Vector v1);
        Vector sum(Vector v1, Vector v2);
        const void subtraction(std::Vector v1, Vector v2);
        const void multiplication(int number, Vector v);
        const void multiplication(std::Vector v1, Vector v2);

        const Vector operator+(const Vector& v1);
        const Vector operator-(const Vector& v1);
        const Vector operator*(Vector v1);
        const Vector operator*(const int number);
        const double operator^(Vector v1);
        const double operator/(Vector v1);
        friend Vector& operator+=(Vector& v1, const Vector& v2);
        friend Vector& operator-=(Vector& v1, const Vector& v2);
        friend Vector& operator*=(Vector& v1, const Vector& v2);
        friend Vector& operator*=(Vector& v1, const int& number);
        const bool operator>(Vector& v1);
        const bool operator<(Vector& v1);
        friend bool operator>=(Vector& v1, Vector& v2);
        friend bool operator<=(Vector& v1, Vector& v2);
        const bool operator==(Vector& v1);


        string getInfo();
    };

} // std

#endif //SEM3_PPOIS_LAB1_VECTOR_H
