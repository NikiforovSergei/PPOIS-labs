#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <utility>


using iterator_category = std::forward_iterator_tag;
using difference_type = std::ptrdiff_t;






template <typename T>
class Graph {
private:
	using vertex_edge  = std::pair<T, T>; //proxy edge for vertex class (because Edge class still not defined)

	class Vertex {	
	public:
		T value;
		std::vector<Vertex> adjacent_vertexes;
		std::vector<vertex_edge> incident_edges;
		Vertex() {

		}
		
		Vertex(T value) {
			this->value = value;
		}		
		Vertex(const Vertex& ref_vertex) {
			this->value = ref_vertex.value;
			this->adjacent_vertexes = ref_vertex.adjacent_vertexes;
			this->incident_edges = ref_vertex.incident_edges;
		}		
		bool operator==(const Vertex& ref_vertex) {
			return this->value == ref_vertex.value;
		}
		bool operator !=(const Vertex& ref_vertex) {
			return this->value != ref_vertex.value;
		}
		void setValue(T value) {
			this->value = value;
		}
		T getValue() {
			return this->value;
		}
		std::vector<Vertex> getAdjacentVertexes() {
			return this->adjacent_vertexes;
		}
		std::vector<vertex_edge> getIncidentEdges() {
			return this->incident_edges;
		}
		void setAdjacentVertexes(std::vector<Vertex> adjacent_vertexes) {
			this->adjacent_vertexes = adjacent_vertexes;
		}
		void addAdjacentVertex(Vertex vertex) {
			this->adjacent_vertexes.push_back(vertex);
		}
		void addAdjacentVertex(T vertex_value) {
			this->adjacent_vertexes.push_back(Node(vertex_value));
		}
		void clearAdjacentVertexes() {
			this->adjacent_vertexes.clear();
		}
		void addIncidentEdge(vertex_edge incident_edge) {
			this->incident_edges.push_back(incident_edge);
		}
		void setIncidentEdges(std::vector<vertex_edge> incident_edges) {
			this->incident_edges = incident_edges;
		}
		void clearIncidentEdges() {
			this->incident_edges.clear();
		}

		friend std::ostream& operator<<(std::ostream& in, const Vertex& vertex) {
			return in << vertex.value;
		}

		//Iterator for incident edges

		using vertex_edge_value_type = vertex_edge;
		using vertex_edge_pointer = vertex_edge*;
		using vertex_edge_reference = vertex_edge&;

		class IncidentEdgeIterator : public std::iterator<iterator_category, vertex_edge_value_type, vertex_edge_pointer, vertex_edge_reference> {
		private:
			vertex_edge_pointer e_ptr;
		public:
			IncidentEdgeIterator(vertex_edge_pointer e_ptr) : e_ptr(e_ptr) {

			}

			vertex_edge_reference operator*() const {
				return *e_ptr;
			}
			vertex_edge_pointer operator->() {
				return e_ptr;
			}

			IncidentEdgeIterator& operator++() {
				e_ptr++;
				return *this;
			}

			IncidentEdgeIterator operator++(int) {
				IncidentEdgeIterator tmp = *this;
				++(*this);
				return tmp;
			}
			IncidentEdgeIterator& operator--() {
				e_ptr--;
				return *this;
			}

			IncidentEdgeIterator operator--(int) {
				IncidentEdgeIterator tmp = *this;
				--(*this);
				return tmp;
			}

			bool operator==(const IncidentEdgeIterator& other)
			{
				return this->e_ptr == other.e_ptr;
			}

			bool operator!=(const IncidentEdgeIterator& other)
			{
				return this->e_ptr != other.e_ptr;
			}
		};

		IncidentEdgeIterator incident_begin() {
			if (!incident_edges.empty()) {
				return IncidentEdgeIterator(&incident_edges[0]);
			}
			else {
				return IncidentEdgeIterator(nullptr);
			}
		}

		IncidentEdgeIterator incident_end() {
			if (!incident_edges.empty()) {
				return IncidentEdgeIterator(&incident_edges[incident_edges.size() - 1] + 1);
			}
			else {
				return IncidentEdgeIterator(nullptr);
			}
		}
		
		using vertex_value_type = Vertex;
		using vertex_pointer = Vertex*;
		using vertex_reference = Vertex&;

		class AdjacentVertexesIterator :public std::iterator<iterator_category, vertex_value_type, vertex_pointer, vertex_reference> {
		private:
			vertex_pointer v_ptr;
		public:
			AdjacentVertexesIterator(vertex_pointer v_ptr) : v_ptr(v_ptr) {

			}

			vertex_reference operator*() {
				return *v_ptr;
			}
			vertex_pointer operator->() {
				return v_ptr;
			}
			AdjacentVertexesIterator& operator++() {
				v_ptr++;
				return *this;
			}
			AdjacentVertexesIterator& operator++(int) {
				AdjacentVertexesIterator tmp = *this;
				v_ptr++;
				return tmp;
			}
			AdjacentVertexesIterator& operator--() {
				v_ptr--;
				return *this;
			}
			AdjacentVertexesIterator& operator--(int) {
				AdjacentVertexesIterator tmp = *this;
				v_ptr--;
				return tmp;
			}
			bool operator==(const AdjacentVertexesIterator& other) {
				return this->v_ptr == other.v_ptr;
			}
			bool operator!=(const AdjacentVertexesIterator& other) {
				return this->v_ptr != other.v_ptr;
			}
			
		};

		AdjacentVertexesIterator adjacent_begin() {
			if (!adjacent_vertexes.empty()) {
				return AdjacentVertexesIterator(&adjacent_vertexes[0]);
			}
			else {
				return AdjacentVertexesIterator(nullptr);
			}
		}

		AdjacentVertexesIterator adjacent_end() {
			if (!adjacent_vertexes.empty()) {
				return AdjacentVertexesIterator(&adjacent_vertexes[adjacent_vertexes.size() - 1] + 1);
			}
			else {
				return AdjacentVertexesIterator(nullptr);
			}
		}

	};

	class Edge {	
	public:
		Vertex out_vertex;
		Vertex to_vertex;

		Edge() {

		}
		Edge(T out_vertex, T to_vertex) {
			this->out_vertex = Vertex(out_vertex);
			this->to_vertex = Vertex(to_vertex);
		}
		/*Edge(Vertex out_vertex, Vertex to_vertex) {
			this->out_vertex = out_vertex;
			this->to_vertex = to_vertex;
		}*/
		Edge(Vertex& out_vertex, Vertex& to_vertex) {
			this->out_vertex = out_vertex;
			this->to_vertex = to_vertex;
		}
		Edge(const Edge& ref_edge) {
			this->to_vertex = ref_edge.to_vertex;
			this->out_vertex = ref_edge.out_vertex;
		}
		Vertex& getOutVertex() {
			return out_vertex;
		}
		Vertex& getToVertex() {
			return to_vertex;
		}
		void setOutVertex(Vertex vertex) {
			this->out_vertex = vertex;
		}
		void setToVertex(Vertex vertex) {
			this->to_vertex = vertex;
		}
		bool operator ==(const Edge& cmp_edge) {
			if ((this->out_vertex == cmp_edge.out_vertex && this->to_vertex == cmp_edge.to_vertex) ||
				(this->to_vertex == cmp_edge.out_vertex && this->out_vertex == cmp_edge.to_vertex)) return true;
			return false;
		}
		bool operator !=(const Edge& cmp_edge) {
			if ((this->out_vertex == cmp_edge.out_vertex && this->to_vertex == cmp_edge.to_vertex) ||
				(this->to_vertex == cmp_edge.out_vertex && this->out_vertex == cmp_edge.to_vertex)) return false;
			return true;
		}
		bool is_vertex_represented_in_edge(Vertex vertex) {
			if (vertex == out_vertex || vertex == to_vertex) return true;
			return false;
		}

		friend std::ostream& operator<<(std::ostream& in, const Edge& edge) {
			return in << edge.out_vertex << "---" << edge.to_vertex;
		}
	};
	std::vector<Vertex> vertex_list;
	std::vector<Edge> edge_container;
	void update_info_about_vertexes() {
		for (Edge edge : edge_container) {
			adjacent_vertexes_for_vertex(edge.to_vertex);
			adjacent_vertexes_for_vertex(edge.out_vertex);
			incident_edges_for_vertex(edge.to_vertex);
			incident_edges_for_vertex(edge.out_vertex);
		}
	}
	void update_vertex_list() {
		vertex_list.clear();
		for (Edge edge : edge_container) {			
			if (std::find(vertex_list.begin(), vertex_list.end(), edge.out_vertex) == vertex_list.end()) vertex_list.push_back(edge.out_vertex);
			if (std::find(vertex_list.begin(), vertex_list.end(), edge.to_vertex) == vertex_list.end()) vertex_list.push_back(edge.out_vertex);
		}		
	}
public:	

	Graph() {
		
	}
	Graph(const Graph& ref_graph) {
		this->edge_container = ref_graph.edge_container;
	}
	~Graph() {

	}
	bool empty() {
		return this->edge_container.empty();
	}
	void clear() {
		edge_container.clear();
	}
	bool is_represented_vertex(T vertex) {
		Vertex proxy(vertex);
		for (Edge edge : edge_container) {
			if (proxy == edge.to_vertex || proxy == edge.out_vertex) return true;
		}
		return false;
	}
	bool is_represented_edge(T out_vertex, T to_vertex) {		
		Edge intrested_edge(out_vertex, to_vertex);
		for (Edge edge : edge_container) {
			if (edge == intrested_edge) return true;
		}
		return false;
	}
	void add_vertex(T vertex) {		
		if (is_represented_vertex(vertex)) {
			std::cout << "Such vertex is already represented in graph!" << std::endl;
			return;
		}
		Vertex new_vertex(vertex);
		Edge new_edge(new_vertex, new_vertex);
		edge_container.push_back(new_edge);
		update_info_about_vertexes();
	}
	void add_edge(T out_vertex, T to_vertex) {
		
		if (is_represented_edge(out_vertex, to_vertex)) {
			std::cout << "Such edge is already represented in graph!" << std::endl;
			return;
		}
		Edge new_edge(out_vertex, to_vertex);
		edge_container.push_back(new_edge);
		update_info_about_vertexes();
	}
	void delete_edge(T out_vertex, T to_vertex) {
		
		if (!is_represented_edge(out_vertex, to_vertex)) {
			std::cout << "Such edge isn't represented in graph!" << std::endl;
			return;
		}
		auto graph_it = edge_container.begin();
		while (graph_it != edge_container.end()) {
			Edge deleted_edge(out_vertex, to_vertex);
			if (deleted_edge == (*graph_it)) {
				edge_container.erase(graph_it);
				return;
			}
			else {
				graph_it++;
			}			
		}
		update_info_about_vertexes();
	}
	void delete_vertex(T vertex) {
		
		if (!is_represented_vertex(vertex)) {
			std::cout << "Such vertex isn't represented in graph!" << std::endl;
			return;
		}
		for (Edge edge : edge_container) {
			if (edge.is_vertex_represented_in_edge(Vertex(vertex))) {
				const auto logical_end = std::remove(edge_container.begin(), edge_container.end(), edge);
				edge_container.erase(logical_end, edge_container.end());
			}			
		}		
		update_info_about_vertexes();
	}	
	int edge_amount() {
		return edge_container.size();
	}
	int vertex_amount() {
		update_vertex_list();
		return vertex_list.size();
	}
	int vertex_degree(T vertex) {		
		if (!is_represented_vertex(vertex)) {
			std::cout << "Such vertex isn't represented in graph!" << std::endl;
			return NULL;
		}
		int degree = 0;
		for (Edge edge : edge_container) {
			if (edge.is_vertex_represented_in_edge(vertex)) degree++;
		}
		return degree;
	}
	bool operator ==(const Graph& cmp_graph) {
		if (edge_container.size != cmp_graph.edge_container.size()) return false;
		for (Edge edge : this->edge_container) {
			bool edge_represented_in_cmp_graph = false;
			for (Edge cmp_edge : cmp_graph.edge_container) {
				if (edge == cmp_edge) {
					edge_represented_in_cmp_graph = true;
					break;
				}
			}
			if (!edge_represented_in_cmp_graph) return false;
		}
		return true;
	}
	void adjacent_vertexes_for_vertex(Vertex& vertex) {		
		vertex.clearAdjacentVertexes();		
		for (Edge edge : edge_container) {
			if (vertex == edge.out_vertex) vertex.addAdjacentVertex(edge.to_vertex);
			else if (vertex == edge.to_vertex) vertex.addAdjacentVertex(edge.out_vertex);
		}
	}

	void incident_edges_for_vertex(Vertex& vertex) {
		vertex.clearIncidentEdges();		
		for (Edge edge : edge_container) {
			if (vertex == edge.out_vertex || vertex == edge.to_vertex) {
				vertex.addIncidentEdge(vertex_edge(edge.out_vertex.value, edge.to_vertex.value));
			}
		}
	}

	void print_adj_vertexes() {		
		update_vertex_list();
		std::cout << "-----Adjacent vertexes-----" << std::endl;		
		for (auto vertex : vertex_list) {
			adjacent_vertexes_for_vertex(vertex);
			std::cout << vertex << ": ";
			auto adj_it = vertex.adjacent_begin();
			while (adj_it != vertex.adjacent_end()) {
				std::cout << *adj_it << "; ";
				adj_it++;
			}			
			std::cout << std::endl;
		}
	}

	void print_inc_edges() {
		update_vertex_list();
		std::cout << "-----Incident edges-----" << std::endl;
		for (auto vertex : vertex_list) {
			incident_edges_for_vertex(vertex);
			std::cout << vertex << ": ";
			auto inc_it = vertex.incident_begin();
			while (inc_it != vertex.incident_end()) {
				std::cout << inc_it->first << "---" << inc_it->second << "; ";
				inc_it++;
			}
			std::cout << std::endl;			
		}
	}

	bool operator !=(const Graph& cmp_graph) {
		return !( *this == cmp_graph );
	}
	bool operator <=(const Graph& cmp_graph) {
		return edge_container.size() <= cmp_graph.edge_container.size();
	}
	bool operator >=(const Graph& cmp_graph) {
		return edge_container.size() >= cmp_graph.edge_container.size();
	}
	bool operator <(const Graph& cmp_graph) {
		return edge_container.size() < cmp_graph.edge_container.size();
	}
	bool operator >(const Graph& cmp_graph) {
		return edge_container.size() > cmp_graph.edge_container.size();
	}
	friend std::ostream& operator <<(std::ostream& in, Graph& graph) {
		if (!graph.edge_container.empty()) {			
			in << "-----VERTEXES-----" << std::endl;
			for (auto it = graph.vertex_begin(); it != graph.vertex_end(); it++) {
				in << *it << std::endl;
			}
			in << "-----EDGES--------" << std::endl;
			for (auto it = graph.edge_begin(); it != graph.edge_end(); it++) {
				in << *it << std::endl;
			}
		}
		return in;
	}	

	using edge_value_type = Edge;
	using edge_pointer = edge_value_type*;
	using edge_reference = edge_value_type&;

	//Iterator for edges

	

	//Forward iterator

	class EdgeIterator : public std::iterator<iterator_category, edge_value_type, edge_pointer, edge_reference> {
	private:
		edge_pointer e_ptr;
	public:
		EdgeIterator(edge_pointer e_ptr) : e_ptr(e_ptr) {

		}

		edge_reference operator*() const {
			return *e_ptr;
		}
		edge_pointer operator->() {
			return e_ptr;
		}

		EdgeIterator& operator++() {
			e_ptr++;
			return *this;
		}

		EdgeIterator operator++(int) {
			EdgeIterator tmp = *this;
			++(*this);
			return tmp;
		}
		EdgeIterator& operator--() {
			e_ptr--;
			return *this;
		}

		EdgeIterator operator--(int) {
			EdgeIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const EdgeIterator& other)
		{
			return this->e_ptr == other.e_ptr;
		}

		bool operator!=(const EdgeIterator& other)
		{
			return this->e_ptr != other.e_ptr;
		}
	};

	EdgeIterator edge_begin() {
		if (!edge_container.empty()) {
			return EdgeIterator(&edge_container[0]);
		}
		else {
			return EdgeIterator(nullptr);
		}
	}

	EdgeIterator edge_end() {
		if (!edge_container.empty()) {
			return EdgeIterator(&edge_container[edge_container.size() - 1] + 1);
		}
		else {
			return EdgeIterator(nullptr);
		}
	}

	//Backward iterator

	class ReverseEdgeIterator : public std::iterator<iterator_category, edge_value_type, edge_pointer, edge_reference> {
	private:
		edge_pointer e_ptr;
	public:
		ReverseEdgeIterator(edge_pointer e_ptr) : e_ptr(e_ptr) {

		}

		edge_reference operator*() const {
			return *e_ptr;
		}
		edge_pointer operator->() {
			return e_ptr;
		}

		ReverseEdgeIterator& operator++() {
			e_ptr--;
			return *this;
		}

		ReverseEdgeIterator operator++(int) {
			ReverseEdgeIterator tmp = *this;
			--(*this);
			return tmp;
		}
		ReverseEdgeIterator& operator--() {
			e_ptr++;
			return *this;
		}

		ReverseEdgeIterator operator--(int) {
			ReverseEdgeIterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const ReverseEdgeIterator& other)
		{
			return this->e_ptr == other.e_ptr;
		}

		bool operator!=(const ReverseEdgeIterator& other)
		{
			return this->e_ptr != other.e_ptr;
		}
	};

	ReverseEdgeIterator reverse_edge_begin() {
		if (!edge_container.empty()) {
			return ReverseEdgeIterator(&edge_container[edge_container.size() - 1]);
		}
		else {
			return ReverseEdgeIterator(nullptr);
		}
	}

	ReverseEdgeIterator reverse_edge_end() {
		if (!edge_container.empty()) {
			return ReverseEdgeIterator(&edge_container[0] - 1);
		}
		else {
			return ReverseEdgeIterator(nullptr);
		}
	}



	//Iterator for vertex

	//Forward iterator

	using vertex_value_type = Vertex;
	using vertex_pointer = Vertex*;
	using vertex_reference = Vertex&;

	class VertexIterator : public std::iterator<iterator_category, vertex_value_type, vertex_pointer, vertex_reference> {
	private:
		vertex_pointer v_ptr;
	public:
		VertexIterator(vertex_pointer v_ptr) : v_ptr(v_ptr) {

		}
		vertex_reference operator*() {
			return *v_ptr;
		}
		vertex_pointer operator->() {
			return v_ptr;
		}
		VertexIterator& operator++() {
			v_ptr++;
			return *this;
		}

		VertexIterator operator++(int) {
			VertexIterator tmp = *this;
			++(*this);
			return tmp;
		}
		VertexIterator& operator--() {
			v_ptr--;
			return *this;
		}

		VertexIterator operator--(int) {
			VertexIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const VertexIterator& other)
		{
			return this->v_ptr == other.v_ptr;
		}

		bool operator!=(const VertexIterator& other)
		{
			return this->v_ptr != other.v_ptr;
		}
	};

	VertexIterator vertex_begin() {
		update_vertex_list();
		if (!vertex_list.empty()) {
			return VertexIterator(&vertex_list[0]);
		}
		else {
			VertexIterator(nullptr);
		}
	}

	VertexIterator vertex_end() {		
		if (!vertex_list.empty()) {
			return VertexIterator(&vertex_list[vertex_list.size() - 1] + 1);
		}
		else {
			return VertexIterator(nullptr);
		}
	}

	//Backward iterator

	class ReverseVertexIterator : public std::iterator<iterator_category, vertex_value_type, vertex_pointer, vertex_reference> {
	private:
		vertex_pointer v_ptr;
	public:
		ReverseVertexIterator(vertex_pointer v_ptr) : v_ptr(v_ptr) {

		}
		vertex_reference operator*() {
			return *v_ptr;
		}
		vertex_pointer operator->() {
			return v_ptr;
		}
		ReverseVertexIterator& operator++() {
			v_ptr--;
			return *this;
		}

		ReverseVertexIterator operator++(int) {
			ReverseVertexIterator tmp = *this;
			--(*this);
			return tmp;
		}
		ReverseVertexIterator& operator--() {
			v_ptr++;
			return *this;
		}

		ReverseVertexIterator operator--(int) {
			ReverseVertexIterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator==(const ReverseVertexIterator& other)
		{
			return this->v_ptr == other.v_ptr;
		}

		bool operator!=(const ReverseVertexIterator& other)
		{
			return this->v_ptr != other.v_ptr;
		}
	};

	ReverseVertexIterator reverse_vertex_begin() {
		update_vertex_list();
		if (!vertex_list.empty()) {
			return ReverseVertexIterator(&vertex_list[vertex_list.size() - 1]);
		}
		else {
			return ReverseVertexIterator(nullptr);
		}
	}

	ReverseVertexIterator reverse_vertex_end() {		
		if (!vertex_list.empty()) {
			return ReverseVertexIterator(&vertex_list[vertex_list.size() - 1]);
		}
		else {
			return ReverseVertexIterator(nullptr);
		}
	}

};