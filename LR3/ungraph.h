#pragma once
#include "Error.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
template<class type>
class Vertex
{
protected:
	type data;
public:
	void setData(type &data)
	{
		this->data = data;
	}
	type getData()
	{
		return data;
	}
	Vertex()
	{

	}
	Vertex(type &data)
	{
		setData(data);
	}
};
class Edge
{
protected:
	double weight;
	int fVertex;
	int sVertex;
	char name = '0';
public:
	void setWeight(double &weight)
	{
		this->weight = weight;
	}
	void setCVertexes(int &fVertex, int &sVertex)
	{
		this->fVertex = fVertex;
		this->sVertex = sVertex;
	}
	void setName(char &name)
	{
		this->name = name;
	}
	double getWeight()
	{
		return weight;
	}
	int getFVertex()
	{
		return fVertex;
	}
	int getSVertex()
	{
		return sVertex;
	}
	char getName()
	{
		return name;
	}
	Edge()
	{

	}
	Edge(char &name, double &weight, int &fVertex, int &sVertex)
	{
		setName(name);
		setCVertexes(fVertex, sVertex);
		setWeight(weight);
	}
};
template<class type>
class Iterator
{
public:
	std::vector<Vertex<type>> vertexes;
	std::vector<Edge> edges;
	std::vector<std::vector<bool>> matrix;
};
template<class type>
class IteratorVertex:public Iterator<type>
{
public:
	int index;
	Vertex<type> element;
	IteratorVertex()
	{

	}
	IteratorVertex(std::vector<Vertex<type>> &vertexes)
	{
		this->index = 0;
		this->vertexes = vertexes;
	}
	IteratorVertex(const IteratorVertex& refItr)
	{
		this->vertexes = refItr.vertexes;
		this->edges = refItr.edges;
		this->matrix = refItr.matrix;
		this->index = refItr.index;
		this->element = refItr.element;
	}
	void setVertexes(std::vector<Vertex<type>>& vertexes)
	{
		element = vertexes[index];
		this->vertexes = vertexes;
	}
	int getIndex()
	{
		return index;
	}
	type getElement()
	{
		return element.getData();
	}
	IteratorVertex<type>& operator++()
	{
		if (this->vertexes.size()==0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		if (index<this->vertexes.size()-1)
		{
			index++;
		}
		element = this->vertexes[index];
		return *this;
	}
	IteratorVertex<type> operator++(int)
	{
		if (this->vertexes.size() == 0)
		{
			int x = 400;
			throw &x;
			return *this;
		}
		IteratorVertex<type> prev = *this;
		if (index < this->vertexes.size()-1)
		{
			++* this;
		}
		return prev;
	}
	IteratorVertex<type>& operator--()
	{
		if (index == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		if (index > 0)
		{
			index--;
		}
		element = this->vertexes[index];
		return *this;
	}
	IteratorVertex<type> operator--(int)
	{
		if (index == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		IteratorVertex<type> prev = *this;
		if (index > 0)
		{
			--* this;
		}
		return prev;
	}
};
template<class type>
std::ostream& operator <<(std::ostream& os, const IteratorVertex<type>& titr)
{
	IteratorVertex<type> itr = titr;
	if (itr.vertexes.size()!=0)
	{
		os << "Номер вершины: " << itr.getIndex() << " информация вершины: " << itr.getElement();
	}
	return os;
}
template<class type>
class IteratorEdge :public Iterator<type>
{
public:
	int index;
	Edge element;
	IteratorEdge()
	{

	}
	IteratorEdge(std::vector<Edge>& edges)
	{
		this->index = 0;
		this->edges = edges;
	}
	IteratorEdge(const IteratorEdge& refItr)
	{
		this->vertexes = refItr.vertexes;
		this->edges = refItr.edges;
		this->matrix = refItr.matrix;
		this->index = refItr.index;
		this->element = refItr.element;
	}
	void setEdges(std::vector<Edge>& edges)
	{
		this->edges = edges;
	}
	int getIndex()
	{
		return this->index;
	}
	Edge getElement()
	{
		return this->edges[index];
	}
	IteratorEdge<type>& operator++()
	{
		if (this->edges.size() == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		if (index < this->edges.size() - 1)
		{
			index++;
		}
		element = this->edges[index];
		return *this;
	}
	IteratorEdge<type> operator++(int)
	{
		if (this->edges.size() == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		IteratorEdge<type> prev = *this;
		if (index < this->edges.size() - 1)
		{
			++* this;
		}
		return prev;
	}
	IteratorEdge<type>& operator--()
	{
		if (index == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		if (index > 0)
		{
			index--;
		}
		element = this->edges[index];
		return *this;
	}
	IteratorEdge<type> operator--(int)
	{
		if (index == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		IteratorEdge<type> prev = *this;
		if (index > 0)
		{
			--* this;
		}
		return prev;
	}
};
template<class type>
std::ostream& operator <<(std::ostream& os, const IteratorEdge<type>& titr)
{
	IteratorEdge<type> itr = titr;
	if (itr.edges.size()!=0)
	{
		Edge edge = itr.getElement();
		os << "Имя ребра: " << edge.getName() << " вес ребра: " << edge.getWeight();
	}
	return os;
}
template<class type>
class AdjVertex:public IteratorVertex<type>
{
public:
	int index_vertex;
	int index;
	std::vector<int> indexesVertexes;
	std::vector<Vertex<type>> adj_vertexes;
	Vertex<type> element;
	AdjVertex()
	{

	}
	AdjVertex(const AdjVertex& refItr)
	{
		this->indexesVertexes = refItr.indexesVertexes;
		this->adj_vertexes = refItr.adj_vertexes;
		this->vertexes = refItr.vertexes;
		this->edges = refItr.edges;
		this->matrix = refItr.matrix;
		this->index = refItr.index;
		this->element = refItr.element;
		this->index_vertex = refItr.index_vertex;
	}
	void setVertexes(std::vector<Vertex<type>> &vertexes,std::vector<Edge>& edges)
	{
		this->vertexes = vertexes;
		this->edges = edges;
	}
	void findAdjVertexes(int index_vertex, std::vector<Edge>& edges)
	{
		this->index_vertex = index_vertex;
		for (int i = 0; i < edges.size(); i++)
		{
			int fVertex = edges[i].getFVertex();
			int sVertex = edges[i].getSVertex();
			if (fVertex==index_vertex)
			{
				adj_vertexes.push_back(this->vertexes[sVertex]);
				this->indexesVertexes.push_back(sVertex);
			}
			else if (sVertex==index_vertex)
			{
				adj_vertexes.push_back(this->vertexes[fVertex]);
				this->indexesVertexes.push_back(fVertex);
			}
		}
		if (adj_vertexes.size()!=0)
		{
			index = 0;
			element = adj_vertexes[0];
		}
	}
	int getIndex()
	{
		return indexesVertexes[index];
	}
	type getElement()
	{
		return adj_vertexes[index].getData();
	}
	AdjVertex<type>& operator++()
	{
		if (this->adj_vertexes.size() == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		if (index < this->adj_vertexes.size() - 1)
		{
			index++;
		}
		element = this->adj_vertexes[index];
		return *this;
	}
	AdjVertex<type> operator++(int)
	{
		if (this->adj_vertexes.size() == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		AdjVertex<type> prev = *this;
		if (index < this->adj_vertexes.size() - 1)
		{
			++* this;
		}
		return prev;
	}
	AdjVertex<type>& operator--()
	{
		if (index == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		if (index > 0)
		{
			index--;
		}
		element = this->adj_vertexes[index];
		return *this;
	}
	AdjVertex<type> operator--(int)
	{
		if (index == 0)
		{
			int x = 400;
			throw& x;
			return *this;
		}
		AdjVertex<type> prev = *this;
		if (index > 0)
		{
			--* this;
		}
		return prev;
	}
};
template<class type>
std::ostream& operator <<(std::ostream& os, const AdjVertex<type>& titr)
{
	AdjVertex<type> itr = titr;
	if (itr.adj_vertexes.size() != 0)
	{
		os << "Номер вершины: " << itr.getIndex() << " информация вершины: " << itr.getElement();
	}
	return os;
}
template<class type>
class incEdge:public IteratorVertex<type>
{
public:
	int index;
	int index_vertex;
	std::vector<Edge> inc_edges;
	Edge element;
	incEdge()
	{

	}
	incEdge(const incEdge& refItr)
	{
		this->index = refItr.index;
		this->index_vertex = refItr.index_vertex;
		this->inc_edges = refItr.inc_edges;
	}
	void setVertexes(std::vector<Vertex<type>>& vertexes, std::vector<Edge>& edges)
	{
		this->vertexes = vertexes;
		this->edges = edges;
	}
	void findIncEdges(int index_vertex, std::vector<Edge> edges)
	{
		this->index_vertex = index_vertex;
		for (int i = 0; i < edges.size(); i++)
		{
			int fVertex = edges[i].getFVertex();
			int sVertex = edges[i].getSVertex();
			if (fVertex == index_vertex)
			{
				inc_edges.push_back(edges[i]);
			}
			else if (sVertex == index_vertex)
			{
				inc_edges.push_back(edges[i]);
			}
		}
		if (inc_edges.size() != 0)
		{
			index = 0;
			element = inc_edges[0];
		}
	}
	char getName()
	{
		return inc_edges[index].getName();
	}
	double getWeight()
	{
		return inc_edges[index].getWeight();
	}
	incEdge<type>& operator++()
	{
		if (this->inc_edges.size() == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		if (index < this->inc_edges.size() - 1)
		{
			index++;
		}
		element = this->inc_edges[index];
		return *this;
	}
	incEdge<type> operator++(int)
	{
		if (this->inc_edges.size() == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		incEdge<type> prev = *this;
		if (index < this->inc_edges.size() - 1)
		{
			++* this;
		}
		return prev;
	}
	incEdge<type>& operator--()
	{
		if (index == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		if (index > 0)
		{
			index--;
		}
		element = this->inc_edges[index];
		return *this;
	}
	incEdge<type> operator--(int)
	{
		if (index == 0)
		{
			int x = 401;
			throw& x;
			return *this;
		}
		incEdge<type> prev = *this;
		if (index > 0)
		{
			--* this;
		}
		return prev;
	}
};
template<class type>
std::ostream& operator <<(std::ostream& os, const incEdge<type>& titr)
{
	incEdge<type> itr = titr;
	if (itr.inc_edges.size() != 0)
	{
		os << "Имя ребра: " << itr.getName() << " вес ребра: " << itr.getWeight();
	}
	return os;
}
template<class type>
class Graph: public Vertex<type>,Edge
{
protected:
	int x_size = 0;
	int y_size = 0;
	std::vector<Vertex<type>> vertexes;
	std::vector<Edge> edges;
	std::vector<std::vector<bool>> matrix;//incidence matrix
public:
	Graph()
	{

	}
	Graph(const Graph& refGraph)
	{
		x_size = refGraph.x_size;
		y_size = refGraph.y_size;
		vertexes = refGraph.vertexes;
		edges = refGraph.edges;
		matrix = refGraph.matrix;
	}
	std::vector<Vertex<type>>& getVertexes()
	{
		return vertexes;
	}
	std::vector<Edge>& getEdges()
	{
		return edges;
	}
	std::vector<std::vector<bool>>& getMatrix()
	{
		return matrix;
	}
	void addVertex(type &data)
	{
		y_size++;
		Vertex<type> vertex(data);
		vertexes.push_back(vertex);
		matrix.push_back({});
		if (x_size!=0)
		{
			for (int i = 0; i < x_size; i++)
			{
				matrix[y_size - 1].push_back({});
			}
		}
	}//adding a vertex
	void addEdge(double &weight, int &fVertex, int &sVertex, char &name) //f/sVertex - first&second vertex
	{
		if (((y_size * (y_size - 1)) / 2)==x_size)
		{
			int x = 303;
			throw &x;
			return;
		}
		if (!isVertexExist(fVertex) || !isVertexExist(sVertex))
		{
			int x = 304;
			throw& x;
			return;
		}
		if (isEdgeBetVertexes(fVertex,sVertex))
		{
			int x = 305;
			throw& x;
			return;
		}
		for (int i = 0; i < x_size; i++)
		{
			if (edges[i].getName()==name)
			{
				int x = 306;
				throw& x;;
				return;
			}
		}
		Edge edge(name, weight, fVertex, sVertex);
		x_size++;
		edges.push_back(edge);
		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].push_back({});
		}
		matrix[fVertex][x_size-1] = true;
		matrix[sVertex][x_size-1] = true;
	}//adding an edge
	void getVertexData(int &index_vertex)
	{
		if (!isVertexExist(index_vertex))
		{
			throw std::exception();
		}
		std::cout << "Информация вершины: " << vertexes[index_vertex].getData();
		system("pause");
	}
	void getEdgeWeight(char &name)
	{
		bool check = false;
		int index_edge = 0;
		for (int i = 0; i < x_size; i++)
		{
			if (edges[i].getName() == name)
			{
				check = true;
				index_edge = i;
			}
		}
		if (!check)
		{
			throw std::exception();
		}
		std::cout << "Вес ребра: " << edges[index_edge].getWeight();
		system("pause");
	}
	void deleteVertex()
	{
		std::cout << "Введите номер вершины: ";
		int number = getChoice<int>();
		if (number>=y_size)
		{
			throw std::exception();
		}
		y_size--;
		matrix.erase(matrix.begin() + number);
		vertexes.erase(vertexes.begin() + number);
	}//Deleting vertex
	void deleteEdge()
	{
		std::cout << "Введите имя ребра: ";
		char name = getChoice<char>();
		int number = -1;
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].getName() == name)
			{
				number = i;
				edges.erase(edges.begin() + number);
				break;
			}
		}
		if (number==-1)
		{
			throw std::exception();
		}
		x_size--;
		for ( int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (j==number)
				{
					matrix[i].erase(matrix[i].begin() + j);
				}
			}
		}
	}//Deleting edge
	bool empty()
	{
		return !(x_size == 0 && y_size == 0);
	}//is empty
	void clear()
	{
		edges.clear();
		vertexes.clear();
		matrix.clear();
		x_size = 0;
		y_size = 0;
	}//clearing graph
	int NumberOfVertexes()
	{
		return y_size;
	}//number of vertexes
	int NumberOfEdgex()
	{
		return x_size;
	}//number of edges
	void showMatrix()
	{
		std::cout << "  ";
		for (auto nameEdges : edges)
		{
			std::cout << nameEdges.getName() << " ";
		}
		std::cout << std::endl;
		int i = 0;
		for (auto rows : matrix)
		{
			std::cout << i << " ";
			i++;
			for (auto value : rows)
			{
				std::cout << value << " ";
			}
			std::cout << std::endl;
		}
	}//show matrix
	int powerVertex(int &index_vertex)
	{
		int power = 0;
		for (int i = 0; i < matrix[index_vertex].size(); i++)
		{
			if (matrix[index_vertex][i] == 1)
			{
				power++;
			}
		}
		return power;
	}//power of vertex
	int powerEdge(char &name)
	{
		int power = 0;
		int index_edge = 0;
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].getName()==name)
			{
				index_edge = i;
				break;
			}
		}
		int k = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[i][index_edge]==1)
			{
				k++;
				power += powerVertex(i);
			}
			if (k==2)
			{
				return power;
			}
		}
		return 0;
	}//power of edge
	bool isVertexExist(int &index_vertex)
	{
		return index_vertex < y_size;
	} //checking existing of a vertex
	bool isEdgeBetVertexes(int &fIndex, int &sIndex)
	{
		bool check = (isVertexExist(fIndex) && isVertexExist(sIndex));
		if (check)
		{
			for (int i = 0; i < matrix[fIndex].size(); i++)
			{
				if ((matrix[fIndex][i]== 1) && (matrix[sIndex][i] == 1))
				{
					return true;
				}
			}
		}
		return false;
	} //Checking existing of an edge between vertexes
};
template<class type>
bool operator ==(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes == graph_2->vertexes) && (graph_1->edges == graph_2->edges) && (graph_1->matrix == graph_2->matrix));
}
template<class type>
Graph<type> operator !=(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes != graph_2->vertexes) || (graph_1->edges != graph_2->edges) || (graph_1->matrix != graph_2->matrix));
}
template<class type>
Graph<type> operator >(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes > graph_2->vertexes) && (graph_1->edges > graph_2->edges) && (graph_1->matrix > graph_2->matrix));
}
template<class type>
Graph<type> operator <(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes < graph_2->vertexes) && (graph_1->edges < graph_2->edges) && (graph_1->matrix < graph_2->matrix));
}
template<class type>
Graph<type> operator >=(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes >= graph_2->vertexes) && (graph_1->edges >= graph_2->edges) && (graph_1->matrix >= graph_2->matrix));
}
template<class type>
Graph<type> operator <=(Graph<type> graph_1, Graph<type> graph_2)
{
	return ((graph_1->vertexes <= graph_2->vertexes) && (graph_1->edges <= graph_2->edges) && (graph_1->matrix <= graph_2->matrix));
}
template<class type>
std::ostream& operator <<(std::ostream& os, const Graph<type>& Tgraph)
{
	os << "  ";
	Graph<type> graph = Tgraph;
	std::vector<Edge> edges;
	std::vector<std::vector<bool>> matrix;//incidence matrix
	edges = graph.getEdges();
	matrix = graph.getMatrix();
	for (auto nameEdges : edges)
	{
		os << nameEdges.getName() << " ";
	}
	os << std::endl;
	int i = 0;
	for (auto rows : matrix)
	{
		os << i << " ";
		i++;
		for (auto value : rows)
		{
			os << value << " ";
		}
		os << std::endl;
	}
	return os;
}
