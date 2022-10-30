#pragma once

#include <string>

namespace xml {

class Comment {
 public:
  Comment(std::string value);
  std::string value;
};

}  // namespace xml