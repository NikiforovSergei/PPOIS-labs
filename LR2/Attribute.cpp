#include"HeaderAttribute.h"
#include<fstream>
#include<iostream>
using namespace std;
Attribute::Attribute()
{

}
Attribute::Attribute(string str)
{
	int i = 0;
	//string delimiter = "=";
	//char simbol = str.find(delimiter);
	vector<char>arr(str.begin(), str.end());
	vector<char>nameArr(0);
	vector<char>valueArr(0);
	while (arr[i] != '=')
	{
		nameArr.push_back(arr[i]);
		i++;
	}
	string name(nameArr.begin(), nameArr.end());
	this->name = name;
	while (arr[i] != '>')
	{
		valueArr.push_back(arr[i]);
		i++;
	}
	string value(valueArr.begin(), valueArr.end());
	this->value = value;
	/*string name;
	string delimiter = "=";
	size_t pos = 0;
	while ((pos = str.find(delimiter)) != string::npos)
	{
		name = str.substr(0, pos);
		this->name = name;
		str.erase(0, pos + delimiter.length());
	}*/
	
}
ostream& operator<< (ostream& os, Attribute& attribute)
{
	return os << attribute.name << attribute.value;
}
void Attribute::Output()
{
	cout << this->name << "=" << this->value;
}
