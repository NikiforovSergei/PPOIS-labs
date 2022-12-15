#pragma once
#include "Graph.h"

template<typename T>
class Menu {
private:
    static void start(int kod, Graph<T>& graph) {
        switch (kod) {
        case 1: {
            graph.detourByNodes(0);
            break;
        }
        case 2: {
            T info;
            int id;
            std::cout << "enter info\n";
            std::cin >> info;
            std::cout << "enter id\n";
            std::cin >> id;
            graph.addNode(info, id);
            break;
        }
        case 3: {
            int id;
            std::cout << "enter id\n";
            std::cin >> id;
            graph.deleteNode(id);
        }
        case 4: {
            int from, to, id;
            std::cout << "enter id of start node\n";
            std::cin >> from;
            std::cout << "enter id of finish node\n";
            std::cin >> to;
            std::cout << "enter id of edge\n";
            std::cin >> id;
            graph.addEdge(from, to, id);
            break;
        }
        case 5: {
            int from, to;
            std::cout << "enter id of start node\n";
            std::cin >> from;
            std::cout << "enter id of finish node\n";
            std::cin >> to;
            graph.deleteEdge(from, to);
            break;
        }
        case 6: {
            if (graph.isEmpty()) {
                std::cout << "is empty\n";
            }
            else std::cout << "is not \n";
            break;
        }
        case 7: {
            T info;
            std::cin >> info;
            std::cout << graph.exist(info);
            break;
        }
        case 8: {

            break;
        }
        case 9: {
            std::cout << graph.getNumberOfNodes();
            break;
        }
        case 10: {
            std::cout << graph.getNumberOfEdges();
            break;
        }
        case 11: {
            int id;
            std::cin >> id;
            std::cout << graph.getDegreeOfNode(id);
            break;
        }
        case 12: {
            int id;
            std::cin >> id;
            for (auto nodeIterator = graph.begin(); nodeIterator != graph.end(); ++nodeIterator) {
                if (nodeIterator->id == id) {
                    graph.deleteNode(nodeIterator->id);
                }
            }
            break;
        }
        case 13: {
            int id;
            std::cin >> id;
            for (auto edgeIterator = graph.ebegin(); edgeIterator != graph.eend(); ++edgeIterator) {
                if (edgeIterator->id == id) {
                    graph.deleteEdge(edgeIterator->id);
                }
            }
            break;
        }
        default: {
            std::cout << "incorrect input\ntry again\n";
            print(graph);
        }
        }
    }

public:

    static void print(Graph<T>& graph) {
        while (true) {
            std::cout << "1  - detour\n"
                "2  - add node\n"
                "3  - delete node\n"
                "4  - add edge\n"
                "5  - delete edge\n"
                "6  - is empty\n"
                "7  - exist node\n"
                "8  - exist edge\n"
                "9  - get number of nodes\n"
                "10 - get number of edges\n"
                "11 - get node degree\n"
                "12 - delete node by iterator\n"
                "13 - delete edge by iterator\n";
            int kod;
            std::cin >> kod;
            start(kod, graph);
        }
    }
};