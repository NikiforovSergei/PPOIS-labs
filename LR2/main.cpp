#include <fstream>
#include <iostream>

#include "Element.h"
#include "XmlDocument.h"
#include "XmlSearcher.h"

using namespace xml;

int main(int argc, char* argv[]) {
  std::ifstream input;

  input.open("/Users/glebchanskiy/main/PPOIS-labs/LR2/resources/input.xml");

  if (input.is_open()) {
    XmlDocument xml(&input);

    XmlSearcher search(&xml, argv[1]);
    for (auto& node : search.getResult()) {
      std::cout << node->toString() << std::endl;
    }
  } else {
    std::cout << "file not founded" << std::endl;
  }

  input.close();

  return 0;
}
