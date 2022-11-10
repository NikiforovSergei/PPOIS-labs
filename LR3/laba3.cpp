#include <iostream>
#include "Menu.h"
#include "OrientedGraph.h"

typedef std::string TYPE;

int main() 
{

    oriented_graph<TYPE> gr("graph.txt");

    Menu<TYPE>::print(gr);

   
    return 0;
}