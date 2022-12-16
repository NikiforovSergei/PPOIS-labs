#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Header.h"



using namespace std;

int main()
{
int tmpdeg = 0;

cout << "N1:" << endl;
cout << "Input degree:" << endl;
cin >> tmpdeg;
system("cls");

double* tmparr1 = new double [tmpdeg + 1 ];
cout << "Input coefficients:" << endl;
for (int i = 0; i <= tmpdeg; i++) 
{
    cin >> tmparr1[i];
}
MC test1(tmpdeg, tmparr1);
delete[] tmparr1;
system("cls");

//-----------------------------------------------------------------------------

cout << "N2:" << endl;
cout << "Input degree:" << endl;
cin >> tmpdeg;
system("cls");

double* tmparr2 = new double[tmpdeg + 1];
cout << "Input coefficients:" << endl;
for (int i = 0; i <= tmpdeg; i++)
{
    cin >> tmparr2[i];
}
MC test2(tmpdeg, tmparr2);
delete[] tmparr2;
system("cls");

//-----------------------------------------------------------------------------

int key = 0;

while(key == 0)
{

    cout << "N1:" << endl;
    test1.out();
    cout << "N2:" << endl;
    test2.out();
    cout << "Choose:" << endl;
    cout << "1)()" << endl;
    cout << "2)[]" << endl;
    cout << "3)+" << endl;
    cout << "4)-" << endl;
    cout << "5)*" << endl;
    cout << "6)/" << endl;
    cout << "7)Q" << endl;
    cin >> key;
    system("cls");

    int x = 0;
    MC test3;

    switch (key) 
    {
    case 1:
        x = 0;
        cout << "Imput x:" << endl;
        cin >> x;
        system("cls");
        cout << "N1:" << endl;
        test1.out();
        cout << "X = " << x << endl;
        cout << "Output:" << endl;
        cout << test1(x) << endl;
        key = 0;
        system("pause");
        system("cls");
        break;

    case 2:
        x = 0;
        cout << "Imput num:" << endl;
        cin >> x;
        system("cls");
        cout << "N1:" << endl;
        test1.out();
        cout << "Num = " << x << endl;
        cout << "Output:" << endl;
        cout << test1[x] << endl;
        key = 0;
        system("pause");
        system("cls");
        break;
    case 3:
        cout << "N1:" << endl;
        test1.out();
        cout << "N2:" << endl;
        test2.out();
        cout << "test3 = test1 + test2" << endl;
        test3 = test1 + test2;
        test3.out();
        cout << "test3 = test2 + test1" << endl;
        test3 = test2 + test1;
        test3.out();
        cout << "test1 += test2" << endl;
        test3 = test1;
        test3 += test2;
        test3.out();
        cout << "test2 += test1" << endl;
        test3 = test2;
        test3 += test1;
        test3.out();
        key = 0;
        system("pause");
        system("cls");
        break;
    case 4:
        cout << "N1:" << endl;
        test1.out();
        cout << "N2:" << endl;
        test2.out();
        cout << "test3 = test1 - test2" << endl;
        test3 = test1 - test2;
        test3.out();
        cout << "test3 = test2 - test1" << endl;
        test3 = test2 - test1;
        test3.out();
        cout << "test1 -= test2" << endl;
        test3 = test1;
        test3 -= test2;
        test3.out();
        cout << "test2 -= test1" << endl;
        test3 = test2;
        test3 -= test1;
        test3.out();
        key = 0;
        system("pause");
        system("cls");
        break;
    case 5:
        cout << "N1:" << endl;
        test1.out();
        cout << "N2:" << endl;
        test2.out();
        cout << "test3 = test1 * test2" << endl;
        test3 = test1 * test2;
        test3.out();
        cout << "test3 = test2 * test1" << endl;
        test3 = test2 * test1;
        test3.out();
        cout << "test1 *= test2" << endl;
        test3 = test1;
        test3 *= test2;
        test3.out();
        cout << "test2 *= test1" << endl;
        test3 = test2;
        test3 *= test1;
        test3.out();
        key = 0;
        system("pause");
        system("cls");
        break;
    case 6:
        cout << "N1:" << endl;
        test1.out();
        cout << "N2:" << endl;
        test2.out();
        cout << "test3 = test1 / test2" << endl;
        test3 = test1 / test2;
        test3.out();
        cout << "test3 = test2 / test1" << endl;
        test3 = test2 / test1;
        test3.out();
        cout << "test1 /= test2" << endl;
        test3 = test1;
        test3 /= test2;
        test3.out();
        cout << "test2 /= test1" << endl;
        test3 = test2;
        test3 /= test1;
        test3.out();
        key = 0;
        system("pause");
        system("cls");
        break;

    case 7:
        system("cls");
        break;
    }

}

}



