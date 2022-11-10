//
// Created by Vladimir Moshchuk on 9.11.22.
//

#ifndef TEP_STC_EXCEPTIONS_EXCEPTIONS_H_
#define TEP_STC_EXCEPTIONS_EXCEPTIONS_H_
#include <exception>
#include <iostream>
#include <string>
#include <utility>

namespace stc {
class Exception : public std::exception {
  std::string _msg;
 public:
  explicit Exception(std::string msg) : _msg(std::move(msg)) {}

  virtual const char *what() const noexcept override {
    return _msg.c_str();
  }
};

}

#endif //TEP_STC_EXCEPTIONS_EXCEPTIONS_H_
