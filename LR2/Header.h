#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class set
{
public:
	void print(set*);
	set* solve(string);
	set* MakeSet(string);
	set* Union(set*, set*);
	set* Intersection(set*, set*);
	set* Difference(set*, set*);
	bool compare(set*, set*);
	void FindSubsets(string);
protected:
	vector<string> elements;
	vector<set*> subsets;
};

class NamedSet : public set
{
public:
	void SaveSet(string, string&);
	set* solve(string, string&);
	void NamedSolve(string, string&);
private:
	map<char, set*> NamedSets;
};

class line : public set, public NamedSet
{
public:
	void read();
};