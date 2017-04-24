#include "node.h"

Node::Node(int aorder):
    forder(aorder), fparent(nullptr)
{
}

Node::Node(int aorder, Node* aparent):
    forder(aorder), fparent(aparent)
{
}

Node::~Node()
{
}

int Node::order() const
{
    return forder;
}

Node* Node::parent() const
{
    return fparent;
}

void Node::setParent(Node* aparent)
{
    fparent = aparent;
}

bool Node::isRoot() const
{
    return !fparent;
}
