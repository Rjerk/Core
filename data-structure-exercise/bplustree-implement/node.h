#ifndef NODE_H
#define NODE_H

#include <string>
#include "common.h"

// key used where only the entry's pointer has meaning.
const KeyType dummy_key{-1};

// abstract class
class Node {
public:
    explicit Node(int aorder);
    explicit Node(int aorder, Node* aparent);
    virtual ~Node();
    int order() const;
    Node* parent() const;
    void setParent(Node* aparent);
    bool isRoot() const;

    virtual bool isLeaf() const = 0;
    virtual int size() const = 0;
    virtual int minSize() const = 0;
    virtual int maxSize() const = 0;
    virtual std::string toString(bool averbose = false) const = 0;
private:
    const int forder;
    Node* fparent; // pointer to node's parent.
};


#endif
