#ifndef HASH_H
#define HASH_H

#include "hashnode.h"
#include "hashfunc.h"
#include <cstddef>

/*
struct Hashfunc {
    unsigned operator()(const char* s) { // fnv1a hash.
        unsigned hashvalue = 0x811C9DC5; // 2166136261 as seed.
        const unsigned fnv_prime = 0x01000193; // 16777619
        while (*s) {
            hashvalue = (*s++ ^ hashvalue) * fnv_prime;
        }
        return hashvalue;
    }
};
*/

template <typename K, typename V, size_t tablesz,
          typename F = Hashfunc<K>>
class Hashtable {
public:
    Hashtable(): table(), hashfunc() { }

    ~Hashtable()
    {
        for (size_t i = 0; i < tablesz; ++i) {
            Hashnode<K, V>* entry = table[i];
            while (entry != nullptr) {
                Hashnode<K, V>* prev = entry->getNext();
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
    }

    Hashtable(const Hashtable&) = delete;
    Hashtable& operator=(const Hashtable&) = delete;

    bool get(K key, V& value)
    {
        //unsigned hashvalue = hashfunc(key);
        Hashnode<K, V>* entry = table[hashfunc(key)];

        while (entry != nullptr) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
   }

    void put(const K key, const V value)
    {
        unsigned hashvalue = hashfunc(key);
        Hashnode<K, V>* entry = table[hashvalue];
        Hashnode<K, V>* prev = nullptr;

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry != nullptr) {
            entry->setValue(value);
        } else {
            entry = new Hashnode<K, V>(key, value);
            if (prev == nullptr) { // empty slot
                table[hashvalue] = entry;
            } else {
                prev->setNext(entry); // end of linklist.
            }
        }
    }

    void remove(const K key)
    {
        unsigned hashvalue = hashfunc(key);
        Hashnode<K, V>* prev = nullptr;
        Hashnode<K, V>* entry = table[hashvalue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) { // not found
            return ;
        } else {
            if (prev == nullptr) {// remove the element in slot
                table[hashvalue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }
private:
    Hashnode<K, V>* table[tablesz];
    F hashfunc;
};

#endif
