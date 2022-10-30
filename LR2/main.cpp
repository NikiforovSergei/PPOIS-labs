#include <fstream>
#include <iostream>

#include "XmlDocument.h"
#include "XmlSearcher.h"
#include "exceptions/XmlException.h"
#include "exceptions/ParsingTagException.h"

using namespace xml;

int main(int argc, char* argv[]) {
  std::ifstream input;

  input.open("/Users/glebchanskiy/main/PPOIS-labs/LR2/resources/input.xml");

  if (input.is_open()) {
    try {
      XmlDocument xml(&input);

      XmlSearcher search(&xml, argv[1]);
      for (auto& node : search.getResult()) {
        std::cout << node->toString() << std::endl;
      }
    } catch (ParsingTagException& ex) {
      std::cout << "failed to load xml file: " << ex.what() << std::endl;
    }
  } else {
    std::cout << "input file not founded" << std::endl;
  }

  input.close();

  return 0;
}
