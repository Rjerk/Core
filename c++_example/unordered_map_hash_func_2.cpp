#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <unordered_map>

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
        using std::hash;
        return ( (hash<string>()(k.first))
            ^ ((hash<string>()(k.second) << 1) >> 1)
            ^ (hash<int>()(k.third) << 1) );
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
