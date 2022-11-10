#pragma once

#include <string>

#include "Attribute.h"
#include "Node.h"

namespace xml {

/**
 * @brief Класс xml тега.
 * @details Класс реализует тег xml документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class Element : public Node {
 public:
  /**
   * @brief Конструктор создаёт тег с заданным именем, аттрибутами и родителем.
   * @param value имя тега
   * @param std::vector<Attribute> вектор аттрибутов элемента
   * @param Element родитель элемента
   */
  Element(std::string value, std::vector<Attribute> attributes,
          Element *parent);

  /**
   * @brief Возвращает имя тега.
   * @return std::string имя тега
   */
  std::string getValue() override;

  /**
   * @brief Возвращает содержимое тега (текст).
   * @return std::string содержимое тега
   */
  std::string getContent() override;

  /**
   * @brief Возвращает аттрибуты тега.
   * @return std::vector<Attribute> вектор аттрибутов
   */
  std::vector<Attribute> getAttributes() override;

  /**
   * @brief Для отображения в терминале.
   * @return std::string текстовое предстваление объекта.
   */
  virtual std::string toString() override;

  std::vector<Attribute> attributes;

  bool operator==(Element &other);
};

}  // namespace xml
