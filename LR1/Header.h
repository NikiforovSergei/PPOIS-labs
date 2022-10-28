#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Set
{
private:
	vector <string> set;
	string Sort_str(string str);
	vector <string> Delete_element(string str);
	vector <string> Bulian_metod( vector <string> vec, int num, string s);
	bool Proverka_na_skobki(string str);
	bool Proverka_na_povtorenie(string str);
public:
	void Show();
	void Empti();
	void Mochnost();
	void Bulian();
	vector <string> Delete();
	vector <string> Add();
	friend Set& operator + (Set& a, Set& b);
	friend Set& operator += (Set& a, Set& b);
	friend Set& operator * (Set& a, Set& b);
	friend Set& operator *= (Set& a, Set& b);
	friend Set& operator - (Set& a, Set& b);
	friend Set& operator -= (Set& a, Set& b);
	//string operator [] (int str);
	void operator [] (string str);
};
