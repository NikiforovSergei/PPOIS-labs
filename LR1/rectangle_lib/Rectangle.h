//
// Created by Egor Vasilkov on 3.09.22.
//

#ifndef PPOISLAB1_RECTANGLE_H
#define PPOISLAB1_RECTANGLE_H

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * \brief Represents rectangle in coordinate system
 *
 * This class keeps track rectangle in coordinate system. Note that the coordinate system uses
 * the origin (0,0) as the top left of the screen, with the x and y
 * values increasing as they move to the right and down respectively.
 *
 * @author Egor Vasilkov  (valoshkaegor\@icloud.com)
 */
class Rectangle {
private:
    int topLeftX;
    int topLeftY;

    int bottomRightX;
    int bottomRightY;

    int width;
    int height;
    bool empty;

    bool isIntersect(const Rectangle &other) const;

public:
    /**
     * Initializes a new instance from the specified inputs.
     *
     * @param topLeftX the X coordinate of the top left corner
     * @param topLeftY the Y coordinate of the top left corner
     * @param width the width of the rectangle
     * @param height the height of the rectangle
     */
    Rectangle(int topLeftX, int topLeftY, int width, int height);

    /**
     * Initialize a new rectangle with a top left corner
     * at (0,0) and a width and height of 0.
     */
    Rectangle();

    /**
     * Tests whether or not this rectangle is empty. An empty
     * rectangle has non-positive width or height.
     *
     * @return true if rectangle is empty
     */
    bool isEmpty() const;

    /**
     * Get the X coordinate of the upper-left corner.
     *
     * @return the value of X as int
     */
    int getTopLeftX() const;

    /**
     * Get the Y coordinate of the upper-left corner.
     *
     * @return the value of Y as int
     */
    int getTopLeftY() const;

    /**
     * Get the X coordinate of the lower-right corner.
     *
     * @return the value of X as int
     */
    int getBottomRightX() const;

    /**
     * Get the Y coordinate of the lower-right corner.
     *
     * @return the value of Y as int
     */
    int getBottomRightY() const;

    /**
     * Get the width of rectangle.
     *
     * @return the value of width as int
     */
    int getWidth() const;

    /**
     * Get the height of rectangle.
     *
     * @return the value of height as int
     */
    int getHeight() const;

    /**
     * Get the area of rectangle.
     *
     * @return the value of area rectangle
     */
    int getArea() const;

    /**
     * Sets top left X coordinate of rectangle.
     *
     * @param topLeftX the new X coordinate of the upper left corner
     */
    void setTopLeftX(int topLeftX);

    /**
     * Sets top left Y coordinate of rectangle.
     *
     * @param topLeftY the new Y coordinate of the upper left corner
     */
    void setTopLeftY(int topLeftY);

    /**
     * Sets the new width of rectangle.
     *
     * @param width the new width of rectangle.
     */
    void setWidth(int width);

    /**
     * Sets the new height of rectangle.
     *
     * @param height the new height of rectangle.
     */
    void setHeight(int height);

    /**
     * Updates this rectangle to have the specified dimensions.
     *
     * @param topLeftX the new X coordinate of the upper left corner
     * @param topLeftY the new Y coordinate of the upper left corner
     * @param width the new width of rectangle.
     * @param height the new height of rectangle.
     */
    void setBounds(int topLeftX, int topLeftY, int width, int height);

    /**
     * Prints coordinates of rectangle
     */
    void printPoints() const;

    /**
     * Move this rectangle by the given amounts.
     *
     * @param x the new X coordinate of the upper left corner
     * @param y the new Y coordinate of the upper left corner
     */
    void move(int x, int y);

    /**
     * Sets the size of this rectangle based on the specified dimensions.
     *
     * @param newWidth the new width of rectangle.
     * @param newHeight the new height of rectangle.
     */
    void resize(int newWidth, int newHeight);

    /**
     * A prefix increment operator. It increments the rectangle by 1.
     *
     * @return incremented rectangle by 1
     */
    Rectangle &operator++();

    /**
     * A postfix increment operator. It increments the rectangle by 1.
     *
     * @param value "crutch" for postfix increment
     * @return incremented rectangle by 1
     */
    Rectangle &operator++(int value);

    /**
     * A prefix decrement operator. It decrements the rectangle by 1.
     *
     * @return decremented rectangle by 1
     */
    Rectangle &operator--();

    /**
    * A postfix decrement operator. It decrements the rectangle by 1.
    *
    * @param value "crutch" for postfix decrement
    * @return decremented rectangle by 1
    */
    Rectangle &operator--(int value);

    /**
     * Intersection of two rectangles.
     *
     * @param other second rectangle which is needed for intersection
     * @return the result of intersection of two rectangles.
     */
    Rectangle operator-(const Rectangle &other);

    /**
     * Common part of two rectangles.
     *
     * @param other second rectangle which is needed for common part
     * @return the result of common part of two rectangles.
     */
    Rectangle operator+(const Rectangle &other);

    /**
     * Intersection with assignment.
     *
     * @param other second rectangle which is needed for intersection
     * @return the result of intersection of two rectangles.
     */
    Rectangle operator-=(const Rectangle &other);

    /**
     * Common part with assignment
     * @param other second rectangle which is needed for common part
     * @return the result of common part of two rectangles.
     */
    Rectangle operator+=(const Rectangle &other);
};


#endif //PPOISLAB1_RECTANGLE_H
