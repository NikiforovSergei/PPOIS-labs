#include <iostream>
#include "source/Graph.h"
#include "source/Menu.h"

typedef int TYPE;

int main() {
    Graph<TYPE> graph("graph.txt");
    Menu<TYPE>::print(graph);
    return 0;
}
