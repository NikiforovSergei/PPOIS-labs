#include "XmlException.h"

#include <utility>

using namespace xml;

XmlException::XmlException(std::string &&whatStr) noexcept
    : whatStr(std::move(whatStr)) {}

XmlException::XmlException(const std::string &whatStr) noexcept
    : whatStr(whatStr) {}

const char* XmlException::XmlException::what() const noexcept { return whatStr.c_str(); }