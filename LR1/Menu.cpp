#include"PPOIS_1.h"

Menu::Menu(bool log_check) ///\brief Menu class constructor, which initially reads information from a file
{
    string vocabulary, word;
    vector<string> str_rule;
    ifstream a("D:\\univer\\PPOIS\\PPOIS_1\\PPOIS_1\\rules.txt");
    if (a.is_open())
    {
        a >> vocabulary;
        a >> word;
        while (!a.eof())
        {
            string b;
            a >> b;
            str_rule.push_back(b);
        }
        a.close();
        Marcov_algorithm my_obj(vocabulary, word, str_rule, log_check);
        this->obj = my_obj;
    }
    else cout << "file_error!";

}

void Menu::menu_choose() ///\brief action choise 
///\details case 2 describes the menu for working with rules
///\details case 4 describes the menu for choosing how to perform an operator
{
    while (true)
    {
        cout << "\nChoose action: " << endl;
        cout << "1. loading tape state from stream;\n2. rules;\n3. change word;\n4. Program interpretation; \n5. Exit: ";
        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:                             
            obj.tape_state_form_stream();
            break;
        case 2:
            cout << "\n1.Viewing Rules;\n2. Adding rules;\n3. deleting rules: ";
            int choose;
            cin >> choose;
            switch (choose)
            {
            case 1:
                obj.get_rule();
                break;
            case 2:
                obj.add_rule(obj.vocabulary);
                break;
            case 3:
                obj.del_rule();
                break;
            }
            break;
        case 3:
            obj.change_word();
            break;
        case 4:
            if (obj.log_on_off == 0)
            {
                cout << "\nHow to perform the operation?: " << endl << "1. all at once;\n2. step by step: ";
                int choose_2;
                cin >> choose_2;
                switch (choose_2)
                {
                case 1:
                    obj.change_word_1(0);
                    obj.get_res();
                    break;
                case 2:
                    obj.change_word_1(1);
                    break;
                }
            }
            else
            {
                obj.change_word_1(0);
            }

            break;

        case 5:
            return;
        }
    }
}