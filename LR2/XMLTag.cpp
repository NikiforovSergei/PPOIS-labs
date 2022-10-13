#include "XMLTag.h"

XMLEmptyTag::XMLEmptyTag()
{
	name = "";
}

XMLEmptyTag::XMLEmptyTag(string _name) : name(_name)
{
}

string XMLEmptyTag::GetText()
{
	return "";
}

string XMLEmptyTag::GetName()
{
	return this->name;
}

void XMLEmptyTag::SetLeaf(XMLEmptyTag& leaf)
{
}

void XMLEmptyTag::SetText(string str)
{
}

XMLTagWithAttibute::XMLTagWithAttibute() : XMLTag()
{
	attributes = vector<XMLTagAttribute*>{};
}

XMLTagWithAttibute::XMLTagWithAttibute(string _name, string _text, vector<XMLTagAttribute*> _attributes ) : XMLTag(_name, _text), attributes(_attributes)
{
}

XMLTagWithAttibute::XMLTagWithAttibute(string _name, vector<XMLTagAttribute*> _attributes) : XMLTag(_name), attributes(_attributes)
{
}

XMLTagWithAttibute::~XMLTagWithAttibute() 
{
	for (int i = 0; i < attributes.size(); i++)
	{
		delete attributes[i];
	}
}

XMLTag::XMLTag() : XMLEmptyTag()
{
	text = "";
}

XMLTag::XMLTag(string _name, string _text) : XMLEmptyTag(_name), text(_text)
{
}

XMLTag::XMLTag(string _name) : XMLEmptyTag(_name)
{
}

XMLTag::~XMLTag()
{
	for (int i = 0; i < leafs.size(); i++)
	{
		delete leafs[i];
	}
}

string XMLTag::GetText()
{
	return this->text;
}

void XMLTag::SetLeaf(XMLEmptyTag& leaf)
{
	this->leafs.push_back(&leaf);
}

void XMLTag::SetText(string str)
{
	this->text += str;
}

XMLTagWithCDATA::XMLTagWithCDATA() : XMLEmptyTag()
{
	CDATA = nullptr;
}

XMLTagWithCDATA::XMLTagWithCDATA(XMLCDATA& _CDATA) : CDATA(&_CDATA)
{
}

XMLTagWithCDATA::~XMLTagWithCDATA()
{
	delete CDATA;
}
