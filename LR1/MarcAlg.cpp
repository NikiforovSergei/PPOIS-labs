#include "hfile.h"

Marcov_algorithm::Marcov_algorithm(string vocabulary, string word, vector<string> str_rule, bool log_check) ///\brief tipically construct
{
    this->vocabulary = vocabulary;
    this->word = word;
    this->rule_str_to_rule_map(str_rule, vocabulary);
    this->log_on_off = log_check;
}

Marcov_algorithm::Marcov_algorithm() {} ///\brief construct for declare an object of the given type, but do not assign a value to it



void Marcov_algorithm::change_word_1(bool step) ///\brief creating change_word for changing it, calling change_word_2
{
    changed_word = word;
    this->verification_counter = 0;
    change_word_2(step);
}

void Marcov_algorithm::check_terms(bool step, map <string, string>::iterator it) ///\brief checking for checkbox "-log"  and for a condition if the user has chosen to execute as they go
{
    if (log_on_off)
    {
        cout << it->first << "->" << it->second << endl;
        cout << changed_word << endl;
    }

    if (step == 1)
    {
        cout << "rule: " << it->first << "->" << it->second << endl;
        cout << "\n" << word << ">>>" << changed_word << endl;
        string indicator = "";
        while (indicator != "c")
        {
            cout << "Enter \"c\" for continuation: ";
            cin >> indicator;
        }
    }
}

void Marcov_algorithm::change_word_2(bool step) ///\brief changing a word according to Markov's rules
{
    /*!
    * \details the program is executed recursively, checking that the program does not run out of bounds.
    * \details a substring of the word is replaced by another substring according to the established rules
    */
    if (this->verification_counter >= 100)
    {
        cout << "Счетчик выполнения правил переполнен! Дальнейшее преобразование невозможно!!!" << endl;
        verification_counter = 0;
        return;

    }
    for (map <string, string>::iterator it = rule.begin(); it != rule.end(); it++)
    {
        if (it->first == "")
        {
            changed_word += it->second;
            check_terms(step, it);
            continue;
        }
        int sub_word = changed_word.find(it->first);
        if (sub_word != -1)
        {
            changed_word.replace(sub_word, it->first.length(), it->second);
            check_terms(step, it);

            this->verification_counter++;
            change_word_2(step);
            return;
        }
        else continue;
    }
}

void Marcov_algorithm::tape_state_form_stream() ///\brief tape status output (output all possible information)
{
    cout << "\nСлово: " << vocabulary << ";" << endl;
    cout << "Правила: " << endl;
    int a = 1;
    for (map <string, string>::iterator it = rule.begin(); it != rule.end(); it++)
    {
        cout << a << ". " << it->first << "->" << it->second << ";" << endl;
        a++;
    }
    cout << "Слово: " << word << ";" << endl;
    cout << "Преобразованное слово: " << changed_word << ";" << endl;

}

void Marcov_algorithm::get_res()
{
    cout << word << ">>>" << changed_word << endl;
}

void Marcov_algorithm::change_word()///\brief checks a new word against a dictionary    
{
    cout << "\nВведите новое слово: ";
    string new_word;
    cin >> new_word;
    if (this->check_vocabulary(new_word, vocabulary))
    {
        word = new_word;
    }
}