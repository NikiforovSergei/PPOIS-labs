#include <iostream>

#include "Graph.cpp"

int main() {
  Graph<int, int>* g = new Graph<int, int>();

  g->insertVertex(1, 1);
  g->insertVertex(2, 2);
  g->insertVertex(3, 3);

  g->insertEdge(1, 2, 1);
  g->insertEdge(1, 3, 2);
  g->insertEdge(2, 3, 3);

  std::cout << g->verticesSize() << std::endl;
  std::cout << g->edgesSize() << std::endl;

  for (auto it1 = g->adjBegin(); it1 != g->adjEnd(); it1++) {
    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
      std::cout << g->atEdges(*it2) << " ";
    }
    std::cout << std::endl;
  }




}

