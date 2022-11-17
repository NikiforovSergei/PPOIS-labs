/*!
    \file
	\brief Задаётся код операции с классом Point
    \author Иван Титлов

    Задаются различные операции с поинтером работает со значениями координат
*/

#include "Point.h"
/*!

	\brief Извлечение значения координаты x
    \author Иван Титлов
*/
double Point::getX() const {
    return x;
}
/*!

	\brief Операция задавания значения координате x
    \author Иван Титлов

*/
void Point::setX(double x) {
    Point::x = x;
}
/*!

	\brief Извлечение значения координаты y
    \author Иван Титлов
*/
double Point::getY() const {
    return y;
}
/*!

	\brief Операция задавания значения координате y
    \author Иван Титлов
*/
void Point::setY(double y) {
    Point::y = y;
}
/*!

	\brief Извлечение значения координаты z
    \author Иван Титлов

    Задаются различные операции с поинтером работает со значениями координат
*/
double Point::getZ() const {
    return z;
}
/*!
	\brief Операция задавания значения координате z
    \author Иван Титлов

    Задаются различные операции с поинтером работает со значениями координат
*/
void Point::setZ(double z) {
    Point::z = z;
}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

Point::Point() {}
