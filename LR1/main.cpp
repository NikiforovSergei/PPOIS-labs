#include <iostream>
#include "rectangle_lib/Rectangle.h"

using namespace std;

int main() {
    // test constructor and print points of object;
    cout << "First test\n";
    cout << "all fields are zero, empty\n";
    Rectangle first;
    first.printPoints();
    first.setTopLeftX(3);
    first.setBounds(2,9,6,4);
    first.printPoints();

    // test move rectangle;
    cout << "Second test\n";
    cout << "move to (3,7)\n";
    first.move(3,7);
    first.printPoints();

    //test resize rectangle;
    cout << "Third test\n";
    cout << "resizing\n";
    first.resize(4,3);
    first.printPoints();

    // test each side magnification;
    cout << "Fourth test\n";
    cout << "each side magnification\n";
    first++;
    first.printPoints();

    // test each side reduction;
    cout << "Fifth test\n";
    cout << "each side reduction\n";
    first--;
    first.printPoints();

    // test intersection of two rectangles;
    cout << "Sixth test\n";
    cout << "intersection of two rectangles\n";
    first.setBounds(2,9,6,4);
    first.printPoints();
    Rectangle second(5,7,8,5);
    second.printPoints();
    Rectangle third;
    third = first - second;
    third.printPoints();

    // test finding common part of two rectangles;
    cout << "Seventh test\n";
    cout << "common part of two rectangles;\n";
    first.setBounds(2,9,6,4);
    first.printPoints();
    second.setBounds(5,7,8,4);
    second.printPoints();
    third = first + second;
    third.printPoints();

    // test intersection if rectangles don't have common points;
    cout << "Eighth test\n";
    cout << "no common points;\n";
    first.setBounds(2,9,6,4);
    first.printPoints();
    second.setBounds(9,7,8,4);
    second.printPoints();
    third = first - second;
    third.printPoints();
    cout << third.isEmpty() << endl;
    cout << "--------\n";

    //test shorthand intersection, "third is empty";
    third -= first;
    third.printPoints();
    cout << "--------\n";

    // test shorthand intersection;
    first.printPoints();
    second.setBounds(5,7,8,4);
    first -= second;
    first.printPoints();
    cout << "--------\n";

    //test shorthand common part;
    first.setBounds(2,9,6,4);
    first += second;
    first.printPoints();
    cout << "--------\n";
    Rectangle rect;
    rect++;
    rect.printPoints();




    return 0;
}
