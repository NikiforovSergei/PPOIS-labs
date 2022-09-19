#include "RubiksCube.h"
/*****************************************************************//**
 * \file   main.cpp
 * \brief  Main файл, который управляет главным меню.
 * \author dokkabae
 * \date   September 2022
 *********************************************************************/
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    RubiksCube Cube;
    while (true)
    {
        while (true)
        {
            bool fail = true;
            int choice = 0;
            do //Выбор способа создания куба
            {
                cout << "Задание цветов случайным образом - 1\nЗадание цветов с файла - 2\nВыход из программы - 3 : ";
                cin >> choice;
                if (!cin.fail())
                {
                    if (choice < 4 && choice > 0)
                    {
                        fail = false;
                    }
                    else cout << "Неккоректный ввод." << endl;
                }
                else cout << "Неккоректный ввод." << endl;
                cin.clear();
                cin.ignore();
            } while (fail);
            switch (choice)
            {
            case 1: Cube.Initializate();Cube.CreateRandom(); break;
            case 2: Cube.CreateFromFile(); break;
            case 3: exit(0);
            }
            break;
        }
        while (true) //кубик уже создан
        {
            bool fail = true;
            int choice = 0;
            do
            {
                cout << "Просмотр кубика - 1\nПоворот грани кубика - 2\nВыход из программы - 3 : ";
                cin >> choice;
                if (!cin.fail())
                {
                    if (choice > 0 && choice < 4)
                    {
                        fail = false;
                    }
                    else cout << "Неккоректный ввод." << endl;
                }
                else cout << "Неккоректный ввод." << endl;
                cin.clear();
                cin.ignore();
            } while (fail);
            switch (choice)
            {
            case 1: Cube.Print(); break;
            case 2: Cube.InputCommands(); break;
            case 3: exit(0);
            }
        }
    }
}