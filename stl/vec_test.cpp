#include "my_vector.h"
#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::cerr;

using namespace mystl;

int main()
{
	Vector<Vector<int>> vec(10, Vector<int>());
	cout << vec.size() << " " << vec.capacity() << " " << vec.max_size() << "\nok\n";
}
