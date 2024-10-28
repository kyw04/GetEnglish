#include <iostream>
#include "Word.hpp"

using namespace std;

int main()
{
  int count;
  cin >> count;
  while (count--)
  {
    Word w = GetRandomWord();
    cout << w.kr << ' ' << w.en << '\n';
  }

  return 0;
}