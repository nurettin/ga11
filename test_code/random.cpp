#include <vector>
#include <iostream>
#include <random>

int main()
{
  std::random_device device;
  std::mt19937 rand_range(device());
  std::vector<int> v{ 1, 2, 3 };
  std::uniform_int_distribution<> container(0, v.size()- 1);
  auto begin= v.cbegin();
  std::advance(begin, container(rand_range));
  std::cout<< "random element: "<< *begin<< '\n';
}

