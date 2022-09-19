#include "Rectangle.h"
#include <gtest/gtest.h>

TEST(RectangleTest, isEmpty) {
    Rectangle rect1;
    EXPECT_EQ(rect1.isEmpty(), true);
    rect1.setBounds(2, 9, 6, 4);
    EXPECT_EQ(rect1.isEmpty(), false);
    Rectangle rect2(9, 7, 8, 4);
    Rectangle rectRez;
    rectRez.setBounds(0, 0, 0, 0);
    EXPECT_EQ(rectRez.isEmpty(), true);
    rectRez = rect1 - rect2;
    EXPECT_EQ(rectRez.isEmpty(), true);
    rect2.setBounds(5, 7, 8, 5);
    rectRez = rect1 - rect2;
    EXPECT_EQ(rectRez.isEmpty(), false);
}

TEST(RectangleTest, intersection) {
    Rectangle rect1;
    rect1.setBounds(2, 9, 6, 4);
    Rectangle rect2(5, 7, 8, 4);
    Rectangle rectRez;
    rectRez = rect1 - rect2;
    EXPECT_EQ(rectRez.getTopLeftX(), 5);
    EXPECT_EQ(rectRez.getTopLeftY(), 7);
    EXPECT_EQ(rectRez.getBottomRightX(), 8);
    EXPECT_EQ(rectRez.getBottomRightY(), 5);
}

TEST(RectangleTest_intersection_Test, noIntersection) {
    Rectangle rect1;
    rect1.setBounds(2, 9, 6, 4);
    Rectangle rect2(9, 7, 8, 4);
    Rectangle rectRez;
    rectRez = rect1 - rect2;
    EXPECT_EQ(rectRez.getTopLeftX(), 0);
    EXPECT_EQ(rectRez.getTopLeftY(), 0);
    EXPECT_EQ(rectRez.getBottomRightX(), 0);
    EXPECT_EQ(rectRez.getBottomRightY(), 0);
}

TEST(RectangleTest_intersection_Test, intersectAsign) {
    Rectangle rect1;
    rect1.setBounds(2, 9, 6, 4);
    Rectangle rect2(9, 7, 8, 4);
    rect1 -= rect2;
    EXPECT_EQ(rect1.getTopLeftX(), 2);
    EXPECT_EQ(rect1.getTopLeftY(), 9);
    EXPECT_EQ(rect1.getBottomRightX(), 8);
    EXPECT_EQ(rect1.getBottomRightY(), 5);

    rect2.setBounds(5, 7, 8, 4);
    rect1 -= rect2;
    EXPECT_EQ(rect1.getTopLeftX(), 5);
    EXPECT_EQ(rect1.getTopLeftY(), 7);
    EXPECT_EQ(rect1.getBottomRightX(), 8);
    EXPECT_EQ(rect1.getBottomRightY(), 5);
}

TEST(RectangleTest, commonPart) {
    Rectangle rect1;
    rect1.setBounds(2, 9, 6, 4);
    Rectangle rect2(5, 7, 8, 4);
    Rectangle rectRez;
    rectRez = rect1 + rect2;
    EXPECT_EQ(rectRez.getTopLeftX(), 2);
    EXPECT_EQ(rectRez.getTopLeftY(), 9);
    EXPECT_EQ(rectRez.getBottomRightX(), 13);
    EXPECT_EQ(rectRez.getBottomRightY(), 3);
}

TEST(RectangleTest_commonPart_Test, commonPartAsign) {
    Rectangle rect1(1, 5, 3, 2);
    Rectangle rect2;
    rect2.setBounds(4, 2, 3, 1);
    rect1 += rect2;
    EXPECT_EQ(rect1.getTopLeftX(), 1);
    EXPECT_EQ(rect1.getTopLeftY(), 5);
    EXPECT_EQ(rect1.getBottomRightX(), 7);
    EXPECT_EQ(rect1.getBottomRightY(), 1);
}

TEST(RectangleTest, magnification) {
    Rectangle rect(3, 10, 6, 4);
    rect++;
    EXPECT_EQ(rect.getTopLeftX(), 2);
    EXPECT_EQ(rect.getTopLeftY(), 11);
    EXPECT_EQ(rect.getBottomRightX(), 10);
    EXPECT_EQ(rect.getBottomRightY(), 5);
}

TEST(RectangleTest, reduction) {
    Rectangle rect(3, 10, 6, 4);
    rect--;
    EXPECT_EQ(rect.getTopLeftX(), 4);
    EXPECT_EQ(rect.getTopLeftY(), 9);
    EXPECT_EQ(rect.getBottomRightX(), 8);
    EXPECT_EQ(rect.getBottomRightY(), 7);
}

TEST(RectangleTest, move) {
    Rectangle rect(1, 6, 5, 3);
    EXPECT_EQ(rect.getTopLeftX(), 1);
    EXPECT_EQ(rect.getTopLeftY(), 6);
    EXPECT_EQ(rect.getBottomRightX(), 6);
    EXPECT_EQ(rect.getBottomRightY(), 3);

    rect.move(3, 3);
    EXPECT_EQ(rect.getTopLeftX(), 3);
    EXPECT_EQ(rect.getTopLeftY(), 3);
    EXPECT_EQ(rect.getBottomRightX(), 8);
    EXPECT_EQ(rect.getBottomRightY(), 0);
}

TEST(RectangleTest, resize) {
    Rectangle rect(2, 5, 5, 3);
    EXPECT_EQ(rect.getTopLeftX(), 2);
    EXPECT_EQ(rect.getTopLeftY(), 5);
    EXPECT_EQ(rect.getBottomRightX(), 7);
    EXPECT_EQ(rect.getBottomRightY(), 2);

    rect.resize(3, 2);
    EXPECT_EQ(rect.getTopLeftX(), 2);
    EXPECT_EQ(rect.getTopLeftY(), 5);
    EXPECT_EQ(rect.getBottomRightX(), 5);
    EXPECT_EQ(rect.getBottomRightY(), 3);

    rect.resize(7, 4);
    EXPECT_EQ(rect.getTopLeftX(), 2);
    EXPECT_EQ(rect.getTopLeftY(), 5);
    EXPECT_EQ(rect.getBottomRightX(), 9);
    EXPECT_EQ(rect.getBottomRightY(), 1);
}

TEST(RectangleTest, area) {
    Rectangle rect(2, 5, 5, 3);
    EXPECT_EQ(rect.getArea(), 15);
}
