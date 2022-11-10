#ifndef TEP_STC_TREE_TREE_H_
#define TEP_STC_TREE_TREE_H_

#include <string>
#include <vector>
#include <iostream>
#include <exception>
namespace stc {
class Tree {
 private:

  static Tree *newSetSubset(Tree *a);
  static bool subsetComparing(Tree *a, Tree *b);

 public:
  std::vector<std::string> elements;
  std::vector<Tree *> subsets;
  static std::string print(Tree *check,  std::string& output);
  static Tree *sum(Tree *a, Tree *b);
  static Tree *intersection(Tree *a, Tree *b);
  static Tree *simetricDifference(Tree *first, Tree *second);
};
}
#endif //TEP_STC_TREE_TREE_H_