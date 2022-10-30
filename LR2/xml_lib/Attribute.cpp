#include "Attribute.h"

#include <utility>

using namespace xml;

Attribute::Attribute(std::string name, std::string value) {
  this->name = std::move(name);
  this->value = std::move(value);
}

bool Attribute::operator== (const Attribute &other) const {
  return this->value == other.value && this->name == other.name;
}