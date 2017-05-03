#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <utility>
#include <cstddef>
#include <queue>

#include "leafnode.h"
#include "internal_node.h"
#include "common.h"

class BPlusTree {
	using LeafType = std::pair<LeafNode*, size_t>;
	using Entry = std::tuple<KeyType, ValueType, LeafNode*>;
public:
	BPlusTree(int order_ = default_order);
	~BPlusTree();
	bool search(KeyType key) const;
	void insert(KeyType key, ValueType value);
	void remove(KeyType key);
	void print() const;
private:
	void destroyTree();
	LeafNode* findLeaf(KeyType key) const;
	void printCurrentLevel(std::queue<Node*>* currenLevel, std::queue<Node*>* nextLevel) const;
	void insertAsRoot(KeyType key, ValueType value);
	void insertIntoLeaf(KeyType key, ValueType value);
	void insertToParent(Node* node, Node* sibling, KeyType key);
	void removeFromLeaf(KeyType key);
	void ajustRoot();
	bool empty() const;

	template <typename T>
	T* split(T* node);
	template <typename T>
	void coalesceOrRedistribute(T* node);
	template <typename T>
	void coalesce(T* node, T* sibling, InternalNode* parent, int node_index);
	template <typename T>
	void redistribute(T* node, T* sibling, InternalNode* parent, int node_index);
private:
	Node* root;
	const int order;
};

#endif
