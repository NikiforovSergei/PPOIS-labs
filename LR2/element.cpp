#include "element.h"
xml::Element::Element(Element* parent, std::string& value)
{
	this->parent = parent;
	this->value = value;
}
xml::Attribute::Attribute(std::string& name, std::string& value)
{
	this->name = name;
	this->value = value;
}

xml::Tag::Tag(std::string& value, std::vector<Attribute>& attributes, Tag* parent) : Element(parent, value){
	this->attributes = attributes;
}

xml::Text::Text(std::string& value, Tag* parent,std::string& content) : Element(parent, value) {
	this->content = content;
}
std::vector<xml::Attribute>  xml::Tag::getAttributes() const {
	return attributes;
}
std::vector<xml::Attribute>  xml::Text::getAttributes() const {
	return attributes;
}
std::string xml::Text::getText() const {
	return value;
}
std::string xml::Tag::getText() const {
	std::string txt = "";
	for (auto i : children) {
		txt += i->content;
	}
	return txt;
}
std::string xml::Attribute::getName() const {
	return name;
}
std::string xml::Attribute::getValue() const {
	return value;
}