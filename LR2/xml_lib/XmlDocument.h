#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>

#include "Document.h"
#include "ProcessingInstruction.h"
#include "TextElement.h"

namespace xml {
class XmlDocument {
 public:
  XmlDocument(std::ifstream* file);
  Document* document;

 private:
  std::ifstream* input;
  std::stack<Element*> tagStack;
  int currentLine;

  void load();
  
  void skipTabsAndLineBreaks();

  void processingOfCharacters();
  void processingOfSpecialSymbol();

  void processingOfProcessingInstruction();
  void processingOfOpeningTag();
  void processingOfClosingTag();
  void processingOfText();
  void processingOfComment();

  std::string getStringUntil(char symbol);
  Element* convertStringToElement(std::string content) const;
};
}  // namespace xml