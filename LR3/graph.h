//
// Created by konstantin on 27.10.22.
//

#ifndef STL_GRAPH_GRAPH_H
#define STL_GRAPH_GRAPH_H

#include <iostream>
#include <memory>
#include <vector>
#include "error.h"

template<class T>
struct Node;

template<class T>
class graph;

template<class T>
struct Node {
    T data;
    std::vector<Node<T> *> next_node;
    int adjacent_counter = 0;
};

template<class T>
class graph {

public:
    typedef Node<T> *node;
    typedef T value_type;
    typedef std::vector<node> list_node;
    typedef std::vector<std::pair<T, T>> list_edge;

    class NodeIterator {
    public:
        typedef Node<T> **pointer;

        friend class graph;

        NodeIterator &operator=(const NodeIterator &other) {
            element = other.element;
            position = other.position;
            size_st = other.size_st;
            return *this;
        }

        virtual value_type operator*() {
            return (*(*element)).data;
        }

        virtual bool operator==(const NodeIterator &other) {
            return element == other.element;
        }

        virtual bool operator!=(const NodeIterator &other) {
            return element != other.element;
        }

        virtual NodeIterator &operator++() {
            if (position == size_st) throw Exception("OUT OF RANGE");
            element++;
            position++;
            return *this;
        }

        virtual NodeIterator &operator++(int) {
            if (position == size_st) throw Exception("OUT OF RANGE");
            NodeIterator temp = *this;

            element++;
            position++;
            return temp;
        }

        virtual NodeIterator &operator--() {
            if (position == 0) throw Exception("OUT OF RANGE");
            element--;
            position--;
            return *this;
        }

        virtual NodeIterator &operator--(int) {
            if (position == 0) throw Exception("OUT OF RANGE");
            NodeIterator temp = *this;

            element--;
            position--;
            return temp;
        }

        NodeIterator(const NodeIterator &other) : element(other.element),
                                                  position(other.position), size_st(other.size_st) {};
    private:
        NodeIterator(pointer element_pointer, int value_index, int size) : element(element_pointer),
                                                                           position(value_index), size_st(size) {};
    protected:
        pointer element;

        int position;

        int size_st;
    };

    class NodeIteratorReverse : public NodeIterator {
    public:
        typedef Node<T> **pointer;

        friend class graph;

        NodeIteratorReverse(const NodeIteratorReverse &other) : NodeIterator(other) {};

        NodeIteratorReverse &operator=(const NodeIteratorReverse &other) {
            this->element = other.element;
            this->position = other.position;
            this->size_st = other.size_st;
            return *this;
        }

        value_type operator*() {
            return (*(*this->element)).data;
        }

        bool operator==(const NodeIteratorReverse &other) {
            return this->element == other.element;
        }

        bool operator!=(const NodeIteratorReverse &other) {
            return this->element != other.element;
        }

        NodeIteratorReverse &operator++() {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            this->element--;
            this->position--;
            return *this;
        }

        NodeIteratorReverse &operator++(int) {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            NodeIteratorReverse temp = *this;

            this->element--;
            this->position--;
            return temp;
        }

        NodeIteratorReverse &operator--() {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            this->element++;
            this->position++;
            return *this;
        }

        NodeIteratorReverse &operator--(int) {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            NodeIteratorReverse temp = *this;

            this->element++;
            this->position++;
            return temp;
        }

    private:
        NodeIteratorReverse(pointer element_pointer, int value_index, int size) :
                NodeIterator(element_pointer, value_index, size) {};

    };

    class EdgeIterator {
    public:
        typedef std::pair<T, T> *pointer;

        friend class graph;

        virtual bool operator==(const EdgeIterator &other) {
            return iterator == other.iterator;
        }

        virtual bool operator!=(const EdgeIterator &other) {
            return iterator != other.iterator;
        }

        EdgeIterator &operator=(const EdgeIterator &other) {
            iterator = other.iterator;
            position = other.position;
            size_st = other.size_st;
            return *this;
        }

        virtual std::pair<T, T> operator*() {
            return *iterator;
        }

        virtual EdgeIterator &operator++() {
            if (position == size_st) throw Exception("OUT OF RANGE");
            iterator++;
            position++;
            return *this;
        }

        virtual EdgeIterator &operator++(int) {
            if (position == size_st) throw Exception("OUT OF RANGE");
            EdgeIterator temp = *this;
            iterator++;
            position++;

            return temp;
        }

        virtual EdgeIterator &operator--() {
            if (position == 0) throw Exception("OUT OF RANGE");
            iterator--;
            position--;

            return *this;
        }

        virtual EdgeIterator &operator--(int) {
            if (position == 0) throw Exception("OUT OF RANGE");
            EdgeIterator temp = *this;
            iterator--;
            position--;

            return temp;
        }

        EdgeIterator(const EdgeIterator &other) : iterator(other.iterator), position(other.position),
                                                  size_st(other.size_st) {};
    private:
        EdgeIterator(pointer iterator_pointer, int begin_position, int size) : iterator(iterator_pointer),
                                                                               position(begin_position),
                                                                               size_st(size) {};
    protected:
        pointer iterator;

        int position;

        int size_st;
    };

    class EdgeReverseIterator : public EdgeIterator {
    public:
        typedef std::pair<T, T> *pointer;

        friend class graph;

        EdgeReverseIterator(const EdgeReverseIterator &other) : EdgeIterator(other) {};

        EdgeReverseIterator &operator=(const EdgeReverseIterator &other) {
            this->iterator = other.iterator;
            this->position = other.position;
            this->size_st = other.size_st;
            return *this;
        }

        std::pair<T, T> operator*() {
            return *(this->iterator);
        }

        bool operator==(const EdgeReverseIterator &other) {
            return this->iterator == other.iterator;
        }

        bool operator!=(const EdgeReverseIterator &other) {
            return this->iterator != other.iterator;
        }

        EdgeReverseIterator &operator++() {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            this->iterator--;
            this->position--;
            return *this;
        }

        EdgeReverseIterator &operator++(int) {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            EdgeReverseIterator temp = *this;

            this->iterator--;
            this->position--;
            return temp;
        }

        EdgeReverseIterator &operator--() {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            this->iterator++;
            this->position++;
            return *this;
        }

        EdgeReverseIterator &operator--(int) {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            EdgeReverseIterator temp = *this;

            this->iterator++;
            this->position++;
            return temp;
        }

    private:
        EdgeReverseIterator(pointer iterator_pointer, int begin_position, int size) : EdgeIterator(iterator_pointer,
                                                                                                   begin_position,
                                                                                                   size) {};
    };

    class AdjacencyEdgeIterator : public EdgeIterator {
    public:
        typedef std::pair<T, T> *pointer;

        friend class graph;

        AdjacencyEdgeIterator(const AdjacencyEdgeIterator &other) : EdgeIterator(other) {};

        AdjacencyEdgeIterator &operator=(const AdjacencyEdgeIterator &other) {
            this->iterator = other.iterator;
            this->position = other.position;
            this->size_st = other.size_st;
            return *this;
        }

        std::pair<T, T> operator*() {
            return *(this->iterator);
        }

        bool operator==(const AdjacencyEdgeIterator &other) {
            return this->iterator == other.iterator;
        }

        bool operator!=(const AdjacencyEdgeIterator &other) {
            return this->iterator != other.iterator;
        }

        AdjacencyEdgeIterator &operator++() {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            this->iterator++;
            this->position++;
            while (true) {
                if(this->position== this->size_st){
                    return *this;
                }
                if (this->iterator->first == vertex || this->iterator->second == vertex) {
                    break;
                } else {
                    this->iterator++;
                    this->position++;
                }
            }
            return *this;
        }

        AdjacencyEdgeIterator &operator++(int) {
            if (this->position == this->size_st) throw Exception("OUT OF RANGE");
            AdjacencyEdgeIterator temp = *this;
            this->iterator++;
            this->position++;
            while (true) {
                if(this->position== this->size_st){
                    return *this;
                }
                if (this->iterator->first == vertex || this->iterator->second == vertex) {
                    break;
                } else {
                    this->iterator++;
                    this->position++;
                }

                if (this->position == this->size_st) break;
            }
            return temp;
        }

        AdjacencyEdgeIterator &operator--() {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            this->iterator--;
            this->position--;
            while (true) {

                if (this->iterator->first == vertex || this->iterator->second == vertex) {
                    break;
                } else {
                    this->iterator--;
                    this->position--;
                }

                if (this->position == this->size_st) break;
            }
            return *this;
        }

        AdjacencyEdgeIterator &operator--(int) {
            if (this->position == 0) throw Exception("OUT OF RANGE");
            AdjacencyEdgeIterator temp = *this;
            this->iterator--;
            this->position--;
            while (true) {

                if (this->iterator->first == vertex || this->iterator->second == vertex) {
                    break;
                } else {
                    this->iterator--;
                    this->position--;
                }

                if (this->position == this->size_st) break;
            }
            return temp;
        }

    private:
        AdjacencyEdgeIterator(pointer iterator_pointer, int begin_position, int size, value_type val)
                : EdgeIterator(
                iterator_pointer,
                begin_position,
                size), vertex(val) {};
        value_type vertex;
    };

    graph();

    graph(const graph &);

    void clear();

    void push_node(const value_type &);

    bool find_node(const value_type &);

    bool find_edge(const value_type &, const value_type &);

    node get_node(const value_type &);

    void add_edge(const value_type &, const value_type &);

    inline NodeIterator begin();

    inline NodeIterator end();

    inline NodeIteratorReverse rbegin();

    inline NodeIteratorReverse rend();

    inline EdgeIterator edge_begin();

    inline EdgeIterator edge_end();

    inline EdgeReverseIterator edge_rbegin();

    inline EdgeReverseIterator edge_rend();

    NodeIterator adjacency_node_begin(const value_type &);

    NodeIterator adjacency_node_end(const value_type &);

    AdjacencyEdgeIterator adjacency_edge_begin(const value_type &);

    AdjacencyEdgeIterator adjacency_edge_end();

    inline int node_size();

    inline int edge_size();

    int node_degree(const value_type &);

    inline bool empty();

    bool delete_node(const value_type &);

    bool delete_edge(const value_type &, const value_type &);

    bool operator==(const graph<T> &);

    bool operator!=(const graph<T> &);

    bool operator<=(const graph<T> &);

    bool operator>=(const graph<T> &);

    bool operator<(const graph<T> &);

    bool operator>(const graph<T> &);

    graph &operator=(const graph<T> &);

    template<class os>
    friend std::ostream &operator<<(std::ostream &ost, const graph<os> &);

private:
    list_node stl_graph;
    list_edge edges_of_graph;
};

template<class T>
graph<T>::graph() = default;

template<class T>
graph<T>::graph(const graph &copy_graph) {
    this->stl_graph = copy_graph.stl_graph;
    this->edges_of_graph = copy_graph.edges_of_graph;
}

template<class T>
void graph<T>::clear() {
    for (size_t i = 0; i < stl_graph.size(); i++) {
        stl_graph[i]->next_node.clear();
    }
    stl_graph.clear();
    edges_of_graph.clear();
}

template<class T>
void graph<T>::push_node(const value_type &value) {

    if (find_node(value) == true) {
        std::cout << "Such value already exist!";
    } else {
        node new_node = new Node<T>();
        new_node->data = value;
        stl_graph.push_back(new_node);
    }
}

template<class T>
bool graph<T>::find_node(const value_type &value) {
    for (auto it = begin(); it != end(); ++it) {
        if ((*(*(it.element))).data == value) {
            return true;
        }
    }
    return false;
}

template<class T>
bool graph<T>::find_edge(const value_type &first_edge, const value_type &second_edge) {
    for (auto it = edge_begin(); it != edge_end(); ++it) {
        if (it.iterator->first == first_edge && it.iterator->second == second_edge) {
            return true;
        }
    }
    return false;
}

template<class T>
Node<T> *graph<T>::get_node(const value_type &value) {

    for (auto it = begin(); it != end(); ++it) {
        if ((*(*(it.element))).data == value) {
            return *(it.element);
        }
    }

    std::cout << "No such node exist!";
    return nullptr;
}

template<class T>
void graph<T>::add_edge(const value_type &first_node, const value_type &second_node) {

    if (find_node(first_node) == false || find_node(second_node) == false) {
        std::cout << "No such node exists." << std::endl;
        return;
    }

    if(find_edge(first_node,second_node)){
        std::cout<<"Such edge already exist!\n";
        return;
    }

    for (size_t i = 0; i < stl_graph.size(); i++) {
        if (stl_graph[i]->data == first_node) {
            stl_graph[i]->adjacent_counter++;
            for (size_t j = 0; j < stl_graph.size(); j++) {
                if (stl_graph[j]->data == second_node) {
                    stl_graph[i]->next_node.push_back(stl_graph[j]);
                    edges_of_graph.push_back(std::make_pair(first_node, second_node));
                    stl_graph[j]->adjacent_counter++;
                    break;
                }
            }
            break;
        }

    }
}

template<class T>
typename graph<T>::NodeIterator graph<T>::begin() {
    return NodeIterator(stl_graph.begin().base(), 0, stl_graph.size());
}

template<class T>
typename graph<T>::NodeIterator graph<T>::end() {
    return NodeIterator(stl_graph.end().base(), stl_graph.size(), stl_graph.size());
}

template<class T>
typename graph<T>::NodeIteratorReverse graph<T>::rbegin() {
    return NodeIteratorReverse(stl_graph.end().base() - 1,
                               stl_graph.size(), stl_graph.size());
}

template<class T>
typename graph<T>::NodeIteratorReverse graph<T>::rend() {
    return NodeIteratorReverse(stl_graph.begin().base() - 1,
                               0, stl_graph.size());
}

template<class T>
typename graph<T>::EdgeIterator graph<T>::edge_begin() {
    return EdgeIterator(edges_of_graph.begin().base(), 0, edges_of_graph.size());
}

template<class T>
typename graph<T>::EdgeIterator graph<T>::edge_end() {
    return EdgeIterator(edges_of_graph.end().base(), edges_of_graph.size(), edges_of_graph.size());
}

template<class T>
typename graph<T>::EdgeReverseIterator graph<T>::edge_rbegin() {
    return EdgeReverseIterator(edges_of_graph.end().base() - 1, edges_of_graph.size(), edges_of_graph.size());
}

template<class T>
typename graph<T>::EdgeReverseIterator graph<T>::edge_rend() {
    return EdgeReverseIterator(edges_of_graph.begin().base() - 1, 0, edges_of_graph.size());
}

template<class T>
typename graph<T>::NodeIterator graph<T>::adjacency_node_begin(const value_type &value) {
    node node_iterator = get_node(value);
    return NodeIterator(node_iterator->next_node.begin().base(), 0, node_iterator->next_node.size());
}

template<class T>
typename graph<T>::NodeIterator graph<T>::adjacency_node_end(const value_type &value) {
    node node_iterator = get_node(value);
    return NodeIterator(node_iterator->next_node.end().base(), node_iterator->next_node.size(),
                        node_iterator->next_node.size());
}

template<class T>
typename graph<T>::AdjacencyEdgeIterator graph<T>::adjacency_edge_begin(const value_type &value) {
    int position = 0;
    for (auto i = edges_of_graph.begin(); i != edges_of_graph.end(); i++) {
        if ((*i).first == value || (*i).second == value) {
            return AdjacencyEdgeIterator(i.base(), position, edges_of_graph.size(), value);
        }
        position++;
    }

    throw Exception("No such node exist!");

}

template<class T>
typename graph<T>::AdjacencyEdgeIterator graph<T>::adjacency_edge_end() {
    return AdjacencyEdgeIterator(edges_of_graph.end().base(), edges_of_graph.size(), edges_of_graph.size(), 0);
}

template<class T>
int graph<T>::node_size() {
    return stl_graph.size();
}

template<class T>
int graph<T>::edge_size() {
    return edges_of_graph.size();
}

template<class T>
int graph<T>::node_degree(const value_type &value) {
    node temp = get_node(value);
    return temp->adjacent_counter;
}

template<class T>
bool graph<T>::empty() {
    return stl_graph.empty();
}

template<class T>
bool graph<T>::delete_edge(const value_type &first_node, const value_type &second_node) {
    if (!find_edge(first_node, second_node)) {
        std::cout << "\nNo such edge exist!" << std::endl;
        return false;
    }
    for (auto it = edges_of_graph.begin(); it != edges_of_graph.end(); ++it) {
        if ((*it).first == first_node && (*it).second == second_node) {
            edges_of_graph.erase(it);
            break;
        }
    }

   node temp = get_node(first_node);
    for (auto it = temp->next_node.begin(); it != temp->next_node.end(); ++it) {
        if((*it)->data==second_node){
            temp->next_node.erase(it);
            break;
        }
    }
    return true;
}

template<class T>
bool graph<T>::delete_node(const value_type &value) {
    if(!find_node(value)){
        std::cout << "\nNo such node exist!" << std::endl;
        return false;
    }

    for (auto it = stl_graph.begin(); it != stl_graph.end(); ++it) {
       if((*it)->data==value){
           (*it)->next_node.clear();
           stl_graph.erase(it);
           break;
       }
    }

    for (auto it = edges_of_graph.begin(); it != edges_of_graph.end(); ++it) {
        if ((*it).first == value || (*it).second == value) {
            edges_of_graph.erase(it);
            --it;
        }
    }
    return true;
}

template<class T>
bool graph<T>::operator!=(const graph<T> &other) {
    return stl_graph.size() != other.stl_graph.size();
}

template<class T>
bool graph<T>::operator==(const graph<T> &other) {
    return stl_graph.size() == other.stl_graph.size();
}

template<class T>
bool graph<T>::operator<=(const graph<T> &other) {
    return stl_graph.size() <= other.stl_graph.size();
}

template<class T>
bool graph<T>::operator>=(const graph<T> &other) {
    return stl_graph.size() >= other.stl_graph.size();
}

template<class T>
bool graph<T>::operator<(const graph<T> &other) {
    return stl_graph.size() < other.stl_graph.size();
}

template<class T>
bool graph<T>::operator>(const graph<T> &other) {
    return stl_graph.size() > other.stl_graph.size();
}

template<class T>
graph<T> &graph<T>::operator=(const graph<T> &other) {
    this->stl_graph = other.stl_graph;
    this->edges_of_graph = other.edges_of_graph;
}

template<class T>
std::ostream& operator<<(std::ostream &ost, const graph<T> & graph) {
    if(graph.stl_graph.empty()){
        throw Exception("The graph is empty\n");
    }

    for(size_t i = 0; i < graph.stl_graph.size(); i++){
        ost<<graph.stl_graph[i]->data<<" : ";

        for(size_t j = 0; j < graph.stl_graph[i]->next_node.size(); j++){
            if(j==graph.stl_graph[i]->next_node.size()-1){
                ost<<graph.stl_graph[i]->next_node[j]->data;
                break;
            }
            ost<<graph.stl_graph[i]->next_node[j]->data<<" -> ";
        }
        ost<<";\n";
    }
}


#endif //STL_GRAPH_GRAPH_H
