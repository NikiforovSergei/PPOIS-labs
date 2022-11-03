#ifndef __LAB2_XML_ELEMENT_HPP__
#define __LAB2_XML_ELEMENT_HPP__

#include <string>
#include <vector>

#include "XMLAttribute.hpp"

using namespace std;

class XMLElement {
public:
  XMLElement(string name, XMLElement *parent);
  ~XMLElement();
  string get_name();
  string get_pc_data();
  XMLElement *get_first_child();
  XMLElement *get_next_sibling();
  XMLElement *get_parent();
  void set_attribute_value(const string &attributeName,
                           const string &attributeValue);
  string get_attribute_value(const string &attributeName);
  int attribute_size();
  XMLAttribute get_attribute(int index);
  void print(ofstream &outputStream, int level);
  void set_next_sibling(XMLElement *nextSibling);
  void set_first_child(XMLElement *firstChild);
  void add_attribute(XMLAttribute xmlAttribute);
  void set_pc_data(string pcData);
  bool has_attributes();

private:
  string name = "";
  string pc_data = "";

  vector<XMLAttribute> attributes;

  XMLElement *parent;
  XMLElement *first_child;
  XMLElement *next_sibling;
};

#endif
