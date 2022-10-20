#include "Rules.h"
#include <iostream>
#include <Windows.h>
#include <string>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Данная программа является простейшей реализацией абстрактной машины Поста.\n";
    cout << "Лента состоит из двоичного кода, где элементы – число, представленное в двоичном виде.\n";
    cout << "Пользователь вводит ленту и программа считывает необходимые операции из файла input.txt\n";
    cout << "Вывод происходит в файле result.txt\n\n\n\n";
        int help;
        PostMachine postMachine;
        postMachine.readTape();
        postMachine.readInputFile("input.txt");
        cout << "\n\n\n";
        string result = postMachine.start();
        if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
        {
            string s = argv[1];
            if (s == "-log") {
                postMachine.coutStateBefore();
                postMachine.coutStateAfter();
            }
            else
            {
                cout << "Аргументов нет\n";
            }
            cout << result;
            return 0;
        }
    }