#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::vector<int> vec = {1, 2, 3, 4};

  if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
      itr != vec.end()) {
      *itr = 3;
  }

  // 需要重新定义一个新的变量

  if (const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
      itr2 != vec.end()) {
      *itr2 = 4;
  }

  // 将输出 1, 4, 3, 4
  for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
      std::cout << *element << std::endl;
}

