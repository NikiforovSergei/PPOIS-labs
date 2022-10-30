#pragma once

#include "XmlException.h"

namespace xml {

class ParsingTagException : public XmlException {
 public:
  ParsingTagException(std::string &&whatStr) noexcept : XmlException(std::move(whatStr)) { }
  ParsingTagException(const std::string &whatStr) noexcept : XmlException(whatStr) { }
};

}