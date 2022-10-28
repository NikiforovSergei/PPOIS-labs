#include "sort.cpp"
#include <vector>
#include <iostream>

/**
 * @brief example class
 *
 */
class tmp
{
public:
  double a;
  tmp(double _a) : a(_a) {}
  friend bool operator<(tmp fst, tmp snd) { return fst.a < snd.a; }
};

int main()
{
  int c[] = {9, 5, 1, 41, 123, 0, 1, 16, 40, 502};
  std::vector<int> a(c, c + 10);
  std::vector<tmp> b({tmp(425), tmp(51), tmp(5), tmp(8), tmp(141)});
  _sortingNetwork(std::begin(b), std::end(b));

  std::cout << std::endl;

  for (auto j : b)
    std::cout << " " << j.a << " ";

  std::cout << std::endl
            << std::endl;

  return 0;
}
