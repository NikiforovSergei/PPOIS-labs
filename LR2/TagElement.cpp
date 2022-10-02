#include "TagElement.h"

XML::TagElement::TagElement(std::string value, std::vector<Attribute> attributes, TagElement *parent)
	:Element(parent, value)
{
	this->attributes = attributes;
}

std::string* XML::TagElement::GetValueWStringArray() const
{
	std::string demoTag = "<" + value;
	if (this->children.size() > 0)
	{
		std::string closingTag = "</" + value + ">";
		for (int i = 0; i < attributes.size(); i++)
		{
			demoTag += " " + attributes[i].name + "=" + attributes[i].value;
		}
		
		demoTag += ">";
		return new std::string[2]{ demoTag, closingTag };
	}
	else
	{
		return new std::string[1]{ demoTag + "/>"};
	}
}