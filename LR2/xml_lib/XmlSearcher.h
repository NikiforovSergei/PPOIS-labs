#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "Document.h"
#include "XmlDocument.h"

const bool DEBUG = false;

namespace xml {

/**
 * @brief Класс поиска в XML.
 * @details Класс, реализует поиск по xml документу. Поддерживает абсолютные
 * поисковые запросы и предикаты, причем предикаты могут быть комплексные.
 * @author Левков Глеб
 * @date 2022-09-10
 */

class XmlSearcher {
 public:
  /**
   * @brief Конструктор принимает на вход xml док и поисковой запрс.
   * @param xml XML Документ
   * @param request строка запрос
   */
  XmlSearcher(XmlDocument* xml, std::string request);

  /**
   * @brief Возвращает вектор удовлетворяющих запросу узлов.
   */
  std::vector<Node*> getResult();

 private:
  Document* document;

  std::string request;
  std::vector<std::string> requestPath;

  std::vector<Node*> result;
  std::unordered_map<std::string, std::vector<Node*>> searchTable;

  /**
   * @brief Инициирует обработку запроса.
   */
  void find();

  /**
   * @brief Иницииализирует хеш таблицу елемнтов xml документа.
   */
  void initSearchTable(Node* node);

  /**
   * @brief Парсит путь запроса.
   * @return std::string последний элемент завпроса
   */
  std::string initPath();

  /**
   * @brief Инициирует обработку простого запроса.
   */
  void solutionWithoutSearchQueries(const std::string& current);

  /**
   * @brief Инициирует обработку комплексного запроса.
   */
  void solutionWithSearchQueries(const std::string& current);

  /**
   * @brief преобразует строку запроса с атрибутом или текстом в вектор
   * Элементов.
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> processQuery(const std::string& query);

  /**
   * @brief Рекурсиивно разбирает комплексный запрос.
   * @param query комплексный запрос
   * @param operation операция найденная в запросе
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> recursionParse(const std::string& query,
                                    const std::string& operation);
  /**
   * @brief Возвращает все Элементы найденные по данным из строки.
   * @param expression строка содержащая искомые аттрибуты или текст
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> convertToNodes(const std::string& expression);

  /**
   * @brief Разбирает строку на аттрибуты и их значения.
   * @param query строка содержащая искомые атрибуты
   * @param logicalNot логической отрицание в запросе
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> attributeQuery(const std::string& query, bool logicalNot);

  /**
   * @brief Разбирает строку, находит искомый текст.
   * @param query строка содержащая искомый текст
   * @param logicalNot логической отрицание в запросе
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> textQuery(const std::string& query, bool logicalNot);

  /**
   * @brief Разбирает строку на аттрибуты и их значения.
   * @param query строка содержащая искомые атрибуты
   * @return std::string* массив, первый элемент - имя, второй - значение
   * аттрибута.
   */
  std::string* parseAttribute(std::string request_result);

  /**
   * @brief Ищет элементы содержащие нужный текст.
   * @param text строка содержащая искомый текст
   * @param logicalNot логической отрицание в запросе
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> checkText(const std::string& text, bool logicalNot);

  /**
   * @brief Ищет элементы содержащие нужный аттрибут.
   * @param name имя аттрибута
   * @param value значение аттрибута
   * @return std::vector<Node*> вектор удовлетворяющих запросу элементов.
   */
  std::vector<Node*> checkAttribute(const std::string& name,
                                    const std::string& value, bool logicalNot);
  /**
   * @brief Разделяте комплексный запрос на два.
   * @param query строка содержащая запрос
   * @param operation логическая операция по которой будет делится зарос
   std::string* массив из 2-ух подзаросов.
   */
  static std::string* splitRequest(const std::string& operation,
                                   const std::string& query);
  static void debug(const std::string& message);
};

}  // namespace xml