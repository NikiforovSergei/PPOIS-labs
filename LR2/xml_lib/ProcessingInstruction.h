#pragma once

#include <string>

namespace xml {

/**
 * @brief Класс инструкции xml документа.
 * @details Класс реализует инструкцию документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class ProcessingInstruction {
 public:
  std::string value;
};

}  // namespace xml