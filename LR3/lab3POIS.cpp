#include "seemslikegraph.h"
#include <iostream>


int main()
{
	graph<int> A;
	int key;

	std::cout << "0\tAdd vertex\n";
	std::cout << "1\tAdd edge\n";
	std::cout << "2\tcheck vertex\n";
	std::cout << "3\tcheck edge\n";
	std::cout << "4\tvertex_counter\n";
	std::cout << "5\tedge_counter\n";
	std::cout << "6\tdegree_vertex\n";
	std::cout << "7\tdelete_vertex\n";
	std::cout << "8\tdelete_edge\n";
	std::cout << "9\tprint\n";
	std::cout << "10\tprint_iterator_vertex\n";
	std::cout << "11\tclear\n";
	std::cout << "12\temty\n";
	std::cout << "13\titerator_node\n";
	std::cout << "14\tnode->iterator\n";

	do
	{
		std::cout << "Input the key: ";
		std::cin >> key;
		switch (key)
		{
		case 0:
		{
			int value;
			std::cout << "Vertex: \n";
			std::cin >> value;
			A.add_vertex(value);
			break;
		}
		case 1:
		{
			int v1, v2;
			std::cout << "Edge: \n";
			std::cin >> v1;
			std::cin >> v2;
			A.add_edge(v1, v2);
			break;
		}
		case 2:
		{
			int value;
			std::cout << "Check vertex: \n";
			std::cin >> value;
			if (A.finder(value))
				std::cout << "Exist\n";
			else std::cout << "Doesn't exist\n";
			break;
		}
		case 3:
		{
			int v1, v2;
			std::cout << "Check edge: \n";
			std::cin >> v1;
			std::cin >> v2;
			if (A.find_edge(v1, v2))
				std::cout << "Exist\n";
			else std::cout << "Doesn't exist\n";
			break;
		}
		case 4:
		{
			std::cout << A.get_vertex_counter() << "\n";
			break;
		}
		case 5:
		{
			std::cout << A.get_edges_counter() << "\n";
			break;
		}
		case 6:
		{
			int value;
			std::cout << "Degree vertex: \n";
			std::cin >> value;
			std::cout << A.get_vertex_degree(value) << "\n";
			break;
		}
		case 7:
		{
			int value;
			std::cout << "Delete vertex: \n";
			std::cin >> value;
			A.delete_vertex(value);
			break;
		}
		case 8:
		{
			int v1, v2;
			std::cout << "Delete edge: \n";
			std::cin >> v1;
			std::cin >> v2;
			A.delete_edge(v1, v2);
			break;
		}
		case 9:
		{
			std::cout << "---------------------------------------------------------\n";
			A.print();
			std::cout << "\n";
			break;
		}
		case 10:
		{
			auto i = graph<int>::iterator_node(A.Begin());
			std::cout << "\n";
			while (i != A.End())
			{
				std::cout << (*i).key << " ";
				i++;
			}
			std::cout << "\n";
			break;
		}
		case 11:
		{
			A.clear(A.get_begin());
			break;
		}
		case 12:
		{
			A.empty();
			break;
		}
		case 13:
		{
			auto i = graph<int>::iterator_node(A.Begin());
			std::cout << "\n";
			while (i != A.End())
			{
				auto j = graph<int>::iterator_edge(A.eBegin(i));
				while (j != A.eEnd())
				{
					std::cout << (*i).key << "->" << (*j).key << " ";
					j++;
				}
				i++;
			}
			std::cout << "\n";
			break;
		}
		case 14:
		{
			int x;
			std::cout << "Input the node ";
			std::cin >> x;
			auto i = graph<int>::iterator_node(A.Begin());
			std::cout << "\n";
			while (i != A.End())
			{
				auto j = graph<int>::iterator_edge(A.eBegin(i));
				while (j != A.eEnd())
				{
					if ((*i).key == x)
					{
						std::cout << (*i).key << "->" << (*j).key << " ";
					}
					j++;
				}
				i++;
			}
			std::cout << "\n";
			break;
		}
		}
	} while (key > -1 && key < 15);

	return 0;
}