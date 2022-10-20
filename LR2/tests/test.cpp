#include <iostream>

#include "../src/XMLDocument.hpp"

int main() {
  auto *doc = new XMLDocument("test.xml");

  doc->parse();
  XMLElement *root = doc->get_first_child();

  std::cout << ("frameset" == root->get_name());
}
