#pragma once

#include <vector>

#include "Comment.h"
#include "Element.h"
#include "ProcessingInstruction.h"

namespace xml {

/**
 * @brief Класс xml документа.
 * @details Класс реализует xml документ.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class Document {
 public:
  /**
   * @brief Конструктор инициализирует root=nullptr и ProcessingInstruction=nullptr.
   */
  Document();

  Element *root;
  std::vector<Comment> comments;
  ProcessingInstruction *PI;
};

}  // namespace xml
