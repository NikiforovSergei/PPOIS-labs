#include <iostream>
#include <vector>
#include "sort.h"
using namespace std;

int main()
{
    Start:
    std::vector<int> vect = { -6, 4, -1, -18, 9, -7, -5, 25 };
    int type, type2;
    setlocale(LC_ALL, "Russian");
    cout << "Выберите тип сортировки:\n";
    cout << "1.Сетями\n2.Быстрая сортировка\n";
    cin >> type;
    
    netsort::sorting_network sn;
    if (type == 1) {
        cout << "Выберите порядок\n0 - по убыванию\n1 - по возрастанию\n";
        cin >> type2;
        netsort::sorting_network sn;
        sn.sort(&vect[0], 0, 8, type2);
    }
    else if (type == 2) {
        cout << "Выберите порядок\n0 - по убыванию\n1 - по возрастанию\n";
        cin >> type2;
        netsort::quickSort(&vect[0], 0, 7, type2);
    }
    else {
        cout << "Вы выбрали не тот тип!\n";
    }

    for (int elem : vect) {
        cout << elem << " ";
    }
    cout << "\n\n";
    goto Start;
}