#include <iostream>
#include <string>
#include <vector>
#include "orGraph.h"

using namespace std;

typedef OrGraph<std::string>::Vertex Node;
typedef std::pair<typename OrGraph<std::string>::Vertex*, typename OrGraph<std::string>::Vertex*> Edge;




int main() {
  OrGraph<std::string> graph;

  cout << "graph is empty: " << (graph.isEmpty() ? "true" : "false") << endl;
  cout << "vertex count: " << graph.getVertexCount() << ", edges count: " << graph.getEdgesCount() << endl << endl;



  Node *n1 = new Node("node_1");
  Node *n2 = new Node("node_2");
  Node *n3 = new Node("node_3");
  Node *n4 = new Node("node_4");
  Node *n5 = new Node("node_5");
  Node *n6 = new Node("node_6");
  Node *n7 = new Node("node_7");
  Node *n8 = new Node("node_8");
  Node *n9 = new Node("node_9");
  Node *n10 = new Node("node_10");
  Node *n11 = new Node("node_11");
  Node *n12 = new Node("node_12");


  graph.addEdge(n1, n2);
  graph.addEdge(n1, n3);
  graph.addVertex(n3);
  graph.addVertex(n4);
  graph.addVertex(n5);
  graph.addEdge(n4, n5);
  graph.addEdge(n6, n7);
  graph.addEdge(n7, n8);
  graph.addEdge(n8, n9);
  graph.addEdge(n9, n10);
  graph.addEdge(n10, n11);
  graph.addEdge(n11, n12);
  graph.addEdge(n1, n12);
  graph.addEdge(n2, n12);
  graph.addEdge(n3, n12);



  cout << graph.toString() << endl;

//  OrGraph<std::string>::VertexIterator it1 = graph.getVertexIterator(n1);
//  OrGraph<std::string>::EdgeIterator it2 = graph.getEdgeIterator(new std::pair(n1,n2));

  OrGraph<std::string>::VertexIterator it1 = graph.begin();
  OrGraph<std::string>::EdgeIterator it2 = graph.EBegin();

  cout << "Вершины графа: ";
  while (it1.hasNext()) {
    ++it1;
    cout << (*it1).content << endl;
  }
  cout << "\n---\n";
  cout << "Рёбра графа: ";
  while (it2.hasNext()) {
    ++it2;
    cout << (*it2).first->content << "-" << (*it2).second->content << endl;
  }
  cout << endl << endl;


  cout << "vertex count: " << graph.getVertexCount() << ", edges count: " << graph.getEdgesCount() << endl;

  cout << "graph is empty: " << (graph.isEmpty() ? "true" : "false") << endl;

  cout << "degree of 'node_1' vertex is " << graph.getVertexDegree(n1) << endl;
  cout << "degree of 'node_2' vertex is " << graph.getVertexDegree(n2) << endl;
  cout << "degree of 'node_3' vertex is " << graph.getVertexDegree(n3) << endl;
  cout << "degree of 'node_4' vertex is " << graph.getVertexDegree(n4) << endl;

  cout << "degree of 'node_1-node_4' edge is " << graph.getEdgeDegree(n1, n4) << endl;
  cout << "degree of 'node_1-node_3' edge is " << graph.getEdgeDegree(n1, n3) << endl;
  cout << "degree of 'node_1-node_12' edge is " << graph.getEdgeDegree(n1, n12) << endl << endl;

  graph.removeVertex(n4);
  graph.removeVertex(n5);
  graph.removeVertex(n6);
  graph.removeVertex(n7);
  cout << "vertexes node_4, node_5, node_6, node_7 was deleted" << endl;

  cout << graph.toString() << endl;

  graph.clear();
  cout << "clear graph" << endl;

  cout << graph.toString() << endl;

  return 0;
}
