#include "Saru.h"
#include <iostream>
#include <fstream>

int main() {
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      for (int k = 0; k < 10; k++) {
        hoomd::detail::Saru saru(i, j, k);
        std::cout << saru.u32() << std::endl;
      }
}
