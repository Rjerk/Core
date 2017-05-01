#ifndef HASHFUNC_H
#define HASHFUNC_H

#include <cstddef>

template <typename K>
struct Hashfunc {
    unsigned operator()(K key) const
    {
        unsigned v = 2166136261;
        const unsigned p = 16777619;
        while (*key) {
            v = (*key++ ^ v) * p;
        }
        return v & 9;
        //return reinterpret_cast<unsigned>(key) % tablesz;a
    }
};

#endif
