#include <iostream>

using namespace std;

class Node {
public:
	virtual ~Node() {}
	virtual double Calc() const = 0;
};

class NumNode: public Node {
public:
	NumNode(double num_): num(num_) {}
	double Calc() const override;
private:
	const double num;
};

double NumNode::Calc() const
{
	return num;
}

class BinNode: public Node {
public:
	BinNode(Node* left_, Node* right_):
		left(left_), right(right_) {}
	~BinNode();
protected:
	Node* const left;
	Node* const right;
};

BinNode::~BinNode()
{
	delete left;
	delete right;
}

class AddNode: public BinNode {
public:
	AddNode(Node* left_, Node* right_):
		BinNode(left_, right_) {}
	double Calc() const;
};

double AddNode::Calc() const
{
	return left->Calc() + right->Calc();
}

class MinNode: public BinNode {
public:
	MinNode(Node* left_, Node* right_):
		BinNode(left_, right_) {}
	double Calc() const; 
};

double MinNode::Calc() const
{
	return left->Calc() - right->Calc();
}

class MulNode: public BinNode {
public:
	MulNode(Node* left_, Node* right_):
		BinNode(left_, right_) {}
	double Calc() const;
};

double MulNode::Calc() const
{
	return left->Calc() * right->Calc();
}

class DivNode: public BinNode {
public:
	DivNode(Node* left_, Node* right_):
		BinNode(left_, right_) {}
	double Calc() const;
};

double DivNode::Calc() const
{
	return left->Calc() / right->Calc();
}

int main()
{
	// calculate: (1+2)*(4-1) / 3
	Node* node1 = new NumNode(1);
	Node* node2 = new NumNode(2);
	Node* addNode1 = new AddNode(node1, node2); // + 1 2
	Node* node3 = new NumNode(4);
	Node* node4 = new NumNode(1);
	Node* addNode2 = new MinNode(node3, node4); // - 4 1
	Node* mulNode = new MulNode(addNode1, addNode2); // * 3 3
	Node* node5 = new NumNode(3);
	Node* divNode = new DivNode(mulNode, node5); // / 9 3
	cout << divNode->Calc() << endl; // 3
	delete divNode;
}
