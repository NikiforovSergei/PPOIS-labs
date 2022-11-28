#include "hfile.h"


///

bool Rules::check_vocabulary(string vocabulary, string check_word) ///\brief checks the new rule against a dictionary
{
    for (int i = 0; i < check_word.length(); i++)
    {
        if (vocabulary.find(check_word[i]) == -1)
        {
            cout << "\nСимвола \"" << check_word[i] << "\" нет в словаре" << endl;
            return 0;
        }
    }
    return 1;
}

void Rules::rule_str_to_rule_map(vector<string>& str_rule, string vocabulary) ///\brief translates a string into a rule (map)
{
    for (auto it = str_rule.begin(); it != str_rule.end(); it++)
    {
        string str = *it;
        int place = str.find("->");
        if (place == -1)
        {
            throw "Неправильный ввод!";
        }
        pair<string, string> new_pair = make_pair(str.substr(0, place), str.substr(place + 2, str.length() - place - 2));

        if (rule.find(new_pair.first) == rule.end() && check_vocabulary(vocabulary, new_pair.first) && check_vocabulary(vocabulary, new_pair.second))
        {
            rule.insert(new_pair);
        }
        else
        {
            cout << "Такое условие уже имеется" << endl;
            str_rule.pop_back();
            break;
        }
    }
}

void Rules::add_rule(string vocabulary) ///\brief add new rule
{
    vector<string> str_rule;
    while (true)
    {

        cout << "Введите новое правило \"ab->bc\", где ab - заменяемое, bc - замена: ";
        string str;
        cin >> str;
        str_rule.push_back(str);
        try
        {
            this->rule_str_to_rule_map(str_rule, vocabulary);
        }
        catch (...)
        {
            cout << "Error!" << endl;
        }

        cout << "Enter rule one more?: 1. Yes, 2. No: ";
        int choose;
        cin >> choose;
        if (choose == 1) continue;
        else break;
    }
}

void Rules::get_rule() ///\brief output of all rules
{
    for (auto id = rule.begin(); id != rule.end(); id++)
    {
        cout << id->first << "->" << id->second << endl;
    }
}

void Rules::del_rule() ///\brief delete rule
{
    cout << "Каое правило удалить?: " << endl;
    int a = 0;
    for (auto i = rule.begin(); i != rule.end(); i++)
    {
        cout << a << ". " << i->first << "->" << i->second << ";" << endl;
        a++;
    }

    cin >> a;
    map<string, string>::iterator choose = rule.begin();
    advance(choose, a);
    rule.erase(choose);
}