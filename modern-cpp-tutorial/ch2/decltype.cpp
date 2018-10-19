#include <iostream>


int main()
{
  auto x = 1;
  auto y = 2.3111;
  if (std::is_same<decltype(x), int>::value)
    std::cout << "type x == int" << std::endl;
  if (std::is_same<decltype(y), double>::value)
    std::cout << "type y == double" << std::endl;
  if (std::is_same<decltype(x), decltype(y)>::value)
    std::cout << "type y == type x" << std::endl;
}
