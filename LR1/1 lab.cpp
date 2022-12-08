#include "Library.h"
#include <fstream>
#include<Windows.h>

using namespace std;
/// <summary>
/// menu of program
/// </summary>
/// <param name="root">vocabluary</param>
/// <returns>return this menu while program wont be completed</returns>
int choise(anglo_russkii vocabulary) {
    int c; string x, s;
    cout << "Выберите действие:\n1) Добавление нового английского слова и перевода для него\n2) Удаление существующего ";
    cout << "английского слова из словаря\n3) Поиск перевода английского слова\n4) Замена перевода английского слова\n5) Определение ";
    cout << "количества слов в словаре\n6) Просмотр словаря\n7) Выход " << endl;
    cin >> c;
    system("cls");
    switch (c) {
    case 1: {
        cout << "Введите английское слово                    "; cin >> x;
        cout << "Введите перевод английского слова           "; cin >> s;
        pair<string, string> ab;
        ab.first = x;
        ab.second = s;
        vocabulary = (vocabulary += ab);
        return choise(vocabulary);
    }
    case 2: {
        cout << "Введите английское слово                    "; cin >> x;
        vocabulary = (vocabulary -= x);
        return choise(vocabulary);
    }
    case 3: {
        cout << "Введите английское слово                    "; cin >> x;
        anglo_russkii::Node* a;
        a = vocabulary[x];
        cout << "Перевод    " << a->rus << endl;
        return choise(vocabulary);
    }
    case 4: {
        cout << "Введите английское слово                    "; cin >> x;
        cout << "Введите новый перевод английского слова     "; cin >> s;
        anglo_russkii::Node* a;
        a = vocabulary[x];
        cout << "Было: " << a->angl << " " << a->rus << endl;
        a->rus = s;
        cout << "Стало: " << a->angl << " " << a->rus << endl;
        return choise(vocabulary);
    }
    case 5: {
        cout << "В данном словаре " << vocabulary.get_size() << " слов" << endl;
        return choise(vocabulary);
    }
    case 6: {
        cout << "Ваш словарь: " << endl;
        if (vocabulary.get_root() != nullptr) {
            vocabulary.view_tree(vocabulary.get_root(), vocabulary.get_size());
        }
        else {
            cout << "Cловарь пуст" << endl;
        }
        return choise(vocabulary);
    }
    case 7: {
        cout << "До встречи!" << endl;
        return 0;
    }
    default: {
        cout << "Попробуйте еще" << endl;
        return choise(vocabulary);
    }
    }
}
int main()
{   
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    anglo_russkii vocabulary;
    vocabulary.tree();
    int c, n; string x, s;
    cout << "Выберите способ задания словаря:\n1) В консоли\n2) Из файла" << endl;
    cin >> c;
    if (c == 1) {
        cout << "Сколько слов нужно создать?";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Введите английское слово                    "; cin >> x;
            cout << "Введите перевод английского слова           "; cin >> s;
            pair<string, string> ab;
            ab.first = x;
            ab.second = s;
            vocabulary = (vocabulary += ab);
        }
    }
    else if (c == 2) {

        fstream in("test.txt");
        while (!in.eof()) {
            in >> x >> s;
            pair<string, string> ab;
            ab.first = x;
            ab.second = s;
            vocabulary = (vocabulary += ab);
        }
    }

    choise(vocabulary);
    return 0;
}
