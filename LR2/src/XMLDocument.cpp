#include "XMLDocument.hpp"
#include "XMLTextType.hpp"

#include <fstream>
#include <iostream>

XMLDocument::XMLDocument(string filename) {
  this->filename = move(filename);
  this->root = nullptr;
}

string XMLDocument::read_token(char prev_ch, char *next_ch, bool extra,
                               bool quota) {
  string buffer;
  char ch = prev_ch;
  while ((ch != '\'' || extra) && (ch != '\"' || quota) &&
         (ch != '=' || quota) && (ch != ' ' || extra) && (ch != '/' || extra) &&
         (ch != EOF) && (ch != '<') && (ch != '>' || quota)) {
    buffer += ch;
    input_stream.get(ch);
  }
  *next_ch = ch;
  return buffer;
}

string XMLDocument::parse_tag() {
  string token;
  char ch;
  input_stream.get(ch);
  if (ch == '/') {
    last_read_token_type = XMLTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES;
    input_stream.get(ch);
  } else {
    last_read_token_type = XMLTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES;
  }
  token = read_token(ch, &ch);
  if (ch == '>' &&
      last_read_token_type == XMLTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES) {
    last_read_token_type = XMLTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES;
  }
  if (last_read_token_type ==
          XMLTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES &&
      ch != '>') {
    cout << "Wrong tag value";
    last_read_token_type = XMLTokenType::XML_END;
    return "";
  } else {
    return token;
  }
}

string XMLDocument::parse_attribute_value() {
  string token;
  char ch;
  input_stream.get(ch);
  if (ch == '\"') {
    last_read_token_type = XMLTokenType::XML_ATTRIBUTE_VALUE;
    return "";
  }
  token = read_token(ch, &ch, true);
  if (ch != '\"') {
    cout << "Wrong attribute value";
    last_read_token_type = XMLTokenType::XML_END;
    return "";
  }
  last_read_token_type = XMLTokenType::XML_ATTRIBUTE_VALUE;
  return token;
}

string XMLDocument::parse_empty_tag() {
  char ch;
  input_stream.get(ch);
  if (ch != '>') {
    cout << "Wrong tag value";
    last_read_token_type = XMLTokenType::XML_END;
  } else {
    last_read_token_type = XMLTokenType::XML_CLOSING_TAG_WITH_ATTRIBUTES;
  }
  return "";
}

string XMLDocument::get_next_token(XMLTextType xmlTextType) {
  char ch;
  string token;
  try {
    input_stream.get(ch);
    while (ch == ' ' || ch == '\t' || ch == '\n') {
      input_stream.get(ch);
    }
    switch (ch) {
    case '<':
      return parse_tag();
    case '\"':
      if (xmlTextType == XMLTextType::XML_TEXT_VALUE) {
        token = read_token(ch, &ch, true, true);
        last_read_token_type = XMLTokenType::XML_TEXT;
        input_stream.putback(ch);
        return token;
      } else {
        return parse_attribute_value();
      }
    case '/':
      return parse_empty_tag();
    case '=':
      if (xmlTextType == XMLTextType::XML_TEXT_VALUE) {
        token = read_token(ch, &ch, true, true);
        last_read_token_type = XMLTokenType::XML_TEXT;
        input_stream.putback(ch);
        return token;
      } else {
        last_read_token_type = XMLTokenType::XML_EQUAL;
      }
      break;
    case '>':
      if (xmlTextType == XMLTextType::XML_TEXT_VALUE) {
        token = read_token(ch, &ch, true, true);
        last_read_token_type = XMLTokenType::XML_TEXT;
        input_stream.putback(ch);
        return token;
      } else {
        last_read_token_type = XMLTokenType::XML_OPENING_TAG_FINISH;
      }
      return "";
    default:
      if (xmlTextType == XMLTextType::XML_TEXT_VALUE) {
        token = read_token(ch, &ch, true, true);
      } else {
        token = read_token(ch, &ch, true);
      }
      last_read_token_type = XMLTokenType::XML_TEXT;
      input_stream.putback(ch);
      return token;
    }
  } catch (ifstream::failure &e) {
    last_read_token_type = XMLTokenType::XML_END;
    return "";
  }
  return "";
}

void XMLDocument::print(string fileName) {
  ofstream outputStream;
  outputStream.open(fileName, ios::out);
  root->print(outputStream, 0);
  outputStream.close();
}

void XMLDocument::parse() {
  XMLTextType textType = XMLTextType::XML_TEXT_ATTRIBUTE;
  bool siblingClosed = false;
  string token;
  XMLAttribute xmlAttribute;
  XMLElement *sibling = nullptr, *current = nullptr, *parent = nullptr;
  input_stream.exceptions(ifstream::failbit | ifstream::badbit);
  try {
    input_stream.open(filename, ios::in);
    token = get_next_token(textType);
    while (last_read_token_type != XMLTokenType::XML_END) {
      switch (last_read_token_type) {
      case XMLTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES:
      case XMLTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES:
        current = new XMLElement(token, parent);
        if (parent) {
          if (sibling && siblingClosed) {
            sibling->set_next_sibling(current);
            sibling = current;
          } else {
            parent->set_first_child(current);
          }
        } else {
          if (!root) {
            root = current;
          }
        }
        parent = current;
        siblingClosed = false;
        if (last_read_token_type ==
            XMLTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES) {
          textType = XMLTextType::XML_TEXT_ATTRIBUTE;
        } else {
          textType = XMLTextType::XML_TEXT_VALUE;
        }
        break;
      case XMLTokenType::XML_OPENING_TAG_FINISH:
        textType = XMLTextType::XML_TEXT_VALUE;
        siblingClosed = false;
        break;
      case XMLTokenType::XML_CLOSING_TAG_WITH_ATTRIBUTES:
        sibling = current;
        parent = current->get_parent();
        textType = XMLTextType::XML_TEXT_VALUE;
        siblingClosed = true;
        break;
      case XMLTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES:
        if (token == current->get_name()) {
          sibling = current;
          parent = current->get_parent();
        } else {
          if (token == current->get_parent()->get_name()) {
            sibling = parent;
            parent = current->get_parent()->get_parent();
            current = current->get_parent();
          }
        }
        siblingClosed = true;
        textType = XMLTextType::XML_TEXT_VALUE;
        break;
      case XMLTokenType::XML_ATTRIBUTE_VALUE:
        if (!token.empty()) {
          replace_escape_characters(token);
          xmlAttribute.set_value(token);
        } else {
          xmlAttribute.set_value("");
        }
        current->add_attribute(xmlAttribute);
        textType = XMLTextType::XML_TEXT_ATTRIBUTE;
        break;
      case XMLTokenType::XML_EQUAL:
        textType = XMLTextType::XML_TEXT_NOT_AVAILABLE;
        break;
      case XMLTokenType::XML_TEXT:
        if (textType == XMLTextType::XML_TEXT_ATTRIBUTE) {
          xmlAttribute = XMLAttribute(token);
        } else {
          if (textType == XMLTextType::XML_TEXT_VALUE) {
            replace_escape_characters(token);
            current->set_pc_data(token);
          }
        }
        break;
      default:
        cout << "This token type not supported\n";
        break;
      }
      token = get_next_token(textType);
    }
    input_stream.close();
  } catch (ifstream::failure &e) {
    cout << "Exception opening file " << filename;
  }
}

XMLElement *XMLDocument::get_first_child() { return root; }

XMLDocument::~XMLDocument() { delete root; }

void XMLDocument::replace_escape_characters(string &token) {
  while (token.find("&quot;") != string::npos) {
    token.replace(token.find("&quot;"), 6, "\"");
  }
  while (token.find("&amp;") != string::npos) {
    token.replace(token.find("&amp;"), 5, "&");
  }
  while (token.find("&lt;") != string::npos) {
    token.replace(token.find("&lt;"), 4, "<");
  }
  while (token.find("&gt;") != string::npos) {
    token.replace(token.find("&gt;"), 4, ">");
  }
  while (token.find("&apos;") != string::npos) {
    token.replace(token.find("&apos;"), 6, "'");
  }
}
