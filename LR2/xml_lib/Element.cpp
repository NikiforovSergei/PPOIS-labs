#include "Element.h"

using namespace xml;

Element::Element(std::string value, std::vector<Attribute> attributes,
                 Element* parent)
    : Node(parent, value), attributes(attributes) {}

std::string Element::getValue() { return value; }

std::string Element::getContent() {
  std::string allContent = " ";
  for (auto& child : childrens) {
    allContent += child->value + " ";
  }
  return allContent.empty() ? "..." : allContent;
}

std::vector<Attribute> Element::getAttributes() { return attributes; }

std::string Element::toString() {
  std::string attrs;
  for (const auto& attr : this->attributes) {
    if (attr == this->attributes.back())
      attrs += attr.name + ":" + attr.value;
    else
      attrs += attr.name + ":" + attr.value + ", ";
  }

  return this->getValue() + "[" + this->getContent() + "| " + attrs + "]";
}

bool Element::operator==(Element& other) {
  return this->value == other.value && this->content == other.content &&
         this->attributes == other.attributes &&
         this->childrens == other.childrens &&
         this->getContent() == other.getContent();
}