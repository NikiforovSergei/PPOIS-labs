#pragma once
#ifndef Header.h
#include <iostream>
#include <list>
using namespace std;


class Point {
private:
    int x, y;
public:

    ~Point() { cout << "point with coordinates " << this->x << '.' << this->y << " was deleted\n"; }

    Point() {
        x = 0;
        y = 0;
    };
    
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
   
    void  Show_coordinates() {
        cout << '(' << x << ", " << y << ')' << endl;
    }
   
    int GetX() {
        return x;
    }
   
    int GetY() {
        return y;
    }
   
    void Set_coordinates(int coord_x, int coord_y) {
        x = coord_x;
        y = coord_y;
    }
  
    void Up(int number) {
        y += number;
    }
   
    void Right(int number) {
        x += number;
    }
};


struct Cell {
    double value = 0;                                    
    Point first_point;                                   
    Point second_point;                                  
    Cell(double val, Point f, Point s) {
        value = val;
        first_point = f;
        second_point = s;
    }
   
    Cell() {}
};
class Rectangle;
Cell GetDistanceCell(Rectangle, Rectangle);

class Rectangle: public Point {
private:
    Point point[4];
    string name;
public:
    

    Rectangle() {}
    ~Rectangle() { cout << "rectangle " << this->name << " was deleted\n"; }
    Rectangle(Point A, Point B) {
        point[0].Set_coordinates(A.GetX(), A.GetY());
        point[2].Set_coordinates(B.GetX(), B.GetY());
        point[1].Set_coordinates(A.GetX(), B.GetY());
        point[3].Set_coordinates(B.GetX(), A.GetY());
    }
    Rectangle(const Rectangle& rect) {
        this->name = rect.name;
        for (size_t i = 0; i < 4; i++) {
            this->point[i] = rect.point[i];
        }
 }
   
    void SetName(string name) {
        this->name = name;
    }
   
    string GetName() {
        return name;
    }
    
    void Show_rectangle_coordinates() {
        for (auto _point : point) {
            _point.Show_coordinates();
        }
        cout << endl;
    }
    
    void Set_rectangle_coordinates(int X1, int Y1, int X2, int Y2) {
        point[0].Set_coordinates(X1, Y1);
        point[2].Set_coordinates(X2, Y2);
        point[1].Set_coordinates(X1, Y2);
        point[3].Set_coordinates(X2, Y1);
    }
   
    void MoveRectangle(int direction, int number) {
        switch (direction) {
        case 1: {for (auto& _point : point) { _point.Up(number); }break; }
        case 2: {for (auto& _point : point) { _point.Right(number); }break; }
        case 3: {for (auto& _point : point) { _point.Up(-number); }break; }
        case 4: {for (auto& _point : point) { _point.Right(-number); }break; }
        }
    }
   
    void MoveUpSide(int number) {
        if (point[0].GetY() > point[1].GetY()) { point[0].Up(number); point[3].Up(number); }
        else { point[1].Up(number); point[2].Up(number); }
    }
   
    void MoveRightSide(int number) {
        if (point[0].GetX() > point[3].GetX()) { point[0].Right(number); point[1].Right(number); }
        else { point[3].Right(number); point[2].Right(number); }
    }
   
    void MoveDownSide(int number) {
        if (point[0].GetY() > point[1].GetY()) { point[1].Up(number); point[2].Up(number); }
        else { point[0].Up(number); point[3].Up(number); }
    }
   
    void MoveLeftSide(int number) {
        if (point[0].GetX() > point[3].GetX()) { point[3].Right(number); point[2].Right(number); }
        else { point[0].Right(number); point[1].Right(number); }
    }
   
    Rectangle& operator ++ () {
        MoveUpSide(1);
        MoveRightSide(1);
        return *this;
    }
   
    Rectangle operator ++(int rect) {
        Rectangle temp(*this);
        this->MoveUpSide(1);
        this->MoveRightSide(1);
        return temp;
    }
   
    Rectangle& operator -- () {
        MoveUpSide(-1);
        MoveRightSide(-1);
        return *this;
    }
   
    Rectangle operator --(int rect) {
        Rectangle temp(*this);
        this->MoveUpSide(-1);
        this->MoveRightSide(-1);
        return temp;
    }
   
    Point& GetPoint(int value) {
        return  point[value];
    }
    
    Rectangle operator+= (Rectangle& second) {
        Cell dist = GetDistanceCell(*this, second);
        this->Set_rectangle_coordinates(dist.first_point.GetX(), dist.first_point.GetY(), dist.second_point.GetX(), dist.second_point.GetY());
        return *this;
    }
  
    Rectangle operator+(Rectangle& second) {
        Cell dist = GetDistanceCell(*this, second);
        return Rectangle(dist.first_point.GetX(), dist.first_point.GetY(), dist.second_point.GetX(), dist.second_point.GetY());
    }
    
    int FindRight() {
        if (point[0].GetX() > point[3].GetX()) {
            return point[0].GetX();
        }
        else return point[3].GetX();
    }
   
    int FindLeft() {
        if (point[0].GetX() < point[3].GetX()) {
            return point[0].GetX();
        }
        else return point[3].GetX();
    }
   
    Rectangle(int X1, int Y1, int X2, int Y2) {
        point[0].Set_coordinates(X1, Y1);
        point[2].Set_coordinates(X2, Y2);
        point[1].Set_coordinates(X1, Y2);
        point[3].Set_coordinates(X2, Y1);
    }

    int FindDown() {
        if (point[0].GetY() < point[1].GetY()) {
            return point[0].GetY();
        }
        else return point[1].GetY();
    }
   
    int FindUp() {
        if (point[0].GetY() > point[1].GetY()) {
            return point[0].GetY();
        }
        else return point[1].GetY();
    }
   
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
    
    Rectangle operator-(Rectangle& second) {
        if (this->FindLeft() < second.FindLeft()) return FindBetween(*this, second);
        else return FindBetween(second, *this);
    }
   
    Rectangle operator-=(Rectangle& second) {
        if (this->FindLeft() < second.FindLeft()) *this = FindBetween(*this, second);
        else *this = FindBetween(second, *this);
        return *this;
    }

};

double GetDistance(Point& first, Point& second) {
    return (pow((first.GetX() - second.GetX()), 2) + pow((first.GetY() - second.GetY()), 2));
}

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