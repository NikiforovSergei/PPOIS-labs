#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

int main()
{
    int buffer[] = { 5, -3, 1, 3, 2, 9, 17, -17, 1 };
    cout << "Array size: " << sizeof(buffer) / sizeof(buffer[0]) << endl;
    show(buffer, sizeof(buffer) / sizeof(buffer[0]));
    cout << endl << endl;

    vector<double> vBuffer = { 3.2, 2, 1, 10.23, -1.5, 12, 9, 3 };
    cout << "Vector size: " << vBuffer.size() << endl;
    show(vBuffer, vBuffer.size());
    cout << endl << endl;

    int way;
    cout << "[Select the needed sorting]\n1 - Cocktail Sort\n2 - Strand Sort\n\n--> ";
    cin >> way; cout << endl;
    switch (way)
    {
    case 1:
    {
        cout << "[Array after sorting]" << endl;
        cocktailSort(buffer, sizeof(buffer) / sizeof(buffer[0]));
        show(buffer, sizeof(buffer) / sizeof(buffer[0]));
        cout << endl << endl;

        cout << "[Vector after sorting]" << endl;
        cocktailSort(vBuffer, vBuffer.size());
        show(vBuffer, vBuffer.size());
        cout << endl << endl;

        break;
    }

    case 2:
    {
        cout << "[Array after sorting]" << endl;
        strandSort(buffer, sizeof(buffer) / sizeof(buffer[0]));
        show(buffer, sizeof(buffer) / sizeof(buffer[0]));
        cout << endl << endl;

        cout << "[Vector after sorting]" << endl;
        strandSort(vBuffer, vBuffer.size());
        show(vBuffer, vBuffer.size());
        cout << endl << endl;

        break;
    }

    default:
        cout << "\nThere is no such item";
        break;
    }

}
