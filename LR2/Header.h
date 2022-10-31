#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

class Set
{
private:
	Set* add_new_set_subset(Set* a);
	bool compare_subset(Set* Union, Set* b);
	Set* sum_private(Set* a, Set* b);
public:
	vector<string> elements;
	vector<Set*> subsets;
	void get_info(Set* check);
	Set* sum(Set* a, Set* b);
	Set* composition(Set* a, Set* b);
	Set* simmetric_differences(Set* a, Set* b);
	//int size(Set* a);

};



class Sets_and_operations: public Set
{
private:

	vector<Set*> sets;
	vector<string> operations;
	
	Set* find_Set(int& i, string line);

public:
	Set* solution(string line);
	Set* create_set(string set_str);


	
};

class Saved_Set : public Sets_and_operations
{
public:
	map<char, Set*> named_sets;
	void save_sets(string line);
	void distr(string my_str);
	Set* operation_with_named_sets(string my_str);
	void save_sets_work_with_named_sets(string my_str);
};


class Another_operations	 : public Sets_and_operations
{
private:
	int size_for_set(Set* a);
public:
	void size(string str, Saved_Set a);
	Set* subset(string str, Saved_Set a);
};

class Read_a_line : public Set, public Sets_and_operations, public Saved_Set, public Another_operations
{
private:
	void save_sets(string line);
public:
	map<string, Set*> named_sets;
	void read_line();


};