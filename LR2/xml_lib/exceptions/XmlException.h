#pragma once

#include <exception>
#include <string>

namespace xml {

class XmlException : public std::exception {
 public:
  XmlException(std::string &&whatStr) noexcept;
  XmlException(const std::string &whatStr) noexcept;
  ~XmlException() noexcept override = default;

  const char *what() const noexcept override;

 private:
  std::string whatStr;
};

}