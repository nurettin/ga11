#include <iostream>
#include <random>
#include <vector>

template <typename C, typename I= typename C::const_iterator>
I random(C const &c, std::mt19937 &rand)
{
  std::uniform_int_distribution<> range(0, c.size()- 1);
  I which= c.begin(); 
  std::advance(which, range(rand));
  return which;
}

/*! Genes can mutate
*/
struct BasicGene
{
  virtual void mutate(std::mt19937 &)= 0;
  virtual ~BasicGene()= 0;
};

BasicGene::~BasicGene(){}

//! Every gene has a range of traits (alleles) which are chosen when it mutates.
template <typename Alleles>
struct Gene: BasicGene
{
  // Alleles are not copied 
  Alleles const &alleles;
  typedef typename Alleles::const_iterator Allele;
  // Current allele
  Allele allele;

  Gene(Alleles const &alleles)
  : alleles(alleles)
  , allele(alleles.begin())
  {}
 
  Gene(Alleles const &alleles, std::mt19937 &rand)
  : alleles(alleles)
  , allele(random(alleles, rand))
  {}
 
  void mutate(std::mt19937 &rand)
  {
    // coin flip on which way to mutate
    std::uniform_int_distribution<> range(0, 1);
    auto up= range(rand);
    if(up)
    {
      // try to mutate forward
      ++ allele;
      // can't mutate forward, go back instead
      if(allele== alleles.cend())
        std::advance(allele, -2);
    }
    // can't mutate back, go forward instead
    else if(allele== alleles.cbegin())
      ++ allele;
    // mutate backward
    else
      -- allele;
  }
};

#include <memory>

struct Chromosome
{
  typedef std::shared_ptr<BasicGene> GenePtr;
  typedef std::vector<GenePtr> Genes;
  Genes genes;
  
  template <typename Allele>
  void add(Allele const &allele, std::mt19937 &rand)
  {
    genes.push_back(GenePtr(new Gene<Allele>(allele, rand)));
  }

  //! Choose and mutate a gene in the chromosome at random
  void mutate(std::mt19937 &rand)
  {
    (*random(genes, rand))-> mutate(rand);
  }
};

struct Population
{
  std::vector<Chromosome> chromosomes;

  void add(Chromosome const &chromosome)
  {
    chromosomes.emplace_back(chromosome);
  }

  void mutate(std::mt19937 &rand)
  {
    for(auto &c: chromosomes)
      c.mutate(rand);
  }

  template <typename B>
  void sort(B block)
  {
    
  }
};

int main()
{
  std::random_device engine;
  std::mt19937 random(engine());
  std::vector<int> legs { 1, 2, 3, 4 };
  std::vector<std::string> color { "RED", "GREEN", "BLUE" };

  Population population;
  for(int n= 1; n--;)
  {
    Chromosome chromosome;
    chromosome.add(legs, random);
    chromosome.add(legs, random);
    chromosome.add(color, random);
    population.add(chromosome);
  }
  population.mutate(random);
}

