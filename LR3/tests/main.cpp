#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <chrono>
#include <cassert>

#include "../src/Graph.cpp"
#include "../src/Edge.cpp"


void msg(const std::string& str) {
  std::cout << str << "...\n";
}

void ok() {
  std::cout << "OK" << std::endl;
} 

void err() { std::cerr << "ERROR" << std::endl;
}

void test_edge_struct() {
  msg("Generationg first edge");
  Edge<int> e (5, 10);
  ok();

  msg("Checking values");
  assert(e.smaller_element() == 5);
  assert(e.bigger_element() == 10);
  ok();

  msg("Generating second edge");
  Edge<int> oe (-22, 0);

  msg("Checking comparison");
  assert(oe < e);
  assert(e > oe);
  assert(e != oe);
  ok();
}

void test_graph_vertices() {
  std::default_random_engine random(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
  const int n = 100;
  typedef UndirectedGraph<std::string, Edge<int>, std::string> graph_type;

  graph_type graph;

  msg("Checking if graph is empty");
  assert(graph.is_empty());
  ok();

  std::vector<std::string> strings;
  strings.reserve(n);

  msg("Inserting " + std::to_string(n) + " values");
  for (int i = 0; i < n; i++) {
    std::string s (std::to_string(random()));
    strings.push_back(s);
    auto e = graph.insert_vertex(i, s);
    assert(e.second);
    assert(s.compare(e.first->second) == 0);
  }
  ok();

  msg("Checking inserted values");
  {
    int i = 0;
    for (auto it = graph.begin_vertices(); it != graph.end_vertices(); it++) {
      assert(strings.at(it->first).compare(it->second) == 0);
      i++;
    }
    assert(i == graph.n_vertices());
  }
  ok();

  msg("Removing vertices");
  for (int i = n / 2; i < n; i++) {
    graph.delete_vertex(i);
  }
  ok();

  msg("Checking removed vertices");
  {
    int i = 0;
    for (auto it = graph.begin_vertices(); it != graph.end_vertices(); it++) {
      assert(strings.at(it->first).compare(it->second) == 0);
      i++;
    }
    assert(i == graph.n_vertices());
    assert(i == n / 2);
  }
  ok();

  msg("Checking clear functions");
  {
    graph.clear();
    assert(graph.n_vertices() == 0);
    assert(graph.n_edges() == 0);
    assert(graph.is_empty());
  }
  ok();
}

void test_graph_edges() {
  std::default_random_engine random(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
  const int n = 100;
  typedef UndirectedGraph<std::string, Edge<int>, std::string> graph_type;
  graph_type graph;

  std::vector<std::string> sv;
  sv.reserve(n);

  msg("Adding vertices");
  for (int i = 0; i < n; i++) {
    std::string s (std::to_string(random()));
    sv.push_back(s);
    auto p = graph.insert_vertex(i, s);
    assert(p.second);
    assert(s.compare(p.first->second) == 0);
  }
  ok();

  std::unordered_map<Edge<int>, std::string> se;

  msg("Adding edges");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        std::string s (std::to_string(random()));
        se.insert(std::make_pair(graph.make_edge_id(i, j), s));
        auto p = graph.insert_edge(i, j, s);
      }
    }
  }
  ok();

  msg("Printing adj matrix");
  for (int i = 0; i < graph.n_vertices(); i++) {
    for (auto it = graph.begin_adj(i); it != graph.end_adj(i); it++) {
      std::cout << *it << " ";
    }
    std::cout << std::endl; 
  }
}


int main() {
  msg("-------[TEST EDGE STRUCT]----");
  test_edge_struct();
  msg("----[TEST GRAPH VERTICES]----");
  test_graph_vertices();
  msg("----[TEST GRAPH EDGES]----");
  test_graph_edges();
}
