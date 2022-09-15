#include "Matrix.h"

using namespace std;

int main() {
    Matrix m;
    m.print();
    m.loadFromFile("resources/matrix1.txt");
    cout << endl;
    m.print();
    cout << endl;

    m.changeColumns(5);
    m.changeRows(5);
    m.setValue(3,3,1);
    m.setValue(4,4,1);
    m.print();

    m.printMatrixType();
    return 0;
}
