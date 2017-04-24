#include "hash.h"

#include <cassert>
#include <iostream>
using namespace std;

struct hashfunc {
    unsigned operator()(const int& i) const
    {
        return i % 10;
    }
};


int main()
{
    {
		constexpr size_t sz = 10;
		Hashtable<const char*, const char*, sz,
                  Hashfunc<const char*>> htable;
		htable.put("a", "1");
		htable.put("b", "2");
		htable.put("c", "3");

		const char* s = nullptr;
		bool ret = htable.get("a", s);
		assert(ret);
		cout << s << endl;
        ret = htable.get("b", s);
        assert(ret);
        cout << s << endl;

		htable.remove("c");
		ret = htable.get("c", s);
		assert(ret == false);
    }
}
