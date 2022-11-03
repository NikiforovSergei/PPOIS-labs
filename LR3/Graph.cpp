
#include <unordered_map>
#include <vector>

template<class VertexType, class EdgeType>
class Graph {
public:
  typedef int VertexKey;
  typedef int EdgeKey;
  typedef VertexType VertexValue;
  typedef EdgeType EdgeValue;
private:
  typedef std::unordered_map<VertexKey, VertexValue> VertexCollection;
  typedef std::unordered_map<EdgeKey, EdgeValue> EdgesCollection;
  typedef std::vector<EdgeKey> SortedEdgesKeys;
  typedef std::unordered_map<VertexKey, SortedEdgesKeys> AdjCollection;

  VertexCollection vertices;
  EdgesCollection edges;
  AdjCollection adj;
public:
  typedef typename VertexCollection::iterator VertexIterator;
  typedef typename EdgesCollection::iterator EdgeIterator;
  typedef typename AdjCollection::iterator AdjIterator;

  Graph<VertexType, EdgeType>() = default;
  ~Graph<VertexType, EdgeType>() {
    clearGraph();
  }
  
  bool isEmpty() { return vertices.empty(); }
  int verticesSize() { return vertices.size(); }
  int edgesSize() { return edges.size(); }

  VertexIterator verticesBegin() { return vertices.begin(); }
  EdgeIterator edgesBegin() { return edges.begin(); }
  AdjIterator adjBegin() { return adj.begin(); }

  VertexIterator verticesEnd() { return vertices.end(); }
  EdgeIterator edgesEnd() { return edges.end(); }
  AdjIterator adjEnd() { return adj.end(); }

  VertexValue atVertices(VertexKey id) { return vertices.at(id); }
  EdgeValue atEdges(EdgeKey id) { return edges.at(id); }

  void clearGraph() {
    vertices.clear();
    edges.clear();
    adj.clear();
  }
  
  std::pair<VertexIterator, bool> insertVertex(VertexKey id, VertexValue data) {
    std::pair<VertexIterator, bool> p = vertices.emplace(id, data);
    adj.emplace(id, SortedEdgesKeys());
    return p;
  }

  std::pair<EdgeIterator, bool> insertEdge(VertexKey v1, VertexKey v2, EdgeValue data) {
    if (vertices.count(v1) == 0 || vertices.count(v2) == 0) {
      return std::make_pair(edges.end(), false);
    }
    
    EdgeKey edgeId = makeEdgeId(v1, v2);
    std::pair<EdgeIterator, bool> p = edges.emplace(edgeId, data);
    
    if (p.second) {
      adj[v1].push_back(edgeId);
      adj[v2].push_back(edgeId);
    } 

    return p;
  }

  bool deleteVertex(VertexKey id) {
    int deleted = vertices.erase(id);
    adj.erase(id);

    if (deleted == 0) {
      return false;
    }
    
    for (int i = 0; i < adj.size(); i++) {
      EdgeKey needToDelete = makeEdgeId(id, i);
      for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
        if (*it == needToDelete) {
            edges.erase(needToDelete);
            adj[i].erase(it);
        }
      }
    }

    return true;
  }

  bool deleteEdge(VertexKey v1, VertexKey v2) {
    if (vertices.count(v1) == 0 || vertices.count(v2) == 0) {
      return false;
    }

    EdgeKey needToDelete = makeEdgeId(v1, v2);

    edges.erase(needToDelete);

    for (int i = 0; i < adj.size(); i++) {
      for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
        if (*it == needToDelete) {
          adj[i].erase(it);
        }
      }
    }

    return true;
  }

  EdgeKey makeEdgeId(VertexKey v1, VertexKey v2) {
    return std::hash<VertexKey>()(v1) ^ (std::hash<VertexKey>()(v2) << 1);
  }
};
