#include <sstream>
#include "exceptions.h"
#include "internal_node.h"
#include "leafnode.h"

LeafNode::LeafNode(int aorder):
    fnext(nullptr), Node(aorder)
{
}

LeafNode::LeafNode(int aorder, Node* aparent):
    fnext(nullptr), Node(aorder, aparent)
{
}

LeafNode::~LeafNode()
{
    for (auto m : fmappings) {
        delete m.second;
    }
}

bool LeafNode::isLeaf() const
{
    return true;
}

LeafNode* LeafNode::next() const
{
    return fnext;
}

void LeafNode::setNext(LeafNode* anext)
{
    fnext = anext;
}

int LeafNode::size() const
{
    return static_cast<int>(fmappings.size());
}

int LeafNode::minSize() const
{
    return order() / 2;
}

int LeafNode::maxSize() const
{
    return order() - 1;
}

std::string LeafNode::toString(bool averbose) const
{
    std::ostringstream os;
    if (averbose) {
        os << "[" << std::hex << this << std::dec << "]<"
           << fmappings.size() << "> ";
    }
    bool first = true;
    for (auto m : fmappings) {
        if (first) {
            first = false;
        } else {
            os << " ";
        }
        os << m.first;
    }

    if (averbose) {
        os << "[" << std::hex << fnext << ">";
    }
}

int LeafNode::createAndInsertRecord(KeyType akey, ValueType avalue)
{
    Record* existingRecord = lookup(akey);
    if (!existingRecord) {
        Record* new_record = new Record(avalue);
        insert(akey, new_record);
    }
    return static_cast<int>(fmappings.size());
}

int LeafNode::insert(KeyType akey, Record* arecord)
{
    auto insertionPoint = fmapping.begin();
    auto end = fmapping.end();
    while (insertionPoint != end && insertionPoint->first < akey) {
        ++insertionPoint;
    }
    fmapping.insert(insertionPoint, MappingType(akey, arecord));
}

Record* LeafNode::lookup(KeyType akey) const
{
    for (auto m : fmappings) {
        if (m.first == akey) {
            return m.second;
        }
    }
    return nullptr;
}

void LeafNode::copyRangeStartingFrom(KeyType akey, std::vector<EntryType&> avector)
{
    bool found = false;
    for (auto m : fmappings) {
        if (m.first == akey) {
            found = true;
        }
        if (found) {
            avector.push_back(std::make_tuple(m.first, m.second->value(), this));
        }
    }
}

void LeafNode::copyRangeUntil(KeyType akey, std::vector<EntryType>& avector)
{
    bool found = false;
    for (auto m : fmappings) {
        if (!found) {
            avector.push_back(std::make_tuple(m.first, m.second->value(), this));
        }
        if (m.first == akey) {
            found = true;
        }
    }
}

void LeafNode::copyRange(std::vector<EntryType>& avector)
{
    for (auto m : fmappings) {
        avector.push_back(std::make_tuple(m.first, m.second->value(), this));
    }
}

int LeafNode::removeAndDeleteRecord(KeyType akey)
{
    auto removalPoint = fmappings.begin();
    auto end = fmappings.end();
    while (removalPoint != end && removalPoint->first != akey) {
        ++removalPoint;
    }
    if (removalPoint == end) {
        throw RecordNotFoundException(akey);
    }
    auto record = *removalPoint;
    fmappings.erase(removalPoint);
    delete record.second;
    return static_cast<int>(fmappings.size());
}

KeyType LeafNode::firstKey() const
{
    return fmappings[0].first;
}

void LeafNode::moveHalfTo(LeafNode* arecipient)
{
    arecipient->copyHalfFrom(fmappings);
    size_t sz = fmappings.size();
    for (size_t i = minSize(); i < sz; ++i) {
        fmappings.pop_back();
    }
}

void LeafNode::copyHalfFrom(std::vector<std::pair<KeyType, Record*>>& amappings)
{
    for (size_t i = 0; i < amappings.size(); ++i) {
        fmappings.push_back(amappings[i]);
    }
}

void LeafNode::moveAllTo(LeafNode* arecipient, int)
{
    arecipient->copyAllTo(fmappings);
    fmappings.clear();
    arecipient->setNext(next());
}

void LeafNode::copyAllTo(std::vector<std::pair<KeyType, Record*>>& amappings)
{
    for (auto m : amappings) {
        fmappings.push_back(m);
    }
}

void LeafNode::moveLastToFrontOf(LeafNode* arecipient, int aparent_index)
{
    arecipient->copyFirstFrom(fmappings.back(), aparent_index);
    fmapping.pop_back();
}

void LeafNode::copyFirstFrom(MappingType apair, int aparent_index)
{
    fmappings.insert(fmappings.begin(), apair);
    static_cast<InternalNode*>(parent())->setKeyAt(aparent_index, fmappings.front().first);
}
