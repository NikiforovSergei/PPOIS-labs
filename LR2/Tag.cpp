#include"HeaderTag.h"
#include <fstream>
#include<iostream>
using namespace std;
Tag::Tag()
{

}
Tag::Tag(string tagName, vector<Attribute>attrib, string value)
{
	if (attrib.size() == 0 || value == "")
	{
		this->name = tagName;
		this->attributes = attrib;
		this->value = value;
	}
	/*if (attrib.size() == 0)
	{
		this->name = tagName;
		this->attributes = attrib;
		this->value = value;
	}*/
	else
	{
		this->name = tagName;
		this->attributes = attrib;
		this->value = '>' + value;
	}

	/*for (int i = 0; i < attrib.size(); i++)
	{
		this->attributes.push_back(att);
	}
	for (auto item : this->attributes)
	{
		cout << item << " ";
	}*/
}
/*void Tag::PrinteTag()
{
	cout << this->name;
	cout << this->value;
	for (auto item : attributes)
	{
		cout << item << " ";
	}

}*/
void Tag::Output()
{
	if (this->name != "" && this->attributes.size() != 0 && this->value != "")
	{
		cout << this->name;

		for (auto item : this->attributes)
		{
			cout << " " << item << " ";
		}
		cout << this->value << this->name.insert(1, 1, '/') + '>' << endl;
	}
	else
	{
		if (this->name != "" && this->attributes.size() == 0 && this->value != "")
		{
			cout << this->name;

			for (auto item : this->attributes)
			{
				cout << " " << item << " ";
			}
			cout << this->value << this->name.insert(1, 1, '/') << endl;
		}
		else
		{
			cout << this->name;

			for (auto item : this->attributes)
			{
				cout << " " << item << " ";
			}
			cout << this->value << endl;
		}
	}
	
	
}
void Tag::OutputClosingTag(int i)
{
	cout << this->name.insert(1, 1, '/') << endl;
}