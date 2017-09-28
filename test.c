#include "saruprng.h"
#include <stdio.h>

int main() {
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      for (int k = 0; k < 10; k++) {
        Saru state;
        saru_init(&state, i, j, k);
        printf("%u\n", saru_u32(&state));
      }
  return 0;
}
