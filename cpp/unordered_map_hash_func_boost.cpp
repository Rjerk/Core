#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/functional/hash.hpp>

using std::string;

struct Key {
    string first;
    string second;
    int third;
    bool operator==(const Key& other) const {
        return (first == other.first && second == other.second && third == other.third);
    }
};

struct KeyHasher {
    std::size_t operator()(const Key& k) const {
        using boost::hash_value;
        using boost::hash_combine;
        size_t seed = 0;
        hash_combine(seed, hash_value(k.first));
        hash_combine(seed, hash_value(k.second));
        hash_combine(seed, hash_value(k.third));
        return seed;
    }
};

int main()
{
    std::unordered_map<Key, string, KeyHasher> mp = {
            {{"John", "Doe", 12}, "first"},
            {{"Mary", "Sue", 11}, "second"}
        };
    Key John {"John", "Doe", 12};
    auto iter = mp.find(John);
    std::cout << iter->second << std::endl;
}
