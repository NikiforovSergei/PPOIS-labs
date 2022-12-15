#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>

template <typename T>
class Graph {
private:

    struct Node {
        int id;
        T info;
        Node* next;
    };
    struct Edge {
        int from;
        int to;
        int id;
        Edge* next;
    };

    Node* headOfNodes = nullptr;
    Node* tailOfNodes;
    Edge* headOfEdges = nullptr;
    Edge* tailOfEdges;
    int numberOfNodes = 0;
    int numberOfEdges = 0;


    bool exist(int id, std::vector<int> arr) {
        for (int i : arr) {
            if (i == id) {
                return true;
            }
        }
        return false;
    }

    T getInfoOfNode(int id) {
        std::ifstream fin;
        fin.open("Info.txt");
        int counter = 0;
        if (fin.is_open()) {
            std::string line;
            while (getline(fin, line)) {
                if (id == counter) {
                    T t;
                    std::istringstream stream(line);
                    stream >> t;
                    return t;
                }
                counter++;
            }
        }


    }

    std::vector<int> getNeighbors(int id) {
        Edge* tmp = headOfEdges;
        std::vector<int> neighbors;
        while (tmp) {
            if (tmp->from == id) {
                neighbors.push_back(tmp->to);
            }
            tmp = tmp->next;
        }
        return neighbors;
    }

    bool isNeighbor(int idFrom, int idTo) {
        std::vector<int> neighbors = getNeighbors(idFrom);
        for (int i : neighbors) {
            if (i == idTo) {
                return true;
            }
        }
        return false;
    }

    void printInfoAboutNode(int id) {
        Node* tmp = headOfNodes;
        while (tmp) {
            if (tmp->id == id) {
                std::cout << "id:\n" << std::to_string(tmp->id) << "\ninfo:\n" << std::to_string(tmp->info) << "\nneighbors:\n";
                std::vector<int> neighbors = getNeighbors(id);
                for (int i : neighbors) {
                    std::cout << i << ", ";
                }
            }
            tmp = tmp->next;
        }
    }

public:
    Graph() {
        headOfNodes = nullptr;
        headOfEdges = nullptr;
        numberOfEdges = 0;
        numberOfNodes = 0;
    }

    Graph(std::string pathOfGraph) {
        std::ifstream fin;
        int buffer;
        std::vector<int> buff;
        fin.open(pathOfGraph);
        if (fin.is_open()) {
            while (!fin.eof()) {
                std::string line;
                fin >> buffer;
                buff.push_back(buffer);

                for (int i = 0; i < buff.size(); i++)
                    if (numberOfNodes < buff[i])
                        numberOfNodes = buff[i];
            }
            fin.seekg(0);
            int i, j;
            while (!fin.eof())
            {
                fin >> i;
                fin >> j;
                addEdge(i--, j--, numberOfEdges);
            }
        }
        fin.close();
        for (int id = 0; id < numberOfNodes; id++) {
            addNode(getInfoOfNode(id), id);
            numberOfNodes--;
        }
    }

    ~Graph() {
        for (int i = 0; i < numberOfNodes; i++) {
            Node* n = headOfNodes;
            while (n) { n->next; }
            delete n;
            numberOfNodes--;
        }
        headOfNodes = nullptr;
        tailOfNodes = nullptr;

        for (int i = 0; i < numberOfEdges; i++) {
            Edge* n = headOfEdges;
            while (n) { n->next; }
            delete n;
            numberOfEdges--;
        }
        headOfEdges = nullptr;
        tailOfEdges = nullptr;

    }

    bool isEmpty() {
        if (numberOfNodes == 0) {
            return true;
        }
        return false;
    }

    void detourByNodes(int id) {
        while (id != -1) {
            printInfoAboutNode(id);
            int number;
            std::cout << "\nenter number of node\n";
            std::cin >> number;
            if (number == -1) {
                return;
            }
            while (!isNeighbor(id, number)) {
                std::cout << "incorrect input";
                std::cin >> number;
            }
            id = number;
        }
    }

    void deleteNode(int id) {
        if (headOfNodes->id == id) {
            headOfNodes = headOfNodes->next;
        }
        else {
            if (tailOfNodes->id == id) {
                Node* temp = headOfNodes;
                while (temp->next->next) {
                    temp = temp->next;
                }
                temp->next = nullptr;
                tailOfNodes = temp;
            }
            else {
                Node* temp = headOfNodes;
                while (temp->next) {
                    if (temp->next->id == id) {
                        temp->next = temp->next->next;
                    }
                    temp = temp->next;
                }
            }
        }
        if (headOfEdges->from == id || headOfEdges->to == id) {
            headOfEdges = headOfEdges->next;
        }
        Edge* tmp = headOfEdges;
        while (tmp->next->next) {
            if (tmp->next->from == id || tmp->next->to == id) {
                tmp->next = tmp->next->next;
            }
            tmp = tmp->next;
        }
        if (tmp->next->from == id || tmp->next->to == id) {
            tmp->next = nullptr;
            tailOfEdges = tmp;
        }
        numberOfNodes--;
    }

    void deleteEdge(int id) {
        if (headOfEdges->id == id) {
            headOfEdges = headOfEdges->next;
        }
        else
            if (tailOfEdges->id == id) {
                Edge* temp = headOfEdges;
                while (temp->next->next) {
                    temp = temp->next;
                }
                temp->next = nullptr;
                tailOfEdges = temp;
            }
            else {
                Edge* temp = headOfEdges;
                while (temp->next) {
                    if (temp->next->id == id) {
                        temp->next = temp->next->next;
                    }
                    temp = temp->next;
                }
            }
        numberOfEdges--;
    }

    void deleteEdge(int from, int to) {
        if (exist(from, to)) {
            if (headOfEdges->from == from && headOfEdges->to == to) {
                headOfEdges = headOfEdges->next;
            }
            else
                if (tailOfEdges->from == from && tailOfEdges->to == to) {
                    Edge* temp = headOfEdges;
                    while (temp->next->next) {
                        temp = temp->next;
                    }
                    delete temp->next;
                    temp->next = nullptr;
                    tailOfEdges = temp;
                }
            Edge* tmp = headOfEdges;
            while (tmp->next->next) {
                if (tmp->next->from == from && tmp->next->to == to) {
                    tmp->next = tmp->next->next;
                }
            }

        }
        else std::cout << "incorrect input";
    }

    void addNode(T info, int id) {
        Node* temp = new Node;

        if (headOfNodes == nullptr)
            headOfNodes = temp;
        else
            tailOfNodes->next = temp;
        temp->info = info;
        temp->id = id;
        temp->next = nullptr;
        tailOfNodes = temp;
        numberOfNodes++;
    }

    void addEdge(int from, int to, int id) {
        Edge* temp = new Edge;
        if (headOfEdges == nullptr)
            headOfEdges = temp;
        else
            tailOfEdges->next = temp;
        temp->from = from;
        temp->to = to;
        temp->id = id;
        temp->next = nullptr;
        tailOfEdges = temp;
        numberOfEdges++;
    }

    int getNumberOfNodes() const {
        return numberOfNodes;
    }

    int getNumberOfEdges() const {
        return numberOfEdges;
    }

    bool exist(T info) {
        Node* tmp = headOfNodes;
        while (tmp) {
            if (tmp->info == info) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    bool exist(int from, int to) {
        Edge* tmp = headOfEdges;
        while (tmp) {
            if (tmp->from == from && tmp->to == to) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    int getDegreeOfNode(int id) {
        return getNeighbors(id).size();
    }

    typedef std::forward_iterator_tag iterator_category;
    typedef Node value_type;
    typedef ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    class NodeIterator :public std::iterator<iterator_category, value_type, pointer, reference> {
    public:
        pointer node;
        explicit  NodeIterator(pointer ptr) {
            node = ptr;
        }
        NodeIterator(const NodeIterator& iterator)
        {
            node = iterator.node;
        }
        NodeIterator& operator++() { node = node->next; return *this; }

        reference operator*() const
        {
            return *node;
        }

        pointer operator->() const
        {
            return node;
        }

        friend bool operator==(const NodeIterator& firstIterator, const NodeIterator& secondIterator)
        {
            return firstIterator.node == secondIterator.node;
        }

        friend bool operator!=(const NodeIterator& firstIterator, const NodeIterator& secondIterator)
        {
            return firstIterator.node != secondIterator.node;
        }

        NodeIterator operator++(int)
        {
            pointer ptr = node;
            node = node->next;
            return ptr;
        }
    };

    NodeIterator begin() { return NodeIterator(headOfNodes); }
    NodeIterator end() { return NodeIterator(tailOfNodes); }

    class EdgeIterator :public std::iterator<iterator_category, value_type, pointer, reference> {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef Edge value_type;
        typedef ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;

        explicit  EdgeIterator(pointer ptr) {
            edge = ptr;
        }

        EdgeIterator(NodeIterator nodeIterator)
        {
            if (nodeIterator == nullptr)
                edge = nullptr;
            else
                edge = nodeIterator->next;
        }

        EdgeIterator(const EdgeIterator& iterator)
        {
            edge = iterator.edge;
        }

        EdgeIterator& operator=(const EdgeIterator& iterator)
        {
            edge = iterator.edge;
            return this;
        }

        EdgeIterator& operator++()
        {
            edge = edge->next;
            return *this;
        }

        reference operator*() const
        {
            return *edge;
        }

        pointer operator->() const
        {
            return edge;
        }

        friend bool operator==(const EdgeIterator& firstIterator, const EdgeIterator& secondIterator)
        {
            return firstIterator.edge == secondIterator.edge;
        }

        friend bool operator!=(const EdgeIterator& firstIterator, const EdgeIterator& secondIterator)
        {
            return firstIterator.edge != secondIterator.edge;
        }

        EdgeIterator operator++(int)
        {
            pointer a = edge;
            edge = edge->next;
            return a;
        }

        pointer edge;
    };

    EdgeIterator ebegin() { return EdgeIterator(headOfEdges); }
    EdgeIterator eend() { return EdgeIterator(tailOfEdges); }

    void deleteByIterator(NodeIterator* nodeIterator) {
        deleteNode(nodeIterator->node->id);
    }

    void deleteByIterator(EdgeIterator* edgeIterator) {
        deleteNode(edgeIterator->edge->id);
    }

    bool operator==(const Graph& graph) const {
        return (headOfNodes == graph.headOfNodes && headOfEdges == graph.headOfEdges);
    }
    bool operator!=(const Graph& graph) const {
        return (headOfNodes == graph.headOfNodes || headOfEdges == graph.headOfEdges);
    }
    bool operator>(const Graph& graph) const {
        return numberOfNodes > graph.numberOfNodes;
    }
    bool operator<(const Graph& graph) const {
        return numberOfNodes < graph.numberOfNodes;
    }
    bool operator>=(const Graph& graph) const {
        return operator>(graph) || operator==(graph);
    }
    bool operator<=(const Graph& graph) const {
        return operator<(graph) || operator==(graph);
    }

    friend std::ostream& operator<< (std::ostream& out, const Graph& graph)
    {
        for (NodeIterator nodeTraveller = graph.Cbegin(); nodeTraveller != graph.Cend(); nodeTraveller++)
        {
            out << "id: " << nodeTraveller->id << std::endl << "info: " << nodeTraveller->info << "\n\n";
        }

        return out;
    }

};