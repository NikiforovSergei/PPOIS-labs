#include "TextElement.h"

XML::TextElement::TextElement(std::string value, TagElement *parent)
	:Element(parent, value)
{
}

std::string* XML::TextElement::GetValueWStringArray() const
{
	return new std::string[1]{ value };
}