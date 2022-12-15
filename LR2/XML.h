#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class Tag
{
private:
	string name;
	vector<string> attributes;

public:
	string getName()
	{
		return this->name;
	}
	vector<string> getAttr()
	{
		return this->attributes;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setAttr(string attribute)
	{
		(this->attributes).push_back(attribute);
	}
};


class Element: public Tag
{
private:
	string content = "";
	string CDATA = "";

public:
	string getContent()
	{
		return this->content;
	}
	string getCDATA()
	{
		return this->CDATA;
	}
	void setContent(string content)
	{
		this->content = content;
	}
	void setCDATA(string CDATA)
	{
		this->CDATA = CDATA;
	}
};

struct Node
{
	Element temp_Element;
	string comment = "";
	vector<Node> infant_Nodes;
	Node* parent_Element = NULL;
};

class XML
{
private:
	string xml_Doc;
	vector<Node> nodes;
	string xml_Instr;

public:
	string getXmlDoc()
	{
		return this->xml_Doc;
	}
	void setXmlDoc(string xml_Doc)
	{
		this->xml_Doc = xml_Doc;
	}
	vector<Node> getXmlNodes()
	{
		return this->nodes;
	}
	void setXmlNodes(Node node) 
	{
		(this->nodes).push_back(node);
	}
	string getXmlInstr()
	{
		return this->xml_Instr;
	}
	void setXmlInstr(string xml_Instr)
	{
		this->xml_Instr = xml_Instr;
	}
	XML readXmlFromFile(string path);
};

ostream& operator<<(ostream& os, XML& Xml);
ostream& operator <<(ostream& os, vector<string> temp_attr);
void coutElement(ostream& os, Node temp_element);

class Test {
	Test();
	~Test();
};