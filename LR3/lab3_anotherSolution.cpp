#include <iostream>
#include <vector>
#include "Header.h"
using namespace std;

int main()
{
    std::vector<int> vect = { -5, 6, 1, 2, 10, -7, -8, 15 };
    int type, type2;
    setlocale(LC_ALL, "Russian");
    cout << "Выберите тип сортировки:\n";
    cout << "1.Сетями\n2.Быстрая сортировка\n";
    cin >> type;
   /* netsort::qsort(&vect[0], 0, vect.size() - 1, [](int a, int b) { return a > b; });*/
    /*netsort::sorting_network sn;
    sn.emplace_back(0, 3);
    sn.emplace_back(1, 2);
    sn.emplace_back(0, 1);
    sn.emplace_back(0, 2);
    sn.emplace_back(2, 3);
    sn.emplace_back(1, 3);
    sn.emplace_back(1, 2);
    sn.apply(&vect[0], [](int a, int b) {return a > b; });*/
    netsort::sorting_network sn;
    //sn.sort(&vect[0], 0, 8, 1);
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
}