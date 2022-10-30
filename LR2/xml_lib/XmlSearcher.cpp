#include "XmlSearcher.h"

using namespace xml;

XmlSearcher::XmlSearcher(XmlDocument *xml, std::string request)
    : document(xml->document), request(std::move(request)) {
  find();
}

std::vector<Node *> XmlSearcher::getResult() { return result; }

void XmlSearcher::find() {
  if (request == "/") return result.push_back(document->root);

  initSearchTable(document->root);
  std::string current = initPath();

  if (current.find('[') != std::string::npos)
    solutionWithSearchQueries(current);
  else
    solutionWithoutSearchQueries(current);
}

void XmlSearcher::initSearchTable(Node *node) {
  if (!node->childrens.empty()) {
    for (auto child : node->childrens) initSearchTable(child);
  }
  if (!node->getValue().empty()) {
    debug("added to map: " + node->getValue());
    searchTable[node->getValue()].push_back(node);
  }
}

std::string XmlSearcher::initPath() {
  std::string current(request);

  debug("current: " + current);
  debug("req_path:");

  while (current.find('/') != std::string::npos) {
    size_t pos = current.find('/');
    requestPath.push_back(current.substr(0, pos));
    current = current.substr(pos + 1, request.size());

    debug("> " + current.substr(0, pos));
  }

  debug("current: " + current);

  return current;
}

void XmlSearcher::solutionWithoutSearchQueries(const std::string& current) {
  requestPath.push_back(current);
  for (auto &node : searchTable[requestPath.back()]) {
    result.push_back(node);
  }
}

void XmlSearcher::solutionWithSearchQueries(const std::string& current) {
  debug("solution with search queries");

  size_t pos = current.find('[');
  requestPath.push_back(current.substr(0, pos));
  std::string query = current.substr(pos, current.size());

  if (query.find("||") != std::string::npos ||
      query.find("&&") != std::string::npos) {
    debug("complex query: " + query);
    result = processQuery(query);
  } else {
    debug("query: " + query);
    if (query.find("attr") != std::string::npos) {
      debug("founded 'attr'");
      result = attributeQuery(query, query.find('!') != std::string::npos);
    } else if (query.find("text") != std::string::npos) {
      debug("founded 'text'");
      result = textQuery(query, query.find('!') != std::string::npos);
    }
  }
}

std::vector<Node *> XmlSearcher::processQuery(const std::string& query) {
  std::vector<Node *> resultSet;

  debug("process query");

  if (query.find("||") != std::string::npos) {
    debug("founded '||'");
    resultSet = recursionParse(query, "||");
  } else if (query.find("&&") != std::string::npos) {
    debug("founded '&&'");
    resultSet = recursionParse(query, "&&");
  }
  return resultSet;
}

std::vector<Node *> XmlSearcher::recursionParse(const std::string &query,
                                                const std::string &operation) {
  std::string *splitedRequest = splitRequest(operation, query);

  std::string left = splitedRequest[0];
  std::string right = splitedRequest[1];

  debug("splited query (" + query + ") = [" + left + "]:[" + right + "]");

  std::vector<Node *> leftResultSet = processQuery(left);
  std::vector<Node *> rightResultSet = processQuery(right);

  std::vector<Node *> temp = convertToNodes(left);
  if (!temp.empty()) leftResultSet = temp;

  temp = convertToNodes(right);
  if (!temp.empty()) rightResultSet = temp;

  std::vector<Node *> resultSet;

  if (operation == "&&") {
    for (auto i : rightResultSet) {
      bool isMatchFounded = false;
      for (auto j : leftResultSet) {
        if (*(Element *)i == *(Element *)j) {
          isMatchFounded = true;
          debug("  " + i->toString() + " is equal to " + j->toString());
        }
      }
      if (isMatchFounded) resultSet.push_back(i);
    }
  } else if (operation == "||") {
    resultSet = rightResultSet.size() > leftResultSet.size() ? rightResultSet
                                                             : leftResultSet;
    for (auto i : rightResultSet) {
      bool isMatchNotFounded = true;
      for (auto j : leftResultSet) {
        if ((Element *)i == (Element *)j) isMatchNotFounded = false;
      }
      if (isMatchNotFounded) resultSet.push_back(i);
    }
  }
  return resultSet;
}

std::vector<Node *> XmlSearcher::attributeQuery(const std::string &query,
                                                bool logical_not) {
  std::string *parsedAttribute = parseAttribute(query);
  std::string attributeName = parsedAttribute[0];
  std::string attributeValue = parsedAttribute[1];
  debug("query parsed:\nattributeName: " + attributeName +
        "\nattributeValue: " + attributeValue +
        "\nlogical_not: " + (logical_not ? "true" : "false"));
    std::vector<Node *> test = checkAttribute(attributeName, attributeValue, logical_not);

    debug("");
    for (auto &node : test) {
        debug(node->toString());
    }
    debug("");
  return test;
}

std::string *XmlSearcher::parseAttribute(std::string request_result) {
  size_t pos = request_result.find("attr");
  request_result = request_result.substr(pos + 6);

  pos = request_result.find(',');
  std::string attr_name = request_result.substr(0, pos - 1);

  request_result = request_result.substr(pos + 1, request.size());
  pos = request_result.find(')');
  std::string attr_value = request_result.substr(2, pos - 3);

  return new std::string[2]{attr_name, attr_value};
}

std::vector<Node *> XmlSearcher::textQuery(const std::string &current,
                                           bool logical_not) {
  size_t pos1 = current.find('(') + 2;
  size_t pos2 = current.find(')');
  std::string text = current.substr(pos1, pos2 - pos1 - 1);
  debug("query parsed:\nlooking for: " + text);
  return checkText(text, logical_not);
}

std::vector<Node *> XmlSearcher::checkAttribute(const std::string &name,
                                                const std::string &value,
                                                bool logical_not) {
  std::vector<Node *> resultSet;

  debug("searching for nodes with \nname = " + name + "\nvalue = " + value);
  debug("filling result set:");

  for (auto node : searchTable[requestPath.back()]) {
    for (auto &attribute : node->getAttributes()) {
      debug("attribute  name: " + attribute.name);
      debug("attribute value: " + attribute.value);

      if (logical_not) {
        debug("logical_not true");
        if (attribute.name != name || attribute.value != value) {
          if (attribute.name != name)
            debug( "attribute.name != name ::: true");
          if (attribute.value != value)
            debug( "attribute.value != value ::: true");
          
        
          debug("added node: " + node->getValue());
        
          resultSet.push_back(node);
        }
      } else {
        debug("logical_not false");
        if (attribute.name == name && attribute.value == value) {
          debug("added node: " + node->getValue());
          resultSet.push_back(node);
          break;
        }
      }
    }
  }
  return resultSet;
}

std::vector<Node *> XmlSearcher::checkText(const std::string &text,
                                           bool logical_not) {
  std::vector<Node *> resultSet;

  debug("filling result set:");

  for (auto &node : searchTable[requestPath.back()]) {
    std::string nodeContent = node->getContent();
    debug("nodeContent: |" + nodeContent);

    if (logical_not) {
      debug(nodeContent + "!=" + text + "?");
      if (nodeContent != ' ' + text + ' ') {
        debug("added node: " + node->getContent());
        resultSet.push_back(node);
      }
    } else {
      debug(nodeContent + "==" + text + "?");
      if (nodeContent == ' ' + text + ' ') {
        debug("added node: " + node->getContent());
        resultSet.push_back(node);
      }
    }
  }
  return resultSet;
}

std::vector<Node *> XmlSearcher::convertToNodes(const std::string &expression) {
  if (expression.find("||") != std::string::npos ||
          expression.find("&&") != std::string::npos) {
    std::vector<Node *> emptySet;
    return emptySet;
  }
  else if (expression.find("attr") != std::string::npos)
    return attributeQuery(expression, expression.find('!') != std::string::npos);
  else
    return textQuery(expression, expression.find('!') != std::string::npos);
}

std::string *XmlSearcher::splitRequest(const std::string &operation,
                                       const std::string &query) {
  size_t pos = query.find(operation);

  return new std::string[2]{query.substr(0, pos),
                            query.substr(pos + 2, query.size())};
}

void XmlSearcher::debug(const std::string& message) {
  if (DEBUG) {
    std::cout << message << std::endl;
  }
}