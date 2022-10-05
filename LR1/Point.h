//
// Created by User on 10.09.2022.
//

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
