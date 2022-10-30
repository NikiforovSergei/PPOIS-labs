#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "Document.h"
#include "XmlDocument.h"

const bool DEBUG = false;

namespace xml {

class XmlSearcher {
 public:
  XmlSearcher(XmlDocument* xml, std::string request);
  std::vector<Node*> getResult();

 private:
  Document* document;

  std::string request;
  std::vector<std::string> requestPath;

  std::vector<Node*> result;
  std::unordered_map<std::string, std::vector<Node*>> searchTable;

  void find();
  void initSearchTable(Node* node);
  std::string initPath();
  void solutionWithoutSearchQueries(const std::string& current);
  void solutionWithSearchQueries(const std::string& current);
  std::vector<Node*> processQuery(const std::string& query);
  std::vector<Node*> recursionParse(const std::string& query,
                                    const std::string& operation);

  std::vector<Node*> convertToNodes(const std::string& str);
  std::vector<Node*> attributeQuery(const std::string& query, bool logical_not);
  std::vector<Node*> textQuery(const std::string& current, bool logical_not);

  std::string* parseAttribute(std::string request_result);

  std::vector<Node*> checkText(const std::string& text, bool logical_not);
  std::vector<Node*> checkAttribute(const std::string& name,
                                    const std::string& value, bool logical_not);
  static std::string* splitRequest(const std::string& operation,
                                   const std::string& query);

  static void debug(const std::string& message);
};

}  // namespace xml