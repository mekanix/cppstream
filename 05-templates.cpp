#include <iostream>
#include <string>
#include <vector>
#include <map>


void
print(int i)
{
  std::cout << "Integer: " << i << '\n';
}


void
print(std::string s)
{
  std::cout << "String: " << s << '\n';
}


template <class myType>
myType GetMax (myType a, myType b)
{
  return (a > b ? a : b);
}


template <class T>
class Pair
{
  public:
    Pair (T first, T second)
    {
      values[0] = first;
      values[1] = second;
    }

    void print()
    {
      std::cout << "Pair::first: " << values[0];
      std::cout << ", Pair::second: " << values[1] << '\n';
    }

  protected:
    T values[2];
};


int
main()
{
  print(1);
  print("trala lala");
  std::cout << '\n';

  int x = 5;
  int y = 12;
  int result = GetMax<int>(x, y);
  std::cout << "Result: " << result << "\n\n";

  Pair<float> myobject(115.534, 36.2546);
  myobject.print();
  std::cout << '\n';

  std::vector<Pair<int>> v;
  Pair<int> arg(1, 2);
  v.push_back(arg);
  std::cout << "size: " << v.size() << '\n';
  v[0].print();
  std::cout << '\n';

  std::map<std::string, std::string> m;
  m["office@tilda.center"] = "Cvrc";
  // m["data"]["jedan"] = "opala";
  /* {
   *   "office@tilda.center": "Cvrc",
   *   "data": {
   *     "jedan": "opala"
   *   }
   * }
   */
  std::cout << "map size: " << m.size() << '\n';
  return 0;
}
