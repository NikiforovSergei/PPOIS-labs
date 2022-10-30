#pragma once

#include <string>

#include "Element.h"
#include "Node.h"

namespace xml {

class TextElement : public Node {
 public:
  TextElement(std::string value, Element* parent);

  std::string getValue() override;
  std::string getContent() override;
  std::vector<Attribute> getAttributes() override;
  
  std::string toString() override;
};

}  // namespace xml
