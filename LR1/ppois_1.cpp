#include <fstream>
#include <locale>
#include <Windows.h>
#include <string>
#include "dict.h"
using namespace std;

int main() 
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");

    Dictionary* dict = new Dictionary();

    while (1) {
        
        cout << "1. Добавить слово и его перевод"<< endl;
        cout << "2. Удалить слово из словоря" << endl;
        cout << "3. Перевод" << endl;
        cout << "4. Замена перевода английского слова" << endl;
        cout << "5. Количество слов в словаре" << endl;
        cout << "6. Загрузка словаря из файла" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие:" << endl;
        int choice; cin >> choice;
        if (!choice)  break;
        switch (choice) {
        case 1:
            while (1) 
            {   system("cls");           
                string eng_word, rus_word;
                cout << "Введите слово на английском: ";
                cin >> eng_word;
                cout << "Введите русский перевод слова \" "<< eng_word<< "\" ";
                cin >> rus_word;
                *dict += make_pair(eng_word, rus_word);
              
                cout << "Хотите ли вы добавить еще? (1 - да, 0 - нет) ";
                int choise2;  cin >> choise2;
                if (!choise2) break;
            }
            break;
        case 2:
            while (1) {
                system("cls");
                cout << "Введите удаляемое слово: ";
                string del_word; cin >> del_word;
                *dict -= del_word;
                cout << "Хотите ли вы удалить еще? (1 - да, 0 - нет) ";
                int choise2;  cin >> choise2;
                if (!choise2) break;
            }
            break;
        case 3:
            while (1) 
            {           
                system("cls");
                string tr_word;
                cout << "Введите слово, которое вы хотите перевести: ";
                cin >> tr_word;
                cout << "Перевод: " << (*dict)[tr_word] << endl;
                cout << "Хотите ли вы перевести что-то еще? (1 - да, 0 - нет) ";
                int choise2;  cin >> choise2;
                if (!choise2) break; 
            }
            break;

        case 4:
           while (1) 
           {
                system("cls");
                string change_word, new_word;
                cout << "Введите слово, перевод которого нужно измменить: ";
                cin >> change_word;

                cout << "Нынешний перевод: " << (*dict)[change_word] << endl<<" Введите новый перевод : ";
                cin >> new_word;
                (*dict)[make_pair(change_word, new_word)];
               
                cout << "Хотите ли вы измениь еще какой-либо перевод? (1 - да, 0 - нет) ";
                int choise2;  cin >> choise2;
                if (!choise2) break;
            }
            break;

        case 5:
                system("cls");
                cout << "Количество слов в словаре: " << (*dict).get_num_of_w() << endl;
            break;


        case 6:
            while (1) {
                system("cls");
                string file_name = "dictionary.txt";
                ifstream inp_file;
                inp_file.open(file_name);

                if (inp_file.is_open()) {
                    string inp_line;
                    while (!inp_file.eof()) {
                        getline(inp_file, inp_line);
                        string inp_eng = inp_line.substr(0, inp_line.find(' '));
                        string inp_rus = inp_line.substr(inp_line.find(' ') + 1, inp_line.find('\n'));
                        *dict += make_pair(inp_eng, inp_rus);
                    }
                    inp_file.close();
                    cout << "Словарь загружен" << endl;
                }
                else cout << "Не удалось открыть файл" << endl;

                cout << "Введите \"0\" для продолжения: ";
                int choise2;  cin >> choise2;
                if (!choise2) break;
            }
            break;  
        }
    }
}