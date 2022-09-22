#pragma once
#include<vector>
#include<fstream>
#include<string>
using namespace std;

/// Класс Alphabet
/// \details Класс Alphabet реализует алфавит
class Alphabet{
private:
	//! Содержит алфавит
	string pattern;
public:
	void setPattern(string&);
	string getPattern();
	/*!
Метод проверят соответствует ли слово алфавиту
\param word Слово
\see std::string word
*/
	bool is_valid(const string& word);
	/*!
Метод проверят соответствует ли правило алфавиту
\param a Левая часть правила
\param b Правая часть правила
*/
	bool is_valid(const string& a, const string& b);

};

/// Класс Tape
/// \details Класс Tape реализует ленту абстрактной машины
class Tape {
	//! объект класса Alphabet
	Alphabet alphabet;
	//! Выполняемое правило
	pair<string, string> action;
	//! алфавит
	string pattern;
	//! Интерпретируемое слово
	string word;
	//! Перечень правил для интерпретации
	vector<pair<string, string>> rules;
public:
	void setAlphabet(string&);
	void setRules(vector<pair<string, string>>&);
	void setWord(string&);
	vector<pair<string, string>>& getRules();
	void setAction(pair<string, string>);
	string getWord();
	/*!
Метод принимает индекс правила и удаляет его из ленты
\param index Индекс правила, которое нужно удалить
\see std::vector<std::pair<std::string, string>> rules
*/
	void delete_rule(int index);
	/*!
Удаляет все правила из ленты
\see std::vector<std::pair<std::string, string>> rules
*/
	void deleteRules();
/*!
Меняет одно из правил
\param[in] index Индекс правила, которое нужно изменить
\param[in] a Левая часть правила
\param[in] b Правая часть правила
\see std::vector<std::pair<std::string, string>> rules
*/
	void changeRule(int index, string& a, string& b);

/*!
Добавление одного правила в конец 
\param a Левая часть правила
\param b Правая часть правила
\see std::vector<std::pair<std::string, string>> rules
*/
	void addRule(string& a, string& b);
	void getInfo(string&);

/*!
Считывает с консоли алфавит, слово и правила
\see std::vector<std::pair<std::string, string>> rules
\see std::string word
\see std::string pattern
*/
	void Read();

	/*!
Считывает из файла алфавит, слово и правила
\param filename Путь к файлу, в котором содержится начальное состояние машины
\see std::vector<std::pair<std::string, string>> rules
\see std::string word
\see std::string pattern
*/
	void operator>>(const string& filename);
/*!
	Выводит в консоль алфавит, слово и правила
	\see std::vector<std::pair<std::string, string>> rules
	\see std::string word
	\see std::string pattern
	*/

	void Write();
	
};

/// Класс Interpretator
/// \details Класс Interpretator реализует выполнение всех правил над словом
class Interpretator  {
private:
	//! Интерпретируемое слово
    string word;
	//! Переменная, которая говорит о том, был ли передан параметр "-log" в консоль
	bool log = false;
	//! Лента абстрактной машины
	Tape tape;
	//! Переменная, обозначающая конец интерпретируемых правил
	bool flag = false;
public:
	/*!
	Конструктор, с помощью которого можно передать интерпретируемое слово при создании объекта интерпретатора
	\param word Слово для интерпретации
	\see std::string word
	*/
	Interpretator(string& word);
	string getWord();
	void setWord(string&);
	/*!
	Метод, выполняющий перестановку в слове
	\param left Подстрока, которую надо заменить в слове
	\param right Подстрока, на которую мы меняет left
	*/
	void rule_executing(string& left, string& right);
	void changeLog(); /// \brief Меняет поле log в случае, если был передан параментр "-log" в консоль
	/*!
	Метод, который перебирает правила для интерпретации в соответствии с правилами нормальных алгорифмов Маркова
	\param rules Перечень выполняемых правил
	\see std::vector<std::pair<std::string, string>> rules

	*/
	void execute(vector<pair<string, string>>& rules);
};

