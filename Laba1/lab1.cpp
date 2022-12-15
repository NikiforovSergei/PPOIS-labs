#include <fstream>
#include <iostream>
#include "Rect.h"
#include <string>
#include<vector>
using namespace std;

int info();

int main()
{
    setlocale(LC_ALL, "Rus");
    ifstream file("file.txt");

    char symbol;
    file >> symbol;

    int number = symbol - '0';

    vector<Rect> LIST(number);

    int i = 0;
    int x;
    int x1;
    int y;
    int y1;
    int key;

    while (i < number) {

        file >> symbol;
        x = symbol - '0';

        file >> symbol;
        y = symbol - '0';

        file >> symbol;
        x1 = symbol - '0';

        file >> symbol;
        y1 = symbol - '0';

        LIST[i].def(x, y, x1, y1);

        i++;
    }

    cout << "0 - Координаты\n1 - Передвинуть по координатам\n2 - Изменить размер\n3 ++\n4 --\n5 +\n6 +=\n7 -\n8 -=\n";
    //cout << "Input the key...\t";

    cin >> key;

    do {

        switch (key)
        {
        case 0: {
            int N = info();
            int* temp = LIST[N].get(); i = 0;

            while (i < 4) {
                cout << temp[i] << " ";
                i++;
            }

            delete[] temp;
            cout << endl;
            LIST[N].show();

            break;
        }
        case 1: {
            int N = info();

            cout << "Введине число, на которое хотите изменить...\t";

            int delta_x;
            int delta_y;

            cin >> delta_x;
            cin >> delta_y;

            LIST[N].move(delta_x, delta_y);
            LIST[N].show();

            break;
        }
        case 2: {
            int N = info();

            cout << "Введине число, на которое хотите изменить...\t";

            int delta_x;
            int delta_y;

            cin >> delta_x;
            cin >> delta_y;

            LIST[N].change(delta_x, delta_y);
            LIST[N].show();

            break;
        }
        case 3: {
            int N = info();

            LIST[N]++;

            LIST[N].show();

            break;
        }
        case 4: {
            int N = info();

            LIST[N]--;

            LIST[N].show();

            break;
        }
        case 5: {
            int N = info();
            int N1 = info();

            Rect temp;

            temp = LIST[N] + LIST[N1];
            LIST.push_back(temp);
            LIST[LIST.size() - 1].show();

            break;
        }
        case 6: {
            int N = info();
            int N1 = info();

            LIST[N] += LIST[N1];
            LIST[N].show();

            break;
        }
        case 7: {
            int N = info();
            int N1 = info();

            Rect temp = LIST[N] - LIST[N1];

            LIST.push_back(temp);
            LIST[LIST.size() - 1].show();

            break;
        }
        case 8: {
            int N = info();
            int N1 = info();

            LIST[N] -= LIST[N1];
            LIST[N].show();

            break;
        }
        }
        cout << "0 - Координаты\n1 - Передвинуть по координатам\n2 - Изменить размер\n3 ++\n4 --\n5 +\n6 +=\n7 -\n8 -=\n";
        //cout << "Input the key...\t";
        cin >> key;

        //system("cls");

    } while (key >= 0 && key <= 8);
}
int info()
{
    cout << "Введите номер прямоугольника...\t";

    int temp;
    cin >> temp;

    return temp;
}