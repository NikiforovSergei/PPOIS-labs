#ifndef WIRTH_UNORIENTED_GRAPH_H
#define WIRTH_UNORIENTED_GRAPH_H

template<typename T>
struct Node;

template<typename T>
struct Edge {

	Node<T>* Id;
	Edge<T>* Next;
};

template<typename T>
struct Node {

	T Key = NULL;
	int Count = NULL;
	Edge<T>* Trail = nullptr;
	Edge<T>* Pred = nullptr;
	Node<T>* Next = nullptr;
};

template<typename T>
class NodeIterator {

	typedef Node<T>* pointer;

private:

	pointer curr_ptr;

public:

	explicit NodeIterator(pointer ptr) : curr_ptr(ptr) {};

	bool operator==(const NodeIterator& other) { return this->curr_ptr == other.curr_ptr; }
	bool operator!=(const NodeIterator& other) { return this->curr_ptr != other.curr_ptr; }

};

template<typename T>
class EdgeIterator {

	typedef Node<T>* pointer_node;
	typedef Edge<T>* pointer_edge;

private:

	pointer_node curr_node;
	pointer_edge curr_edge;

public:

	explicit EdgeIterator(Node<T>* first) : curr_node(first) {
		curr_edge = curr_node->Trail;
	};

	bool operator==(const EdgeIterator& other) { return this->curr_ptr == other.curr_ptr; }
	bool operator!=(const EdgeIterator& other) { return this->curr_ptr != other.curr_ptr; }

};

template<typename T>
class AdjacencyIterator {

	typedef Edge<T>* pointer;

private:

	pointer curr_ptr;

public:

	explicit AdjacencyIterator(Node<T>* node) : curr_ptr(node->Trail) {};

	bool operator!=(const AdjacencyIterator& it) { return curr_ptr != it.curr_ptr; }
	bool operator==(const AdjacencyIterator& it) { return curr_ptr == it.curr_ptr; }

};


template<typename T>
class Graph {

private:

	Node<T>* Head;
	Node<T>* Tail;

private:

	Node<T>* get_added_or_found_node(T key);
	Node<T>* get_found_node(T key);

public:

	Graph() { Head = Tail = new Node<T>; }
	void add_node(T key);
	void add_edge(T x, T y);
	void del_edge(T, T);
	void print_graph();
	void del_node(T);
	bool is_node(T);
	bool is_edge(T, T);
	int count_nodes();
	int count_edges();
	int pow_node(T);

};




template<typename T>
T operator*(NodeIterator<T> iterator) {

	if (iterator->curr_ptr == nullptr)
		throw std::invalid_argument("nullptr exc");

	return iterator->curr_ptr->Key;

}

template<typename T>
NodeIterator<T>& operator++(NodeIterator<T> iterator) {
	if (iterator->curr_ptr == nullptr)
		throw std::invalid_argument("nullptr exc");

	iterator->curr_ptr = iterator->curr_ptr->Next;
	return *this;
}

template<typename T>
NodeIterator<T> operator++(NodeIterator<T> iterator) {

	NodeIterator tmp = *this;
	if (iterator->curr_ptr == nullptr)
		throw std::invalid_argument("nullptr exc");

	iterator->curr_ptr = iterator->curr_ptr->Next;
	return tmp;
}



template<typename T>
std::pair<T, T> operator*(EdgeIterator<T> iterator) {

	return std::pair<T, T>(iterator->curr_node->Key, iterator->curr_edge->Id);

}

template<typename T>
EdgeIterator<T>& operator++(EdgeIterator<T> iterator) {

	if (!iterator->curr_edge->Next && !iterator->curr_node->Next->Next)
		throw std::out_of_range("nullptr exc");

	if (iterator->curr_edge->Next)
		iterator->curr_edge = iterator->curr_edge->Next;
	else if (iterator->curr_edge->Next->Next) {

		do {
			iterator->curr_edge = iterator->curr_edge->Next;
		} while (!iterator->curr_edge->Trail);

		iterator->curr_edge = iterator->curr_edge->Trail;
	}

	return *this;

}

template<typename T>
EdgeIterator<T> operator++(EdgeIterator<T> iterator) {

	EdgeIterator<T> tmp = *this;

	if (!iterator->curr_edge->Next && !iterator->curr_edge->Next->Next)
		throw std::out_of_range("nullptr exc");


	if (iterator->curr_edge->Next)
		iterator->curr_edge = iterator->curr_edge->Next;

	else if (iterator->curr_edge->Next->Next) {
		do {
			iterator->curr_edge = iterator->curr_edge->Next;
		} while (!iterator->curr_edge->Trail);

		iterator->curr_edge = iterator->curr_edge->Trail;
	}
	return tmp;
}



template<typename T>
T operator*(AdjacencyIterator<T> iterator) { return iterator->curr_ptr->Id; }

template<typename T>
AdjacencyIterator<T> operator++(AdjacencyIterator<T> iterator) {

	AdjacencyIterator<T> tmp = *this;

	if (!iterator->curr_ptr->Next)
		throw std::out_of_range("nullptr exc");

	iterator->curr_ptr = iterator->curr_ptr->Next;

	return tmp;
}

template<typename T>
AdjacencyIterator<T>& operator++(AdjacencyIterator<T> iterator) {

	if (!iterator->curr_ptr->Next)
		throw std::out_of_range("nullptr exc");

	iterator->curr_ptr = iterator->curr_ptr->Next;

	return *this;
}



template <typename T>
Node<T>* Graph<T>::get_found_node(T key) {

	Node<T>* h = Head;
	Tail->Key = key;

	while (h->Key != key)
		h = h->Next;

	if (h == Tail)
		h = NULL;

	return h;
}

template <typename T>
Node<T>* Graph<T>::get_added_or_found_node(T key) {

	Node<T>* h;
	h = Head;
	Tail->Key = key;

	while (h->Key != key)
		h = h->Next;

	if (h == Tail) {

		Tail = new Node<T>;
		h->Count;
		h->Trail = h->Pred = NULL;
		h->Next = Tail;
	}

	return h;
}

template<class T>
void Graph<T>::add_node(T key) {

	get_added_or_found_node(key);

}

template<class T>
void Graph<T>::add_edge(T x, T y) {

	Node<T>* node_1, * node_2;
	Edge<T>* edge;
	bool is_present;

	node_1 = get_added_or_found_node(x);
	node_2 = get_added_or_found_node(y);

	edge = node_1->Trail;
	is_present = false;

	while ((edge != NULL) && (is_present == 0))
		if (edge->Id == node_2)
			is_present = true;
		else
			edge = edge->Next;

	if (is_present == 0) {

		edge = new Edge<T>;
		edge->Id = node_2;
		edge->Next = node_1->Trail;
		node_1->Trail = edge;
		node_2->Count++;
		edge->Next = node_1->Pred;
		node_1->Pred = edge;
		node_2->Count++;

		edge = new Edge<T>;
		edge->Id = node_1;
		edge->Next = node_2->Pred;
		node_2->Pred = edge;
		node_1->Count++;
		edge->Next = node_2->Trail;
		node_2->Trail = edge;
		node_1->Count++;
	}

}

template<class T>
void Graph<T>::del_edge(T x, T y)
{
	Node<T>* p, * q;
	Edge<T>* t, * r;
	bool Res;
	p = get_found_node(x);
	q = get_found_node(y);
	if (p != NULL && q != NULL)
	{
		r = p->Trail;
		Res = false;
		while ((r != NULL) && (!Res))
			if (r->Id == q)
				Res = true;
			else
				r = r->Next;
		if (Res) {
			if (r == p->Trail) {
				p->Trail = p->Trail->Next;
				p->Pred = p->Pred->Next;
				delete r;
				q->Count--;
			}
			else {
				t = p->Trail;
				while (t->Next != r)
					t = t->Next;
				t->Next = t->Next->Next;
				delete r;
				q->Count--;
			}
			del_edge(y, x);
		}
	}
}

template<class T>
void Graph<T>::print_graph() {

	Node<T>* p;
	Edge<T>* q;

	p = Head;

	while (p != Tail) {

		std::cout << p->Key << " -- [";
		q = p->Trail;
		while (q != NULL) {

			std::cout << q->Id->Key << " ";
			q = q->Next;
		}

		std::cout << "]\n";

		p = p->Next;

	}
}

template<class T>
void Graph<T>::del_node(T key) {

	Node<T>* p, * q;
	Edge<T>* r, * s;
	T x;
	p = Head;
	while (p != Tail) {
		x = p->Key;
		del_edge(x, key);
		p = p->Next;
	}
	p = get_added_or_found_node(key);
	r = p->Trail;
	while (r != NULL) {
		s = r;
		r = r->Next;
		s->Id->Count++;
		delete s;
	}
	q = Head;
	if (q == p) {
		Head = Head->Next;
		delete q;
	}
	else {
		while (q->Next != p)
			q = q->Next;
		q->Next = p->Next;
		delete p;
	}
}

template<class T>
bool Graph<T>::is_node(T key)
{
	return get_found_node(key);
}

template<class T>
bool Graph<T>::is_edge(T x, T y)
{
	Node<T>* p, * q;
	Edge<T>* r;

	p = get_found_node(x);
	q = get_found_node(y);

	if (!p || !q)
		return false;
	r = p->Trail;
	while (r) {
		if (r->Id == q)
			return true;
		else
			r = r->Next;
	}
	return false;
}

template<class T>
int Graph<T>::count_nodes() {

	Node<T>* p = Head, * q = Tail; int count = 0;
	while (p != q) {
		count++;
		p = p->Next;
	}
	return count;
}

template<class T>
int Graph<T>::count_edges()
{
	Node<T>* p = Head, * q = Tail; int count = 0;
	while (p != q) {
		count += pow_node(p->Key);
		p = p->Next;
	}
	count /= 2;
	return count;
}

template<class T>
int Graph<T>::pow_node(T key)
{
	Node<T>* h;
	h = get_found_node(key);
	int count = 0;
	if (h) {
		Edge<T>* ptr = h->Trail;
		while (ptr) {
			count++;
			ptr = ptr->Next;
		}
	}
	return count;
}

#endif
