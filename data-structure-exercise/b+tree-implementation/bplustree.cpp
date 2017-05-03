#include "bplustree.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

BPlusTree::BPlusTree(int order_):
	root(nullptr), order(order_)
{
}

BPlusTree::~BPlusTree()
{
	destroyTree();
}

void BPlusTree::destroyTree()
{
	if (root->isLeaf()) {
		delete static_cast<LeafNode*>(root);
	} else {
		delete static_cast<InternalNode*>(root);
	}
	root = nullptr;
}

bool BPlusTree::search(KeyType key) const
{
	LeafNode* leaf = findLeaf(key);
	return leaf->lookUp(key) != nullptr;
}

LeafNode* BPlusTree::findLeaf(KeyType key) const
{
	if (empty()) {
		return nullptr;
	}
	auto node = root;
	while (!node->isLeaf()) {
		auto internal_node = static_cast<InternalNode*>(node);
		node = internal_node->lookUp(key);
	}
	return static_cast<LeafNode*>(node);
}

void BPlusTree::insert(KeyType key, ValueType value)
{
	if (empty()) {
		insertAsRoot(key, value);
	} else {
		insertIntoLeaf(key, value);
	}
}

void BPlusTree::print() const
{
	if (root == nullptr) {
		cout << "empty tree.\n";
	} else {
		std::queue<Node*> q0;
        std::queue<Node*> q1;
        auto currentLevel = &q0;
        auto nextLevel = &q1;
        currentLevel->push(root);
        while (!currentLevel->empty()) {
            printCurrentLevel(currentLevel, nextLevel);
            std::swap(currentLevel, nextLevel);
        }
	}
}

void BPlusTree::printCurrentLevel(std::queue<Node*>* currentLevel,
								  std::queue<Node*>* nextLevel) const
{
    cout << "|";
    while (!currentLevel->empty()) {
        Node* currentNode = currentLevel->front();
        cout << currentNode->displayAllKey();
        cout << " |";
        if (!currentNode->isLeaf()) {
            auto internal_node = static_cast<InternalNode*>(currentNode);
            internal_node->queuePushChild(nextLevel);
        }
        currentLevel->pop();
    }
    cout << endl;
}

bool BPlusTree::empty() const
{
	return root == nullptr;
}

void BPlusTree::insertAsRoot(KeyType key, ValueType value)
{
	LeafNode* newnode = new LeafNode(order);
	newnode->insertToLeaf(key, value);
	root = newnode;
}

void BPlusTree::insertIntoLeaf(KeyType key, ValueType value)
{
	LeafNode* node = findLeaf(key);
	if (node == nullptr) {
		// not found.
		return ;
	}

	if (node->insertToLeaf(key, value) > node->maxNum()) {
		LeafNode* sibling = split(node);
		sibling->setNext(node->getNext());
		node->setNext(sibling);
		KeyType k = sibling->firstKey();
		insertToParent(node, sibling, k);
	}
}

// split a part of node to new sibling.
template <typename T>
T* BPlusTree::split(T* node)
{
	T* sibling = new T(order, node->getParent());
	node->moveHalfTo(sibling);
	return sibling;
}

void BPlusTree::insertToParent(Node* node, Node* sibling, KeyType key)
{
	InternalNode* parent = static_cast<InternalNode*>(node->getParent());
	if (parent == nullptr) { // insert to root.
		root = new InternalNode(order);
		parent = static_cast<InternalNode*>(root);
		node->setParent(parent);
		sibling->setParent(parent);
		parent->generateNewRoot(node, sibling, key);
	} else {
		size_t newsz = parent->insertIntoAfter(node, sibling, key);
		if (newsz > parent->maxNum()) {
			InternalNode* parent_sibling = split(parent);
			KeyType k = parent_sibling->getKeyAt(0);
			insertToParent(parent, parent_sibling, k);
		}
	}
}

void BPlusTree::remove(KeyType key)
{
	if (empty()) {
		return ;
	} else {
		return removeFromLeaf(key);
	}
}

void BPlusTree::removeFromLeaf(KeyType key)
{
	LeafNode* leafnode = findLeaf(key);
	if (!leafnode) {
		return ;
	}
	if (!leafnode->lookUp(key)) {
		return ;
	}
	
	size_t new_size = leafnode->removeAndDeleteRecord(key);
	if (new_size < leafnode->minNum()) {
		coalesceOrRedistribute(leafnode);
	}
}

template <typename T>
void BPlusTree::coalesceOrRedistribute(T* node)
{
	if (node->isRoot()) {
		ajustRoot();
		return ;
	}
	auto parent = static_cast<InternalNode*>(node->getParent());
	size_t node_index = parent->nodeIndex(node);
	// node_index == 0, sibling is right sibling, else it is left sibling.
	size_t sibling_index = (node_index == 0 ? 1 : node_index-1);
	// get sibling node.
	T* sibling = static_cast<T*>(parent->sibling(sibling_index));
	
	if (node->num() + sibling->num() >= sibling->maxNum()) {
		redistribute(sibling, node, parent, node_index);
	} else {
		coalesce(sibling, node, parent, node_index);
	}
}

void BPlusTree::ajustRoot()
{
	if (!root->isLeaf() && root->num() == 1) {
		auto node = static_cast<InternalNode*>(root);
		root = static_cast<InternalNode*>(root)->removeAndReturnOnlyChild();
		root->setParent(nullptr);
		delete node;
	} else if (root->num() == 0) {
		delete root;
		root = nullptr;
	}
}

// coalesce node to sibling.
template <typename T>
void BPlusTree::coalesce(T* sibling, T* node,
						InternalNode* parent, int node_index)
{
	// swap right sibling to left side.
	if (node_index == 0) {
		std::swap(node, sibling);
		node_index = 1;
	}
	node->moveAllTo(sibling, node_index);
	parent->remove(node_index);
	// recursively process parent node.
	if (parent->num() < parent->minNum()) {
		coalesceOrRedistribute(parent);
	}
	delete node;
}

template <typename T>
void BPlusTree::redistribute(T* sibling, T* node,
						InternalNode* parent, int node_index)
{
	if (node_index == 0) {
		sibling->moveFirstToEndOf(node);
	} else {
		sibling->moveLastToFrontOf(node, node_index);
	}
}
	
