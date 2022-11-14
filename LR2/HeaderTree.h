#pragma once
#include "HeaderNode.h"
class Tree
{
public:
	Node* root;
	Tree();
	Node* AddToTree(Node*, Element*);
	void PrintTree();
	void Print(Node*);
};