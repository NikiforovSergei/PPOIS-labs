// Implemented by @kitanoyoru

#ifndef __KITA_GRAPH__
#define __KITA_GRAPH__

#include <cstddef>
#include <utility>
#include <forward_list>
#include <vector>
#include <unordered_map>

template<class TV, class TE>
class UndirectedGraph {
public:
  typedef size_t vertex_id_type;
  typedef size_t edge_id_type;
  typedef TV vertex_data_type;
  typedef TE edge_data_type;
private:
  typedef UndirectedGraph<vertex_data_type, edge_data_type> graph_type;
  typedef std::unordered_map<vertex_id_type, vertex_data_type> vertex_container;
  typedef std::unordered_map<edge_id_type, edge_data_type> edge_container;
  typedef std::vector<size_t> adj_list; // 0 1 1 0 1 ...
  typedef std::unordered_map<vertex_id_type, adj_list> adj_container;

  vertex_container vertices;
  edge_container edges;
  adj_container adj;  // adj matrix
public:
  typedef typename vertex_container::iterator graph_vertex_iterator;
  typedef typename vertex_container::const_iterator graph_vertex_const_iterator;
  typedef typename edge_container::iterator graph_edge_iterator;
  typedef typename edge_container::const_iterator graph_edge_const_iterator;
  typedef typename adj_list::iterator graph_adj_iterator;
  typedef typename adj_list::const_iterator graph_adj_const_iterator;

  bool is_empty() const;
  
  size_t n_vertices() const;
  size_t n_edges() const;
  
  vertex_data_type& at_vertex(const vertex_id_type& id);
  const vertex_data_type& at_vertex(const vertex_id_type& id) const;
  edge_data_type& at_edge(const edge_id_type& id);
  const edge_data_type& at_edge(const edge_id_type& id) const;
  
  graph_vertex_iterator find_vertex(const vertex_id_type& id);
  graph_vertex_const_iterator find_vertex(const vertex_id_type& id) const;
  graph_edge_iterator find_edge(const edge_id_type& id);
  graph_edge_const_iterator find_edge(const edge_id_type& id) const;
  
  graph_vertex_iterator begin_vertices();
  graph_vertex_const_iterator begin_vertices() const;
  graph_edge_iterator begin_edges();
  graph_edge_const_iterator begin_edges() const;

  graph_vertex_iterator end_vertices();
  graph_vertex_const_iterator end_vertices() const;
  graph_edge_iterator end_edges();
  graph_edge_const_iterator end_edges() const;
  graph_adj_iterator begin_adj(const vertex_id_type& vertex_id);
  graph_adj_const_iterator begin_adj(const vertex_id_type& vertex_id) const;
  graph_adj_iterator end_adj(const vertex_id_type& vertex_id);
  graph_adj_const_iterator end_adj(const vertex_id_type& vertex_id) const;

  void clear();

  bool insert_vertex(const vertex_id_type& vertex_id, const vertex_data_type& vertex_data);
  bool delete_vertex(const vertex_id_type& vertex_id);  
  
  bool insert_edge(const vertex_id_type& v1, const vertex_id_type& v2, edge_data_type& data);
};

#endif
