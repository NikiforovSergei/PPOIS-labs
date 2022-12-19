#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

template <typename T>
T input(T buffer, int n)
{
    cout << endl;
    cout << "Введите элементы\n";
    for (int i = 0; i < n; i++)
        cin >> buffer[i];
    cout << endl;
    return buffer;
}

template <typename T>
vector <T> inputV (vector <T> buffer, int n)
{
    T a;
    cout << endl;
    cout << "Введите элементы вектора\n";
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        buffer.push_back(a);
    }
    cout << endl;
    return buffer;
}

int main()
{
    setlocale(0, "");
    int n;
    cout << "Ввелите размер масива\n";
    cin >> n;
    int* buffer = new int[n];
    buffer = input(buffer, n);
    vector <int> vBuffer=inputV(vBuffer,n);
    int way;
    cout << "1 - Cocktail Sort\n2 - Strand Sort\n--> ";
    cin >> way;
    switch (way)
    {
    case 1:
    {
        cout << "Массив после сортировки:" << endl;
        cocktailSort(buffer, n);
        show(buffer, n);
        cout << endl;

        cout << "Вектор после сортировки" << endl;
        cocktailSort(vBuffer, vBuffer.size());
        show(vBuffer, vBuffer.size());
        cout << endl;
        break;
    }

    case 2:
    {
        cout << "Массив после сортировки" << endl;
        strandSort(buffer, n);
        show(buffer, n);
        cout << endl;

        cout << "Вектор после сортировки" << endl;
        strandSort(vBuffer, vBuffer.size());
        show(vBuffer, vBuffer.size());
        cout << endl;

        break;
    }
    }
    delete[] buffer;
}