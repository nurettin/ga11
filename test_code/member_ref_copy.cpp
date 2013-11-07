#include <iostream>

#define BARK std::cout<< __PRETTY_FUNCTION__<< '\n'

struct Wtf
{
  Wtf(){ BARK; }
  Wtf(Wtf const &){ BARK; }
};

struct Omg
{
  Wtf const &wtf;
  Omg(Wtf const &wtf)
  : wtf(wtf)
  {}
};

#include <vector>

int main()
{
  std::vector<Omg> omgs;
  Wtf wtf;
  for(int n= 10000; n--; omgs.push_back(Omg(wtf)));
}

