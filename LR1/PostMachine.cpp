#include "Rules.h"
#include <iostream>
#include <Windows.h>
#include <string>

int main(int argc, char* argv[])
{
    int kod;
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Данная программа является простейшей реализацией абстрактной машины Поста.\n";
    cout << "Лента состоит из двоичного кода, где элементы – число, представленное в двоичном виде.\n";
    cout << "Пользователь вводит ленту и программа считывает необходимые операции из файла input.txt\n";
    cout << "Вывод происходит в файле result.txt\n\n\n\n";
    int help;
    PostMachine postMachine;
    cout << "1: Выполнить с -log\n";
    cout << "2: Выполнить без аргументов\n";
    cout << "\nВыберите действие которое хотите выполнить:\n";
    cin >> kod;
    cout << "\n\n\n";
    switch (kod)
    {
    case 1: {postMachine.readTape();
        postMachine.readInputFile("input.txt");
        string result = postMachine.start();
        cout << "\n\nрезультат: " << "\n\n";
    }
    case 2: {postMachine.readTape();
        postMachine.readInputFile("input.txt");
        string result = postMachine.start2();
    }
    }
    

}
