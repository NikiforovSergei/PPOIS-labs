//
// Created by Vladimir Moshchuk on 8.11.22.
//

#ifndef TEP_STC_PARSER_PARSER_H_
#define TEP_STC_PARSER_PARSER_H_
#include "../Tree/Tree.h"
#include <map>
#include <exception>
namespace stc {
class Parser : public Tree {
 private:

  std::vector<Tree *> sets;
  std::vector<std::string> operations;

 protected:
  static Tree *subsetCounter(int &i, std::string line);
 public:
  static Tree *solution(const std::string &line);

  static Tree *makeSet(std::string setLine);

  static void *pushBackSet(std::vector<Tree *> &lineOfSets, const std::string &line, int &i, char &operation);

  static void solve(std::vector<Tree *> &namesOfSets, char operation);
};

class SavedSet : public Parser {
 public:
  std::map<char, Tree *> named_sets;
  void saveSets(std::string line);
  void distr(const std::string &my_str);
  Tree *solution(const std::string &line);

  void *pushBackSet(std::vector<Tree *> &lineOfSets, const std::string &line, int &i);
  void saveSet(std::string my_str);
};

class SubOperation : public Parser {
 private:
  static int setSize(Tree *set);
 public:
  static void size(std::string str, SavedSet set);
};
}
#endif //TEP_STC_PARSER_PARSER_H_
