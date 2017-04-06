#include <iostream>
#include <functional>

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

template <typename Op>
class BinNode: public Node {
public:
	BinNode(Node* left_, Node* right_):
		left(left_), right(right_) {}
	double Calc() const override;
	~BinNode();
protected:
	Node* const left;
	Node* const right;
};

template <typename Op>
double BinNode<Op>::Calc() const
{
	Op op;
	return op(left->Calc(), right->Calc());
}

template <typename Op>
BinNode<Op>::~BinNode()
{
	delete left;
	delete right;
}

int main()
{
	// calculate: (1+2)*(4-1) / 3
	Node* node1 = new NumNode(1);
	Node* node2 = new NumNode(2);
	Node* addNode1 = new BinNode<std::plus<double>>(node1, node2); // + 1 2
	Node* node3 = new NumNode(4);
	Node* node4 = new NumNode(1);
	Node* addNode2 = new BinNode<std::minus<double>>(node3, node4); // - 4 1
	Node* mulNode = new BinNode<std::multiplies<double>>(addNode1, addNode2); // * 3 3
	Node* node5 = new NumNode(3);
	Node* divNode = new BinNode<std::divides<double>>(mulNode, node5); // / 9 3
	cout << divNode->Calc() << endl; // 3
	delete divNode;
}
