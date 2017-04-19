#ifndef HASHNODE_H
#define HASHNODE_H

#include <cstddef>

template <typename K, typename V>
class Hashnode {
public:
    Hashnode(const K& k, const V& v):
        key(k), value(v), next(nullptr)
    {
    }
    Hashnode(const Hashnode&) = delete;
    Hashnode& operator=(const Hashnode&) = delete;

    K getKey() const { return key;}
    V getValue() const { return value; }
    void setValue(const V& v) { value = v; }
    Hashnode* getNext() const { return next; }
    void setNext(Hashnode* n) { next = n; }
private:
    K key;
    V value;
    Hashnode* next;
};

#endif
