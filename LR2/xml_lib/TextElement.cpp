#include "TextElement.h"

#include <utility>

using namespace xml;

TextElement::TextElement(std::string value, Element* parent)
    : Node(parent, std::move(value)) {}

std::string TextElement::getValue() {
  return {};
}

std::string TextElement::getContent() {
  return value;
}

std::vector<Attribute> TextElement::getAttributes() {
  return {};
}

std::string TextElement::toString() {
  return "[" + this->content + "]";
}