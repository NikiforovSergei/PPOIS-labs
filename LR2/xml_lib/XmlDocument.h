#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>

#include "Document.h"
#include "ProcessingInstruction.h"
#include "TextElement.h"
#include "exceptions/CantFindAttributeException.h"
#include "exceptions/CantFindTagException.h"
#include "exceptions/ParsingTagException.h"

namespace xml {

/**
 * @brief Класс для загрузки XML документа.
 * @author Левков Глеб
 * @date 2022-09-30
 */
class XmlDocument {
 public:
  /**
   * @brief Конструктор принимает аргументом поток чтения из файла.
   * @param file - поток чтения
   */
  XmlDocument(std::ifstream* file);

  Document* document;

 private:
  std::ifstream* input;
  std::stack<Element*> tagStack;
  int currentLine;
  /**
   * @brief Запускает основной цикл посимвольного чтения из потока.
   */
  void load();

  /**
   * @brief Пропускает все символы табов и пробелов.
   */
  void skipTabsAndLineBreaks();

  /**
   * @brief Определяет считан спецсимвол или текст.
   */
  void processingOfCharacters();

  /**
   * @brief Обработка спецсимволов.
   */
  void processingOfSpecialSymbol();

  /**
   * @brief Считывание инструкции обработки документа.
   */
  void processingOfProcessingInstruction();

  /**
   * @brief Считывание тега.
   */
  void processingOfOpeningTag();

  /**
   * @brief Считавание закрывающего тега.
   * @throw ParsingTagException Если не найден закрыващий тег.
   */
  void processingOfClosingTag();

  /**
   * @brief Считавание текста.
   */
  void processingOfText();

  /**
   * @brief Считавание комментариев.
   */
  void processingOfComment();

  /**
   * @brief Возращает строку до переданного символа.
   * @param symbol - Читает поток пока не всxтретит символ
   */
  std::string getStringUntil(char symbol);

 /**
   * @brief Преобразует строку в Element.
   * @param content - строка для преобразований
   */ 
  Element* convertStringToElement(std::string content) const;
};

}  // namespace xml