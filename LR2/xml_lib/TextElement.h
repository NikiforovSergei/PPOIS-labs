#pragma once

#include <string>

#include "Element.h"
#include "Node.h"

namespace xml {

/**
 * @brief Класс текстового элемента xml документа.
 * @details Класс, реализует текст внутри тегов.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class TextElement : public Node {
 public:
  /**
   * @brief Конструктор принимает значение (текст) и родителя.
   * @param file - поток чтения
   */
  TextElement(std::string value, Element* parent);

  /**
   * @return std::string возращат ничто.
   */
  std::string getValue() override;

  /**
   * @return std::string возращат содержимое.
   */
  std::string getContent() override;

  /**
   * @return std::vector<Attribute> возращат ничто.
   */
  std::vector<Attribute> getAttributes() override;

  /**
   * @brief Для отображения в терминале.
   * @return std::string текстовое предстваление объекта.
   */
  std::string toString() override;
};

}  // namespace xml
