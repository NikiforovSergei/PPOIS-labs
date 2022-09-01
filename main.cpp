#include "Matrix.h"

using namespace std;

int main() {

    Matrix<int> m = Matrix<int>();
    m.print();
    m.loadFromFile("../matrix1.txt");
    cout << endl;
    m.print();
    cout << endl;

    m.printMatrixType();
    return 0;
}
