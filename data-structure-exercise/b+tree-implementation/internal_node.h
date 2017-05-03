#ifndef INTERNAL_NODE_H
#define INTERNAL_NODE_H

#include "node.h"

#include <queue>
#include <vector>
#include <utility>

class InternalNode: public Node {
	using MappingType = std::pair<KeyType, Node*>;
public:
	InternalNode(int order_);
	InternalNode(int order_, Node* parent_);
	~InternalNode();
	
	Node* lookUp(KeyType key) const;
	Node* removeAndReturnOnlyChild();
	size_t nodeIndex(Node* node) const;
	KeyType getKeyAt(size_t index) const;
	void setKeyAt(size_t index_in_parent, KeyType key);
	Node* sibling(size_t sibling_index) const;
	void remove(size_t index);
	void moveHalfTo(InternalNode* sibling);
	void moveAllTo(InternalNode* sibling, size_t node_index);
	void moveFirstToEndOf(InternalNode* node);
	void moveLastToFrontOf(InternalNode* node, size_t node_index);
	void generateNewRoot(Node* node, Node* sibling, KeyType key);
	size_t insertIntoAfter(Node* node, Node* sibling, KeyType key);
	void queuePushChild(std::queue<Node*>* nextLevel);
	bool isLeaf() const override;
	size_t num() const override;
	size_t maxNum() const override;
	size_t minNum() const override;
	std::string displayAllKey() const override;
private:
	void copyHalfFrom(std::vector<MappingType>& m);
	void copyAllFrom(std::vector<MappingType>& m);
	void copyLastFrom(MappingType p);
	void copyFirstFrom(MappingType p, size_t node_index);
private:
	std::vector<MappingType> mappings;
};

#endif
