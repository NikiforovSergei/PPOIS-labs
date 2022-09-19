//
// Created by Egor Vasilkov on 3.09.22.
//

#include "Rectangle.h"

Rectangle::Rectangle() {
    empty = true;
    this->topLeftX = 0;
    this->topLeftY = 0;

    this->width = 0;
    this->height = 0;

    this->bottomRightX = topLeftX + width;
    this->bottomRightY = topLeftY - height;
}

Rectangle::Rectangle(int topLeftX, int topLeftY, int width, int height) {
    empty = false;
    this->topLeftX = topLeftX;
    this->topLeftY = topLeftY;

    this->width = width;
    this->height = height;

    this->bottomRightX = topLeftX + width;
    this->bottomRightY = topLeftY - height;

}

bool Rectangle::isEmpty() const {
    return empty;
}

int Rectangle::getWidth() const {
    return width;
}

int Rectangle::getHeight() const {
    return height;
}

int Rectangle::getArea() const {
    return getWidth() * getHeight();
}

void Rectangle::setTopLeftX(int topLeftX) {
    this->topLeftX = topLeftX;
}

void Rectangle::setTopLeftY(int topLeftY) {
    this->topLeftY = topLeftY;
}

void Rectangle::setWidth(int width) {
    this->width = width;
}

void Rectangle::setHeight(int height) {
    this->height = height;
}

void Rectangle::setBounds(int topLeftX, int topLeftY, int width, int height) {
    if (width == 0 && height == 0) {
        this->empty = true;
    } else {
        this->empty = false;
    }
    this->topLeftX = topLeftX;
    this->topLeftY = topLeftY;

    this->width = width;
    this->height = height;

    this->bottomRightX = topLeftX + width;
    this->bottomRightY = topLeftY - height;
}

void Rectangle::printPoints() const {
    cout << "Points:" << setw(6) << topLeftX << " " << topLeftY << setw(5) <<
         bottomRightX << " " << topLeftY << setw(5) << topLeftX << " " <<
         bottomRightY << setw(5) << bottomRightX << " " << bottomRightY << endl;
}

void Rectangle::move(int x, int y) {
    this->topLeftX = x;
    this->topLeftY = y;

    this->bottomRightX = topLeftX + width;
    this->bottomRightY = topLeftY - height;
}

void Rectangle::resize(int newWidth, int newHeight) {
    this->width = newWidth;
    this->height = newHeight;

    this->bottomRightX = topLeftX + width;
    this->bottomRightY = topLeftY - height;
}

Rectangle &Rectangle::operator++() {
    this->topLeftX--;
    this->topLeftY++;

    this->bottomRightX++;
    this->bottomRightY--;

    this->width += 2;
    this->height += 2;

    return *this;
}

Rectangle &Rectangle::operator++(int value) {
    Rectangle temporary(*this);

    this->topLeftX--;
    this->topLeftY++;

    this->bottomRightX++;
    this->bottomRightY--;

    this->width += 2;
    this->height += 2;

    return temporary;
}

Rectangle &Rectangle::operator--() {
    this->topLeftX++;
    this->topLeftY--;

    this->bottomRightX--;
    this->bottomRightY++;

    this->width -= 2;
    this->height -= 2;

    return *this;
}

Rectangle &Rectangle::operator--(int value) {
    Rectangle temporary(*this);

    this->topLeftX++;
    this->topLeftY--;

    this->bottomRightX--;
    this->bottomRightY++;

    this->width -= 2;
    this->height -= 2;

    return temporary;
}

Rectangle Rectangle::operator-(const Rectangle &other) {
    if (this->empty) {
        return *this;
    }
    Rectangle temporary;
    if (isIntersect(other)) {
        temporary.topLeftX = max(this->topLeftX, other.topLeftX);
        temporary.topLeftY = min(this->topLeftY, other.topLeftY);
        temporary.bottomRightX = min(this->bottomRightX, other.bottomRightX);
        temporary.bottomRightY = max(this->bottomRightY, other.bottomRightY);

        temporary.width = temporary.bottomRightX - temporary.topLeftX;
        temporary.height = temporary.topLeftY - temporary.bottomRightY;
        if (temporary.width == 0 && temporary.height == 0) {
            temporary.empty = true;
        } else {
            temporary.empty = false;
        }
        return temporary;
    } else {
        //throw std::out_of_range("Rectangles don't intersect!");
        cout << "Rectangles don't intersect!" << endl;
        return temporary;
    }

}

Rectangle Rectangle::operator+(const Rectangle &other) {
    Rectangle temporary;
    temporary.topLeftX = min(this->topLeftX, other.topLeftX);
    temporary.topLeftY = max(this->topLeftY, other.topLeftY);
    temporary.bottomRightX = max(this->bottomRightX, other.bottomRightX);
    temporary.bottomRightY = min(this->bottomRightY, other.bottomRightY);

    temporary.width = temporary.bottomRightX - temporary.topLeftX;
    temporary.height = temporary.topLeftY - temporary.bottomRightY;
    if (temporary.width == temporary.height == 0) {
        temporary.empty = true;
    } else {
        temporary.empty = false;
    }

    return temporary;
}

Rectangle Rectangle::operator-=(const Rectangle &other) {
    Rectangle temporary(*this);
    /*if (this->empty) {
        return *this;
    }*/
    if (isIntersect(other)) {
        this->topLeftX = max(this->topLeftX, other.topLeftX);
        this->topLeftY = min(this->topLeftY, other.topLeftY);
        this->bottomRightX = min(this->bottomRightX, other.bottomRightX);
        this->bottomRightY = max(this->bottomRightY, other.bottomRightY);

        this->width = this->bottomRightX - this->topLeftX;
        this->height = this->bottomRightY - this->topLeftY;

        return *this;
    } else {
        return temporary;
        //throw std::out_of_range("Rectangles don't intersect!");
        cout << "Rectangles don't intersect!" << endl;
        return *this;
    }
}

Rectangle Rectangle::operator+=(const Rectangle &other) {
    if (this->empty) {
        return other;
    } else {
        this->topLeftX = min(this->topLeftX, other.topLeftX);
        this->topLeftY = max(this->topLeftY, other.topLeftY);
        this->bottomRightX = max(this->bottomRightX, other.bottomRightX);
        this->bottomRightY = min(this->bottomRightY, other.bottomRightY);

        this->width = this->bottomRightX - this->topLeftX;
        this->height = this->bottomRightY - this->topLeftY;

        return *this;
    }

}

bool Rectangle::isIntersect(const Rectangle &other) const {
    // if rectangle has area 0, no overlap
    if (this->topLeftX == this->bottomRightX || this->topLeftY == this->bottomRightY ||
        other.bottomRightX == other.topLeftX || other.topLeftY == other.bottomRightY)
        return false;

    // If one rectangle is on left side of other
    if (this->topLeftX > other.bottomRightX || other.topLeftX > this->bottomRightX)
        return false;

    // If one rectangle is above other
    if (this->bottomRightY > other.topLeftY || other.bottomRightY > this->topLeftY)
        return false;

    return true;
}

int Rectangle::getTopLeftX() const {
    return topLeftX;
}

int Rectangle::getTopLeftY() const {
    return topLeftY;
}

int Rectangle::getBottomRightX() const {
    return bottomRightX;
}

int Rectangle::getBottomRightY() const {
    return bottomRightY;
}
