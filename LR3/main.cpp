#include <iostream>
#include "MyObject.h"
#include "vector"
#include "sorting.h"
using namespace std;


int main() {
    int is_reverse;
    vector<MyObject> vector_temp_bozo = {MyObject(17), MyObject(-15), MyObject(180), MyObject(-250)};
    MyObject array_bozo[] = {MyObject(12), MyObject(-10), MyObject(120), MyObject(-230), MyObject(-250)};
    vector<MyObject> vector_temp_merge = {MyObject(8), MyObject(13), MyObject(-120), MyObject(230)};
    MyObject array_merge[] = {MyObject(14), MyObject(56), MyObject(-98), MyObject(980), MyObject(-250)};
    cout << "Если хотим по возрастанию введите 1 иначе любую другую цифру для убывания" << endl;
    cin >> is_reverse;
    if (is_reverse == 1){
        cout << "Bozo sort" << endl;
        cout << "vector was " << endl;
        show_sequence(vector_temp_bozo, 4);
        BozoSort(vector_temp_bozo, 4);
        cout << "vector after sort " << endl;
        show_sequence(vector_temp_bozo, 4);

        cout << "array was " << endl;
        show_sequence(array_bozo, 4);
        BozoSort(array_bozo, 4);
        cout << "array after sort " << endl;
        show_sequence(array_bozo, 4);
        cout << endl;

        cout << "Merge sort" << endl;
        cout << "vector was " << endl;
        show_sequence(vector_temp_merge, 4);
        MergeSort(vector_temp_merge,0, 3);
        cout << "vector after sort " << endl;
        show_sequence(vector_temp_merge, 4);

        cout << "array was " << endl;
        show_sequence(array_merge, 4);
        MergeSort(array_merge,0, 3);
        cout << "array after sort " << endl;
        show_sequence(array_merge, 4);
    } else {
        cout << "Bozo sort" << endl;
        cout << "vector was " << endl;
        show_sequence(vector_temp_bozo, 4);
        BozoSort(vector_temp_bozo, 4);
        Reverse(vector_temp_bozo, 4);
        cout << "vector after sort " << endl;
        show_sequence(vector_temp_bozo, 4);

        cout << "array was " << endl;
        show_sequence(array_bozo, 4);
        BozoSort(array_bozo, 4);
        Reverse(array_bozo, 4);
        cout << "array after sort " << endl;
        show_sequence(array_bozo, 4);
        cout << endl;

        cout << "Merge sort" << endl;
        cout << "vector was " << endl;
        show_sequence(vector_temp_merge, 4);
        MergeSort(vector_temp_merge,0, 3);
        Reverse(vector_temp_merge, 4);
        cout << "vector after sort " << endl;
        show_sequence(vector_temp_merge, 4);

        cout << "array was " << endl;
        show_sequence(array_merge, 4);
        MergeSort(array_merge,0, 3);
        Reverse(array_merge, 4);
        cout << "array after sort " << endl;
        show_sequence(array_merge, 4);
    }
    return 0;
}
