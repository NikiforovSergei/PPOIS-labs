#include"HeaderDoc.h"
#include<string>
#include<fstream>
#include"HeaderPI.h"
#include<iostream>
#include"HeaderElement.h"
#include"HeaderTag.h"
#include<sstream>
#include"HeaderNode.h"
#include"HeaderTree.h"
using namespace std;
Document::Document()
{

}
void Document::GetELement(ifstream& file)
{
	vector<char>valueArr(0);
	vector<char>nameArr(0);
	vector<Attribute>attrib(0);
	vector<char>subline(0);
	string line;
	vector<char>mas(0);
	Node* parent = NULL;
	Node* prevParent = NULL;
	Tree tree = Tree();
	while (!file.eof())
	{
 		int i = 0;
		int j = 0;
		getline(file, line);
		string delimiter = "[<";
		string subLine = line.substr(0, line.find(delimiter));
		vector<char>mas(line.begin(), line.end());

		if (mas[0] == '<' && mas[1] == '?')
		{
			PI* pi = new PI(line);

			parent = tree.AddToTree(parent, pi);
			continue;
		}

		if (mas[0] == '<' && mas[1] == '!' && mas[2] != '[')
		{
			Comment* comment = new Comment(line);
			tree.AddToTree(parent, comment);
			continue;
		}
		if (subLine == "<![CDATA")
		{
			CDATA* cdata = new CDATA(line);
			tree.AddToTree(parent, cdata);
			continue;
		}
		if (mas[0] == '<')
		{
		
			vector<string>strings1;
			vector<string>strings2;
			string delimiter1 = ">";
			string token = line.substr(0, line.find(delimiter1)) + delimiter1;
			
			if (token.size() != line.size())
			{

				istringstream f1(token);
				string str1;
				while (getline(f1, str1, ' '))
				{
					strings1.push_back(str1);
				}
				string tagName = strings1[0];

				for (i = 1; i < strings1.size(); i++)
				{
					string attr = strings1[i];
					Attribute attribute;
					attribute = Attribute(attr);
					attrib.push_back(attribute);
				}
				istringstream f2(line);
				string str2;
				while (getline(f2, str2, '>'))
				{
					strings2.push_back(str2);
				}

				vector<string>strings3(0);

				string valueAndClosingTag = strings2[1];
				istringstream f3(valueAndClosingTag);
				string str3;
				while (getline(f3, str3, '<'))
				{
					strings3.push_back(str3);
				}


				string valueTag = strings3[0];
			
				Tag* tag = new Tag(tagName, attrib, valueTag);
				tree.AddToTree(parent, tag);
			
			}
			else
			{

				string value = "";
				
				if (mas[1] == '/')
				{
					parent = prevParent;
					continue;
				}
				if (mas[mas.size() - 2] == '/' && mas[mas.size() - 1] == '>')
				{
					Tag* tag = new Tag(line, attrib, value);
					tree.AddToTree(parent, tag);
					
				}
				else
				{
					prevParent = parent;
					Tag* tag = new Tag(line, attrib, value);
					parent = tree.AddToTree(parent, tag);
					
				}
			}
		}
		/*else
		{
			
			tree.AddToTree(parent, &line);
		}*/
		line.clear();
		attrib.clear();
	}

	mas.clear();
	tree.PrintTree();
}
