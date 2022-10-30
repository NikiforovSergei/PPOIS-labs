#pragma once

#include <string>

namespace xml {

class Attribute {
 public:
  Attribute(std::string name, std::string value);
  std::string name;
  std::string value;

  bool operator== (const Attribute &other) const;
};

}  // namespace xml