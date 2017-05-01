#include "node.h"

Node::Node(int order_):
	order(order_), parent(nullptr)
{
}

Node::Node(int order_, Node* parent_):
	order(order_), parent(parent_)
{
}

Node::~Node()
{
}

int Node::getOrder() const
{
	return order;
}

Node* Node::getParent() const
{
	return parent;
}

void Node::setParent(Node* p)
{
	parent = p;
}

bool Node::isRoot() const
{
	return parent == nullptr;
}
