#pragma once

#include <vector>

#include "ProcessingInstruction.h"
#include "Element.h"
#include "Comment.h"

namespace xml {

class Document {
 public:
  Document();
  
  Element *root;
  std::vector<Comment> comments;
  ProcessingInstruction *PI;
};

} // namespace xml;
