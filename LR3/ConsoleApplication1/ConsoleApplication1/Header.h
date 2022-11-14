#pragma once
#include <iostream>

template<typename T>
struct Node;

template<typename T>
struct Edge
{
    Node<T>* Id;
    Edge<T>* Next;
};

template<typename T>
struct Node
{
    T Key = NULL;
    int Count = NULL;
    Edge<T>* Trail = nullptr;
    Edge<T>* Pred = nullptr;
    Node<T>* Next = nullptr;
};

template<typename T>
struct NodeIterator {
    using pointer = Node<T>*;

    explicit NodeIterator(pointer ptr) : curr_ptr(ptr) {};

    bool operator==(const NodeIterator& other) { return this->curr_ptr == other.curr_ptr; }
    bool operator!=(const NodeIterator& other) { return this->curr_ptr != other.curr_ptr; }

    T operator*() const {
        if (curr_ptr == nullptr) 
            throw std::invalid_argument("nullptr exc");
            
        return curr_ptr->Key;
        
    }

    NodeIterator& operator++() {
        if (curr_ptr == nullptr) 
            throw std::invalid_argument("nullptr exc");
            
        curr_ptr = curr_ptr->Next;
        return *this;
    }

    NodeIterator operator++(int) {
        NodeIterator tmp = *this;
        if (curr_ptr == nullptr) 
            throw std::invalid_argument("nullptr exc");
            
        curr_ptr = curr_ptr->Next;
        return tmp;
    }

private:
    pointer curr_ptr;
};

template<typename T>
struct EdgeIterator {

    using pointer_node = Node<T>*;
    using pointer_edge = Edge<T>*;

    explicit EdgeIterator(Node<T>* first) : curr_node(first) {
        curr_edge = curr_node->Trail;
    };

    bool operator==(const EdgeIterator& other) { return this->curr_ptr == other.curr_ptr; }
    bool operator!=(const EdgeIterator& other) { return this->curr_ptr != other.curr_ptr; }

    std::pair<T, T> operator*() const { return std::pair<T, T>(curr_node->Key, curr_edge->Id); }

    EdgeIterator& operator++() {

        if (!curr_edge->Next && !curr_node->Next->Next)
            throw std::out_of_range("nullptr exc");

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

    EdgeIterator operator++(int) {
        EdgeIterator tmp = *this;

        if (!curr_edge->Next && !curr_node->Next->Next) 
            throw std::out_of_range("nullptr exc");
        

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

private:
    pointer_node curr_node;
    pointer_edge curr_edge;
};

template<typename T>
struct AdjacencyIterator {
public:

    using pointer = Edge<T>*;

    explicit AdjacencyIterator(Node<T>* node) : curr_ptr(node->Trail) {};

    bool operator!=(const AdjacencyIterator& it) { return curr_ptr != it.curr_ptr; }
    bool operator==(const AdjacencyIterator& it) { return curr_ptr == it.curr_ptr; }

    T operator*() { return curr_ptr->Id; }

    AdjacencyIterator operator++(int) {
        AdjacencyIterator tmp = *this;

        if (!curr_ptr->Next)
            throw std::out_of_range("nullptr exc");

        curr_ptr = curr_ptr->Next;

        return tmp;
    }

    AdjacencyIterator& operator++() {

        if (!curr_ptr->Next)
            throw std::out_of_range("nullptr exc");

        curr_ptr = curr_ptr->Next;

        return *this;
    }

private:
    pointer curr_ptr;
};


template<typename T>
class Graph
{

private:
    Node<T>* Head;
    Node<T>* Tail;

    Node<T>* SearchGraph(T w);
    Node<T>* Search(T w);
public:
    Graph() { Head = Tail = new Node<T>; }
    void create_graph();
    void add_edge(T, T);
    void add_node(T);
    void del_edge(T, T);
    void print_graph();
    void del_node(T);
    bool is_node(T);
    bool is_edge(T, T);
    int count_nodes();
    int count_edges();
    int pow_node(T);
};



template <typename T>
Node<T>* Graph<T>::Search(T w)
{
    Node<T>* h = Head;
    Tail->Key = w;
    while (h->Key != w)
        h = h->Next;
    if (h == Tail)
        h = NULL;
    return h;
}

template <typename T>
Node<T>* Graph<T>::SearchGraph(T w)
{
    Node<T>* h;
    h = Head;
    Tail->Key = w;
    while (h->Key != w)
        h = h->Next;
    if (h == Tail)
    {
        Tail = new Node<T>;
        h->Count;
        h->Trail = h->Pred = NULL;
        h->Next = Tail;
    }
    return h;
}

template<typename T>
void Graph<T>::create_graph()
{
    T x, y;
    Node<T>* p, * q;
    Edge<T>* t, * r;
    bool Res;

    std::cout << "¬водите начальную вершину дуги: ";
    std::cin >> x;
    while (x != 0) {
        std::cout << "¬водите конечную вершину дуги: ";
        std::cin >> y;
        p = SearchGraph(x);
        q = SearchGraph(y);
        r = p->Trail;
        Res = false;
        while ((r != NULL) && (!Res))
            if (r->Id == q)
                Res = true;
            else
                r = r->Next;
        if (!Res)
        {
            t = new Edge<T>;
            t->Id = q;
            t->Next = p->Trail;
            p->Trail = t;
            q->Count++;
            t->Next = p->Pred;
            p->Pred = t;
            q->Count++;
            t = new Edge<T>;
            t->Id = p;
            t->Next = q->Pred;
            q->Pred = t;
            p->Count++;
            t->Next = q->Trail;
            q->Trail = t;
            p->Count++;
        }
        std::cout << "¬водите начальную вершину дуги: ";
        std::cin >> x;
    }
}

template<typename T>
void Graph<T>::add_node(T key) {
    SearchGraph(key);
}

template<typename T>
void Graph<T>::add_edge(T x, T y)
{
    Node<T>* p, * q;
    Edge<T>* t, * r;
    bool Res;

    p = SearchGraph(x);
    q = SearchGraph(y);
    r = p->Trail;
    Res = false;
    while ((r != NULL) && (!Res))
        if (r->Id == q)
            Res = true;
        else
            r = r->Next;
    if (!Res) {
        t = new Edge<T>;
        t->Id = q;
        t->Next = p->Trail;
        p->Trail = t;
        q->Count++;
        t->Next = p->Pred;
        p->Pred = t;
        q->Count++;
        t = new Edge<T>;
        t->Id = p;
        t->Next = q->Pred;
        q->Pred = t;
        p->Count++;
        t->Next = q->Trail;
        q->Trail = t;
        p->Count++;
    }
}

template<typename T>
void Graph<T>::del_edge(T x, T y)
{
    Node<T>* p, * q;
    Edge<T>* t, * r;
    bool Res;
    p = Search(x);
    q = Search(y);
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

template<typename T>
void Graph<T>::print_graph()
{
    Node<T>* p;
    Edge<T>* q;

    p = Head;
    while (p != Tail)
    {
        std::cout << p->Key << "((";
        q = p->Trail;
        while (q != NULL)
        {
            std::cout << q->Id->Key << " ";
            q = q->Next;
        }
        std::cout << ")(";
        q = p->Pred;
        while (q != NULL)
        {
            std::cout << q->Id->Key << " ";
            q = q->Next;
        }
        std::cout << "))";
        p = p->Next;
        std::cout << " ";
    }
}


template<typename T>
void Graph<T>::del_node(T key)
{
    Node<T>* p, * q;
    Edge<T>* r, * s;
    T x;
    p = Head;
    while (p != Tail) {
        x = p->Key;
        del_edge(x, key);
        p = p->Next;
    }
    p = SearchGraph(key);
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

template<typename T>
bool Graph<T>::is_node(T key)
{
    return Search(key);
}

template<typename T>
bool Graph<T>::is_edge(T x, T y)
{
    Node<T>* p, * q;
    Edge<T>* r;

    p = Search(x);
    q = Search(y);

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

template<typename T>
int Graph<T>::count_nodes() {

    Node<T>* p = Head, * q = Tail; int count = 0;
    while (p != q) {
        count++;
        p = p->Next;
    }
    return count;
}

template<typename T>
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

template<typename T>
int Graph<T>::pow_node(T key)
{
    Node<T>* h;
    h = Search(key);
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
