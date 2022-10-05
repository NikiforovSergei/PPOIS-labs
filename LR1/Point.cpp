//
// Created by User on 10.09.2022.
//

#include "Point.h"

double Point::getX() const {
    return x;
}

void Point::setX(double x) {
    Point::x = x;
}

double Point::getY() const {
    return y;
}

void Point::setY(double y) {
    Point::y = y;
}

double Point::getZ() const {
    return z;
}

void Point::setZ(double z) {
    Point::z = z;
}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

Point::Point() {}
