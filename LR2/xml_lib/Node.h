#pragma once

#include <string>
#include <vector>

#include "Attribute.h"

namespace xml {

class Node {
 public:
  Node(Node *parent, std::string value);

  virtual std::string getValue() = 0;
  virtual std::string getContent() = 0;
  virtual std::vector<Attribute> getAttributes() = 0;

  virtual std::string toString() = 0;

  std::string value;
  std::string content;

  Node *parent;
  std::vector<Node *> childrens;
};

}  // namespace xml
