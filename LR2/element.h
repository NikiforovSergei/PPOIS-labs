#pragma once
#include <vector>
#include <string>

using namespace std;

namespace xml
{
	class Attribute
	{	
		string name;
		string value;
	public:
		string getName() const;
		string getValue() const;
		Attribute(string& name, string& value);
	};

	struct Element
	{   
		string value;
		vector<Element*> children;
		Element* parent;
		string content = "";
		Element(Element* parent, string& value);
		virtual string getText() const = 0;
		virtual vector <Attribute> getAttributes() const = 0;
	};

	class Tag : public Element
	{
		vector <Attribute> attributes;
	public:
		Tag(string& value, vector <Attribute>& attributes, Tag* parent);
		vector <Attribute> getAttributes() const override;
		string getText() const override;
	};

	class Text : public Element
	{
		vector <Attribute> attributes;
	public:
		Text(string& value, Tag* parent, string& content);
		vector <Attribute> getAttributes() const;
		string getText() const override;
	};
}
