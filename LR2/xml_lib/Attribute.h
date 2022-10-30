#pragma once

#include <string>

namespace xml {

/**
 * @brief Класс аттрибут тега xml документа.
 * @details Класс реализует аттрибут тега документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class Attribute {
 public:
  /**
   * @brief Конструктор принимает имя и значение аттрибута.
   * @param name имя аттрибута
   * @param value значение аттрибута
   */
  Attribute(std::string name, std::string value);
  std::string name;
  std::string value;

  bool operator==(const Attribute &other) const;
};

}  // namespace xml