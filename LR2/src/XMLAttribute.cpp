#include "XMLAttribute.hpp"

XMLAttribute::XMLAttribute() = default;

XMLAttribute::XMLAttribute(string name) { this->name = move(name); }

string XMLAttribute::get_name() { return name; }

string XMLAttribute::get_value() { return value; }

void XMLAttribute::set_value(string value) { this->value = move(value); }

string XMLAttribute::to_string() { return name + "=\"" + value + "\""; }
