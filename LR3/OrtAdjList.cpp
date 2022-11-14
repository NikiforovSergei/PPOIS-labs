
#include "Graph.h"

int main()
{
	DirectedGraph<int> graph;
	int choice, value, start, end, amount;
	while (true)
	{
		std::cout << "1 - Make graph\n"
			<< "2 - Add edge\n"
			<< "3 - Add node\n"
			<< "4 - Delete node\n"
			<< "5 - Delete edge\n"
			<< "6 - Existence node\n"
			<< "7 - Existence edge\n"
			<< "8 - Number of nodes\n"
			<< "9 - Number of edgesn\n"
			<< "10 - Print graph\n"
			<< "11 - Read from file\n"
			<< "12 - Node degree in\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1: {
			graph.make_graph();
			break;
		}
		case 2: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			graph.add_edge(start, end);
			break;
		}
		case 3: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			graph.add_node(value);
			break;
		}
		case 4: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			graph.delete_node(value);
			break;
		}
		case 5: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			graph.delete_edge(start, end);
			break;
		}
		case 6: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			if (graph.contains_node(value))
				std::cout << "Yes\n";
			else
				std::cout << "No\n";
			break;
		}
		case 7: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			if (graph.contains_edge(start, end))
				std::cout << "Yes\n";
			else
				std::cout << "No\n";
			break;
		case 8: {
			amount = graph.number_of_nodes();
			std::cout << amount << '\n';
			break;
		}
		case 9: {
			amount = graph.number_of_edges();
			std::cout << amount << '\n';
			break;
		}
		case 10: {
			graph.print_graph();
			break;
		}
		case 11: {
			graph.read_from_file("C:/Users/USER/Desktop/2курс/поис/laba3/ConsoleApplication1/ConsoleApplication1/input.txt");
			break;
		}
		case 12: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			amount = graph.node_degree_in(value);
			std::cout << amount << "\n";
			break;
		}
		}
		default:
			return 0;
		}
	}
}
