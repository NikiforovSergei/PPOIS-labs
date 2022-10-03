/**
* @file Header.h
* @author Daniil Promchuk
* @brief This file contain all necessary definitions 
*/
#pragma once
#ifndef Header.h
#include <iostream>
#include <list>
using namespace std;

/** 
* @brief Class which describes a point in a Cartesian coordinate system
* @param x,y X and Y of point
*/
class Point {
private:
    int x, y;
public:
    /**
    * @brief Default constructor without parameters
    */
    Point() {
        x = 0;
        y = 0;
    };
    /**
    * @brief Default constructor with parameters
    * @param[in] x,y Point's coordinates
    */
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    /**
    * @brief Display point's coordinates
    */
    void  Show_coordinates() {
        cout << '(' << x << ", " << y << ')' << endl;
    }
    /**
    * @brief Return point's X coordinate
    * @return X coordinate
    */
    int GetX() {
        return x;
    }
    /**
    * @brief Return point's Y coordinate
    * @return Y coordinate
    */
    int GetY() {
        return y;
    }
    /**
    * @brief Set point's coordinates
    * @param[in] x,y Point's coordinates
    */
    void Set_coordinates(int coord_x, int coord_y) {
        x = coord_x;
        y = coord_y;
    }
    /**
    * @brief Allows to change Y coordinate 
    * @param[in] number How much to increase(with positive) or decrease(with negative) Y coordinate of point
    */
    void Up(int number) {
        y += number;
    }
    /**
    * @brief Allows to change X coordinate
    * @param[in] number How much to increase(with positive) or decrease(with negative) X coordinate of point
    */
    void Right(int number) {
        x += number;
    }
};

/**
* @brief Struct which contains two points and distance between them
*/
struct Cell {
    double value = 0;                                    ///<Distance between points
    Point first_point;                                   ///<Contains address of the first point
    Point second_point;                                  ///<Contains address of the second point
    /**
    * @brief Default constructor with parameters
    * @param[in] val Distance between points
    * @param[in] f Address of the first point
    * @param[in] s Address of the second point
    */
    Cell(double val, Point f, Point s) {
        value = val;
        first_point = f;
        second_point = s;
    }
    /**
    * @brief Default constructor without parameters
    */
    Cell() {}
};
class Rectangle;
Cell GetDistanceCell(Rectangle, Rectangle);

/** Class which represents rectangle
* @param point[4] Array which contains 4 vertises of rectangle
* @param name Rectangle's name
*/
class Rectangle {
private:
    Point point[4];
    string name;
public:
    /**
    * @brief Default constructor without parameters
    */
    Rectangle() {}
    /**
    * @brief Default constructor with parameters
    * @param[in] X1 X coordinate of the first point
    * @param[in] Y1 Y coordinate of the first point
    * @param[in] X2 X coordinate of the second point
    * @param[in] Y2 Y coordinate of the second point
    * 
    * Calling constructor with coordinates of only 2 diagonal points may be faster and more convenient for user
    */
    Rectangle(int X1, int Y1, int X2, int Y2) {
        point[0].Set_coordinates(X1, Y1);
        point[2].Set_coordinates(X2, Y2);
        point[1].Set_coordinates(X1, Y2);
        point[3].Set_coordinates(X2, Y1);
    }
    /**
    * @brief Set name of rectangle
    * @param[in] name Name of rectangle
    */
    void SetName(string name) {
        this->name = name;  
    } 
    /**
    * @brief Get name of rectangle
    * @return Name of rectangle
    */
    string GetName() {
        return name;
    }
    /**
    * @brief display coordinates of each rectangle's point
    */
    void Show_rectangle_coordinates() {
        for (auto _point : point) {
            _point.Show_coordinates();
        }
        cout << endl;
    }
    /**
    * @brief Allows to set new rectangle's coordinates
    * @param[in] X1 X coordinate of the first point
    * @param[in] Y1 Y coordinate of the first point
    * @param[in] X2 X coordinate of the second point
    * @param[in] Y2 Y coordinate of the second point
    */
    void Set_rectangle_coordinates(int X1, int Y1, int X2, int Y2) {
        point[0].Set_coordinates(X1, Y1);
        point[2].Set_coordinates(X2, Y2);
        point[1].Set_coordinates(X1, Y2);
        point[3].Set_coordinates(X2, Y1);
    }
    /** 
    * @brief Move each rectangle's point in certain direction
    * @param[in] direction Key number of selected direction
    * @param[in] number How many values to move
    * 
    * Key number of directions: 1-up    2-right    3-down     4-left 
    */
    void MoveRectangle(int direction, int number) {
        switch (direction) {
        case 1: {for (auto& _point : point) { _point.Up(number); }break; }
        case 2: {for (auto& _point : point) { _point.Right(number); }break; }
        case 3: {for (auto& _point : point) { _point.Up(-number); }break; }
        case 4: {for (auto& _point : point) { _point.Right(-number); }break; }
        }
    }
    /** 
    * @brief Move top side of rectangle
    * @param[in] number How many values to move
    */
    void MoveUpSide(int number) {
        if (point[0].GetY() > point[1].GetY()) { point[0].Up(number); point[3].Up(number); }
        else { point[1].Up(number); point[2].Up(number); }
    }
    /**
    * @brief Move right side of rectangle
    * @param[in] number How many values to move
    */
    void MoveRightSide(int number) {
        if (point[0].GetX() > point[3].GetX()) { point[0].Right(number); point[1].Right(number); }
        else { point[3].Right(number); point[2].Right(number); }
    }
    /**
    * @brief Move down side of rectangle
    * @param[in] number How many values to move
    */
    void MoveDownSide(int number) {
        if (point[0].GetY() > point[1].GetY()) { point[1].Up(number); point[2].Up(number); }
        else { point[0].Up(number); point[3].Up(number); }
    }
    /**
    * @brief Move left side of rectangle
    * @param[in] number How many values to move
    */
    void MoveLeftSide(int number) {
        if (point[0].GetX() > point[3].GetX()) { point[3].Right(number); point[2].Right(number); }
        else { point[0].Right(number); point[1].Right(number); }
    }
    /**
    * @brief increase each side by 1
    * 
    * pre incremental overload of ++ operator
    */
    Rectangle& operator ++ () {
        MoveUpSide(1);
        MoveRightSide(1);
        return *this;
    }
    /**
    * @brief increase each side by 1
    * 
    * post incremental overload of ++ operator
    */
    Rectangle operator ++(int rect) {
        Rectangle temp(*this);
        this->MoveUpSide(1);
        this->MoveRightSide(1);
        return temp;
    }
    /**
    * @brief decrease each side by 1
    * 
    * pre decremental overload of -- operator
    */
    Rectangle& operator -- () {
        MoveUpSide(-1);
        MoveRightSide(-1);
        return *this;
    }
    /**
    * @brief decrease each side by 1
    * 
    * post decremental overload of -- operator
    */
    Rectangle operator --(int rect) {
        Rectangle temp(*this);
        this->MoveUpSide(-1);
        this->MoveRightSide(-1);
        return temp;
    }
    /** 
    * @brief Allows to get point's address
    * @return Address of point
    * @param[in] value Number of point in array
    */
    Point& GetPoint(int value) {
        return  point[value];
    }
    /**
    * @brief Makes main rectangle a rectangle which contains 2 rectangles
    * @param[in] second the second rectangle
    * 
    * Overload of += operator
    */
    Rectangle operator+= (Rectangle& second) {
        Cell dist = GetDistanceCell(*this, second);
        this->Set_rectangle_coordinates(dist.first_point.GetX(), dist.first_point.GetY(), dist.second_point.GetX(), dist.second_point.GetY());
        return *this;
    }
    /**
    * @brief Creates a rectangle which contains 2 rectangles
    * @param[in] second the second rectangle
    * 
    * Overload of += operator
    */
    Rectangle operator+(Rectangle& second) {
        Cell dist = GetDistanceCell(*this, second);
        return Rectangle(dist.first_point.GetX(), dist.first_point.GetY(), dist.second_point.GetX(), dist.second_point.GetY());
    }
    /**
    * @brief Finding right side
    * @return X coordinate of right side
    */
    int FindRight() {
        if (point[0].GetX() > point[3].GetX()) {
            return point[0].GetX();
        }
        else return point[3].GetX();
    }
    /**
    * @brief Finding left side
    * @return X coordinate of left side
    */
    int FindLeft() {
        if (point[0].GetX() < point[3].GetX()) {
            return point[0].GetX();
        }
        else return point[3].GetX();
    }
    /**
    * @brief Finding down side
    * @return Y coordinate of down side
    */
    int FindDown() {
        if (point[0].GetY() < point[1].GetY()) {
            return point[0].GetY();
        }
        else return point[1].GetY();
    }
    /**
    * @brief Finding top side
    * @return Y coordinate of top side
    */
    int FindUp() {
        if (point[0].GetY() > point[1].GetY()) {
            return point[0].GetY();
        }
        else return point[1].GetY();
    }
    /**
    * @brief Creates a new rectangle which is the result of the intersection of 2 rectangle
    * @param[in] first First rectangle
    * @param[in] second Second rectangle
    * @return Returns new rectangle if 2 rectangles have intersection, or return the first rectangle if they dont have intersections
    */
    Rectangle FindBetween(Rectangle& first, Rectangle& second) {
        int upper = 0, lower = 0, right = 0, left = 0;
        if ((first.FindRight() > second.FindLeft()) && ((first.FindUp() > second.FindDown()) || (first.FindDown() < second.FindUp()))) {
            if (first.FindUp() > second.FindUp()) { lower = second.FindUp(); }
            else { lower = first.FindUp(); }
            if (first.FindDown() < second.FindDown()) { upper = second.FindDown(); }
            else { upper = first.FindDown(); }
            if (first.FindRight() > second.FindRight()) { left = second.FindRight(); }
            else { left = first.FindRight(); }
            if (first.FindLeft() < second.FindLeft()) { right = second.FindLeft(); }
            else { right = first.FindLeft(); }
            return Rectangle(left, lower, right, upper);
        }
        else return first;
    }
    /**
    * @brief Finding left rectangle and creates a new rectangle which is the result of the intersection of 2 
    * 
    * Overload of - operator
    */
    Rectangle operator-(Rectangle& second) {
        if (this->FindLeft() < second.FindLeft()) return FindBetween(*this, second);
        else return FindBetween(second, *this);
    }
    /**
    * @brief Finding left rectangle and mreates a new rectangle which is the result of the intersection of 2
    * 
    * Overload of - operator
    */
    Rectangle operator-=(Rectangle& second) {
        if (this->FindLeft() < second.FindLeft()) *this = FindBetween(*this, second);
        else *this = FindBetween(second, *this);
        return *this;
    }

};

/**
* @return Distance between 2 points
*/
double GetDistance(Point& first, Point& second) {
    return (pow((first.GetX() - second.GetX()), 2) + pow((first.GetY() - second.GetY()), 2));
}

/**
* @brief Allows to get the most distant points of 2 rectangles
* @param[in] first The first rectangle
* @param[in] second The second rectangle
* @return Cell with the most distant points
*/
Cell GetDistanceCell(Rectangle first, Rectangle second) {
    list<Cell> distance;
    int f_num = 0, s_num = 0;
    Point* point_1 = new Point;
    Point* point_2 = new Point;
    for (int i = 0; i < 16; i++) {
        *point_1 = first.GetPoint(f_num);
        *point_2 = second.GetPoint(s_num);
        distance.push_back(Cell(GetDistance(*point_1, *point_2), *point_1, *point_2));
        s_num++;
        if (s_num == 4) { s_num = 0; f_num++; }
    }
    double  max = distance.begin()->value;
    Cell max_i;
    for (auto num = distance.begin(); num != distance.end(); num++) {
        if (max < num->value) {
            max = num->value;
            max_i = *num;
        }
    }
    return max_i;
}
#endif // !Header.h
