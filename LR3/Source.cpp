#include <iostream>
#include "Graph.h"
#include "Menu.h"

int main() {
    Graph<int> graph("graph.txt");
    Menu<int>::print(graph);
    return 0;
}