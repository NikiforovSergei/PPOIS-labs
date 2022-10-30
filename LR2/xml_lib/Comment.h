#pragma once

#include <string>

namespace xml {

/**
 * @brief Класс комментарий xml документа.
 * @details Класс реализует комментарии документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class Comment {
 public:
  /**
   * @brief Конструктор принимает значение (текст) комментария.
   * @param value - текст комментария
   */
  Comment(std::string value);
  std::string value;
};

}  // namespace xml