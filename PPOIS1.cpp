#include "large.hpp"
#include <iostream>

int main() {
    system("chcp 1251");
    string num1, num2;
    large a;
    int input, l = 10;
    cout << "������ �����: ";
    getline(cin, num1);
    a = large(num1);

    while (1) {
        cout << endl << "1 - �������������� �������� ������ � ������;" << endl;
        cout << "2 - ��������;" << endl;
        cout << "3 - ���������;" << endl;
        cout << "4 - ������������;" << endl;
        cout << "5 - �������;" << endl;
        cout << "6 - ���- � �������������, ���- � �������������;" << endl;
        cout << "7 - ���������;" << endl;
        cin >> input;
        switch (input) {

        case 1:
            cout << "Integer: " << a.ToInt() << endl;
            break;
        case 2:
            cout << "������ �����: " << endl;
            cin >> num2;
            a += large(num2);
            cout << "�����: " << (a).ToString() << endl;
            break;
        case 3:
            cout << "������ �����: " << endl;
            cin >> num2;
            a -= large(num2);
            cout << "��������: " << (a).ToString() << endl;
            break;
        case 4:
            cout << "������ �����: " << endl;
            cin >> num2;
            a *= large(num2);
            cout << "������������: " << (a).ToString() << endl;
            break;
        case 5:
            cout << "������ �����: " << endl;
            cin >> num2;
            a /= large(num2);
            cout << "�������: " << (a).ToString() << endl;
            break;
        case 6:
            int i;

            cout << endl << "1 - ���- � �������������;" << endl;
            cout << "2 - ���- � �������������;" << endl;
            cin >> i;
            switch (i) {
            case 1:
                cout << "������������:" << (++a).ToString() << endl;
                cout << "�������������:" << (a++).ToString() << endl;
                break;
            case 2:
                cout << "������������:" << (--a).ToString() << endl;
                cout << "�������������:" << (a--).ToString() << endl;
                break;
            }
            break;
        case 7:
            int j;
            cout << endl << "1 - ==;" << endl;
            cout << "2 - !=;" << endl;
            cout << "3 - >;" << endl;
            cout << "4 - <;" << endl;
            cout << "5 - >=;" << endl;
            cout << "6 - <=;" << endl;
            cin >> j;
            cout << "������ �����: " << endl;
            cin >> num2;
            switch (j) {
            case 1:
                if (a == large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            case 2:
                if (a != large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            case 3:
                if (a > large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            case 4:
                if (a < large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            case 5:
                if (a >= large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            case 6:
                if (a <= large(num2)) cout << "�����" << endl;
                else cout << "�������" << endl;
                break;
            }
            break;
        }
    }

}