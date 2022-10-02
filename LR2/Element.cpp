#include "Element.h"

XML::Element::Element(Element *parent, std::string value)
{
	this->parent = parent;
	this->value = value;
}