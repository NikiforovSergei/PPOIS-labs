#pragma once
#include <string>
#include <map>
#include <iostream> 
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*!
	\brief  ласс, работающий с правилами: просмотр, удаление, добавление, проверка по словарю
*/
class Rules
{
protected:
	map<string, string> rule;
	bool check_vocabulary(string vocabulary, string check_word);
	void rule_str_to_rule_map(vector<string>& str_rule, string vocabulary);

public:
	void add_rule(string vocabulary);
	void get_rule();
	void del_rule();
};


/*!
* \brief Ётот класс описывает работу машины алгоритма ћаркова, а также позвол€ет измен€ть значение слова и работать с правилами.
*/
class Marcov_algorithm : public Rules
{
private:
	string word, changed_word = "";
	int verification_counter;

public:
	bool log_on_off = 0;
	string vocabulary;

	Marcov_algorithm(string vocabulary, string word, vector<string> str_rule, bool log_check);
	Marcov_algorithm();

	void change_word_1(bool step);
	void check_terms(bool step, map <string, string>::iterator it);
	void change_word_2(bool step);
	void tape_state_form_stream();
	void get_res();
	void change_word();

};


/*!
* \brief Program menu
*/
class Menu
{
private:
	Marcov_algorithm obj;

public:

	Menu(bool log_check,string path);
	void menu_choose();

};
