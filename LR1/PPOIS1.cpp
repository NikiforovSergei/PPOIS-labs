#include "large.hpp"
#include <iostream>

int main() {
    system("chcp 1251");
    string num1, num2;
    large a;
    int input, l=10;
    cout << "Первое число: ";
    getline(cin, num1);
    a = large(num1);
    
    while (1) {
        cout << endl << "1 - Преобразование длинного целого к целому;" << endl;
        cout << "2 - Сложение;" << endl;
        cout << "3 - Вычитание;" << endl;
        cout << "4 - Произведение;" << endl;
        cout << "5 - Деление;" << endl;
        cout << "6 - Пре- и постинкремент, пре- и постдекремент;" << endl;
        cout << "7 - Сравнение;" << endl;
        cin >> input;
        switch (input) {
            
        case 1:
            cout <<"Integer: " << a.ToInt() << endl;
            break;
        case 2:
            cout << "Второе число: " << endl;
            cin >> num2;
            a += large(num2);
            cout << "Сумма: " << (a).ToString() << endl;
            break;
        case 3:
            cout << "Второе число: "<<endl;
            cin >> num2;
            a -= large(num2);
            cout << "Разность: " << (a).ToString() << endl;
            break;
        case 4:
            cout << "Второе число: " << endl;
            cin >> num2;
            a *= large(num2);
            cout << "Произведение: " << (a).ToString() << endl;
            break;
        case 5:
            cout << "Второе число: " << endl;
            cin >> num2;
            a /= large(num2);
            cout << "Деление: " << (a).ToString() << endl;
            break;
        case 6:
            int i;
            
            cout << endl << "1 - Пре- и постинкремент;" << endl;
            cout << "2 - Пре- и постдекремент;" << endl;
            cin >> i;
            switch (i) {
            case 1:
                cout << "Преинкремент:" << (++a).ToString() << endl;
                cout << "Постинкремент:" << (a++).ToString() << endl;
                break;
            case 2:
                cout << "Предекремент:" << (--a).ToString() << endl;
                cout << "Постдекремент:" << (a--).ToString() << endl;
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
            cout << "Второе число: " << endl;
            cin >> num2;
            switch (j) {
            case 1:
                if (a == large(num2)) cout << "Верно" << endl;
                else cout << "Неверно" << endl;
                break;
            case 2:
                if (a != large(num2)) cout << "Верно" << endl;
                else cout << "Неверно" << endl;
                break;
            case 3:
                if (a > large(num2)) cout << "Верно" << endl;
                else cout << "Неверно" << endl;
                break;
            case 4:
                if (a < large(num2)) cout << "Верно"<<endl;
                else cout << "Неверно" << endl;
                break;
            case 5:
                if (a >= large(num2)) cout << "Верно" << endl;
                else cout << "Неверно" << endl;
                break;
            case 6:
                if (a <= large(num2)) cout << "Верно" << endl;
                else cout << "Неверно" << endl;
                break;
            }
            break;
        }
    }

}