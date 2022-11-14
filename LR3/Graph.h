#pragma once

#include <iostream>
#include <string>
#include <fstream>

template<typename Type>
struct T
{
    Type Id;
    T<Type>* Next;
};

template<typename Type>
struct L
{
    Type Key = NULL; //Имя заголовочного узла.
    int Count = NULL; //Количество предшественников.
    T<Type>* Trail = nullptr; //Указатель на список смежности.
    L<Type>* Next = nullptr; //Указатель на следующий узел в списке заголовочных узлов.
};

template<typename Type>
class DirectedGraph
{
private:
	L<Type>* Head; //Указатель на начало списка заголовочных узлов.
	L<Type>* Tail; //Указатель на фиктивный узел
	// в конце списка заголовочных узлов.
	void search_graph(Type, L<Type>*&);
	void search(Type, L<Type>*&);

public:
    class iterator_nodes;
    class iterator_edges;
    class iterator_edges_of_node;
    class iterator_nodes_of_node;

    DirectedGraph() {
        Head = Tail = new L<Type>;
    }

    void make_graph(); 
    void add_edge(Type, Type);
    void add_node(Type);
    void delete_edge(Type, Type);
    void delete_edge(iterator_edges);
    void delete_edge(iterator_edges_of_node);
    void print_graph();
    void delete_node(Type);
    void delete_node(iterator_nodes);
    void delete_node(iterator_nodes_of_node);
    bool contains_node(Type);
    bool contains_edge(Type, Type);
    int number_of_nodes();
    int number_of_edges();
    int node_degree_in(Type);
    int node_degree_out(Type);
    std::pair<int, int> edge_degree(Type, Type);
    void clear();
    bool empty();
    void read_from_file(std::string);

    iterator_nodes begin_nodes() const { return iterator_nodes(Head); };
    iterator_nodes end_nodes() const { return iterator_nodes(Tail); };

    iterator_edges begin_edges() const { return iterator_edges(Head); };
    iterator_edges end_edges() const { return iterator_edges(Tail); };

    iterator_edges_of_node begin_edges_of_node(Type key) const {
        L<Type>* curr = Head;
        while (curr) {
            if (curr->Key == key)
                return iterator_edges_of_node(curr);
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };
    iterator_edges_of_node end_edges_of_node(Type key) const {
        L<Type>* curr = Head;
        T<Type>* curr_edge;
        while (curr) {
            if (curr->Key == key) {
                curr_edge = curr->Trail;
                while (curr_edge->Next) curr_edge = curr_edge->Next;
                return iterator_edges_of_node(curr, curr_edge);
            }
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };

    iterator_nodes_of_node begin_nodes_of_node(Type key) const {
        L<Type>* curr = Head;
        while (curr) {
            if (curr->Key == key) {
                return iterator_nodes_of_node(curr);
            }
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };
    iterator_nodes_of_node end_iterator_nodes_of_node() const { return iterator_nodes_of_node(Tail); };

    inline bool operator==(const DirectedGraph<Type>&);
    inline bool operator!=(const DirectedGraph<Type>&);
    inline bool operator<(DirectedGraph<Type>&);
    inline bool operator<=(DirectedGraph<Type>&);
    inline bool operator>(DirectedGraph<Type>&);
    inline bool operator>=(DirectedGraph<Type>&);
};

template <typename Type>
void DirectedGraph<Type>::search(Type w, L<Type>*& h)
{
	h = Head;
	Tail->Key = w;
	while (h->Key != w)
		h = h->Next;
	if (h == Tail)
		h = nullptr;
}

template <typename Type>
void DirectedGraph<Type>::search_graph(Type w, L<Type>*& h)
{
	h = Head;
	Tail->Key = w;
	while (h->Key != w)
		h = h->Next;
	if (h == Tail) {
		Tail = new L<Type>;
		h->Count = 0;
		h->Trail = nullptr;
		h->Next = Tail;
	}
}

template <typename Type>
void DirectedGraph<Type>::make_graph()
{
	int x, y;
	L<Type>* p, * q;
	T<Type>* t, * r; 
	bool Res; 
	std::cout << "Enter the starting nodes of edges\n";
	std::cin >> x;
	while (x != 0)
	{
		std::cout << "Enter the ending nodes of edges\n";
		std::cin >> y;
		search_graph(x, p); search_graph(y, q);
		r = p->Trail;
		Res = false;
		while (r && !Res)
			if (r->Id == y) 
				Res = true;
			else
				r = r->Next;
		if (!Res) {
			t = new T<Type>; 
			t->Id = y;
			t->Next = p->Trail; 
			p->Trail = t; 
			q->Count++;
		}
		std::cout << "Enter the starting nodes of edges\n";
		std::cin >> x;
	}
}

template <typename Type>
void DirectedGraph<Type>::add_node(Type key)
{
	L<Type>* h;
	search_graph(key, h);
}

template <typename Type>
void DirectedGraph<Type>::add_edge(Type x, Type y)
{
	L<Type>* p, * q;
	T<Type>* t, * r;
	bool Res;
	search_graph(x, p);
	search_graph(y, q);
	r = p->Trail;
	Res = false;
	while (r && !Res) {
		if (r->Id = y)
			Res = true;
		else
			r = r->Next;
	}
	if (!Res) {
		t = new T<Type>;
		t->Id = y;
		t->Next = p->Trail;
		p->Trail = t;
		q->Count++;
	}
}

template <typename Type>
void DirectedGraph<Type>::delete_edge(Type x, Type y)
{
	L<Type>* p, * q; 
	T<Type>* t, * r; 
	bool Res;
	search(x, p); 
	search(y, q);
	if (p && q)
	{ 
		r = p->Trail;
	Res = false;
		while (r && !Res)
			if (r->Id == y) 
				Res = true;
			else 
				r = r->Next;
		if (Res) {
			if (r == p->Trail) {
				p->Trail = p->Trail->Next;
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
		}
	}
}

template <typename Type>
void DirectedGraph<Type>::print_graph()
{
	L<Type>* p;
	T<Type>* q;
	p = Head;
	while (p != Tail) {
		std::cout << '(' << p->Key;
		q = p->Trail;
		if (q)
			std::cout << " | ";
		while (q) {
			std::cout << q->Id;
			if (q->Next)
				std::cout << ", ";
			q = q->Next;
		}
		std::cout << ')';
		p = p->Next;
		std::cout << ' ';
	}
	std::cout << "\n";
}

template <typename Type>
void DirectedGraph<Type>::delete_node(Type y)
{
	/*L<Type>* p, * q;
	T<Type>* r, * s;
	Type x;
	p = Head;
	while (p != Tail) {
		x = p->Key;
		delete_edge(x, y);
		delete_edge(y, x);
		p = p->Next;
	}
	search_graph(y, p);
	r = p->Trail;
	while (r != nullptr) {
		s = r;
		r = r->Next;
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
	}*/
	L<Type>* p, * q; 
	T<Type>* r, * s; 
	Type x; 
	p = Head;
	while (p != Tail)
	{
		x = p->Key;
		delete_edge(x, y); 
		delete_edge(y, x);
		p = p->Next;
	}
	search_graph(y, p); 
	r = p->Trail;
	while (r != nullptr)
	{
		s = r;
		r = r->Next; 
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

template <typename Type>
bool DirectedGraph<Type>::contains_node(Type key)
{
	L<Type>* h;
	DirectedGraph::search(key, h);
	return h;
}

template <typename Type>
bool DirectedGraph<Type>::contains_edge(Type x, Type y)
{
	L<Type>* p, * q;
	T<Type>* r;

	search(x, p);
	search(y, q);
	if (!p || !q)
		return false;
	r = p->Trail;
	while (r) {
		if (r->Id == y)
			return true;
		else
			r = r->Next;
	}
	return false;
}

template<typename Type>
int DirectedGraph<Type>::number_of_nodes()
{
	L<Type>* p = Head, * q = Tail;
	int count = 0;
	while (p != q) {
		count++;
		p = p->Next;
	}
	return count;
}

template<typename Type>
int DirectedGraph<Type>::number_of_edges()
{
	L<Type>* p = Head, * q = Tail;
	int count = 0;
	while (p != q) {
		count += p->Count;
		p = p->Next;
	}
	return count;
}

template <typename Type>
int DirectedGraph<Type>::node_degree_in(Type key)
{
	L<Type>* h;
	DirectedGraph::search(key, h);
	if (h)
		return h->Count;
	else
		return -1;
}

template <typename Type>
int DirectedGraph<Type>::node_degree_out(Type key)
{
	L<Type>* h;
	DirectedGraph::search(key, h);
	if (h) {
		int count = 0;
		T<Type>* ptr = h->Trail;
		while (ptr) {
			count++;
			ptr = ptr->Next;
		}
		return count;
	}
	return -1;
}

template <typename Type>
std::pair<int, int> DirectedGraph<Type>::edge_degree(Type x, Type y) {
	if (contains_edge(x, y))
		return { node_degree_in(x) + node_degree_out(y) + node_degree_in(y) + node_degree_out(y) };
	else
		return { -1, -1 };
}

template <typename Type>
class DirectedGraph<Type>::iterator_nodes {
	L<Type>* curr;

public:
	explicit iterator_nodes(L<Type>* first) : curr(first) {};
	Type& operator*() { return curr->Key; }
	iterator_nodes operator+ (int n)
	{
		iterator_nodes tmp = *this;
		for (int i = 0; i < n; i++) {
			if (tmp.curr->Next->Next)
				tmp.curr = tmp.curr->Next;
			else
				throw std::out_of_range("out_of_range");
		}
		return tmp;
	}

	iterator_nodes& operator+= (int n)
	{
		for (int i = 0; i < n; i++) {
			if (curr->Next->Next)
				curr = curr->Next;
			else
				throw std::out_of_range("out_of_range");
		}
		return *this;
	}

	iterator_nodes operator++(int)
	{
		iterator_nodes tmp = *this;
		if (curr->Next->Next)
			curr = curr->Next;
		else
			throw std::out_of_range("out_of_range");
		return tmp;
	}

	iterator_nodes& operator++()
	{
		if (curr->Next->Next) {
			curr = curr->Next;
			return *this;
		}
		else
			throw std::out_of_range("out_of_range");
	}

	bool operator!=(const iterator_nodes& it) { return curr != it.curr; }
	bool operator==(const iterator_nodes& it) { return curr == it.curr; }
};

template <typename Type>
class DirectedGraph<Type>::iterator_edges {
	L<Type>* curr_node;
	T<Type>* curr_edge;

public:

	explicit iterator_edges(L<Type>* first) : curr_node(first) {
		curr_edge = curr_node->Trail;
	};

	std::pair<Type, Type> operator*() { return std::pair<Type, Type>(curr_node->Key, curr_edge->Id); }

	iterator_edges operator+ (int n) {
		iterator_edges tmp = *this;
		for (int i = 0; i < n; i++) {
			if (!tmp.curr_edge->Next && !tmp.curr_node->Next->Next)
				throw std::out_of_range("out_of_range");

			if (tmp.curr_edge->Next)
				tmp.curr_edge = tmp.curr_edge->Next;

			else if (tmp.curr_node->Next->Next) {
				do {
					tmp.curr_node = tmp.curr_node->Next;
				} while (!tmp.curr_node->Trail);

				tmp.curr_edge = tmp.curr_node->Trail;
			}
		}
		return tmp;
	}

	iterator_edges& operator+= (int n) {
		for (int i = 0; i < n; i++) {
			if (!curr_edge->Next && !curr_node->Next->Next)
				throw std::out_of_range("out_of_range");

			if (curr_edge->Next)
				curr_edge = curr_edge->Next;

			else if (curr_node->Next->Next) {
				do {
					curr_node = curr_node->Next;
				} while (!curr_node->Trail);

				curr_edge = curr_node->Trail;
			}
		}
		return *this;
	}

	iterator_edges operator++(int) {
		iterator_edges tmp = *this;

		if (!curr_edge->Next && !curr_node->Next->Next) {
			throw std::out_of_range("out_of_range");
		}

		if (curr_edge->Next)
			curr_edge = curr_edge->Next;

		else if (curr_node->Next->Next) {
			do {
				curr_node = curr_node->Next;
			} while (!curr_node->Trail);

			curr_edge = curr_node->Trail;
		}
		return tmp;
	}

	iterator_edges& operator++() {

		if (!curr_edge->Next && !curr_node->Next->Next)
			throw std::out_of_range("out_of_range");

		if (curr_edge->Next)
			curr_edge = curr_edge->Next;

		else if (curr_node->Next->Next) {
			do {
				curr_node = curr_node->Next;
			} while (!curr_node->Trail);

			curr_edge = curr_node->Trail;
		}
		return *this;
	}

	bool operator!=(const iterator_edges& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
	bool operator==(const iterator_edges& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
};

template <typename Type>
class DirectedGraph<Type>::iterator_edges_of_node {
	L<Type>* curr_node;
	T<Type>* curr_edge;

public:

	explicit iterator_edges_of_node(L<Type>* node) : curr_node(node) {
		if (!curr_node->Trail)
			throw std::out_of_range("out_of_range");
		curr_edge = curr_node->Trail;
	};

	iterator_edges_of_node(L<Type>* node, T<Type>* edge) : curr_node(node), curr_edge(edge) {};

	std::pair<Type, Type> operator*() { return std::pair<Type, Type>(curr_node->Key, curr_edge->Id); }

	iterator_edges_of_node operator+ (int n) {
		iterator_edges_of_node tmp = *this;
		for (int i = 0; i < n; i++) {
			if (!tmp.curr_edge->Next)
				throw std::out_of_range("out_of_range");//?

			tmp.curr_edge = tmp.curr_edge->Next;
		}
		return tmp;
	}

	iterator_edges_of_node& operator+= (int n) {
		for (int i = 0; i < n; i++) {
			if (!curr_edge->Next)
				throw std::out_of_range("out_of_range");//?

			curr_edge = curr_edge->Next;
		}
		return *this;
	}

	iterator_edges_of_node operator++(int) {
		iterator_edges_of_node tmp = *this;

		if (!curr_edge->Next)
			throw std::out_of_range("out_of_range");//?

		curr_edge = curr_edge->Next;

		return tmp;
	}

	iterator_edges_of_node& operator++() {

		if (!curr_edge->Next)
			throw std::out_of_range("out_of_range");

		curr_edge = curr_edge->Next;

		return *this;
	}

	bool operator!=(const iterator_edges_of_node& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
	bool operator==(const iterator_edges_of_node& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
};

template <typename Type>
class DirectedGraph<Type>::iterator_nodes_of_node {
	T<Type>* curr_node;
public:

	explicit iterator_nodes_of_node(L<Type>* node) : curr_node(node->Trail) {};

	Type operator*() { return curr_node->Id; }

	iterator_nodes_of_node operator+ (int n) {
		iterator_nodes_of_node tmp = *this;
		for (int i = 0; i < n; i++) {
			if (!tmp.curr_node->Next)
				throw std::out_of_range("out_of_range");//?

			tmp.curr_node = tmp.curr_node->Next;
		}
		return tmp;
	}

	iterator_nodes_of_node& operator+= (int n) {
		for (int i = 0; i < n; i++) {
			if (!curr_node->Next)
				throw std::out_of_range("out_of_range");//?

			curr_node = curr_node->Next;
		}
		return *this;
	}

	iterator_nodes_of_node operator++(int) {
		iterator_nodes_of_node tmp = *this;

		if (!curr_node->Next)
			throw std::out_of_range("out_of_range");//?

		curr_node = curr_node->Next;

		return tmp;
	}

	iterator_nodes_of_node& operator++() {

		if (!curr_node->Next)
			throw std::out_of_range("out_of_range");

		curr_node = curr_node->Next;

		return *this;
	}

	bool operator!=(const iterator_nodes_of_node& it) { return curr_node != it.curr_node; }
	bool operator==(const iterator_nodes_of_node& it) { return curr_node == it.curr_node; }
};

template <typename Type>
void DirectedGraph<Type>::delete_edge(DirectedGraph::iterator_edges it)
{
	delete_edge((*it).first, (*it).second);
}

template <typename Type>
void DirectedGraph<Type>::delete_edge(DirectedGraph::iterator_edges_of_node it)
{
	delete_edge((*it).first, (*it).second);
}

template <typename Type>
void DirectedGraph<Type>::delete_node(DirectedGraph::iterator_nodes it)
{
	delete_node(*it);
}

template <typename Type>
void DirectedGraph<Type>::delete_node(DirectedGraph::iterator_nodes_of_node it)
{
	delete_node(*it);
}

template <typename Type>
bool DirectedGraph<Type>::empty()
{
	return Head == Tail;
}

template <typename Type>
void DirectedGraph<Type>::clear()
{
	L<Type>* curr_node = Head, * tmp_node;
	T<Type>* curr_edge, * tmp_edge;
	while (curr_node) {
		curr_edge = curr_node->Trail;
		while (curr_edge) {
			tmp_edge = curr_edge->Next;
			delete_edge(curr_node->Key, curr_edge->Id);
			curr_edge = tmp_edge;
		}
		curr_node = curr_node->Next;
	}
	curr_node = Head;
	while (curr_node) {
		tmp_node = curr_node->Next;
		delete_node(curr_node->Key);
		curr_node = tmp_node;
	}
}

template <typename Type>
void DirectedGraph<Type>::read_from_file(std::string file_path)
{
	std::string line;
	std::ifstream in(file_path);
	if (in.is_open()) {
		while (getline(in, line)) {
			Type x, y;
			in >> x >> y;
			add_edge(x, y);
		}
	}
	in.close();
}


template <typename Type>
inline bool DirectedGraph<Type>::operator==(const DirectedGraph<Type>& s2)
{
	return a_contains_all_nodes_of_b(Head, Tail, s2.Head, s2.Tail) && a_contains_all_nodes_of_b(s2.Head, s2.Tail, Head, Tail);
}

template <typename Type>
inline bool DirectedGraph<Type>::operator!=(const DirectedGraph<Type>& s2)
{
	return !(*this == s2);
}

template <typename Type>
inline bool DirectedGraph<Type>::operator<(DirectedGraph<Type>& s2)
{
	return number_of_edges() * number_of_nodes() < s2.number_of_edges() * s2.number_of_nodes();
}

template <typename Type>
inline bool DirectedGraph<Type>::operator>(DirectedGraph<Type>& s2)
{
	return number_of_edges() * number_of_nodes() > s2.number_of_edges() * s2.number_of_nodes();
}

template <typename Type>
inline bool DirectedGraph<Type>::operator<=(DirectedGraph<Type>& s2)
{
	return *this < s2 || *this == s2;
}

template <typename Type>
inline bool DirectedGraph<Type>::operator>=(DirectedGraph<Type>& s2)
{
	return *this > s2 || *this == s2;
}