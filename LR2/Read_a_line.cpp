#include "Header.h"
void Read_a_line::read_line()
{
    Set set;
    Sets_and_operations setsAndOperations;
    Saved_Set save_my_set;
    save_my_set.named_sets;
    while (true)
    {
        bool indicator = false; // выводим ли ответ
        string my_line;
        cout << endl;

        getline(cin, my_line);

        if (my_line.find("[") != -1) //проверка, вызывает ли пользователь подмножество
        {
            cout << endl;
            set.get_info(subset(my_line, save_my_set));
            continue;
        }

        if (my_line.find("size") != -1)  // Проверяем хочет ли пользователь узнать размер множества
        {

            size(my_line, save_my_set);
            continue;
        }

        for (int i = 0; i < my_line.length(); i++)
        {
            if (isalpha(my_line[i]) && isupper(my_line[i])) //проверка на работу с названным множеством
            {
                save_my_set.distr(my_line); // что хотим сделать с названным множеством
                indicator = true; // тк уже вывели
                break;
            }
        }

        if (!indicator)
        {
              set.get_info(setsAndOperations.solution(my_line));
        }

    }
}
