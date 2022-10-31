#pragma once
#include <string>
#include <vector>
#define IN_MAX_LEN_TEXT 50	// максимальный размер исходного кода 
#define IN_CODE_ENDL '\n'			// символ конца строки

// таблица проверки входной информации,	индекс = код (Windows-1251) символа
// значение IN::F - запрещенный символ, IN::T - разрешенный символ, IN::I - игнорирвоать (не вводить)
// если  0 <= значение < 256, то вводится данное значение
#define IN_CODE_TABLE {\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::T,	El::T, El::F, El::T, El::F,	El::F, El::F, El::F,\
	El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::F, El::F, El::T, El::T, El::T, El::F,\
	El::F,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T,\
	El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::F, El::F,	El::F, El::F, El::T,\
	El::F,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T,\
	El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::T,	El::T, El::T, El::T, El::F,	El::T, El::F, El::F,\
																												    \
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::T, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::T, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::T,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
	El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F, El::F,	El::F, El::F, El::F,\
					}


struct El
{
	enum { T = 1024, F = 2048 };			// T - допустимый символ, F - недопустимый
	int size;								// размер исходного кода
	int lines;								// количество строк		
	unsigned char* text;					// исходный код (Windows-1251)
	int code[256] = IN_CODE_TABLE;			// таблица проверки: T, F, I, новое значение
};

class Elements
{
public:
	El getin(char * element, int size);
};

class Set : public Elements
{
public:
	Set(std::vector<char> &temp) {
		this->set_elements = std::move(temp);
	}
	Set() {
		std::vector<char> temp;
		this->set_elements = std::move(temp);
	}
	void add_elements(char element);
	void show_elements();
	void add_set(Set set);
	std::vector<char> get_char_vector();
	std::vector<Set> get_set_vector();
	friend const bool operator == (Set s1, Set s2);
	void parse(std::string& context);
	static void split(std::string str, std::string& fir_set, std::string& sec_set, std::string& sign);
	static void processing(Set& set1, Set& set2, std::string& sign);
	static void check_boolean(std::string& str, bool& a);
	std::vector<char> set_elements;
	std::vector<Set> set;
private:
};

bool const operator == (Set s1, Set s2);

class Name : public Elements
{
public:
	Set set;
	void check_name(std::string buf_name);
	std::string name;
};

