#ifndef __LAB2_XML_DOCUMENT_HPP__
#define __LAB2_XML_DOCUMENT_HPP__

#include <fstream>
#include <string>

#include "XMLElement.hpp"
#include "XMLTextType.hpp"
#include "XMLTokenType.hpp"

using namespace std;

class XMLDocument {
public:
  XMLDocument(string filename);
  ~XMLDocument();
  void print(string filename);
  void parse();
  XMLElement *get_first_child();

private:
  string filename;
  ifstream input_stream;
  XMLTokenType last_read_token_type = XMLTokenType::XML_END;
  XMLElement *root;
  string read_token(char prev_ch, char *next_ch, bool extra = false,
                    bool quota = false);
  string parse_tag();
  string parse_attribute_value();
  string parse_empty_tag();
  string get_next_token(XMLTextType xmlTextType);
  void replace_escape_characters(string &token);
};

#endif
