#include "Tree.h"
#include "../Exceptions/Exceptions.h"

namespace stc {

std::string Tree::print(Tree *check, std::string &output) {
  if (check==nullptr) {
    throw Exception("set is empty!");
  }
  //std::sort(check->elements.begin(), check->elements.end());

  std::cout << "{";
  output += "{";
  for (int i = 0; i < check->elements.size(); i++) {
    std::cout << check->elements[i];
    output += check->elements[i];
    if (i!=check->elements.size() - 1 || !check->subsets.empty()) {
      std::cout << ", ";
      output += ", ";
    }
  }

  for (int i = 0; i < check->subsets.size()!=0; i++) {
    print(check->subsets[i], output);
    if (i!=check->subsets.size() - 1) {
      std::cout << ", ";
      output += ", ";
    } else {
      std::cout << "}";
      output += "}";
      break;
    }

  }
  if (check->subsets.empty()) {
    std::cout << "}";
    output += "}";

  }
  return output;
}

Tree *Tree::newSetSubset(Tree *a) //копирует множество
{
  Tree *Union = new Tree;
  Union->elements = a->elements;
  for (auto &subset : a->subsets) {
    Union->subsets.push_back(newSetSubset(subset));
  }
  return Union;
}

bool Tree::subsetComparing(Tree *a, Tree *b) //сравнивает подмножеств
{
  std::sort(a->elements.begin(), a->elements.end());
  std::sort(b->elements.begin(), b->elements.end());
  if (a->elements!=b->elements) return false;
  if (a->subsets.size()!=b->subsets.size()) return false;
  for (auto &subset : b->subsets) {
    for (auto &j : a->subsets) {
      if (!Tree::subsetComparing(j, subset)) return false;
      else return true;
    }
  }
  return true;
}

Tree *Tree::sum(Tree *a, Tree *b) {
  Tree *Union = Tree::newSetSubset(a);
  for (auto &element : b->elements) {
    if (find(Union->elements.begin(), Union->elements.end(), element)==Union->elements.end()) {
      Union->elements.push_back(element);
    }
  }

  for (auto &subset : b->subsets) {
    int counter = 0;
    for (auto &j : Union->subsets) {
      if (Tree::subsetComparing(j, subset)) {
        break;
      } else { counter++; }

    }
    if (counter==Union->subsets.size()) {
      Union->subsets.push_back(newSetSubset(subset));
    }

  }
  return Union;
}

Tree *Tree::intersection(Tree *a, Tree *b) {
  Tree *intersection = new Tree;
  for (auto &element : a->elements) {
    auto same = find(b->elements.begin(), b->elements.end(), element);
    if (same!=b->elements.end()) {
      intersection->elements.push_back(*same);
    }
  }

  for (auto &subset : a->subsets) {
    for (auto &j : b->subsets) {
      if (Tree::subsetComparing(subset, j)) {
        intersection->subsets.push_back(Tree::newSetSubset(subset));
        break;
      }
    }
  }

  return intersection;
}

Tree *Tree::simetricDifference(Tree *first, Tree *second) {
  Tree *simDif = new Tree;
  for (auto &element : second->elements) {
    if (find(first->elements.begin(), first->elements.end(), element)==first->elements.end())
      simDif->elements.push_back(element);
  }
  for (auto &element : first->elements) {
    if (find(second->elements.begin(), second->elements.end(), element)==second->elements.end())
      simDif->elements.push_back(element);
  }

  for (auto &subset : first->subsets) {
    int counter = 0;
    for (auto &j : second->subsets) {
      if (Tree::subsetComparing(subset, j)) {
        break;
      } else counter++;
    }
    if (counter==second->subsets.size()) simDif->subsets.push_back(Tree::newSetSubset(subset));
  }

  for (auto &subset : second->subsets) {
    int counter = 0;
    for (auto &j : first->subsets) {
      if (Tree::subsetComparing(subset, j)) {
        break;
      } else counter++;
    }
    if (counter==first->subsets.size()) simDif->subsets.push_back(Tree::newSetSubset(subset));
  }

  return simDif;
}
}