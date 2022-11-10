#pragma once
#include <set>
#include <string>

using namespace std;

class MySet
{
public:
	/// <summary>
	/// A set that contains added elements
	/// </summary>
	set <string> mySet;

	/// <summary>
	/// Set input from a string
	/// </summary>
	/// <param name=""></param>
	void input(string);

	string returnStr();

	/// <summary>
	/// Set output
	/// </summary>
	void display();

	/// <summary>
	/// Checking for an empty set
	/// </summary>
	/// <returns></returns>
	bool empty();

	/// <summary>
	/// Adding an element
	/// </summary>
	/// <param name=""></param>
	void add(string);

	/// <summary>
	/// Removing an element
	/// </summary>
	/// <param name=""></param>
	void erase(string);

	/// <summary>
	/// Cleaning up the set
	/// </summary>
	void clear();

	/// <summary>
	/// Capasity of a set
	/// </summary>
	/// <returns></returns>
	int capacity();

	/// <summary>
	/// Finding an element in a set
	/// </summary>
	/// <param name=""></param>
	void find(string);
	//MySet unite(MySet);

	/// <summary>
	/// Set unite
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	MySet operator +(MySet);
	//MySet intersection(MySet);

	/// <summary>
	/// Set intersection
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	MySet operator *(MySet);
	//MySet difference(MySet);

	/// <summary>
	/// Set difference
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	MySet operator -(MySet);

	/// <summary>
	/// Boolean set
	/// </summary>
	/// <returns></returns>
	MySet boolean();
};
