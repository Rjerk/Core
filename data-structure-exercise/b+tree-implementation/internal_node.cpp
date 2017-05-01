#include "internal_node.h"
#include <cmath>

InternalNode::InternalNode(int order_):
	Node(order_)
{
}

InternalNode::~InternalNode()
{
}

Node* InternalNode::lookUp(KeyType key) const
{
	auto p = mappings.cbegin();
	while (p != mappings.cend() && key >= p->first) {
		++p;
	}
	--p;
	return p->second;
}

Node* InternalNode::removeAndReturnOnlyChild()
{
	Node* first = mappings.front().second;
	mappings.pop_back();
	return first;
}

size_t InternalNode::nodeIndex(Node* node) const
{
	for (size_t i = 0; i < num(); ++i) {
		if (mappings[i].second == node)
			return i;
	}
	// not found.
	return num();
}

KeyType InternalNode::getKeyAt(size_t index) const
{
	return mappings[index].first;
}

void InternalNode::setKeyAt(size_t index_in_parent, KeyType key)
{
	mappings[index_in_parent].first = key;
}

Node* InternalNode::sibling(size_t sibling_index) const
{
	return mappings[sibling_index].second;
}

void InternalNode::remove(size_t index)
{
	mappings.erase(mappings.begin()+index);
}

void InternalNode::moveHalfTo(InternalNode* sibling)
{
	sibling->copyHalfFrom(mappings);
	size_t sz = num();
	for (size_t i = minNum(); i < sz; ++i)
		mappings.pop_back();
}

void InternalNode::moveAllTo(InternalNode* sibling, size_t node_index)
{
	mappings[0].first = static_cast<InternalNode*>(this->getParent())->getKeyAt(node_index);
	sibling->copyAllFrom(mappings);
	mappings.clear();
}

void InternalNode::moveFirstToEndOf(InternalNode* node)
{
	node->copyLastFrom(mappings.front());
	mappings.erase(mappings.begin());
	static_cast<InternalNode*>(this->getParent())->setKeyAt(1, mappings.front().first);
}

void InternalNode::moveLastToFrontOf(InternalNode* node, size_t node_index)
{
	node->copyFirstFrom(mappings.back(), node_index);
	mappings.pop_back();
}

void InternalNode::copyHalfFrom(std::vector<MappingType>& m)
{
	size_t sz = m.size();
	for (size_t i = minNum(); i < sz; ++i) {
		m[i].second->setParent(this->getParent()); // ??
		mappings.push_back(m[i]);
	}
}

void InternalNode::copyAllFrom(std::vector<MappingType>& m)
{
	for (auto i : m) {
		i.second->setParent(this->getParent()); // ??
		mappings.push_back(i);
	}
}

void InternalNode::copyLastFrom(MappingType p)
{
	mappings.push_back(p);
	mappings.back().second->setParent(this);
}

void InternalNode::copyFirstFrom(MappingType p, size_t node_index)
{
	mappings.insert(mappings.begin(), p);
	mappings.front().first = static_cast<InternalNode*>(this->getParent())->getKeyAt(node_index);
	static_cast<InternalNode*>(this->getParent())->setKeyAt(node_index, p.first);
}

bool InternalNode::isLeaf() const
{
	return false;
}

size_t InternalNode::num() const
{
	return mappings.size();
}

size_t InternalNode::maxNum() const
{
	return std::ceil(getOrder()/2);
}

size_t InternalNode::minNum() const
{
	return getOrder()/2;
}
