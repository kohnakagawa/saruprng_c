#include "../saruprng.h"
#include <stdio.h>

int main() {
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      for (int k = 0; k < 100; k++) {
        Saru state;
        saru_init(&state, i, j, k);
        printf("%10g\n", saru_normal(&state));
      }
}
