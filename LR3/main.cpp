#include "Menu.h"
#include "Graph.h"


int main() {
	Graph<std::string> graph;
	Menu<std::string>::interface(graph);
	return 0;
}