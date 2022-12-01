#pragma once
//
// Created by denis koltovich on 15.11.2022.
//
#include "iostream"
#include<vector>
#include <algorithm>


template<typename Type>
struct T
{
    Type id;
    T<Type>* Next;
};

template<typename Type>
struct L
{
    Type Key = NULL;
    int Count = NULL; 
    T<Type>* Trail = nullptr;
    L<Type>* Next = nullptr; 
};

template<typename Type>
class Graph
{

private:
    typedef L<Type> value_type;
    typedef value_type* value_pointer;
    typedef T<Type>* edge_pointer;

    value_pointer Head; 
    value_pointer Tail;
    // находит вершину  по ключу, если такой вершины нет, то создает ее
    void getKey_or_addKey(Type key, value_pointer& key_pointer)     {
        key_pointer = Head; Tail->Key = key;
        while (key_pointer->Key != key) key_pointer = key_pointer->Next;
        if (key_pointer == Tail)
        {
            Tail = new value_type;
            key_pointer->Count = 0;
            key_pointer->Trail = nullptr;
            key_pointer->Next = Tail;
        }
    }

    //находит вершину по ключу
    void findKey(Type key, value_pointer& key_pointer)
    {
        key_pointer = Head;
        Tail->Key = key; 
        while (key_pointer->Key != key) key_pointer = key_pointer->Next;
        if (key_pointer == Tail) //В списке заголовочных узлов нет узла с ключом key.
            key_pointer = nullptr;
    }
public:

    Graph() 
    { 
        Head = new value_type;
        Tail = Head;
    }
    ~Graph() {
        node_iterator it2 = node_iterator(Head);

        node_iterator it = node_iterator(Head);
        int s = NumOfNodes();
        for (int i = 0; i < s - 1; ++i) {
            it2++;
            DeleteNode(it);
            it = it2;
        }
    }

   Graph(Graph& graph) {
        node_iterator it_node = node_iterator(graph.begin_nodes());
        edge_iterator it_edges = edge_iterator(graph.begin_edges());
        for (int i = 0; i < graph.NumOfNodes(); ++i) { AddNode(*it_node); it_node++; }
        for (int i = 0; i < graph.NumOfEdges(); ++i) { 
            AddEdge((*it_edges).first, (*it_edges).second);
            it_edges++; 
        }
        
   }
    // итератор по ребрам
    class edge_iterator {
        value_pointer curr_node;
        edge_pointer curr_edge;

    public:

        explicit edge_iterator(value_pointer first) : curr_node(first) {
            curr_edge = curr_node->Trail;
        };

        std::pair<Type, Type> operator*() { return std::pair<Type, Type>(curr_node->Key, curr_edge->id); }

        edge_iterator& operator+= (int n) {
            for (int i = 0; i < n; i++)
            {
                if (!curr_edge->Next && !curr_node->Next->Next)
                    throw std::out_of_range("iterator out of range");

                if (curr_edge->Next) curr_edge = curr_edge->Next; // передвинулсь  в списке смежности 
                else if (curr_node->Next->Next) {
                    do {
                        curr_node = curr_node->Next;
                    } while (!curr_node->Trail); // след вершина, у которой есть смежные вершины

                    curr_edge = curr_node->Trail;
                }
            }
            return *this;
        }

        edge_iterator operator++(int) {
            if (!curr_edge->Next && !curr_node->Next->Next) {
                throw std::out_of_range("iterator out of range");
            }

            if (curr_edge->Next) curr_edge = curr_edge->Next;  // передвинулсь  в списке смежности 

            else if (curr_node->Next->Next) { //если не фиктивный узел
                do {
                    curr_node = curr_node->Next; 
                } while (!curr_node->Trail);// след вершина, у которой есть смежные вершины
                curr_edge = curr_node->Trail;
            }
            return *this;
        }

        bool operator!=(const edge_iterator& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
        bool operator==(const edge_iterator& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
    };

    // константный итератор по ребрам
    class Const_edge_iterator {
        value_pointer curr_node;
        edge_pointer curr_edge;

    public:

        explicit Const_edge_iterator(value_pointer first) : curr_node(first) {
            curr_edge = curr_node->Trail;
        };

        std::pair<Type, Type> operator*() const { return std::pair<Type, Type>(curr_node->Key, curr_edge->id); }

        Const_edge_iterator operator+= (int n) const {
            for (int i = 0; i < n; i++)
            {
                if (!curr_edge->Next && !curr_node->Next->Next)
                    throw std::out_of_range("iterator out of range");

                if (curr_edge->Next) curr_edge = curr_edge->Next; // передвинулсь  в списке смежности 
                else if (curr_node->Next->Next) {
                    do {
                        curr_node = curr_node->Next;
                    } while (!curr_node->Trail); // след вершина, у которой есть смежные вершины

                    curr_edge = curr_node->Trail;
                }
            }
            return this;
        }
        
        Const_edge_iterator operator++(int) const {
            if (!curr_edge->Next && !curr_node->Next->Next) {
                throw std::out_of_range("iterator out of range");
            }

            if (curr_edge->Next) curr_edge = curr_edge->Next;  // передвинулсь  в списке смежности 

            else if (curr_node->Next->Next) { //если не фиктивный узел
                do {
                    curr_node = curr_node->Next;
                } while (!curr_node->Trail);// след вершина, у которой есть смежные вершины
                curr_edge = curr_node->Trail;
            }
            return this;
        }

        bool operator!=(const Const_edge_iterator& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
        bool operator==(const Const_edge_iterator& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
    };
        
    // итератор по вершинам
    class node_iterator {
        value_pointer current_node;
    public:

        explicit node_iterator(value_pointer first) : current_node(first) {};

        Type& operator*() { return current_node->Key; }


        node_iterator& operator+= (int n) {
            for (int i = 0; i < n; i++){
                if (!current_node->Next->Next)  throw std::out_of_range("iterator out of range");
                else current_node = current_node->Next;
            }
            return *this;
        }

        node_iterator operator++(int) {
            if (!current_node->Next->Next)  throw std::out_of_range("iterator out of range");
            else current_node = current_node->Next;  
            return *this;
        }

        bool operator!=(const node_iterator& it) { return current_node != it.current_node; }
        bool operator==(const node_iterator& it) { return current_node == it.current_node; }
    };



    // reverse модификации для итераторов
    node_iterator RBegin() { return node_iterator(Tail); }
    node_iterator REnd() { return node_iterator(Head); }
    edge_iterator R_edge_Bbegin()  { return edge_iterator(Tail); };
    edge_iterator R_edge_End()  { return edge_iterator(Head); };
    
    // константный итератор по вершинам
    class const_node_iterator {
        value_pointer current_node;
    public:

        explicit const_node_iterator(value_pointer first) : current_node(first) {};

        Type& operator*() { return current_node->Key; }

        const_node_iterator& operator+= (int n) const {
            for (int i = 0; i < n; i++) {
                if (!current_node->Next->Next)  throw std::out_of_range("iterator out of range");
                else current_node = current_node->Next;
            }
            return this;
        }

        const_node_iterator operator++(int) const {
            if (!current_node->Next->Next)  throw std::out_of_range("iterator out of range");
            else current_node = current_node->Next;
            return this;
        }

        bool operator!=(const const_node_iterator& it) { return current_node != it.current_node; }
        bool operator==(const const_node_iterator& it) { return current_node == it.current_node; }
    };

    // итератор по смежным вершинам
    class adjacent_nodes_iterator {
        edge_pointer curr_node;
    public:

        explicit adjacent_nodes_iterator(value_pointer node) : curr_node(node->Trail) {};

        Type operator*() { return curr_node->id; }

        adjacent_nodes_iterator& operator+= (int n) {
            for (int i = 0; i < n; i++)
            {
                if (!curr_node->Next) throw std::out_of_range("iterator out of range");
                curr_node = curr_node->Next;
            }
            return *this;
        }

        adjacent_nodes_iterator operator++(int) {
            if (!curr_node->Next) throw std::out_of_range("iterator out of range");
            curr_node = curr_node->Next;
            return *this;
        }

        bool operator!=(const adjacent_nodes_iterator& it) { return curr_node != it.curr_node; }
        bool operator==(const adjacent_nodes_iterator& it) { return curr_node == it.curr_node; }
    };


    // константный итератор по смежным вершинам 
    class const_adjacent_nodes_iterator {
        edge_pointer curr_node;
    public:

        explicit const_adjacent_nodes_iterator(value_pointer node) : curr_node(node->Trail) {};

        Type operator*() { return curr_node->id; }

        const_adjacent_nodes_iterator& operator+= (int n) const {
            for (int i = 0; i < n; i++)
            {
                if (!curr_node->Next) throw std::out_of_range("iterator out of range");
                curr_node = curr_node->Next;
            }
            return this;
        }

        const_adjacent_nodes_iterator operator++(int) const {
            if (!curr_node->Next) throw std::out_of_range("iterator out of range");
            curr_node = curr_node->Next;
            return this;
        }

        bool operator!=(const const_adjacent_nodes_iterator& it) { return curr_node != it.curr_node; }
        bool operator==(const const_adjacent_nodes_iterator& it) { return curr_node == it.curr_node; }
    };
    
    // итератор по инцидентным ребрам
    class incidence_edges_iterator {
        value_pointer curr_node;
        edge_pointer curr_edge;

    public:

        explicit incidence_edges_iterator(value_pointer node) : curr_node(node) {
            if (!curr_node->Trail) throw std::out_of_range("iterator out of range");
            curr_edge = curr_node->Trail;
        };

        incidence_edges_iterator(value_pointer node, edge_pointer edge) : curr_node(node), curr_edge(edge) {};

        std::pair<Type, Type> operator*() { return std::pair<Type, Type>(curr_node->Key, curr_edge->id); }

        incidence_edges_iterator& operator+= (int n) {
            for (int i = 0; i < n; i++)
            {
                if (!curr_edge->Next)
                    throw std::out_of_range("iterator out of range");

                curr_edge = curr_edge->Next;
            }
            return *this;
        }

        incidence_edges_iterator operator++(int) {
            incidence_edges_iterator tmp = *this;

            if (!curr_edge->Next)
                throw std::out_of_range("iterator out of range");

            curr_edge = curr_edge->Next;

            return tmp;
        }

        bool operator!=(const incidence_edges_iterator& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
        bool operator==(const incidence_edges_iterator& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
    };

    // константный итератор по инцидентным ребрам
    class const_incidence_edges_iterator {
        value_pointer curr_node;
        edge_pointer curr_edge;

    public:

        explicit const_incidence_edges_iterator(value_pointer node) : curr_node(node) {
            if (!curr_node->Trail) throw std::out_of_range("iterator out of range");
            curr_edge = curr_node->Trail;
        };

        const_incidence_edges_iterator(value_pointer node, edge_pointer edge) : curr_node(node), curr_edge(edge) {};

        std::pair<Type, Type> operator*() { return std::pair<Type, Type>(curr_node->Key, curr_edge->id); }

        const_incidence_edges_iterator& operator+= (int n) {
            for (int i = 0; i < n; i++)
            {
                if (!curr_edge->Next)
                    throw std::out_of_range("iterator out of range");

                curr_edge = curr_edge->Next;
            }
            return this;
        }

        const_incidence_edges_iterator operator++(int) {
            const_incidence_edges_iterator tmp = this;

            if (!curr_edge->Next)
                throw std::out_of_range("iterator out of range");

            curr_edge = curr_edge->Next;

            return tmp;
        }

        bool operator!=(const const_incidence_edges_iterator& it) { return (curr_edge, curr_node) != (it.curr_edge, it.curr_node); }
        bool operator==(const const_incidence_edges_iterator& it) { return (curr_edge, curr_node) == (it.curr_edge, it.curr_node); }
    };

    // удаление вершин
    void DeleteNode(node_iterator it) { DeleteNode(*it); }
    void DeleteNode(adjacent_nodes_iterator it) { DeleteNode(*it); }

    // проверка на пустой контейнер
    bool empty() { return Head == Tail; }

    // очистка контейнера
    void clear() {
        value_pointer curr_node = Head, tmp_node;
        edge_pointer curr_edge, tmp_edge;
        while (curr_node) {

            curr_edge = curr_node->Trail;
            while (curr_edge) {
                tmp_edge = curr_edge->Next;
                DeleteEdge(curr_node->Key, curr_edge->id);
                curr_edge = tmp_edge;
            }

            curr_node = curr_node->Next;
        }
        curr_node = Head;
        while (curr_node) {
            tmp_node = curr_node->Next;
            DeleteNode(curr_node->Key);
            curr_node = tmp_node;
        }
    }

    // добавление ребра
    void AddEdge(Type x, Type y)
    {
        value_pointer p, q;
        edge_pointer t, x_trail; 
        bool exist_edge;
        getKey_or_addKey(x, p);
        getKey_or_addKey(y, q);
        x_trail = p->Trail;
        exist_edge = false;
        while (x_trail && !exist_edge)
            if (x_trail->id == y) exist_edge = true;
            else x_trail = x_trail->Next;
        if (!exist_edge){
            t = new T<Type>; t->id = y; t->Next = p->Trail;
            p->Trail = t;
            q->Count++;
        }
    }

    // 
    void AddNode(Type key) {
        value_pointer h;
        getKey_or_addKey(key, h);
    }


    // удаление ребра
    void DeleteEdge(Type x, Type y)
    {
        if (!isConteinsEdge(x, y)) return;
        value_pointer p, q;
        edge_pointer t, x_trail;
        bool exist_edge;
        findKey(x, p); findKey(y, q);
        x_trail = p->Trail; exist_edge = false;
        while (x_trail && !exist_edge)
            if (x_trail->id == y) exist_edge = true;
            else x_trail = x_trail->Next;
        // находим это ребро к у 
        if (exist_edge) {
            if (x_trail == p->Trail) {
                p->Trail = p->Trail->Next;
                delete x_trail;
                q->Count--;
            }
            else {
                t = p->Trail;
                while (t->Next != x_trail) t = t->Next;
                t->Next = t->Next->Next;
                delete x_trail;
                q->Count--;
            }
        }

    }
    void DeleteEdge(edge_iterator it) { DeleteEdge((*it).first, (*it).second); }
    void DeleteEdge(incidence_edges_iterator it) { DeleteEdge((*it).first, (*it).second); }


    //удаление вершины
    void DeleteNode(Type y)
    {
        if (!isContainsNode(y)) return;
        value_pointer p,  q; 
        edge_pointer r, s; 
        Type x; 
        //Удаление всех дуг (x,y), оканчивающихся  в вершине y.
        p = Head;
        while (p != Tail)
        {
            x = p->Key;
            DeleteEdge(x, y); DeleteEdge(y, x);
            p = p->Next;
        }
        //Удаление списка смежности вершины y.
        getKey_or_addKey(y, p);
        r = p->Trail;
        while (r != nullptr)
        {
            s = r;
            r = r->Next;
            delete s;
        }
        //Удаление узла, содержащего вершину y, из списка заголовочных узлов.
        q = Head;
        if (q == p) { Head = Head->Next; delete q; }
        else {
            while (q->Next != p) q = q->Next;
            q->Next = p->Next; delete p;
        }
    }

    //проверка на наличие вершины в графе
    bool isContainsNode(Type key) {
        value_pointer h; 
        findKey(key, h);
        return h;
    }
    // проверка на наличие ребра в графе
    bool isConteinsEdge(Type x, Type y) {
        value_pointer p, q;
        edge_pointer r;

        findKey(x, p);
        findKey(y, q);
        if (!p || !q) return false;
        r = p->Trail;
        while (r) {
            if (r->id == y) return true;
            else r = r->Next;
        }
        return false;
    }

    // количество вершин
    int NumOfNodes(){
        //Функция возвращает количество вершин графа
        value_pointer p = Head;
        int count = 0;
        while (p != Tail) {
            count++; p = p->Next;
        }
        return count;
    }


    // количество ребер
    int NumOfEdges() {
        //Функция возвращает количество дуг графа
        value_pointer p = Head; int count = 0;
        while (p != Tail) {
            count += p->Count; p = p->Next;
        }
        return count;
    }

    // сколько ребер входит в вершину
    int NodeDegreeIn(Type key) {
        if (!isContainsNode(key)) return -1;
        value_pointer v;
        findKey(key, v);
        return v->Count;
    }

    // сколько ребер выходит из вершины
    int NodeDegreeOut(Type key) {
        if (!isContainsNode(key)) return -1;
        value_pointer h;
        findKey(key, h);
        int count = 0;
        edge_pointer ptr = h->Trail; // список смежности
        while (ptr) {
            count++; ptr = ptr->Next;
        }
        return count;
    }


    // степень ребра
    std::pair<int, int> EdgeDegree(Type x, Type y) {
        return isConteinsEdge(x, y) ? std::make_pair(NodeDegreeOut(x) + NodeDegreeIn(x),
            NodeDegreeOut(y) + NodeDegreeIn(y)) : 
            std::make_pair(-1,-1);
    }



    node_iterator begin_nodes() const { return node_iterator(Head); };
    node_iterator end_nodes() const { return node_iterator(Tail); };

    edge_iterator begin_edges() const { return edge_iterator(Head); };
    edge_iterator end_edges() const { return edge_iterator(Tail); };

    incidence_edges_iterator begin_edges_of_node(Type key) const {
        value_pointer current_node = Head;
        while (current_node) {
            if (current_node->Key == key)
                return incidence_edges_iterator(current_node);
            current_node = current_node->Next; //идем по узлам из списка заголовочных
        }
        throw std::out_of_range("node_not_found");
    };
    incidence_edges_iterator end_edges_of_node(Type key) const {
        value_pointer current_node = Head;
        edge_pointer curr_edge;
        while (current_node) {
            if (current_node->Key == key) {
                curr_edge = current_node->Trail;
                while (curr_edge->Next) curr_edge = curr_edge->Next;
                return incidence_edges_iterator(current_node, curr_edge);
            }
            current_node = current_node->Next;
        }
        throw std::out_of_range("iterator out of range");
    };

    adjacent_nodes_iterator begin_nodes_of_node(Type key) const {
        value_pointer current_node = Head;
        while (current_node) {
            if (current_node->Key == key) {
                return adjacent_nodes_iterator(current_node);
            }
            current_node = current_node->Next;
        }
        throw std::out_of_range("iterator out of range");
    };
    adjacent_nodes_iterator end_iterator_nodes_of_node() const { return adjacent_nodes_iterator(Tail); };

    // содержит ли граф все ребра другого графа
    bool is_have_equal_edges(edge_pointer curr1, edge_pointer curr2) {
        bool is_present;
        edge_pointer begin = curr2;
        while (curr1) {
            is_present = false;
            curr2 = begin;
            while (curr2) {
                if (curr1->id == curr2->id) {
                    is_present = true;
                    break;
                }
                curr2 = curr2->Next;
            }
            if (!is_present)
                return false;
            curr1 = curr1->Next;
        }
        return true;
    }


    value_pointer getHead() { return Head; }
    value_pointer getTail() { return Tail; }

    // содержит ли граф все вершины другого графа
    bool is_equal_nodes(Graph<Type> g1, Graph<Type> g2) {
        bool is_present;
        value_pointer curr1 = g1.getHead();
        value_pointer begin = g2.getHead();
        value_pointer tail1 = g1.getTail();
        value_pointer tail2 = g2.getTail();
        while (curr1 != tail1) {
            is_present = false;
            value_pointer curr2 = begin;
            while (curr2 != tail2) {
                if (curr1->Key == curr2->Key) {
                    if (is_have_equal_edges(curr1->Trail, curr2->Trail) && is_have_equal_edges(curr2->Trail, curr1->Trail))
                        is_present = true;
                        break;
                    return false;
                   
                }
                curr2 = curr2->Next;
            }
            if (!is_present)
                return false;
            curr1 = curr1->Next;
        }
        return true;
    }

    // операторы сравнения
    inline bool operator==( Graph<Type>& g2) {
        return is_equal_nodes(*this, g2) && is_equal_nodes(*this, g2);
    }
    inline bool operator!=(Graph<Type>& s2) {
        return !(*this == s2);
    }
    inline bool operator<(Graph<Type>& s2) {
        return NumOfEdges() * NumOfNodes() < s2.NumOfEdges() * s2.NumOfNodes();
    }
    inline bool operator> (Graph<Type>& s2) {
        return NumOfEdges() * NumOfNodes() > s2.NumOfEdges() * s2.NumOfNodes();
    }
    inline bool operator <= (Graph<Type>& s2) {
        return *this < s2 || *this == s2;
    }
    inline bool operator >= (Graph<Type>& s2) {
        return *this > s2 || *this == s2;
    }


   // оператор доступа к элементу
   value_pointer operator[](Type index) {
        value_pointer node;
        findKey(index, node);
        if(node == nullptr) throw std::invalid_argument("No such node found");
        return node;
    }
   
   //оператор присваивания
    Graph<value_type>& operator=(const Graph<value_type>& graph)
    {
        while (Tail != nullptr)
        {
            DeleteNode(Head->Key);
        }
        value_pointer vp = graph.Head;
        for (int i = 0; i < graph.NumOfNodes(); i++)
        {
            this->AddNode(vp->Key);
            edge_pointer ribTraveller = vp->Trail;
            for (int j = 0; j < vp->Count; j++)
            {
                this->AddNode(ribTraveller->id);
                this->AddEdge(vp->Key, ribTraveller->id);
                ribTraveller = ribTraveller->Next;
            }
            vp = vp->Next;
        }
        return *this;
    }
};



//оператор вывода графа на экран

template<typename Type>
std::ostream& operator<< (std::ostream& os, Graph<Type>& g)
{
    typedef L<Type> value_type;
    typedef value_type* value_pointer;
    typedef T<Type>* edge_pointer;
    auto p_ = Graph<int>::node_iterator(g.getHead());
    auto q_ = Graph<int>::node_iterator(g.getTail());


    value_pointer p;
    edge_pointer q;
    std::vector<value_pointer> vector_p;

    auto getkey = [](value_pointer n) {};
    p = g.getHead();
    while (p != g.getTail() && p_ != q_ ) {
        os << '(' << p->Key;
        q = p->Trail;
        if (q)
            os << " | ";
        while (q) {
            os << q->id;
            if (q->Next)
                os << ", ";
            q = q->Next;
        }
        vector_p.push_back(p);
        os << ')';
        p = p->Next;
        os << ' ';
    }
    os << "\n";
    std::for_each(vector_p.cbegin(), vector_p.cend(), getkey);  
    return os;
}
