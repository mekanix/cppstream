#include <iostream>
#include <string>


class Horse
{
  public:
    Horse()
    {
      std::cout << "Horse()\n";
    }
    virtual void speak()
    {
      std::cout << "Njihihihi\n";
    }
};


class Bird
{
  public:
    Bird(std::string argType, int argClaws = 8)
      : _type{argType}
      , _claws{argClaws}
    {
      std::cout << "Bird(claws = " << _claws << ")\n";
    }
    virtual void speak() {
      std::cout << "Ćiu ćiu\n";
    }
    void claws(const int &argClaws) { _claws = argClaws; }

  protected:
    std::string _type;

  private:
    int _claws;
};


class Pegasus : public Horse, public Bird
{
  public:
    Pegasus(const int &argLevel)
      : Horse()
      , Bird("vrabac", 1)
      , _magicLevel{argLevel}
    {
      std::cout << "Pegasus()\n";
      std::cout << _type << '\n';
    }
    virtual void speak()
    {
      Horse::speak();
      std::cout << "Magical njihihihihi\n";
      Bird::speak();
    }

  protected:
    int _magicLevel;
};


int main()
{
  // auto horse = new Horse();
  // horse->speak();

  // auto bird = new Bird();
  // bird->speak();

  auto pegasus = new Pegasus(3);
  pegasus->speak();
  return 0;
}
