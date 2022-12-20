#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <fstream>
using namespace std;

void reversestr(string&);
string money(int);

class card
{
public:
	void replenishment(int);
	void replenishment_from_transfer(int);
	void set_password(string);
	void view();
	void withdraw(int);
	void get_for_transfer(int);
	void balance(int);
	bool get_access();
	void info(string);
	void pin();
	void change_pin();
	void setname(const string&, const string&);
private:
	string password = "0000";
	int cash = 0;
	deque<string> history;
	string first;
	string second;
};

void add_money(int, card);