#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "node.h"
#include "record.h"

#include <vector>
#include <utility>

class LeafNode: public Node {
	using MappingType = std::pair<KeyType, Record*>;
public:
	LeafNode(int order_);
	LeafNode(int order_, Node* parent_);
	size_t insertToLeaf(KeyType key, ValueType value);
	size_t removeAndDeleteRecord(KeyType key);
	bool searchInLeaf(KeyType key);
	void setNext(LeafNode* node);
	LeafNode* getNext() const;
	KeyType firstKey() const;
	void moveHalfTo(LeafNode* sibling);
	void moveAllTo(LeafNode* sibling, size_t /* */);
	void moveFirstToEndOf(LeafNode* node);
	void moveLastToFrontOf(LeafNode* node, size_t node_index);
	Record* lookUp(KeyType key) const;
	
	bool isLeaf() const override;
	size_t num() const override;
	size_t maxNum() const override;
	size_t minNum() const override;
	std::string displayAllKey() const override;
private:
	bool earchInLeaf(KeyType key);
	void insertToMappings(KeyType key, Record* record);
	void copyHalfFrom(const std::vector<MappingType>& m);
	void copyAllFrom(const std::vector<MappingType>& m);
	void copyLastFrom(MappingType p);
	void copyFirstFrom(MappingType p, size_t node_index);
private:
	LeafNode* next;
	std::vector<MappingType> mappings;
};

#endif
