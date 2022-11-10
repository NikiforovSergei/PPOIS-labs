#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include "Header.h"

using namespace std;

void MySet::input(string inputString)
{
	mySet.clear();
	MySet helpSet;

	inputString = inputString.substr(1, inputString.size() - 2);
	//cout << inputString << endl;

	vector <string> nests;
	MySet temp;

	char a;
	int openBracket = 0;

	int startCut = 0;
	int endCut = 0;

	for (size_t i = 0; i <=inputString.size(); i++)
	{
		a = inputString[i];
		if (a == '{')
		{
			startCut = i;
			openBracket = 1;

			for (size_t j = startCut + 1; j <= inputString.size(); j++)
			{
				char temp = inputString[j];
				if (temp == '{')
					openBracket++;
				if (temp == '}')
					openBracket--;
				if (openBracket == 0)
				{
					endCut = j - startCut + 1;
					i--;
					break;
				}
			}
			nests.push_back(inputString.substr(startCut, endCut));

			inputString.erase(startCut - 1, endCut + 1);
		}
	}

	for (int i = 0; i < nests.size(); i++)
	{
		helpSet.input(nests[i]);
		temp.add(helpSet.returnStr());
	}

	for (auto i : temp.mySet)
	{
		mySet.insert(i);
	}
	//cout << inputString << endl;

	string delimiter = ",";

	size_t pos = 0;
	string token;
	while ((pos = inputString.find(delimiter)) != string::npos) {
		token = inputString.substr(0, pos);
		mySet.insert(token);
		inputString.erase(0, pos + delimiter.length());
	}
	mySet.insert(inputString);
}

string MySet::returnStr()
{
	string result = "{";

	for (auto it : mySet)
		result += it + ",";

	result = result.substr(0, result.size() - 1);
	return result + "}";
}

void MySet::display() 
{
	string result = "{";

	for (auto it : mySet)
		result += it + ",";

	result = result.substr(0, result.size() - 1);
	cout << result + "}" << endl;
}

bool MySet::empty() 
{
	return mySet.empty();
}

void MySet::add(string element) 
{
	mySet.insert(element);
}

void MySet::erase(string element)
{
	mySet.erase(element);
}

void MySet::clear()
{
	mySet.clear();
}

int MySet::capacity() 
{
	return mySet.size();
}

void MySet::find(string element)
{
	auto result = mySet.find(element);
	if (result != mySet.end()) 
		cout << "Ёлемент \"" << *result << "\" был найден" << endl;
	else 
		cout << "Ёлемент \""<< element << "\" не был найден" << endl;
}

//MySet MySet::unite(MySet secondSet)
//{
//	MySet result;
//	for (auto i = mySet.begin(); i != mySet.end(); ++i)
//	{
//		result.add(*i);
//		for (auto j = secondSet.mySet.begin(); j != secondSet.mySet.end(); ++j)
//		{
//			if (*i != *j)
//				result.add(*j);
//		}
//	}
//	//result.display();
//	return result;
//}

MySet MySet::operator +(MySet secondSet) //unite
{
	MySet result;
	for (auto i = mySet.begin(); i != mySet.end(); ++i)
	{
		result.add(*i);
		for (auto j = secondSet.mySet.begin(); j != secondSet.mySet.end(); ++j)
		{
			if (*i != *j)
				result.add(*j);
		}
	}
	//result.display();
	return result;
}

//MySet MySet::intersection(MySet secondSet)
//{
//	MySet result;
//	for (auto i = mySet.begin(); i != mySet.end(); ++i)
//	{
//		for (auto j = secondSet.mySet.begin(); j != secondSet.mySet.end(); ++j)
//		{
//			if (*i == *j)
//				result.add(*j);
//		}
//	}
//	//result.display();
//	return result;
//}

MySet MySet::operator *(MySet secondSet) //intersection
{
	MySet result;
	for (auto i = mySet.begin(); i != mySet.end(); ++i)
	{
		for (auto j = secondSet.mySet.begin(); j != secondSet.mySet.end(); ++j)
		{
			if (*i == *j)
				result.add(*j);
		}
	}
	//result.display();
	return result;
}

//MySet MySet::difference(MySet secondSet)
//{
//	MySet result;
//	for (auto i = mySet.begin(); i != mySet.end(); ++i)
//	{
//		result.add(*i);
//		for (auto j = mySet.begin(); j != mySet.end(); ++j)
//		{
//			if (*i == *j)
//				result.erase(*j);
//		}
//	}
//	//result.display();
//	return result;
//}

MySet MySet::operator -(MySet secondSet) //difference
{
	MySet result;
	for (auto i = mySet.begin(); i != mySet.end(); ++i)
	{
		result.add(*i);
		for (auto j = secondSet.mySet.begin(); j != secondSet.mySet.end(); ++j)
		{
			if (*i == *j)
				result.erase(*j);
		}
	}
	//result.display();
	return result;
}

MySet MySet::boolean()
{
	MySet result;
	vector <string> res;
	vector <string> elements;
 
	for (auto i : mySet)
		res.push_back(i);

	string temp;

	int size = res.size();
	int p = (1 << size);
	for (int i = 0; i < p; i++)
	{
		temp = "{";
		for (int j = 0; j < size; j++) 
		{
			if ((i >> j) & 1) temp +=  res[j] + ", ";
		}
		temp += "}";
		elements.push_back(temp);
	}

	for (int i = 1; i < elements.size(); i++)
		elements[i].erase(elements[i].size() - 3, 2);

	for (auto i : elements)
		result.add(i);

	//for (auto i : elements)
	//	cout << i << endl;

	//result.display();
	return result;
}