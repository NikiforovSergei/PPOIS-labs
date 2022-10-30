#pragma once

#include <string>
#include <vector>

#include "Attribute.h"

namespace xml {

/**
 * @brief Класс обобщённого xml элемента.
 * @details Класс реализует узел xml документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class Node {
 public:
   /**
   * @brief Конструктор задаёт значение и родителя элемента.
   */
  Node(Node *parent, std::string value);

  virtual std::string getValue() = 0;
  virtual std::string getContent() = 0;
  virtual std::vector<Attribute> getAttributes() = 0;

  virtual std::string toString() = 0;

  std::string value;
  std::string content;

  Node *parent;
  std::vector<Node *> childrens;
};

}  // namespace xml
