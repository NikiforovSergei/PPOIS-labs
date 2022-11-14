#include"HeaderNode.h"
Node::Node(vector<Node*>children, Element* elem)
{
	this->children = children;
	this->element = elem;
}
Node::Node()
{

}
Node::Node(Element* elem)
{
	this->element = elem;
}