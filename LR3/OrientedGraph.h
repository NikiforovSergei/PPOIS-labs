#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <memory> 


typedef std::forward_iterator_tag iterator_category;
typedef ptrdiff_t difference_type;
typedef int id_value_type;
typedef id_value_type* id_pointer;
typedef id_value_type& id_reference;

template <typename T> 
class oriented_graph
{
private:

	class Node
	{
	public:
		int nodeID;
		T info;
		std::vector<int> incedentEdges;
		std::vector<int> adjNodes;
		Node() {};
		Node(int nodeID, T info)
		{
			this->nodeID = nodeID;
			this->info = info;
		}

		//iterator for incedentEdges and adjNodes

		

		class IDIterator :public std::iterator<iterator_category, id_value_type, id_pointer, id_reference>
		{

		private:
			id_pointer ptr_ID;
		public:

			IDIterator(id_pointer int_value) :ptr_ID(int_value) {}

			id_reference operator*() const
			{
				return *ptr_ID;
			}

			id_pointer operator->()
			{
				return ptr_ID;
			}

			IDIterator& operator++()
			{
				ptr_ID++;
				return *this;
			}

			IDIterator operator++(int)
			{
				IDIterator tmp = *this;
				++(*this);
				return tmp;
			}

			IDIterator& operator--()
			{
				ptr_ID--;
				return *this;
			}

			IDIterator operator--(int)
			{
				IDIterator tmp = *this;
				--(*this);
				return tmp;
			}

			bool operator==(const IDIterator& other)
			{
				return this->ptr_ID == other.ptr_ID;
			}

			bool operator!=(const IDIterator& other)
			{
				return this->ptr_ID != other.ptr_ID;
			}

		};

		IDIterator inc_edges_begin()
		{
			return IDIterator(&incedentEdges[0]);
		}

		IDIterator inc_edges_end()
		{
			return IDIterator(&incedentEdges[incedentEdges.size() - 1] + 1);
		}

		IDIterator adj_nodes_begin()
		{
			return IDIterator(&adjNodes[0]);
		}

		IDIterator adj_nodes_end()
		{
			return IDIterator(&adjNodes[adjNodes.size()-1]+1);
		}
	};

	class Edge
	{
	public:
		int fromID;
		int toID;
		int edgeID;
		Edge() {};
		Edge(int fromID, int toID, int edgeID)
		{
			this->fromID = fromID;
			this->toID = toID;
			this->edgeID = edgeID;
		}
	};

	std::vector<Node> nodes;
	std::vector<Edge> edges;
	int numberOfNodes, numberOfEdges;

	//methods to create graph from file

	void FindIncedentEdgesToNode(int nodeID)
	{
		IsNodeExist(nodeID);
		Node* pNode = NULL;
		for (auto node : nodes)
		{
			if (node.nodeID == nodeID)
				pNode = &node;
		}
		pNode->incedentEdges.clear();
		for (auto edge : edges)
		{
			if (edge.fromID == pNode->nodeID)
				pNode->incedentEdges.push_back(edge.edgeID);
		}
	}

	void FindAdjNodes(int nodeID)
	{
		Node* pNode = NULL;
		for (auto node : nodes)
		{
			if (node.nodeID == nodeID)
			{
				pNode = &node;
				break;
			}
		}
		pNode->adjNodes.clear();
		for (auto edge : edges)
		{
			if (edge.fromID == pNode->nodeID)
				pNode->adjNodes.push_back(edge.toID);
		}
	}

	void FindIncedentEdgesToNode(Node& node)
	{
		node.incedentEdges.clear();
		for (auto edge : edges)
		{
			if (edge.fromID == node.nodeID)
				node.incedentEdges.push_back(edge.edgeID);
		}
	}

	void FindAdjNodes(Node& node)
	{
		node.adjNodes.clear();
		for (auto edge : edges)
		{
			if (edge.fromID == node.nodeID)
				node.adjNodes.push_back(edge.toID);
		}
	}

	void AddEdge(int fromID, int toID)
	{
		Edge tmp(fromID, toID, edges.size());
		edges.push_back(tmp);
		numberOfEdges++;
	}

	void AddNode(int nodeID, T info)
	{
		Node tmp(nodeID, info);
		nodes.push_back(tmp);
	}

	T GetNodeInfoFromFile(int nodeID)
	{
		try
		{
			std::ifstream fin;
			std::string info;
			T tmp;
			int counter = 0;
			fin.open("info.txt");
			if (!fin.is_open())
			{
				throw std::exception("Error. It's unavailable to open info.txt file.");
			}
			else
			{
				while (getline(fin, info))
				{
					if (nodeID == counter)
					{
						T t;
						std::istringstream stream(info);
						stream >> t;
						return t;
					}
					counter++;
				}
			}
		}
		catch (std::exception& e)
		{
			e.what();
		}
	}

	bool IsNodeExist(int nodeID)
	{
		for (auto node : nodes)
		{
			if (node.nodeID == nodeID)
				return true;
		}
		std::cout << "Node with ID " << nodeID << " doesn't exist.\n";
		return false;
	}

	bool IsEdgeExist(int edgeID)
	{
		for (auto edge : edges)
		{
			if (edge.edgeID == edgeID)
				return true;
		}
		std::cout << "Edge with ID " << edgeID << " doesn't exist.\n";
		return false;
	}

	std::vector<int> getNeighbors(Node node) {
		std::vector<int> neighbors;
		for (auto edge : edges)
		{
			if (edge.fromID == node.nodeID)
				neighbors.push_back(edge.toID);
		}
		return neighbors;
	}

	bool IsNodeIDFree(int nodeID)
	{
		for (auto node : nodes)
		{
			if (node.nodeID == nodeID)
			{
				std::cout << "This id is already taken. Try another id.\n";
				return false;
			}
		}
		return true;
	}

	bool IsEdgeIDFree(int edgeID)
	{
		for (auto edge : edges)
		{
			if (edge.edgeID == edgeID)
			{
				std::cout << "This id is already taken. Try another id.\n";
				return false;
			}

		}
		return true;
	}

	bool IsNeighbour(int fromID, int toID)
	{
		for (auto node : nodes)
		{
			if (node.nodeID == fromID)
			{
				for (auto el : node.adjNodes)
				{
					if (el == toID)
						return true;
				}
			}
		}
		return false;
	}

public:

	//constructors and users methods

	oriented_graph()
	{
		numberOfNodes = 0;
		numberOfEdges = 0;
	}

	oriented_graph(std::string path) : oriented_graph()
	{
		try 
		{	
			std::string adjMatrixRow;
			int adjMatrixValue;
			std::ifstream fin;
			fin.open(path);
			if (!fin.is_open())
			{
				throw std::exception("Error. It's unavailable to open graph.txt file.");
			}
			else
			{
				while (!fin.eof()) 
				{
					getline(fin, adjMatrixRow);
					if (adjMatrixRow != "")
						numberOfNodes++;
				}
				fin.seekg(0);
				for (auto i = 0; i < numberOfNodes; i++)
				{
					for (auto j = 0; j < numberOfNodes; j++)
					{
						fin >> adjMatrixValue;
						if (adjMatrixValue)
						{
							AddEdge(i, j);
						}
					}
				}
				for (auto i = 0; i < numberOfNodes; i++)
				{
					AddNode(i, GetNodeInfoFromFile(i));
				}
				for (int i = 0; i < nodes.size(); i++)
				{
					FindAdjNodes(nodes[i]);
					FindIncedentEdgesToNode(nodes[i]);
				}
			}
		}
		catch (std::exception& e)
		{
			e.what();
			return;
		}
	}

	void PrintNodeInfo(int nodeID)
	{
		Node node;
		for (auto n : nodes)
		{
			if (n.nodeID == nodeID)
			{
				node = n;
				break;
			}
		}
		std::cout << "ID: " << node.nodeID << "\nInfo: " << node.info <<
		"\nNeighbours: ";
		for (auto el : getNeighbors(node))
		{
			std::cout << el << ", ";
		}
		std::cout << std::endl;
	}

	~oriented_graph()
	{
		clear();
	}

	void adj_nodes()
	{
		for (auto node : nodes)
		{
			std::cout << "Node id: " << node.nodeID << "\tneighbours: ";
			for (auto it = node.adj_nodes_begin(); it != node.adj_nodes_end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << "\n";
		}
	}

	void incedent_edges()
	{
		for (auto node : nodes)
		{
			std::cout << "Node id: " << node.nodeID << "\tincedental edges  ";
			for (auto it = node.inc_edges_begin(); it != node.inc_edges_end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << "\n";
		}
	}

	bool is_empty()
	{
		if (nodes.empty())
			return true;
		return false;
	}
	
	void clear()
	{
		nodes.clear();
		edges.clear();
		numberOfNodes = 0;
		numberOfEdges = 0;
	}

	int get_nodes_number()
	{
		return numberOfNodes;
	}

	int get_edges_number()
	{
		return numberOfEdges;
	}

	int node_degree(int nodeID)
	{
		if(IsNodeExist(nodeID))
		{
			int nodeDegree = 0;
				for (auto edge : edges)
				{
					if (edge.toID == nodeID)
						nodeDegree++;
				}
			return nodeDegree;
		}
		return -1;
	}

	int edge_degree(int edgeID)
	{
		Edge tmp;
		if (IsEdgeExist(edgeID))
		{
			int edgeDegree = 0;
			for (auto edge : edges)
			{			
				if (edge.edgeID == edgeID)
					tmp = edge;
			}
			for (auto edge : edges)
			{
				if (edge.fromID == tmp.fromID && edge.toID == tmp.toID)
					edgeDegree++;
			}
			return edgeDegree;
		}
		return 0;
	}

	void add_node(int nodeID, T info)
	{
		if (IsNodeIDFree(nodeID))
		{
			Node* node = new Node(nodeID, info);
			nodes.push_back(*node);
			numberOfNodes++;
		}
	}

	void add_edge(int edgeID, int fromID, int toID)
	{
		if (IsEdgeIDFree(edgeID) && IsNodeExist(fromID) && IsNodeExist(toID))
		{
			Edge* edge = new Edge(fromID, toID, edgeID);
			edges.push_back(*edge);
			numberOfEdges++;
		}
		for (int i = 0; i < nodes.size(); i++)
		{
			FindAdjNodes(nodes[i]);
			FindIncedentEdgesToNode(nodes[i]);
		}
	}

	void remove_node(int nodeID)
	{
		if (IsNodeExist(nodeID))
		{
			for (auto it = nodes.begin(); it != nodes.end(); ++it)
			{
				if (it->nodeID == nodeID)
				{
					nodes.erase(it);
					break;
				}
			}
			for (auto edge : edges)
			{
				if (edge.toID == nodeID || edge.fromID == nodeID)
				{
					remove_edge(edge.edgeID);
				}
			}
			numberOfNodes--;
		}
	}

	void remove_edge(int edgeID)
	{
		if (IsEdgeExist(edgeID))
		{
			for (auto it = edges.begin(); it != edges.end(); ++it)
			{
				if (it->edgeID == edgeID)
				{
					edges.erase(it);
					break;
				}
			}
			for (int i = 0; i < nodes.size(); i++)
			{
				FindAdjNodes(nodes[i]);
				FindIncedentEdgesToNode(nodes[i]);
			}
			numberOfEdges--;
		}
	}

	void remove_edge(int fromID, int toID)
	{
		if (is_edge_exist(fromID, toID))
		{
			for (auto it = edges.begin(); it != edges.end(); ++it)
			{
				if (it->fromID == fromID && it->toID == toID)
				{
					edges.erase(it);
					break;
				}
			}
			for (int i = 0; i < nodes.size(); i++)
			{
				FindAdjNodes(nodes[i]);
				FindIncedentEdgesToNode(nodes[i]);
			}
			numberOfEdges--;
		}
		else
		{
			std::cout << "Edge isn't exist" << std::endl;
		}
	}

	bool is_node_exist(int nodeID)
	{
		return IsNodeExist(nodeID);
	}

	bool is_edge_exist(int edgeID)
	{
		return IsEdgeExist(edgeID);
	}

	bool is_edge_exist(int fromID, int toID)
	{
		for (auto edge : edges)
		{
			if (edge.fromID == fromID && edge.toID == toID)
				return true;
		}
		return false;
	}

	void detour(int nodeID) 
	{
		while (IsNodeExist(nodeID)) 
		{
			PrintNodeInfo(nodeID);
			int number;
			std::cout << "\nenter number of node\n";
			std::cin >> number;
			if (number == -1) 
			{
				system("cls");
				return;
			}
			while (!IsNeighbour(nodeID, number)) {
				std::cout << "incorrect input\n";
				std::cin >> number;
			}
			nodeID = number;
		}
	}

	//operators overloading

	bool operator==(oriented_graph& graph)
	{
		return (this->nodes == graph.nodes && this->edges == graph.edges);
	}

	bool operator!=(oriented_graph graph)
	{
		return (this->nodes != graph.nodes || this->edges != graph.edges);
	}

	bool operator<(oriented_graph graph)
	{
		return (this->numberOfNodes < graph.numberOfNodes);
	}

	bool operator<=(oriented_graph graph)
	{
		return (this->numberOfNodes <= graph.numberOfNodes);
	}

	bool operator>(oriented_graph graph)
	{
		return (this->numberOfNodes > graph.numberOfNodes);
	}

	bool operator>=(oriented_graph graph)
	{
		return (this->numberOfNodes >= graph.numberOfNodes);
	}

	friend std::ostream& operator << (std::ostream& s, oriented_graph& graph)
	{
		if (graph.get_nodes_number() != 0)
		{
			s << "**********NODES**********" << std::endl;
			for (auto it = graph.node_begin(); it != graph.node_end(); ++it)
			{
				s << "Node id: " << it->nodeID << "\tNode info: " << it->info << std::endl;
			}
		}
		if (graph.get_edges_number() != 0)
		{
			s << "**********EDGES**********" << std::endl;
			for (auto it = graph.edge_begin(); it != graph.edge_end(); ++it)
			{
				s << "Edge id: " << it->edgeID << "\t" << it->fromID << " ---> " << it->toID << std::endl;
			}
		}
		s << "\n\n";
		return s;
	}
	
	//iterator for nodes vector

	typedef Node value_type;
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;

	class NodeIterator :public std::iterator<iterator_category, value_type, pointer, reference>
	{
	private:
		pointer m_node;
	public:

		NodeIterator(pointer node):m_node(node){}

		reference operator*() const
		{
			return *m_node;
		}

		pointer operator->()
		{
			return m_node;
		}

		NodeIterator& operator++()
		{
			m_node++;
			return *this;
		}

		NodeIterator operator++(int)
		{
			NodeIterator tmp = *this;
			++(*this);
			return tmp;
		}

		NodeIterator& operator--()
		{
			m_node--;
			return *this;
		}

		NodeIterator operator--(int)
		{
			NodeIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const NodeIterator& other)
		{
			return this->m_node == other.m_node;
		}

		bool operator!=(const NodeIterator& other)
		{
			return this->m_node != other.m_node;
		}
	};

	NodeIterator node_begin()
	{
		return NodeIterator(&nodes[0]);
	}

	NodeIterator node_end()
	{
		return NodeIterator(&nodes[nodes.size()-1]+1);
	}

	//iterator for edge vector

	typedef Edge e_value_type;
	typedef e_value_type* e_pointer;
	typedef e_value_type& e_reference;
	typedef const e_value_type& e_const_reference;

	class EdgeIterator :public std::iterator<iterator_category, e_value_type, e_pointer, e_reference>
	{
	
	private:
		e_pointer m_edge;
	public:

		EdgeIterator(e_pointer edge) :m_edge(edge) {}

		e_reference operator*() const
		{
			return *m_edge;
		}

		e_pointer operator->()
		{
			return m_edge;
		}

		EdgeIterator& operator++()
		{
			m_edge++;
			return *this;
		}

		EdgeIterator operator++(int)
		{
			EdgeIterator tmp = *this;
			++(*this);
			return tmp;
		}

		EdgeIterator& operator--()
		{
			m_edge--;
			return *this;
		}

		EdgeIterator operator--(int)
		{
			EdgeIterator tmp = *this;
			--(*this);
			return tmp;
		}

		bool operator==(const EdgeIterator& other)
		{
			return this->m_edge == other.m_edge;
		}

		bool operator!=(const EdgeIterator& other)
		{
			return this->m_edge != other.m_edge;
		}
	};

	EdgeIterator edge_begin()
	{
		return EdgeIterator(&edges[0]);
	}

	EdgeIterator edge_end()
	{
		return EdgeIterator(&edges[edges.size()-1]+1);
	}
};

