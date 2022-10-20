#pragma once
#include <vector>
#include <string>


namespace xml
{
	class Attribute
	{	
		std::string name;
		std::string value;
	public:
		std::string getName() const;
		std::string getValue() const;
		Attribute(std::string& name, std::string& value);
		
	};

	struct Element
	{   
		std::string value;
		std::vector<Element*> children;
		Element* parent;
		std::string content = "";
		Element(Element* parent, std::string& value);
		virtual std::string getText() const = 0;
		virtual std::vector <Attribute> getAttributes() const = 0;

		
	
	};

	class Tag : public Element
	{
		std::vector <Attribute> attributes;
	public:
		Tag(std::string& value, std::vector <Attribute>& attributes, Tag* parent);
		std::vector <Attribute> getAttributes() const override;
		std::string getText() const override;
	};

	class Text : public Element
	{
		std::vector <Attribute> attributes;
	public:
		Text(std::string& value, Tag* parent, std::string& content);
		std::vector <Attribute> getAttributes() const;
		std::string getText() const override;
	};
}
