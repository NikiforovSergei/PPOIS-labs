#ifndef __LAB2_XML_ATTRIBUTE_HPP__
#define __LAB2_XML_ATTRIBUTE_HPP__

#include <string>

using namespace std;

class XMLAttribute {
public:
  XMLAttribute();
  XMLAttribute(string name);

  string get_name();
  string get_value();

  void set_value(string value);

  string to_string();

private:
  string name;
  string value;
};

#endif
