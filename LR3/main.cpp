#include <iostream>
#include <vector>
#include <lab3.h>
using namespace std;

int main()
{
    cout<<"Sorting vector with integers:"<<endl;
    std::vector<int> vect = {1, 6, 3, 0, -4, 126, 31, -35, 35, 7, 8, -3, 4, -7};
    netsort::qsort(&vect[0], 0, vect.size() - 1, [](int a, int b) { return a < b; });
    for (int elem: vect){
        cout << elem << " ";
    }
    cout<<"\n\n";

    cout<<"Sorting array with integers:"<<endl;
    int arr[] = {1, 6, 3, 0, -4, 126, 31, -35, 35, 7, 8, -3, 4, -7};
    int array_size = *(&arr + 1) - arr;

    netsort::qsort(arr, 0, 13, [](int a, int b) { return a < b; });
    for (int i=0;i<array_size;i++)
        cout<<arr[i]<<" ";
    cout<<"\n\n";
    return 0;
}
