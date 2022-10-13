#include <fstream>
#include <iostream>

#include "XMLElement.hpp"

XMLElement::XMLElement(string name, XMLElement *parent) {
  this->parent = parent;
  this->next_sibling = nullptr;
  this->first_child = nullptr;
  this->name = move(name);
}

void XMLElement::set_attribute_value(const string &attributeName,
                                     const string &attributeValue) {
  for (XMLAttribute xmlAttribute : attributes) {
    if (xmlAttribute.get_name() == attributeName) {
      xmlAttribute.set_value(attributeValue);
    }
  }
}

string XMLElement::get_attribute_value(const string &attributeName) {
  for (XMLAttribute xmlAttribute : attributes) {
    if (xmlAttribute.get_name() == attributeName) {
      return xmlAttribute.get_value();
    }
  }
  return "";
}

void XMLElement::print(ofstream &output, int level) {
  int i;
  for (i = 0; i < level; i++) {
    output << "\t";
  }
  output << "<";
  output << name;
  for (XMLAttribute xmlAttribute : attributes) {
    output << " " << xmlAttribute.to_string();
  }
  if (first_child == nullptr) {
    if (pc_data.empty()) {
      output << "/>\n";
    } else {
      output << ">" << pc_data << "</" << name << ">\n";
    }
  } else {
    output << ">\n";
    first_child->print(output, level + 1);
    for (i = 0; i < level; i++) {
      output << "\t";
    }
    output << "</" << name << ">\n";
  }
  if (next_sibling != nullptr) {
    next_sibling->print(output, level);
  }
}

XMLElement *XMLElement::get_first_child() { return first_child; }

XMLElement *XMLElement::get_next_sibling() { return next_sibling; }

XMLElement *XMLElement::get_parent() { return parent; }

XMLElement::~XMLElement() {
  delete first_child;
  delete next_sibling;
}

void XMLElement::set_next_sibling(XMLElement *next_sibling) {
  this->next_sibling = next_sibling;
}

void XMLElement::set_first_child(XMLElement *first_child) {
  this->first_child = first_child;
}

string XMLElement::get_name() { return name; }

string XMLElement::get_pc_data() { return pc_data; }

void XMLElement::add_attribute(XMLAttribute xmlAttribute) {
  attributes.push_back(xmlAttribute);
}

void XMLElement::set_pc_data(string pcData) { this->pc_data = move(pcData); }

bool XMLElement::has_attributes() { return !attributes.empty(); }

int XMLElement::attribute_size() { return attributes.size(); }

XMLAttribute XMLElement::get_attribute(int index) {
  return attributes.at(index);
}
