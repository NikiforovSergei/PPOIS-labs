//
// Created by denis koltovich on 15.11.2022.
//

#include"Header.h"
#include<iostream>

int main() {
	Graph<int> graph;
	graph.AddNode(5);
	graph.AddNode(4);
	graph.AddNode(6);
	graph.AddNode(7);

	graph.AddEdge(4, 5);
	graph.AddEdge(4, 6);
	graph.AddEdge(4, 7);
	graph.AddEdge(5, 7);
	int choice, value, start, end, amount;
	while (true)
	{
		std::cout
			<< "1 - Add edge\n"
			<< "2 - Add node\n"
			<< "3 - Delete node\n"
			<< "4 - Delete edge\n"
			<< "5 - Existence node\n"
			<< "6 - Existence edge\n"
			<< "7 - Number of nodes\n"
			<< "8 - Number of edgesn\n"
			<< "9 - Print graph\n"
			<< "10 - Node degree in\n"
			<< "11 - Node degree out\n\n";

		std::cin >> choice;
		switch (choice)
		{
		
		case 1: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			graph.AddEdge(start, end);
			std::cout << '\n';
			break;
		}
		case 2: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			graph.AddNode(value);
			std::cout << '\n';

			break;
		}
		case 3: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			graph.DeleteNode(value);
			std::cout << '\n';

			break;
		}
		case 4: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			graph.DeleteEdge(start, end);
			std::cout << '\n';

			break;
		}
		case 5: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			if (graph.isContainsNode(value))
				std::cout << "Yes\n";
			else
				std::cout << "No\n";
			std::cout << '\n';

			break;
		}
		case 6: {
			std::cout << "Enter the start of the edge\n";
			std::cin >> start;
			std::cout << "Enter the end of the edge\n";
			std::cin >> end;
			if (graph.isConteinsEdge(start, end))
				std::cout << "Yes\n";
			else
				std::cout << "No\n";
			std::cout << '\n';

			break;
		case 7: {
			amount = graph.NumOfNodes();
			std::cout << amount << '\n';
			std::cout << '\n';

			break;
		}
		case 8: {
			amount = graph.NumOfEdges();
			std::cout << amount << '\n';
			std::cout << '\n';

			break;
		}
		case 9: {
			std::cout << graph;
			std::cout << '\n';

			break;
		}
		case 10: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			amount = graph.NodeDegreeIn(value);
			std::cout << amount << "\n";
			std::cout << '\n';

			break;
		}
		case 11: {
			std::cout << "Enter the value of the node\n";
			std::cin >> value;
			amount = graph.NodeDegreeOut(value);
			std::cout << amount << "\n";
			std::cout << '\n';

			break;
		}
		default:
			return 0;
		}

			  
		}
	}
	return 0;
}