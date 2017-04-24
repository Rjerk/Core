#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include <tuple>
#include <utility>
#include <vector>
#include "node.h"
#include "record.h"

class LeafNode : public Node {
public:
    explicit LeafNode(int aorder);
    explicit LeafNode(int aorder, Node* parent);
    ~LeafNode override;

    using MappingType = std::pair<KeyType, Record*>;
    using EntryType = std::tuple<KeyType, ValueType, LeafNode*>;

    bool isLeaf() const override;
    int size() const override;
    int minSize() const override;
    int maxSize() const override;
    std::string toString(bool averbose = false) const override;

    LeafNode* next() const;
    void setNext(LeafNode* anext);
    int createAndInsertRecord(KeyType akey, ValueType avalue);
    void insert(KeyType akey, Record* arecord);
    Record* lookup(KeyType akey) const;
    int removeAndDeleteRecord(KeyType akey);
    KeyType firstKey() const;
    void moveHalfTo(LeafNode* arecipient);
    void moveAllTo(LeafNode* arecipient, int /* unused */);
    void moveFirstToEndOf(LeafNode* arecipient);
    void moveLastToFrontOf(LeafNode* arecipient, int aparent_index);
    void copyRangeStartingFrom(KeyType akey, std::vector<EntryType>& avector);
    void copyRangeUntil(KeyType akey, std::vector<EntryType>& avector);
    void copyRange(std::vector<EntryType>& avector);
private:
    void copyHalfFrom(std::vector<MappingType>& amappings);
    void copyAllFrom(std::vector<MappingType>& ammapings);
    void copyLasfFrom(MappingType apair);
    void copyFirstFrom(MappingType apair, int aparent_index);
    std::vector<MappingType> fmappings;
    LeafNode* fnext;
};

#endif
