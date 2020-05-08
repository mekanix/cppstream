#include <iostream>
#include <string>
#include <vector>


int p;


int main()
{
  int i = 0;
  float f = i;
  char c = 'c';
  std::string s = "Ovo je string";
  s += " koji je besmislen";
  std::cout << "Hello World!\n";
  std::cout << "i = " << i << '\n';
  std::cout << "p = " << p << '\n';
  std::cout << "f = " << f << '\n';
  std::cout << "c = " << c << '\n';
  std::cout << "s = " << s << '\n';

  std::vector<float> v = {2, 23};
  v.push_back(1);
  v.push_back(13.3);
  // čitam sa tastature vrednost

  for (int j = 0; j < v.size(); ++j)
  {
    int tmp = v[j];
    std::cout << "vektor[" << j << "] = " << tmp << '\n';
  }

  auto nesto = v[0];
  std::cout << "nesto = " << nesto << '\n';

  for (const auto &vrednost : v)
  {
    std::cout << "vrednost = " << vrednost << '\n';
  }

  std::vector<int> noviVektor;
  noviVektor.resize(10);
  std::cout << "novi vektor je veličine " << noviVektor.size() << '\n';
  noviVektor.clear();
  std::cout << "novi vektor je veličine " << noviVektor.size() << '\n';
  std::cout << "string je veličine " << s.size() << '\n';
  s.clear();
  std::cout << "string je veličine " << s.size() << '\n';
  return 0;
}
