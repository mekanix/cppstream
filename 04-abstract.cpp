#include <iostream>


class Animal
{
  public:
    Animal()
    {
      _name = new char[32];
      std::cout << "Animal::Animal()\n";
    }
    virtual ~Animal()
    {
      delete []_name;
      std::cout << "Animal::~Animal()\n";
    }

    virtual void move() = 0;

  protected:
    char *_name;
};


class Horse : public Animal
{
  public:
    Horse()
    {
      _data = new int[16];
      std::cout << "Horse::Horse()\n";
    }
    virtual ~Horse()
    {
      delete []_data;
      std::cout << "Horse::~Horse()\n";
    }
    virtual void move()
    {
      std::cout << "Horse::move()\n";
    }

  protected:
    int *_data;
};


int
main()
{
  Animal *a = new Horse();
  std::cout << '\n';
  a->move();
  std::cout << '\n';
  delete a;
  return 0;
}
