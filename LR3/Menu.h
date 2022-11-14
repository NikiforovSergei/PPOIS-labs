#pragma once

#include "Graph.h"
#include <conio.h>
#include <stdlib.h>


template <typename T>
class Menu {
private:	
	static void start(int choise, Graph<T>& graph) {
		switch (choise) {
		case 1:
		{
			std::cout << graph;
			std::cout << '\n';
			system("PAUSE");
			break;
		}			
		case 2:
		{
			std::cout << "Adding new vertex" << std::endl;
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;
			graph.add_vertex(vertex_value);
			std::cout << "\nDone\n";
			system("PAUSE");
			break;
		}			
			
		case 3:
		{
			std::cout << "Adding new edge" << std::endl;
			T out_value, to_value;
			std::cout << "Enter vertexes values: ";
			std::cin >> out_value >> to_value;
			graph.add_edge(out_value, to_value);
			std::cout << "\nDone\n";
			system("PAUSE");
			break;
		}
		case 4:
		{
			std::cout << "Deleting vertex" << std::endl;
			T delete_value;
			std::cout << "Enter vertex to delete: ";
			std::cin >> delete_value;
			graph.delete_vertex(delete_value);
			std::cout << "\nDone\n";
			system("PAUSE");
			break;
		}
		case 5:
		{
			std::cout << "Deleting edge" << std::endl;
			T delete_out_value, delete_to_value;
			std::cout << "Enter vertex to delete: ";
			std::cin >> delete_out_value >> delete_to_value;
			graph.delete_edge(delete_out_value, delete_to_value);
			std::cout << "\nDone\n";
			system("PAUSE");
			break;
		}
		case 6:
		{
			std::cout << "Vertex amount: " << graph.vertex_amount() << "\n";
			system("PAUSE");
			break;
		}
		case 7:			
		{
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;
			std::cout << vertex_value << " vertex degree: " << graph.vertex_degree(vertex_value) << "\n";
			std::cout << "\nDone\n";
			system("PAUSE");
			break;
		}
		case 8:
		{
			T vertex_value;
			std::cout << "Enter vertex value: ";
			std::cin >> vertex_value;
			std::cout << "Does vertex " << vertex_value << " exist? " << graph.is_represented_vertex(vertex_value) << std::endl;
			system("PAUSE");
			break;
		}
		case 9:
		{
			T out_value, to_value;
			std::cout << "Enter edge value: ";
			std::cin >> out_value >> to_value;
			std::cout << "Does edge " << out_value << "---" << to_value << " exist? " << graph.is_represented_edge(out_value, to_value) << std::endl;
			system("PAUSE");
			break;
		}
		case 10:
		{
			std::cout << "Is your graph empty? " << graph.empty() << std::endl;
			system("PAUSE");
			break;
		}
		case 11:
		{
			/*std::cout << "-----Adjacent vertexes-----" << std::endl;
			auto vert_it = graph.vertex_begin();
			while (vert_it != graph.vertex_end()) {
				std::cout << *vert_it << ": ";
				auto adj_it = vert_it->adjacent_begin();
				while (adj_it != vert_it->adjacent_end()) {
					std::cout << *adj_it << " ";
					adj_it++;
				}
				vert_it++;
				std::cout << std::endl;
			}*/
			graph.print_adj_vertexes();
			system("PAUSE");
			break;
		}
		case 12:
		{
			graph.print_inc_edges();
			system("PAUSE");
			break;
		}
		case 13:
		{
			graph.clear();
			std::cout << "Graph cleared!" << std::endl;
			system("PAUSE");
			break;
		}
		case 0:
			std::cout << "Goodbye!" << std::endl;
			exit(EXIT_SUCCESS);
		default:
			std::cout << "Improper choise!" << std::endl;
			system("PAUSE");
			break;
		}
		system("CLS");
	}
public:
	static void interface(Graph::Graph<T>& graph) {
		while (true) {
			std::cout << "1. Print graph\n2. Add new vertex\n3. Add new edge\n4. Delete vertex\n5. Delete edge\n6. Vertex amount\n7. Vertex degree\n8. Does vertex exist?\n9. Does edge exist?\n10. Check graph for emptiness\n11. Adjacent nodes for all vertexes\n12. Incident edges for all vertexes\n0. Exit\n";
			int choise;
			std::cout << "Make your choise: ";
			std::cin >> choise;
			system("CLS");
			start(choise, graph);
		}		
	}
};

