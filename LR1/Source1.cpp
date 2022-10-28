#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Header.h"

using namespace std;

void Set::Show()
{
	cout << "{ ";
	for (int i = 0; i < set.size(); i++)
	{
		cout << set[i];
		if (i != set.size() - 1)
			cout << ", ";
	}
	cout << " }";
}

vector <string> Set::Add()
{
	string str;
	cout << "Введите новый элемент --> ";
	cin >> str;
	if (str[0] == '{')
	{
		str = Sort_str(str);
		if (Proverka_na_skobki(str))
			if (Proverka_na_povtorenie(str))
				set.push_back(str);
			else
				cout << "Данный элемент уже существует!\n";
	}
	else if (Proverka_na_povtorenie(str))
		set.push_back(str);
	return set;
}

string Set::Sort_str(string str)
{
	vector <string> help;
	string helpstr;
	string finelstr;
	int sk = 0;
	if (str[0] == '{')
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '{')
				sk++;
			if (str[i + 1] != '{')
				break;
		}
		for (int i = sk; i < str.length() - sk; i++)
		{
			if (str[i] != ',')
				helpstr += str[i];
			else
			{
				if (helpstr[0] == '{')
				{
					helpstr += ',';
					continue;
				}
				help.push_back(helpstr);
				helpstr.clear();
			}
		}
		help.push_back(helpstr);
		sort(help.begin(), help.end());
		for (int i = 0; i < sk; i++)
			finelstr += '{';
		for (int i = 0; i < help.size(); i++)
		{
			finelstr += help[i];
			if (i != help.size() - 1)
				finelstr += ',';
		}
		for (int i = 0; i < sk; i++)
			finelstr += '}';
	}
	return finelstr;
}

bool Set::Proverka_na_povtorenie(string str)
{
	for (int i = 0; i < set.size(); i++)
	{
		if (str == set[i])
		{
			return false;
		}
	}
	return true;
}

bool Set::Proverka_na_skobki(string str)
{
	int f = 0, l = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '{')
			f++;
		if (str[i] == '}')
			l++;
	}
	if (f != l)
	{
		cout << "Во время ввода допущена ошибка!\n";
		return false;
	}
	return true;
}

void Set::Empti()
{
	if (set.empty())
		cout << "Множество пустое.\n";
	else
		cout << "Множество не пустое\n";
}

vector <string> Set::Delete()
{
	system("cls");
	string str;
	cout << "Введите элемент для удаления.\n";
	cin >> str;
	if (str[0] == '{')
	{
		str = Sort_str(str);
		if (Proverka_na_skobki(str))
			if (!Proverka_na_povtorenie(str))
				set = Delete_element(str);
			else
				cout << "Такогo элемента не существует!\n";
	}
	else
	{
		if (!Proverka_na_povtorenie(str))
			set = Delete_element(str);
		else
			cout << "Такогo элемента не существует!\n";
	}
	return set;
}

vector <string> Set::Delete_element(string str)
{
	int delete_pos = 0;
	for (int i = 0; i < set.size(); i++)
	{
		if (str == set[i])
		{
			delete_pos = i;
			break;
		}
	}
	set.erase(set.begin() + delete_pos);
	return set;
}

void Set::Mochnost()
{
	cout << "Мощность множества === " << set.size() << "\n";
}
//Объединение
Set& operator + (Set& a,Set& b)
{
	Set c;
	int count = 0;
	for (int i = 0; i < a.set.size(); i++)
		c.set.push_back(a.set[i]);
	for (int i = 0; i < b.set.size(); i++)
	{
		for (int j = 0; j < a.set.size(); j++)
		{
			if (b.set[i] == a.set[j])
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			c.set.push_back(b.set[i]);
		}
		count = 0;
	}
	sort(c.set.begin(), c.set.end());
	b = c;
	return b;
}

Set& operator += (Set& a, Set& b)
{
	Set c;
	int count = 0;
	for (int i = 0; i < a.set.size(); i++)
		c.set.push_back(a.set[i]);
	for (int i = 0; i < b.set.size(); i++)
	{
		for (int j = 0; j < a.set.size(); j++)
		{
			if (b.set[i] == a.set[j])
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			c.set.push_back(b.set[i]);
		}
		count = 0;
	}
	sort(c.set.begin(), c.set.end());
	a = c;
	return a;
}
//Пересечение
Set& operator * (Set& a, Set& b)
{
	Set c;
	for (int i = 0; i < a.set.size(); i++)
	{
		for (int j = 0; j < b.set.size(); j++)
		{
			if (a.set[i] == b.set[j])
			{
				c.set.push_back(a.set[i]);
			}
		}
	}
	sort(c.set.begin(), c.set.end());
	b = c;
	return b;
}

Set& operator *= (Set& a, Set& b)
{
	Set c;
	for (int i = 0; i < a.set.size(); i++)
	{
		for (int j = 0; j < b.set.size(); j++)
		{
			if (a.set[i] == b.set[j])
			{
				c.set.push_back(a.set[i]);
			}
		}
	}
	sort(c.set.begin(), c.set.end());
	a = c;
	return a;
}
//Разность
Set& operator - (Set& a, Set& b)
{
	Set c;
	int count = 0;
	for (int i = 0; i < a.set.size(); i++)
	{
		for (int j = 0; j < b.set.size(); j++)
		{
			if (a.set[i] == b.set[j])
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			c.set.push_back(a.set[i]);
		}
		count = 0;
	}
	sort(c.set.begin(), c.set.end());
	b = c;
	return b;
}

Set& operator -= (Set& a, Set& b)
{
	Set c;
	int count = 0;
	for (int i = 0; i < a.set.size(); i++)
	{
		for (int j = 0; j < b.set.size(); j++)
		{
			if (a.set[i] == b.set[j])
			{
				count = 1;
			}
		}
		if (count == 0)
		{
			c.set.push_back(a.set[i]);
		}
		count = 0;
	}
	sort(c.set.begin(), c.set.end());
	a = c;
	return a;
}

//string Set::operator [] (int str)
//{
//	return set[str];
//}

void Set::operator [] (string str)
{
	int q = 0;
	for (int i = 0; i < set.size(); i++)
		if (str == set[i])
		{
			cout << "Существует!";
			q = 1;
			break;
		}
		if(q==0)
			cout << "Не существует";
}

void Set::Bulian()
{
	Set a;
	a.set = Set::Bulian_metod(a.set, 0, "");
	sort(a.set.begin(), a.set.end());
	set = a.set;
}

vector <string> Set::Bulian_metod(vector <string> vec, int num, string s)
{
	if (num == set.size())
	{
		vec.push_back(s);
		return vec;
	}
	vec = Set::Bulian_metod(vec, num + 1, s);
	s = s + set[num] + ' ';
	vec = Set::Bulian_metod(vec, num + 1, s);
	return vec;
}