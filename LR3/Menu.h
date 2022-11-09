#pragma once
#include "OrientedGraph.h"
#include <conio.h>

template<typename T>
class Menu {
private:
    static void start(int ch, oriented_graph<T>& graph) 
    {
        switch (ch) {
        case 1: 
        {
            std::cout << graph;
            int x = _getch();
            break;
        }
        case 2: 
        {
            T info;
            int id;
            std::cout << "Enter node info "; std::cin >> info;
            std::cout << "Enter node id "; std::cin >> id;
            graph.add_node(id, info);
            int x = _getch();
            break;

        }
        case 3:
        {
            int id;
            std::cout << "Enter node id "; std::cin >> id;
            graph.remove_node(id);
            int x = _getch();
            break;
        }
        case 4: 
        {
            int fromID, toID, id;
            std::cout << "Enter start node id "; std::cin >> fromID;
            std::cout << "Enter finish node id "; std::cin >> toID;
            std::cout << "Enter edge id "; std::cin >> id;
            graph.add_edge(id, fromID, toID);
            int x = _getch();
            break;
        }
        case 5: 
        {
            int fromID, toID;
            std::cout << "Enter start node id "; std::cin >> fromID;
            std::cout << "Enter finish node id "; std::cin >> toID;
            graph.remove_edge(fromID, toID);
            int x = _getch();
            break;
        }
        case 6: 
        {
            if (graph.is_empty()) {
                std::cout << "is empty\n";
            }
            else std::cout << "isn't empty\n";
            int x = _getch();
            break;
        }
        case 7:
        {
            int id;
            std::cout << "Enter node id "; std::cin >> id;
            std::cout << graph.is_node_exist(id) << std::endl;
            int x = _getch();
            break;
        }
        case 8:
        {
            int id;
            std::cout << "Enter edge id "; std::cin >> id;
            std::cout << graph.is_edge_exist(id) << std::endl;
            int x = _getch();
            break;
        }
        case 9: 
        {
            std::cout << graph.get_nodes_number() << std::endl;
            int x = _getch();
            system("cls");
            break;
        }
        case 10:
        {
            std::cout << graph.get_edges_number() << std::endl;
            int x = _getch();
            break;
        }
        case 11: 
        {
            int id;
            std::cout << "Enter node id "; std::cin >> id;
            std::cout << graph.node_degree(id);
            int x = _getch();
            break;
        }
        case 12:
        {
            int id;
            std::cout << "Enter node id "; std::cin >> id;
            for (auto it = graph.node_begin(); it != graph.node_end(); ++it) 
            {
                if (it->nodeID == id)
                {
                    graph.remove_node(it->nodeID);
                }
            }
            int x = _getch();
            break;
        }
        case 13:
        {
            int id;
            std::cout << "Enter edge id "; std::cin >> id;
            for (auto it = graph.edge_begin(); it != graph.edge_end(); ++it)
            {
                if (it->edgeID == id) 
                {
                    graph.remove_edge(it->edgeID);
                }
            }
            int x = _getch();
            break;
        }

        case 14:
        {
            int id;
            std::cout << "Enter edge id "; std::cin >> id;
            std::cout << graph.is_edge_exist(id) << std::endl;
            int x = _getch();
            break;
        }
        case 15: 
        {
            int id;
            std::cout << "Enter edge id "; std::cin >> id;
            std::cout << graph.edge_degree(id);
            int x = _getch();
            break;
        }
        case 16:
        {
            int id;
            std::cout << "Enter node id "; std::cin >> id;
            graph.detour(id);
            break;
        }
        case 17:
        {
            graph.clear();
            int x = _getch();
            break;
        }
        case 18: 
        {
            graph.adj_nodes();
            int x = _getch();
            break;
        }
        case 19:
        {
            graph.incedent_edges();
            int x = _getch();
            break;
        }
        default:
        {
            std::cout << "Incorrect input\ntry again\n";
            print(graph);
        }
        }
    }

public:

    static void print(oriented_graph<T>& graph)
    {
        while (true) 
        {
            system("cls");
            std::cout << "1  - graph.operator <<\n"
                "2  - graph.add_node\n"
                "3  - graph.remove_node\n"
                "4  - graph.add_edge\n"
                "5  - graph.remove_edge\n"
                "6  - graph.is_empty\n"
                "7  - graph.is_node_exist\n"
                "8  - graph.is_edge_exist(from, to)\n"
                "9  - graph.get_nodes_number\n"
                "10 - graph.get_edges_number\n"
                "11 - graph.node_degree\n"
                "12 - graph.remove_node by iterator\n"
                "13 - graph.remove_edge by iterator\n"
                "14 - graph.is_edge_exist(ID)\n"
                "15 - graph.edge_degree\n"
                "16 - graph.detour\n"
                "17 - graph.clear\n"
                "18 - nodes neighbours by iterators\n"
                "19 - incedent edges for graph nodes by iterators\n";

            int ch;
            std::cin >> ch;
            system("cls");
            start(ch, graph);
        }
    }
};

