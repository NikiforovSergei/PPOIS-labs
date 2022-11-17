/*!
    \file
	\brief задаётся класс Point
    \author Иван Титлов

    Описан класс Point, отвечающий за поинтер, который будет извлекать значения координат x, y, z векторов
*/

#ifndef SEM3_PPOIS_LAB1_POINT_H
#define SEM3_PPOIS_LAB1_POINT_H


class Point {
private:
    double x;
    double y;
    double z;

public:
    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;
    void setZ(double z);

    Point(double x, double y, double z);

    Point();
};


#endif //SEM3_PPOIS_LAB1_POINT_H
