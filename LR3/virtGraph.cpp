#include<iostream>
using namespace std;


template <typename T>
class Node;
template <typename T>
class Edge;
template <typename T>
class Graph;


template <typename T>
class Node
{
	friend class Graph<T>;

	template<typename Ts>
	friend ostream& operator<<(ostream& os, const Graph<Ts>& graph);

	template<typename Ts>
	friend bool operator==(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator!=(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator>(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator>=(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator<(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator<=(const Node<Ts>& firstNode, const Node<Ts>& secondNode);

	template<typename Ts>
	friend bool operator<(const Graph<Ts>& graph1, const Graph<Ts>& graph2);


public:
	Node();
	Node(T Key, int Count, Node* Next, Edge<T>* Trail);

private:
	T Key;
	int Count;
	Node* Next;
	Edge<T>* Trail;

};

template <typename T>
class Edge
{
	friend class Graph<T>;

	template<typename Ts>
	friend ostream& operator<<(ostream& os, const Graph<Ts>& graph);

public:
	Edge();

private:
	Node<T>* Id;
	Edge* Next;
};

template <typename T>
class Graph
{
public:
	Graph();
	Graph(const Graph& graph);
	~Graph();
	/*Поиск узла. Возвращает указатель на узел с Key равным key, если он есть, nullptr если нет.*/
	Node<T>* SearchNode(T key) const noexcept;
	/*Вставка узла с Key равным keyPush. Если такой узел уже есть, возвращает исключение.*/
	void PushNode(T keyPush);
	/*Вставка ребра между узлами с Key равным keyPush и keyPush. Если одного из узлов нету, возвращает исключение.*/
	void PushEdge(T keyPush, T keyWith);
	/*Вставка узла с Key равным keyPush и ребра с узлом с Key равным keyWith. Если такой узел уже есть, возвращает исключение. 
	Если keyWith нету, возвращает исключение.*/
	void PushNodeWithEdge(T keyPush, T keyWith);
	/*Проверка, существует ли ребро между узлами с Key равным firstNode и secondNode. Возвращает true если есть, false, если нет. 
	Если одного из узлов нету, возвращает исключение.*/
	bool IsEdge(T firstNode, T secondNode) const noexcept;
	/*Проверка, существует ли узел с Key равным key. Возвращает true если есть, false, если нет.*/
	bool IsNode(T key) const noexcept;
	/*Проверка, пуст ли граф. Возвращает true если пуст, false, если нет.*/
	bool Empty() const noexcept;
	/*Получение количества узлов*/
	int SizeNodes() const noexcept;
	/*Получение количества ребер*/
	int SizeEdges() const noexcept;
	/*Получение степени узла*/
	int PovNode(T key);
	/*Удаление узла. Еслиу узла нету, возвращает исключение.*/
	void DeleteNode(T key);
	/*Удаление ребра.  Если одного из узлов нету, возвращает исключение. Если ребра нету, возвращает исключение.*/
	void DeleteEdge(T firstNode, T secondNode);

	//Итератор для перебора узлов
	struct NodeIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Node<T>;
		using pointer = Node<T>*;
		using reference = Node<T>&;
		NodeIterator(pointer ptr) : m_ptr(ptr) {};
		T operator*() const { 
			try
			{
				if (m_ptr==nullptr)
				{
					throw exception("Exception : node is nullptr");
				}
				return m_ptr->Key; 
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		NodeIterator& operator++()
		{ 
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : node is nullptr");
				}
				else if (m_ptr->Next == nullptr)
				{
					throw exception("Exception : node is Tail");
				}
				m_ptr = m_ptr->Next; 
				return *this; 
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		NodeIterator operator++(int)
		{ 
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : node is nullptr");
				}
				else if (m_ptr->Next == nullptr)
				{
					throw exception("Exception : node is Tail");
				}
				NodeIterator tmp = *this;
				m_ptr = m_ptr->Next;
				return tmp;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		friend bool operator== (const NodeIterator& a, const NodeIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const NodeIterator& a, const NodeIterator& b) { return a.m_ptr != b.m_ptr; };

	private:

		pointer m_ptr;
	};

	NodeIterator beginNodes() { return NodeIterator(this->Head); }
	NodeIterator endNodes() { return NodeIterator(this->Tail); }

	//Итератор для перебора ребер, инцидентных узлу. Принимает указатель на узел. 
	struct EdgeIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Edge<T>;
		using pointer = Edge<T>*;
		using reference = Edge<T>&;
		T returnKeyMain() 
		{
			return m_node->Key;
		}
		T returnKeyTrail()
		{
			return m_ptr->Id->Key;
		}
		EdgeIterator(Node<T>* node)
		{
			try
			{
				if (node == nullptr)
				{
					throw exception("Exception : node is not existed");
				}
				m_node = node;
				m_ptr = m_node->Trail;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		EdgeIterator& operator++()
		{
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : edge is nullptr");
				}
				m_ptr = m_ptr->Next;
				return *this;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		EdgeIterator operator++(int)
		{
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : edge is nullptr");
				}
				NodeIterator tmp = *this;
				m_ptr = m_ptr->Next;
				return tmp;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		friend bool operator== (const EdgeIterator& a, const EdgeIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const EdgeIterator& a, const EdgeIterator& b) { return a.m_ptr != b.m_ptr; };

	private:

		pointer m_ptr;
		Node<T>* m_node;
	};

	EdgeIterator beginEdges() { return EdgeIterator(this->Head); }
	EdgeIterator endEdges() { return EdgeIterator(this->Tail); }

	//Итератор для перебора узлов, смежных узлу. Принимает указатель на узел. 
	struct NodeNodesIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Node<T>;
		using pointer = Node<T>*;
		using pointerTrail = Edge<T>*;
		using reference = Node<T>&;
		NodeNodesIterator(Node<T>* node)
		{
			try
			{
				if (node == nullptr)
				{
					throw exception("Exception : node is not existed");
				}
				if (node->Trail == nullptr)
				{
					throw exception("Exception : node dosen't have adjacent nodes");
				}
				m_Mainnode = node;
				m_ptr = m_Mainnode->Trail;
				m_node = m_ptr->Id;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		T operator*() const { return m_node->Key; }
		NodeNodesIterator& operator++()
		{
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : edge is nullptr");
				}
				m_ptr = m_ptr->Next;
				m_node = m_ptr->Id;
				return *this;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		NodeNodesIterator operator++(int)
		{
			try
			{
				if (m_ptr == nullptr)
				{
					throw exception("Exception : edge is nullptr");
				}
				NodeNodesIterator tmp = *this;
				m_ptr = m_ptr->Next;
				m_node = m_ptr->Id;
				return tmp;
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
		friend bool operator== (const NodeNodesIterator& a, const NodeNodesIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const NodeNodesIterator& a, const NodeNodesIterator& b) { return a.m_ptr != b.m_ptr; };

	private:

		pointer m_Mainnode;
		pointer m_node;
		pointerTrail m_ptr;
	};

	NodeNodesIterator beginNodeNodes() { return NodeNodesIterator(this->Head); }
	NodeNodesIterator endNodeNodes() { return NodeNodesIterator(this->Tail); }

	//Удаление узла по итератору на узел
	void eraseNode(NodeIterator delNode);
	//Уаление ребра по итератору на ребро
	void eraseEdge(EdgeIterator delEdge);

	template<typename Ts>
	//Перегруженный оператор вывода
	friend ostream& operator<<(ostream& os, const Graph<Ts>& graph);

	template<typename Ts>
	//Перегруженный оператор вывода
	friend ostream& operator<<(ostream& os, const NodeIterator& node);

	//Метод clear
	void clear();

	//Перегруженный оператор присваивания =
	Graph& operator=(const Graph& graph);

	template<typename Ts>
	//Перегруженный оператор сравнения ==
	friend bool operator==(const Graph<Ts>& graph1, const Graph<Ts>& graph2);

	template<typename Ts>
	//Перегруженный оператор сравнения !=
	friend bool operator!=(const Graph<Ts>& graph1, const Graph<Ts>& graph2);

	template<typename Ts>
	//Перегруженный оператор сравнения <
	friend bool operator<(const Graph<Ts>& graph1, const Graph<Ts>& graph2);
	
	template<typename Ts>
	//Перегруженный оператор сравнения <
	friend bool operator>(const Graph<Ts>& graph1, const Graph<Ts>& graph2);

	template<typename Ts>
	//Перегруженный оператор сравнения <=
	friend bool operator<=(const Graph<Ts>& graph1, const Graph<Ts>& graph2);

	template<typename Ts>
	//Перегруженный оператор сравнения >
	friend bool operator>=(const Graph<Ts>& graph1, const Graph<Ts>& graph2);

private:
	Node<T>* Head;
	Node<T>* Tail;
	bool IsEdgePrivate(Node<T>* firstNode, Node<T>* secondNode) const noexcept;
	void DeleteEdgePrivate(Edge<T>* trailFirstNode, Node<T>* firstNode, Node<T>* secondNode);
	void PushEdgePrivate(Node<T>* firstNode, Node<T>* secondNode);
	void clearPrivate();
	void FreeEdges(Edge<T>** edge);
	void FreeNodes(Node<T>** TempHead, Node<T>** TempTail);
	void copyPrivate(const Graph& graph);
	bool CompareGraphs(const Graph& graph1, const Graph& graph2) const noexcept;
	bool CompareGraph(const Graph& graph1, const Graph& graph2) const noexcept;
	bool CompareEdges(Node<T>& node, const Graph& graph) const noexcept;
	bool CompareNodes(Node<T>& node, const Graph& graph) const noexcept;
	bool CompareGraphWithoutEdges(const Graph& graph1, const Graph& graph2) const noexcept;
};

template<typename T>
Node<T>::Node()
{
	Key = T();
	Count = 0;
	Next = nullptr;
	Trail = nullptr;
}

template<typename T>
Node<T>::Node(T Key, int Count, Node* Next, Edge<T>* Trail)
{
	this->Key = Key;
	this->Count = Count;
	this->Next = Next;
	this->Trail = Trail;
}

template<typename T>
Edge<T>::Edge()
{
	Id = nullptr;
	Next = nullptr;
}

template<typename T>
Graph<T>::Graph()
{
	Head = nullptr;
	Tail = new Node<T>();
}

template<typename T>
Graph<T>::Graph(const Graph& graph) : Graph()
{
	this->copyPrivate(graph);
}

template<typename T>
Graph<T>::~Graph()
{
	clearPrivate();
	delete Tail;
}

template<typename T>
Node<T>* Graph<T>::SearchNode(T key) const noexcept
{
	Node<T>* temp = this->Head;
	while (temp != nullptr && temp->Key != key && temp != this->Tail)
	{
		temp = temp->Next;
	}
	if (temp == this->Tail)
	{
		return nullptr;
	}
	return temp;
}

template<typename T>
void Graph<T>::PushNode(T keyPush)
{
	try
	{
		Node<T>* push = SearchNode(keyPush);
		if (push != nullptr)
		{
			throw exception("Exception : node is existed");
		}
		Node<T>* temp = this->Head;
		if (temp == nullptr)
		{
			push = new Node<T>(keyPush, 0, this->Tail, nullptr);
			this->Head = push;
			return;
		}
		while (temp->Next->Next != nullptr)
		{
			temp = temp->Next;
		}
		push = new Node<T>(keyPush, 0, this->Tail, nullptr);
		temp->Next = push;
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}

}

template<typename T>
void Graph<T>::PushEdge(T keyPush, T keyWith)
{
	Node<T>* push = SearchNode(keyPush);
	Node<T>* with = SearchNode(keyWith);
	if (!IsEdgePrivate(push, with))
	{
		PushEdgePrivate(push, with);
		PushEdgePrivate(with, push);
	}
}

template<typename T>
void Graph<T>::PushNodeWithEdge(T keyPush, T keyWith)
{
	try {
		if (SearchNode(keyWith) == nullptr)
		{
			throw exception("Exception : node is not existed");
		}
		PushNode(keyPush);
		PushEdge(keyPush, keyWith);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}

template<typename T>
bool Graph<T>::IsEdge(T firstNode, T secondNode) const noexcept
{
	try
	{
		Node<T>* firstN = SearchNode(firstNode);
		Node<T>* secondN = SearchNode(secondNode);
		if (firstN == nullptr || secondN == nullptr)
		{
			throw exception("Exception : node is not existed");
		}
		return IsEdgePrivate(firstN, secondN);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}

template<typename T>
bool Graph<T>::IsNode(T key) const noexcept
{
	return SearchNode(key) != nullptr;
}

template<typename T>
bool Graph<T>::Empty() const noexcept
{
	return Head == nullptr || Head->Next == nullptr;
}

template<typename T>
int Graph<T>::SizeNodes() const noexcept
{
	Node<T>* temp = this->Head;
	if (this->Empty())
	{
		return 0;
	}
	int answer = 0;
	while (temp != this->Tail)
	{
		++answer;
		temp = temp->Next;
	}
	return answer;
}

template<typename T>
int Graph<T>::SizeEdges() const noexcept
{
	Node<T>* temp = this->Head;
	if (this->Empty())
	{
		return 0;
	}
	int answer = 0;
	while (temp != this->Tail)
	{
		answer += temp->Count;
		temp = temp->Next;
	}
	return answer / 2;
}

template<typename T>
int Graph<T>::PovNode(T key)
{
	try 
	{ 
		Node<T>* temp = SearchNode(key);
		if (temp == nullptr)
		{
			throw exception("Exception : node is not existed");
		}
		return temp->Count; 
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return -1;
	}
}

template<typename T>
void Graph<T>::DeleteNode(T key)
{
	try
	{
		Node<T>* delNode = SearchNode(key);
		if (delNode == nullptr)
		{
			throw exception("Exception : node is not existed");
		}
		Node<T>* temp = this->Head;
		while (temp != this->Tail)
		{
			if (IsEdge(key,temp->Key))
			{
				DeleteEdgePrivate(delNode->Trail, delNode, temp);
				DeleteEdgePrivate(temp->Trail, temp, delNode);
			}
			temp = temp->Next;
		}
		Edge<T>* tempTrail = delNode->Trail;
		while (tempTrail != nullptr)
		{
			Edge<T>* tempTrailDel = tempTrail;
			tempTrail = tempTrail->Next;
			delete tempTrailDel;
		}
		temp = this->Head;
		if (temp == delNode)
		{
			this->Head = this->Head->Next;
			delete temp;
		}
		else
		{
			while (temp->Next!=delNode)
			{
				temp = temp->Next;
			}
			temp->Next = delNode->Next;
			delete delNode;
		}
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}

}

template<typename T>
void Graph<T>::DeleteEdge(T firstNode, T secondNode)
{
	try
	{
		Node<T>* firstN = SearchNode(firstNode);
		Node<T>* secondN = SearchNode(secondNode);
		if (!IsEdge(firstNode, secondNode))
		{
			throw exception("Exception : edge is not existed");
		}
		DeleteEdgePrivate(firstN->Trail, firstN, secondN);
		DeleteEdgePrivate(secondN->Trail, secondN, firstN);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}

template<typename T>
void Graph<T>::eraseNode(NodeIterator delNode)
{
	DeleteNode(*delNode);
}

template<typename T>
void Graph<T>::eraseEdge(EdgeIterator delEdge)
{
	DeleteEdge(delEdge.returnKeyMain(), delEdge.returnKeyTrail());
}

template<typename T>
void Graph<T>::clear()
{
	clearPrivate();
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& graph)
{
	if (this->Head!=nullptr)
	{
		this->clearPrivate();
	}
	this->copyPrivate(graph);
	return *this;
}

template<typename T>
bool operator==(const Graph<T>& graph1, const Graph<T>& graph2)
{
	if (graph1.Empty() && graph2.Empty())
	{
		return true;
	}
	if (graph1.SizeNodes() != graph2.SizeNodes() || graph1.SizeEdges() != graph2.SizeEdges())
	{
		return false;
	}
	return graph1.CompareGraphs(graph1,graph2);
}

template<typename Ts>
bool operator!=(const Graph<Ts>& graph1, const Graph<Ts>& graph2)
{
	return !(graph1==graph2);
}

template<typename Ts>
bool operator<(const Graph<Ts>& graph1, const Graph<Ts>& graph2)
{
	if (graph1.Empty() && graph2.Empty())
	{
		return false;
	}
	if (graph1.CompareGraphWithoutEdges(graph1,graph2)&& graph1.CompareGraphWithoutEdges(graph2, graph1))
	{
		return graph1.SizeEdges() < graph2.SizeEdges();
	}
	Node<Ts>* tempNode = graph1.Head;
	bool answer = true;
	while (tempNode != graph1.Tail && tempNode != nullptr && answer)
	{
		answer = graph1.CompareNodes(*tempNode, graph2);
		tempNode = tempNode->Next;
	}
	return answer;
}

template<typename Ts>
bool operator>=(const Graph<Ts>& graph1, const Graph<Ts>& graph2)
{
	return !(graph1 < graph2);
}

template<typename Ts>
bool operator>(const Graph<Ts>& graph1, const Graph<Ts>& graph2)
{
	return graph2 < graph1;
}

template<typename Ts>
bool operator<=(const Graph<Ts>& graph1, const Graph<Ts>& graph2)
{
	return  !(graph2 < graph1);
}

template<typename T>
bool Graph<T>::IsEdgePrivate(Node<T>* firstNode, Node<T>* secondNode) const noexcept
{
	Edge<T>* tempTrail = firstNode->Trail;
	bool check = false;
	while ((tempTrail != nullptr) && (!check))
	{
		if (tempTrail->Id == secondNode)
		{
			check = true;
		}
		else
		{
			tempTrail = tempTrail->Next;
		}
	}
	return check;
}

template<typename T>
void Graph<T>::DeleteEdgePrivate(Edge<T>* trailFirstNode, Node<T>* firstNode, Node<T>* secondNode)
{
	Edge<T>* tempTrailFirstNode = trailFirstNode;
	while (tempTrailFirstNode->Id != secondNode)
	{
		tempTrailFirstNode = tempTrailFirstNode->Next;
	}
	if (tempTrailFirstNode == trailFirstNode)
	{
		firstNode->Trail = firstNode->Trail->Next;
		firstNode->Count--;
		delete tempTrailFirstNode;
	}
	else
	{
		Edge<T>* temp = trailFirstNode;
		while (temp->Next != tempTrailFirstNode)
		{
			temp = temp->Next;
		}
		temp->Next = tempTrailFirstNode->Next;
		firstNode->Count--;
		delete tempTrailFirstNode;
	}
}

template<typename T>
void Graph<T>::PushEdgePrivate(Node<T>* firstNode, Node<T>* secondNode)
{
	Edge<T>* temp = new Edge<T>();
	temp->Id = secondNode;
	temp->Next = firstNode->Trail;
	firstNode->Trail = temp;
	firstNode->Count++;
}

template<typename T>
void Graph<T>::clearPrivate()
{
	Node<T>* temp = this->Head;
	while (temp != this->Tail && temp != nullptr)
	{
		FreeEdges(&(temp->Trail));
		temp = temp->Next;
	}
	FreeNodes(&(this->Head), &(this->Tail));
}

template<typename T>
void Graph<T>::FreeEdges(Edge<T>** edge)
{
	if (*edge!=nullptr)
	{
		FreeEdges(&(**edge).Next);
		delete *edge;
		*edge = nullptr;
	}
}

template<typename T>
void Graph<T>::FreeNodes(Node<T>** TempHead, Node<T>** TempTail)
{
	if (*TempHead!=*TempTail &&*TempHead != nullptr)
	{
		FreeNodes(&(**TempHead).Next, TempTail);
		delete* TempHead;
		*TempHead = nullptr;
	}
}

template<typename T>
void Graph<T>::copyPrivate(const Graph& graph)
{
	Node<T>* temp = graph.Head;
	while (temp != nullptr && temp != graph.Tail)
	{
		this->PushNode(temp->Key);
		temp = temp->Next;
	}
	temp = graph.Head;
	while (temp != nullptr && temp != graph.Tail)
	{
		Edge<T>* tempTrail = temp->Trail;
		while (tempTrail != nullptr)
		{
			this->PushEdge(temp->Key, tempTrail->Id->Key);
			tempTrail = tempTrail->Next;
		}
		temp = temp->Next;
	}
}

template<typename T>
bool Graph<T>::CompareGraphs(const Graph& graph1, const Graph& graph2) const noexcept
{ 
	return CompareGraph(graph1, graph2) && CompareGraph(graph2, graph1);
}

template<typename T>
bool Graph<T>::CompareGraph(const Graph& graph1, const Graph& graph2) const noexcept
{
	bool answer = true;
	Node<T>* temp = graph1.Head;
	while (temp != nullptr && temp != graph1.Tail && answer)
	{
		answer = graph2.IsNode(temp->Key);
		answer = CompareEdges(*temp, graph2);
		temp = temp->Next;
	}
	return answer;
}

template<typename T>
bool Graph<T>::CompareGraphWithoutEdges(const Graph& graph1, const Graph& graph2) const noexcept
{
	bool answer = true;
	Node<T>* temp = graph1.Head;
	while (temp != nullptr && temp != graph1.Tail && answer)
	{
		answer = graph2.IsNode(temp->Key);
		temp = temp->Next;
	}
	return answer;
}

template<typename T>
bool Graph<T>::CompareEdges(Node<T>& node, const Graph& graph) const noexcept
{
	Edge<T>* tempTrail = node.Trail;
	bool answer = true;
	while (tempTrail != nullptr && answer)
	{
		answer = graph.IsEdge(node.Key, tempTrail->Id->Key);
		tempTrail = tempTrail->Next;
	}
	return answer;
}

template<typename T>
bool Graph<T>::CompareNodes(Node<T>& node, const Graph& graph) const noexcept
{
	Node<T>* tempNode = graph.Head;
	bool answer = true;
	while (tempNode != graph.Tail && tempNode != nullptr && answer)
	{
		answer = node < *tempNode;
		tempNode = tempNode->Next;
	}
	return answer;
}

template<typename T>
ostream& operator<<(ostream& os, const Graph<T>& graph)
{
	try
	{
		Node<T>* tempNode = graph.Head;
		if (tempNode == nullptr)
		{
			throw exception("Exception : graph is empty");
		}
		while (tempNode != graph.Tail)
		{
			os << "(" << " [" << tempNode->Key << "] ";
			Edge<T>* tempTrail = tempNode->Trail;
			while (tempTrail != nullptr)
			{
				os << tempTrail->Id->Key << " ";
				tempTrail = tempTrail->Next;
			}
			os << ")";
			tempNode = tempNode->Next;
			os << " ";
		}
		return os;
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return os;
	}
}

template<typename Ts>
bool operator==(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return firstNode.Key == secondNode.Key;
}

template<typename Ts>
bool operator!=(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return !(firstNode==secondNode);
}

template<typename Ts>
bool operator>(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return secondNode < firstNode;
}

template<typename Ts>
bool operator>=(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return !(firstNode < secondNode);
}

template<typename Ts>
bool operator<(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return firstNode.Key < secondNode.Key;
}

template<typename Ts>
bool operator<=(const Node<Ts>& firstNode, const Node<Ts>& secondNode)
{
	return  !(secondNode < firstNode);
}
