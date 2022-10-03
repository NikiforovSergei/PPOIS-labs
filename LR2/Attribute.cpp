#include "Attribute.h"

#include <string>

XML::Attribute::Attribute(std::string name, std::string value)
{
	this->name = name;
	this->value = value;
}
