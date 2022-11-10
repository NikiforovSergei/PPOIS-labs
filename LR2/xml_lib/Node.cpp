#include "Node.h"

using namespace xml;

Node::Node(Node *parent, std::string value) {
  this->parent = parent;
  this->value = value;
}

