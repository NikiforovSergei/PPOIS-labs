#include "Header.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    card a, b;
    string password, first, second;
    int choice, choice2 = 0, choice4, cash = 0, cash2 = 0, wallet;

    cout << "Введите имя фамилию пользователя: ";
    cin >> first >> second;
    a.setname(first, second);
    b.setname(first, second);
    system("cls");

    cout << "Введите ваш пароль: ";
    cin >> password;
    a.set_password(password);
    system("cls");

    cout << "Введите ваш пароль для второго счёта: ";
    cin >> password;
    b.set_password(password);
    system("cls");

    cout << "Ваш баланс: ";
    cin >> cash;
    a.balance(cash);
    cout << "Ваш баланс на втором счету: ";
    cin >> cash2;
    b.balance(cash2);
    system("cls");

    cout << "1 - продолжить" << endl << "0 - выход" << endl;
    cin >> choice;
    system("cls");

    if (choice == 1) {
        while (true) {
            cout << "1 - пополнение счёта" << endl << "2 - снять со счёта" << endl << "3 - посмотреть выписку" <<
                endl << "4 - получить информацию о карте" << endl << "5 - изменить ПИН-код" << endl << "6 - перевести с первого счёта на второй" << endl <<
                "7 - перевести со второго счёта на первый" << endl << "0 - выход" << endl << endl;
            cin >> choice;
            system("cls");

            cout << "Выберите счёт:" << endl << "1 - основной" << endl << "2 - дополнительный" << endl;
            cin >> wallet;
            if (choice == 1) {

                if (wallet == 1) {

                    a.pin();
                    cout << "Сумма: ";
                    cin >> choice2;
                    a.replenishment(choice2);
                    system("cls");
                }
                else if (wallet == 2) {
                    b.pin();
                    cout << "Сумма: ";
                    cin >> choice2;
                    b.replenishment(choice2);
                    system("cls");
                }
                continue;
            }


            if (choice == 2) {

                if (wallet == 1) {
                    a.pin();
                    cout << "Сумма: ";
                    cin >> choice2;
                    a.withdraw(choice2);
                    system("cls");
                }
                else if (wallet == 2)
                {
                    b.pin();
                    cout << "Сумма: ";
                    cin >> choice2;
                    b.withdraw(choice2);
                    system("cls");
                }
                continue;

            }

            if (choice == 3)
            {
                if (wallet == 1)
                {
                    a.pin();
                    a.view();
                }

                else if (wallet == 2)
                {
                    b.pin();
                    b.view();
                }
                continue;
            }

            if (choice == 4)
            {
                if (wallet == 1)
                {
                    a.pin();
                    a.info("info.txt");
                }

                else if (wallet == 2)
                {
                    b.pin();
                    b.info("info.txt");
                }
                continue;
            }

            if (choice == 5)
            {
                if (wallet == 1)
                    a.change_pin();
                else if (wallet == 2)
                    b.change_pin();
                continue;
            }

            if (choice == 6)
            {
                a.pin();
                cout << "Сумма: ";
                cin >> choice4;
                a.get_for_transfer(choice4);
                b.replenishment_from_transfer(choice4);
                continue;
            }

            if (choice == 7)
            {
                b.pin();
                cout << "Сумма: ";
                cin >> choice4;
                b.get_for_transfer(choice4);
                a.replenishment_from_transfer(choice4);
                continue;
            }
            if (choice == 0) break;
        }
    }
    else if (choice == 0) return 0;
    
}
