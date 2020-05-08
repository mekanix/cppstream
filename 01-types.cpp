#include <iostream>
#include <string>


void printSomething()
{
  std::cout << "Something\n";
}


int saberi(int i, int j = 3)
{
  return i + j;
}


/* Tipovi
 * ------
 *  int
 *  float
 *  char
 *  std::vector<T>
 *  std::string
 *  class Klasa
 */

class Klasa
{
  public:
    int x;
    float f;
    std::string s;
};


class Covek
{
  public:
    int godiste;
    float visina;
    std::string ime;

    void spavaj()
    {
      std::cout << "Odlično, to najviše volim!\n";
    }

    float proporcija()
    {
      return visina / godiste;
    }
};


int main()
{
  Klasa k;
  Klasa trt;
  k.x = 1;
  std::cout << "k.x = " << k.x << '\n';
  k.s = "neki novi stringic";
  k.f = 3.5;

  printSomething();
  auto rezultat = saberi(1, 2);
  std::cout << "rezultat = " << rezultat << '\n';
  rezultat = saberi(32);
  std::cout << "rezultat = " << rezultat << '\n';

  Covek cova;
  cova.visina = 180.3;
  cova.godiste = 1990;
  cova.spavaj();
  std::cout << "Čovine proporcije su " << cova.proporcija() << '\n';

  Covek jova;
  jova.visina = 200.4;
  jova.godiste = 2000;
  std::cout << "Jovine proporcije su " << jova.proporcija() << '\n';

  int j;
  int i = 1;
  int *pi = &i;
  std::cout << "i = " << i << '\n';
  std::cout << "pi = " << pi << '\n';
  std::cout << "*pi = " << *pi << '\n';

  auto pc = new Covek();
  pc->visina = 190;
  pc->godiste = 1998;
  std::cout << "PC proporcije su " << pc->proporcija() << '\n';
  delete pc;


  return 0;
}
