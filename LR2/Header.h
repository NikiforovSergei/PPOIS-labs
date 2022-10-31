#include <iostream>
#include <string>
#include <deque>
#include <fstream>
using namespace std;

void reversestr(string&);
string itos(int);

class balance
{
public:
	void add(int);
	void add_from_transfer(int);
	void setpass(string);
	void view();
	void get(int);
	void get_for_transfer(int);
	void setcash(int);
	bool get_access();
	void get_information(string);
	void pin();
	void change_pin();
	void setname(const string&, const string&);
private:
	string pass = "0000";
	int cash = 0;
	deque<string> history;
	string first_name;
	string second_name;
};

void add_money(int, balance);