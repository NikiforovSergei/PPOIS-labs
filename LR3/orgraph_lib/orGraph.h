#pragma once

#include <algorithm>
#include <vector>
#include <sstream>

#include "../matrix_lib/Matrix.h"




template<class ContentType>
class OrGraph {

 public:

  class Vertex {
   public:
    ContentType content;
    OrGraph *parent;

    explicit Vertex(ContentType content);

    inline bool operator==(const Vertex &other) const {
      return this->content == other.content;
    }
    inline bool operator!=(const Vertex &other) const {
      return this->content != other.content;
    }
  };

  class VertexIterator {
   public:

    typedef Vertex *pointer;
    typedef Vertex &reference;

    explicit VertexIterator(pointer node) : node(node), index(0) {}
    VertexIterator(const VertexIterator &it) : node(it.node), index(0) {}

    bool hasNext() {
      if (index < node->parent->vertexes.size()) {
        return true;
      } else
        return false;
    }
//    VertexIterator next() {
//      return VertexIterator(node->parent->vertexes[++index]);
//    }

    VertexIterator &operator=(const VertexIterator &iterator) {
      node = iterator.node;
      return *this;
    }

    reference operator*() const {
      return *node;
    }
    pointer operator->() const {
      return node;
    }

    VertexIterator &operator++() {
      node = node->parent->vertexes[index];
      index++;
      return *this;
    }

    bool operator!=(VertexIterator const &other) const {
      return node != other.node;
    }
    bool operator==(VertexIterator const &other) const {
      return node == other.node;
    }
    friend bool operator==(const VertexIterator &it1, const VertexIterator &it2) {
      return it1.node == it2.node;
    }

    friend bool operator!=(const VertexIterator &it1, const VertexIterator &it2) {
      return it1.node != it2.node;
    }

   private:
    pointer node;
    int index;

  };

  class constVertexIterator {
   public:

    typedef Vertex *pointer;
    typedef Vertex &reference;

    explicit constVertexIterator(pointer node) : node(node), index(0) {}
    constVertexIterator(const constVertexIterator &it) : node(it.node), index(0) {}

    bool hasNext() {
      if (index < node->parent->vertexes.size() - 1) {
        return true;
      } else
        return false;
    }
//    }
//    constVertexIterator next() {
//      return constVertexIterator(node->parent->vertexes[++index]);
//    }

    constVertexIterator &operator=(const constVertexIterator &iterator) {
      node = iterator.node;
      return *this;
    }

    reference operator*() const {
      return *node;
    }
    pointer operator->() const {
      return node;
    }

    constVertexIterator &operator++() {
      node = node->parent->vertexes[index];
      index++;
      return *this;
    }

    bool operator!=(constVertexIterator const &other) const {
      return node != other.p;
    }
    bool operator==(constVertexIterator const &other) const {
      return node == other.p;
    }
    friend bool operator==(const constVertexIterator &it1, const constVertexIterator &it2) {
      return it1.node == it2.node;
    }

    friend bool operator!=(const constVertexIterator &it1, const constVertexIterator &it2) {
      return it1.node != it2.node;
    }

   private:
    pointer node;
    int index;

  };

  class EdgeIterator  {
   public:

    friend class OrGraph;
    typedef std::pair<typename OrGraph<ContentType>::Vertex *, typename OrGraph<ContentType>::Vertex *> Edge;
//    typedef std::pair<Vertex *, Vertex *> Edge;
    typedef Edge *pointer;
    typedef Edge &reference;

    explicit EdgeIterator(pointer node) : node(node), index(0) {}
    EdgeIterator(const EdgeIterator &it) : node(it.node), index(0) {}

    bool hasNext() {
      if (index < node->first->parent->getEdges().size()) {
        return true;
      } else
        return false;
    }
//    EdgeIterator next() {
//      return EdgeIterator((node->first->parent->getEdges()[++index]));
//    }

    EdgeIterator &operator=(const EdgeIterator &iterator) {
      node = iterator.node;
      return *this;
    }

    bool operator!=(EdgeIterator const &other) const {
      return node != other.node;;
    }
    bool operator==(EdgeIterator const &other) const {
      return node == other.node;;
    }
    reference operator*() const {
      return *node;
    }
    pointer operator->() const {
      return node;
    }
    EdgeIterator &operator++() {
      node = (node->first->parent->getEdges()[index]);
      ++index;
      return *this;
    }

   private:
    pointer node;
    int index;
  };

  class constEdgeIterator {
   public:

    friend class OrGraph;
    typedef std::pair<typename OrGraph<ContentType>::Vertex *, typename OrGraph<ContentType>::Vertex *> Edge;
    typedef Edge *pointer;
    typedef Edge &reference;

    explicit constEdgeIterator(pointer node) : node(node), index(0) {}
    constEdgeIterator(const EdgeIterator &it) : node(it.node), index(0) {}

    bool hasNext() {
      if (index < node->first->parent->getEdges()->size()) {
        return true;
      } else
        return false;
    }
//    EdgeIterator next() {
//      return EdgeIterator((node->first->parent->getEdges()[++index]));
//    }

    constEdgeIterator &operator=(const constEdgeIterator &iterator) {
      node = iterator.node;
      return *this;
    }

    bool operator!=(constEdgeIterator const &other) const {
      return node != other.node;;
    }
    bool operator==(constEdgeIterator const &other) const {
      return node == other.node;;
    }
    reference operator*() const {
      return *node;
    }
    pointer operator->() const {
      return node;
    }
    constEdgeIterator &operator++() {
      node = node->first->parent->getEdges()[++index];
      return *this;
    }

   private:
    pointer node;
    int index;
  };

  VertexIterator begin() {
    return VertexIterator((vertexes.empty() ? nullptr : vertexes[0]));
  }

  VertexIterator end() {
    return VertexIterator(nullptr);
  }

  constVertexIterator Cbegin() const {
    return ConstNodeIterator((vertexes.empty() ? nullptr : vertexes[0]));
  }

  constVertexIterator Cend() const {
    return constVertexIterator(nullptr);
  }

  EdgeIterator EBegin() {
    return EdgeIterator((getEdges().empty() ? nullptr : getEdges()[0]));
  }

  EdgeIterator EEnd() {
    return EdgeIterator(nullptr);
  }

  constEdgeIterator CEBegin() const {
    return ConstRibIterator((getEdges()->empty() ? nullptr : getEdges()[0]));
  }

  constEdgeIterator CEEnd() const {
    return constEdgeIterator(nullptr);
  }

  typedef std::pair<typename OrGraph<ContentType>::Vertex *, typename OrGraph<ContentType>::Vertex *> Edge;

  friend class Iterator;

  OrGraph();

  OrGraph(const OrGraph<ContentType> &graph);

  bool isExists(Vertex *vertex);

  bool isExists(Vertex *from, Vertex *to);

  bool isEmpty();

  void clear();

  int getVertexCount();

  int getEdgesCount();

  int getVertexDegree(Vertex *vertex);

  int getEdgeDegree(Vertex *from, Vertex *to);

  void addVertex(Vertex *vertex);

  void addEdge(Vertex *from, Vertex *to);

  void removeVertex(Vertex *vertex);

  void removeEdge(Vertex *from, Vertex *to);

  std::vector<std::pair<Vertex *, Vertex *> *> getEdges();

  std::string toString();

//  std::vector<Vertex> *getNearbyVertexes(Vertex *vertex);

  VertexIterator getVertexIterator(Vertex *vertex) {
    return VertexIterator(vertex);
  }

  EdgeIterator getEdgeIterator(Edge *edge) {
    return EdgeIterator(edge);
  }

 private:
  // rows - vertex
  // columns - edges
  std::vector<Vertex *> vertexes;
  Matrix matrix;

  void addIfNotExists(Vertex *vertex);

  int getVertexNumber(Vertex *vertex);

  int getEdgeNumber(Vertex *from, Vertex *to);

  void makeEdge(Vertex *from, Vertex *to);

  bool isVertexesInvolved(Vertex *from, Vertex *to);

  void removeEdgeFromMatrix(int edgeNumber);

  void removeVertexFromMatrix(int vertexNumber);

  void removeVertexFromVertexList(Vertex *vertex);

  void removeIncidenceEdges(Vertex *vertex);
};

template<class ContentType>
OrGraph<ContentType>::OrGraph() = default;

template<class ContentType>
OrGraph<ContentType>::OrGraph(const OrGraph &graph) {
  this->matrix = graph.matrix;
  this->vertexes = graph.vertexes;
}

template<class ContentType>
OrGraph<ContentType>::Vertex::Vertex(ContentType content) : content(content) {}

template<class ContentType>
bool OrGraph<ContentType>::isExists(Vertex *vertex) {
  return std::any_of(vertexes.begin(), vertexes.end(),
                     [vertex](const Vertex *v) { return vertex == v; });
}

template<class ContentType>
bool OrGraph<ContentType>::isExists(Vertex *from, Vertex *to) {
  bool isFromExists = isExists(from);
  bool isToExists = isExists(to);
  bool isVertexesAlreadyInvolved = isVertexesInvolved(from, to);

  return isFromExists && isToExists && isVertexesAlreadyInvolved;
}

template<class ContentType>
bool OrGraph<ContentType>::isVertexesInvolved(Vertex *from, Vertex *to) {
  std::vector<int> v1 = matrix.getRow(getVertexNumber(from));
  std::vector<int> v2 = matrix.getRow(getVertexNumber(to));

  for (int i = 0; i < v1.size(); i++) {
    for (int j = 0; j < v2.size(); j++) {
      if (i == j && v1[i] == 1 && v2[j] == -1) {
        return true;
      }
    }
  }
  return false;
}

template<class ContentType>
bool OrGraph<ContentType>::isEmpty() {
  return matrix.getRows() == 0;
}

template<class ContentType>
void OrGraph<ContentType>::clear() {
  matrix.clear();
  vertexes.clear();

}



// template <class ContentType>
// OrGraph<ContentType>::~OrGraph() {
//   delete matrix;
// }

template<class ContentType>
int OrGraph<ContentType>::getVertexCount() {
  return matrix.getRows();
}

template<class ContentType>
int OrGraph<ContentType>::getEdgesCount() {
  return matrix.getColumns();

}

template<class ContentType>
void OrGraph<ContentType>::addVertex(Vertex *vertex) {
  return addIfNotExists(vertex);
}

template<class ContentType>
void OrGraph<ContentType>::addEdge(Vertex *from, Vertex *to) {
  addIfNotExists(from);
  addIfNotExists(to);
  makeEdge(from, to);
}

template<class ContentType>
void OrGraph<ContentType>::makeEdge(Vertex *from, Vertex *to) {
  if (!isExists(from, to)) {
    int fromSeqNumber = getVertexNumber(from);
    int toSeqNumber = getVertexNumber(to);

    matrix.addColumns();
    matrix.setValue(fromSeqNumber, matrix.getColumns() - 1, 1);
    matrix.setValue(toSeqNumber, matrix.getColumns() - 1, -1);
  }
}

template<class ContentType>
int OrGraph<ContentType>::getVertexNumber(Vertex *vertex) {
  int sequenceNumber = 0;
  for (const auto &v : vertexes) {
    if (v == vertex) {
      break;
    }
    sequenceNumber++;
  }
  // throw
  return sequenceNumber;
}

template<class ContentType>
void OrGraph<ContentType>::addIfNotExists(Vertex *vertex) {
  if (!isExists(vertex)) {
    this->matrix.addRows();
    this->vertexes.push_back(vertex);
    vertex->parent = this;
  }
}

template<class ContentType>
int OrGraph<ContentType>::getVertexDegree(Vertex *vertex) {
  int count = 0;
  for (const auto &i : matrix.getRow(getVertexNumber(vertex))) {
    if (i == 1 || i == -1)
      count++;
  }
  return count;
}

template<class ContentType>
int OrGraph<ContentType>::getEdgeNumber(Vertex *from, Vertex *to) {
  std::vector<int> v1 = matrix.getRow(getVertexNumber(from));
  std::vector<int> v2 = matrix.getRow(getVertexNumber(to));

  for (int i = 0; i < v1.size(); i++) {
    for (int j = 0; j < v2.size(); j++) {
      if (i == j && v1[i] == 1 && v2[j] == -1) {
        return i;
      }
    }
  }
  return -1;
}

template<class ContentType>
int OrGraph<ContentType>::getEdgeDegree(Vertex *from, Vertex *to) {
  int count = 0;
  if (isVertexesInvolved(from, to)) {
    for (auto i : *matrix.getColumn(getEdgeNumber(from, to))) {
      if (i == 1 || i == -1)
        count++;
    }
  }
  // throw
  return count;
}

template<class ContentType>
std::string OrGraph<ContentType>::toString() {
  std::stringstream ss;
  int v;

  if (matrix.getRows() > 0 && matrix.getColumns() > 0)
    for (int i = 0; i < matrix.getRows(); i++) {
      for (int j = 0; j < matrix.getColumns(); j++) {
        v = matrix.getValue(i, j);
        if (v == -1)
          ss << v << " ";
        else
          ss << " " << v << " ";
      }
      ss << "   v" << i + 1 << ":" << (*vertexes[i]).content;
      ss << std::endl;
    }
  else {
    ss << "matrix is empty" << std::endl;
  }
  return ss.str();
}

template<class ContentType>
void OrGraph<ContentType>::removeEdge(Vertex *from, Vertex *to) {
  if (isExists(from, to)) {
    removeEdgeFromMatrix(getEdgeNumber(from, to));
  }
}

template<class ContentType>
void OrGraph<ContentType>::removeVertex(Vertex *vertex) {
  if (isExists(vertex)) {
    removeIncidenceEdges(vertex);
    removeVertexFromMatrix(getVertexNumber(vertex));
    removeVertexFromVertexList(vertex);
  }
}

template<class ContentType>
void OrGraph<ContentType>::removeVertexFromMatrix(int vertexNumber) {
  matrix.removeRows(vertexNumber);
}

template<class ContentType>
void OrGraph<ContentType>::removeVertexFromVertexList(Vertex *vertex) {
  vertexes.erase(vertexes.begin() + getVertexNumber(vertex));
}

template<class ContentType>
void OrGraph<ContentType>::removeEdgeFromMatrix(int edgeNumber) {
  matrix.removeColumns(edgeNumber);
}

template<class ContentType>
void OrGraph<ContentType>::removeIncidenceEdges(Vertex *vertex) {
  std::vector<int> row = matrix.getRow(getVertexNumber(vertex));
  int indexToRemove = 0;
  for (int i = 0; i < row.size(); i++, indexToRemove++) {
    if (row[i] != 0) {
      matrix.removeColumns(indexToRemove);
      indexToRemove--;
    }
  }
}
//template<class ContentType>
//std::vector<OrGraph<ContentType>::Vertex*> *OrGraph<ContentType>::getNearbyVertexes(OrGraph::Vertex *vertex) {
//
//  auto *result = new std::vector<ContentType>();
//
//  int vertexNumber = getVertexNumber(vertex);
//
//  for (int i = 0; i < matrix.getColumns(); i++) {
//    if (matrix.getValue(vertexNumber, i) == 1)
//      for (int j = 0; j < matrix.getRows(); j++) {
//        if (matrix.getValue(j, i) == -1) {
//          result->push_back(vertexes[j]);
//        }
//      }
//  }
//  return result;
//}

template<class ContentType>
std::vector<std::pair<typename OrGraph<ContentType>::Vertex *, typename OrGraph<ContentType>::Vertex *> *> OrGraph<ContentType>::getEdges() {

  std::vector<std::pair<typename OrGraph<ContentType>::Vertex *, typename OrGraph<ContentType>::Vertex *> *> result;

  for (const auto i : vertexes) {
    for (const auto j : vertexes) {
      if (isExists(i, j))
        result.push_back(new std::pair(i, j));
    }
  }
  return result;
}
