#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void oneIteration(PrintWorld a) {
    cout << "---------- " <<" stage ----------\n";
    a.movementStage();
    cout << "---------- movement stage ----------\n";
    a.printStage();
    a.eatStage();
    cout << "---------- eat stage ----------\n";
    a.printStage();
    a.reproductionStage();
    cout << "---------- reproduction stage ----------\n";
    a.printStage();
    cout << "---------- end stage ----------\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    ifstream fin;
    int grass, rabbits, foxes;
    fin.open("input.txt");
    if (fin.is_open()) {
        fin >> grass >> rabbits >> foxes;
    }
    else {
        cout << "Введите количество травянистых растений: " << endl;
        cin >> grass;
        cout << "Введите количество зайцев: " << endl;
        cin >> rabbits;
        cout << "Введите количество лис: " << endl;
        cin >> foxes;
    }
    
    PrintWorld a(grass, rabbits, foxes);
    cout << "---------- init world ----------\n";
    a.initWorld();
    a.printStage();
    int status = 1;
    for (int i = 0; i < 40; i++) {
        if (status != 2) {
            cout << "Выберите\n1.Сделать 1 итерацию\n2.Сделать оставшиеся итерации\n";
            cin >> status;
        }
        oneIteration(a);
    }
    
}