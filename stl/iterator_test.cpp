#include "vec_iterator.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace mystl;

int main()
{
	using iter = VecIterator<int>;
	int num = 10;
	std::vector<int> vi = {1, 2, 3, 4, 5, 6};
	for (iter begin = &vi[0], end = &vi[vi.size()]; begin != end; ) {
		std::cout << *begin++ << " " << end - begin << std::endl;
	}
	auto b = &vi[0];
	std::cout << *(3+ b);
}
