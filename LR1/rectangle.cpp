#include <fstream>
#include <iostream>
#include "object.h"
#include <string>
#include<vector>
using namespace std;

int get_info();

int main()
{
    ifstream file("file.txt"); 

    char symbol;
    file >> symbol;

    int number_of_rect = symbol - '0';

    vector<RECT> LIST(number_of_rect);

    int i = 0;
    int x;
    int x1;
    int y;
    int y1;
    int key;

    while (i<number_of_rect) {

        file >> symbol; 
        x = symbol - '0';

        file >> symbol;
        y = symbol - '0';

        file >> symbol;
        x1 = symbol - '0';

        file >> symbol;
        y1 = symbol - '0';

        LIST[i].define(x, y, x1, y1);

        i++;
    }

    cout << "0 get xy\t1 move\t2 ch_size\t3 ++\t4 --\t5 +\t6 +=\t7 -\t8 -=\n";
    cout << "Input the key...\t";

    cin >> key;

    do {
      
        switch (key)
        {
        case 0: {
            int N = get_info();
            int* temp = LIST[N].get_xy(); i = 0;

            while (i < 4) {
                cout << temp[i] << " ";
                i++;
            }

            delete[] temp;
            cout << endl;
            LIST[N].show_xy();

            break;
        }
        case 1: {
            int N = get_info();

            cout << "Input delta_x and delta_y...\t";

            int delta_x;
            int delta_y;

            cin >> delta_x;
            cin >> delta_y;

            LIST[N].move(delta_x, delta_y);
            LIST[N].show_xy();

            break;
        }
        case 2: {
            int N = get_info();

            cout << "Input delta_x and delta_y...\t";

            int delta_x;
            int delta_y;

            cin >> delta_x;
            cin >> delta_y;

            LIST[N].change_size(delta_x, delta_y);
            LIST[N].show_xy();

            break;
        }
        case 3: {
            int N = get_info();

            LIST[N]++;

            LIST[N].show_xy();

            break;
        }
        case 4: {
            int N = get_info();

            LIST[N]--;

            LIST[N].show_xy();

            break;
        }
        case 5: {
            int N = get_info();
            int N1 = get_info();

            RECT temp;

            temp = LIST[N] + LIST[N1];
            LIST.push_back(temp);
            LIST[LIST.size()-1].show_xy();

            break;
        }
        case 6: {
            int N = get_info();
            int N1 = get_info();

            LIST[N] += LIST[N1];
            LIST[N].show_xy();

            break;
        }
        case 7: {
            int N = get_info();
            int N1 = get_info();

            RECT temp = LIST[N] - LIST[N1];

            LIST.push_back(temp);
            LIST[LIST.size()-1].show_xy();

            break;
        }
        case 8: {
            int N = get_info();
            int N1 = get_info();

            LIST[N] -= LIST[N1];
            LIST[N].show_xy();

            break;
        }
        }
        cout << "0 get xy\t1 move\t2 ch_size\t3 ++\t4 --\t5 +\t6 +=\t7 -\t8 -=\n";
        cout << "Input the key...\t";
        cin >> key;

        system("cls");

    } while (key >= 0 && key <= 8);
}
int get_info()
{
    cout << "Input the number of rectangular...\t";

    int temp; 
    cin >> temp;

    return temp;
}