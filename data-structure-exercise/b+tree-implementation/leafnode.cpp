#include "leafnode.h"
#include "internal_node.h"
#include <cmath>

LeafNode::LeafNode(int order_):
	Node(order_), next(nullptr)
{
}

LeafNode::LeafNode(int order_, Node* parent_):
	Node(order_, parent_), next(nullptr)
{
	
}
size_t LeafNode::insertToLeaf(KeyType key, ValueType value)
{
	if (!searchInLeaf(key)) {
		Record* newrecord = new Record(value);
		this->insertToMappings(key, newrecord);
	}
	return this->num();
}

bool LeafNode::searchInLeaf(KeyType key)
{
	for (auto m : mappings) {
		if (m.first == key) {
			return true;
		}
	}
	return false;
}

void LeafNode::insertToMappings(KeyType key, Record* record)
{
	auto p = mappings.begin();
	while (p != mappings.end() && key > p->first) {
		++p;
	}
	mappings.insert(p, std::make_pair(key, record));
}

size_t LeafNode::removeAndDeleteRecord(KeyType key)
{
	auto p = mappings.begin();
	while (p != mappings.end() && p->first != key) {
		++p;
	}
	if (p == mappings.end()) {
		// not found
		return num();
	}
	delete (*p).second;
	(*p).second = nullptr;
	mappings.erase(p);
	return num();
}





void LeafNode::setNext(LeafNode* next_node)
{
	next = next_node;
}

LeafNode* LeafNode::getNext() const
{
	return next;
}

KeyType LeafNode::firstKey() const
{
	return mappings[0].first;
}

void LeafNode::moveHalfTo(LeafNode* sibling)
{
	sibling->copyHalfFrom(mappings);
	size_t sz = this->num();
	for (auto i = this->minNum(); i < sz; ++i) {
		mappings.pop_back();
	}
}

void LeafNode::moveAllTo(LeafNode* sibling, size_t /* */)
{
	sibling->copyAllFrom(mappings);
	mappings.clear();
	sibling->setNext(this->getNext());
}

void LeafNode::moveFirstToEndOf(LeafNode* node)
{
	node->copyLastFrom(mappings.front());
	mappings.erase(mappings.begin());
	static_cast<InternalNode*>(this->getParent())->setKeyAt(1, mappings.front().first);
}

void LeafNode::moveLastToFrontOf(LeafNode* node, size_t node_index)
{
	node->copyFirstFrom(mappings.back(), node_index);
	mappings.pop_back();
}

void LeafNode::copyHalfFrom(const std::vector<MappingType>& m)
{
	size_t sz = m.size();
	for (size_t i = this->minNum(); i < sz; ++i)
		mappings.push_back(m[i]);
}

void LeafNode::copyAllFrom(const std::vector<MappingType>& m)
{
	for (auto i : m)
		mappings.push_back(i);
}

void LeafNode::copyLastFrom(MappingType p)
{
	mappings.push_back(p);
}

void LeafNode::copyFirstFrom(MappingType p, size_t node_index)
{
	mappings.insert(mappings.begin(), p);
	static_cast<InternalNode*>(this->getParent())->setKeyAt(node_index, mappings.front().first);
}

Record* LeafNode::lookUp(KeyType key) const
{
	for (auto m : mappings) {
		if (m.first == key)
			return m.second;
	}
	return nullptr;
}




bool LeafNode::isLeaf() const
{
	return true;
}

size_t LeafNode::num() const
{
	return mappings.size();
}

size_t LeafNode::maxNum() const
{
	return getOrder() - 1;
}

size_t LeafNode::minNum() const
{
	return std::ceil((getOrder()-1) / 2);
}
