#ifndef NODE_H
#define NODE_H

#include "common.h"
#include <cstddef>
#include <string>

class Node {
public:
	Node(int order_);
	Node(int order_, Node* parent_);
	virtual ~Node();
	
	int getOrder() const;
	Node* getParent() const;
	void setParent(Node* p);
	bool isRoot() const;
	
	virtual bool isLeaf() const = 0; 
	virtual size_t num() const = 0;
	virtual size_t maxNum() const = 0;
	virtual size_t minNum() const = 0;
	virtual std::string displayAllKey() const = 0;
private:
	const int order;
	Node* parent;
};

#endif
