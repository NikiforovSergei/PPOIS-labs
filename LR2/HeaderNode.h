#pragma once
#include "HeaderElement.h"
#include <vector>
using namespace std;
class Node
{
public:
	vector<Node*>children;
	Element* element;
	Node();
	Node(vector<Node*>, Element*);
	Node(Element*);
};
