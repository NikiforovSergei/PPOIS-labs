#include "XmlDocument.h"

#include "Element.h"
#include "Node.h"

using namespace xml;

XmlDocument::XmlDocument(std::ifstream *inputFile) {
  this->input = inputFile;
  currentLine = 1;
  document = new Document();
  try {
    load();
  } catch (ParsingTagException &ex) {
    throw ex;
  }
 
}

void XmlDocument::load() {
  while (true) {
    skipTabsAndLineBreaks();
    if (input->eof()) {
      return;
    }
    try {
      processingOfCharacters();
    } catch (ParsingTagException &ex) {
      throw ex;
    }
  }
}

void XmlDocument::skipTabsAndLineBreaks() {
  while (true) {
    char nextCharacter = input->peek();
    if (nextCharacter == '\n')
      currentLine++;
    else if (nextCharacter != ' ') {
      return;
    }
    input->get();
  }
}

Element *XmlDocument::convertStringToElement(std::string content) const {
  char *nextToken = nullptr, *tokenValue, *subTokenValue,
       *nextSubToken = nullptr;
  tokenValue = strtok_r(&content[0], " ", &nextToken);
  int counter = 1;
  std::string value;
  std::vector<Attribute> attributes;
  while (tokenValue != nullptr) {
    if (counter == 1)
      value = tokenValue;
    else {
      subTokenValue = strtok_r(&tokenValue[0], "=", &nextSubToken);
      std::string attributeName = subTokenValue;
      subTokenValue = strtok_r(nullptr, "=\"", &nextSubToken);
      std::string attributeValue = subTokenValue;
      attributes.push_back(*new Attribute(attributeName, attributeValue));
    }
    tokenValue = strtok_r(nullptr, " ", &nextToken);
    counter++;
  }

  return new Element(value, attributes, nullptr);
}

void XmlDocument::processingOfSpecialSymbol() {
  switch (input->peek()) {
    case '?':
      processingOfProcessingInstruction();
      break;
    case '!':
      processingOfComment();
      break;
    case '/':
      try {
        processingOfClosingTag();
      } catch (ParsingTagException &ex) {
        throw ex;
      }
      break;
    default:
      processingOfOpeningTag();
  }
}

void XmlDocument::processingOfCharacters() {
  if (input->peek() == '<') {
    input->get();
    try {
      processingOfSpecialSymbol();
    } catch (ParsingTagException &ex) {
      throw ex;
    }

  } else {
    processingOfText();
  }
}

void XmlDocument::processingOfProcessingInstruction() {
  input->get();
  document->PI = new ProcessingInstruction();
  document->PI->value = getStringUntil('?');

  getStringUntil('>');
  if (input->get() == '\n') currentLine++;
}

void XmlDocument::processingOfOpeningTag() {
  std::string content = getStringUntil('>');
  bool isDoubleTag = true;
  if (content.back() == '/') {
    isDoubleTag = false;
    content.pop_back();
  }
  Element *tagElement = convertStringToElement(content);
  if (document->root == nullptr)
    document->root = tagElement;
  else {
    tagElement->parent = tagStack.top();
    tagStack.top()->childrens.push_back(tagElement);
  }
  if (isDoubleTag) tagStack.push(tagElement);
}

void XmlDocument::processingOfClosingTag() {
  input->get();
  std::string content = getStringUntil('>');
  if (tagStack.empty())
    throw ParsingTagException("Met closing tag before any opening ones");
  if (content == tagStack.top()->value)
    tagStack.pop();
  else
    throw ParsingTagException("The closing tag will not match the opening tag");
}

void XmlDocument::processingOfText() {
  auto *a = new TextElement(getStringUntil('<'), tagStack.top());
  tagStack.top()->childrens.push_back(a);
  processingOfSpecialSymbol();
}

void XmlDocument::processingOfComment() {
  input->get();
  auto *comment = new Comment(getStringUntil('>'));
  document->comments.push_back(*comment);
}

std::string XmlDocument::getStringUntil(char symbol) {
  std::string str;
  getline(*input, str, symbol);
  currentLine += (int)count(str.begin(), str.end(), '\n');
  return str;
}