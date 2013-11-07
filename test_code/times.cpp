#include <functional>

struct Times
{
  unsigned long long t;
  Times(unsigned long long t)
  : t(t)
  {}

  void operator()(std::function<void(unsigned long long)> block)
  {
    for(unsigned long long n= 0; n< t; ++ n)
      block(n);
  }
};

Times operator "" _times(unsigned long long t)
{
  return Times(t);
}

#define DO ([&](int i){
#define END });

#include <iostream>

int main()
{
  100_times DO
    std::cout<< "ruby";
  END
}

