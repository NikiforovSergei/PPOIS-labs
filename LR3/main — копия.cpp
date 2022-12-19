#include "MyObject.h"
#include "sorting.h"
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    setlocale(LC_ALL, "Rus");
    vector<MyObject> vector_temp_bozo = { MyObject(17), MyObject(-15), MyObject(180), MyObject(-250) };
    MyObject array_bozo[] = { MyObject(12), MyObject(-10), MyObject(120), MyObject(-230), MyObject(-250) };
    vector<MyObject> vector_temp_merge = { MyObject(8), MyObject(13), MyObject(-120), MyObject(230) };
    MyObject array_merge[] = { MyObject(14), MyObject(56), MyObject(-98), MyObject(980), MyObject(-250) };

    cout << "\t-Bozo-" << endl;
    cout << "Vector: ";
    show_sequence(vector_temp_bozo, 4);
    BozoSort(vector_temp_bozo, 4);
    cout << "Sorted Vector ";
    show_sequence(vector_temp_bozo, 4);

    cout << "\nArray ";
    show_sequence(array_bozo, 4);
    BozoSort(array_bozo, 4);
    cout << "Sorted Array ";
    show_sequence(array_bozo, 4);

    cout << "\n\n\t-Merge-" << endl;
    cout << "Vector: ";
    show_sequence(vector_temp_merge, 4);
    MergeSort(vector_temp_merge, 0, 3);
    cout << "Sorted Vector: ";
    show_sequence(vector_temp_merge, 4);

    cout << "\nArray: ";
    show_sequence(array_merge, 4);
    MergeSort(array_merge, 0, 3);
    cout << "Sorted Array: ";
    show_sequence(array_merge, 4);
   
}