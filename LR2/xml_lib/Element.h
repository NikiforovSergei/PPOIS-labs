#pragma once

#include <string>

#include "Node.h"
#include "Attribute.h"

namespace xml {
        
class Element : public Node {
 public:
  Element(std::string value, std::vector<Attribute> attributes,
          Element *parent);

  std::string getValue() override;
  std::string getContent() override;
  std::vector<Attribute> getAttributes() override;

  virtual std::string toString() override;

  std::vector<Attribute> attributes;

  bool operator==(Element &other);
};

}  // namespace xml
