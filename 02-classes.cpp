#include <iostream>
#include <string>


class Covek
{
  public:
    Covek(std::string j)
    {
      _jmbg = j;
      std::cout << "Konstruktor čoveka\n";
    }
    int godiste;
    float visina;
    std::string ime;

    virtual void spavaj()
    {
      std::cout << "Odlično, to najviše volim!\n";
    }

    float proporcija()
    {
      return visina / godiste;
    }

    std::string jmbg()
    {
      return _jmbg;
    }

    void jmbg(std::string argJmbg)
    {
      // Proveri pravila za generisanje JMBG
      _jmbg = argJmbg;
    }

  protected:
    std::string _jmbg;
};


class Radnik : public Covek
{
  public:
    Radnik(std::string j)
      : Covek(j)
    {
      std::cout << "Konstruktor radnika\n";
    }
    std::string titula;
    virtual void spavaj()
    {
      std::cout << "Ne mogu, radim\n";
    }
};


int main()
{
  auto radnik = new Radnik("2345234");
  radnik->godiste = 1993;
  radnik->titula = "Dr Mr";
  std::cout << "radnik je godišta " << radnik->godiste << '\n';
  std::cout << "radnik ima titulu " << radnik->titula << '\n';
  std::cout << "JMBG radnika " << radnik->jmbg() << '\n';
  radnik->spavaj();
  std::cout << '\n';

  Covek *cova = new Radnik("2345234543");
  cova->spavaj();

  cova = new Covek("234523454");
  cova->spavaj();
  cova->jmbg("123");
  return 0;
}
