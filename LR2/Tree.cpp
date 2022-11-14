#include"HeaderTree.h"
#include"HeaderNode.h"
#include<iostream>
using namespace std;
Node* Tree::AddToTree(Node *parent, Element* elem)
{

	if (parent == NULL)
	{
		this->root = new Node(elem);
		return root;
	}
	Node *node = new Node(elem);
	parent->children.push_back(node);
	return node;
}
void Tree::PrintTree()
{
	Print(root);
}
void Tree::Print(Node* node)
{
	node->element->Output();
	int size = node->children.size();
	for (int i = 0; i < size; i++)
	{
		Print(node->children[i]);
		int index = size - 1;
		if (i > 0 && i == index)
		{
			node->element->OutputClosingTag(i);
		}
	}

}
Tree::Tree()
{

}