#include "euler.h"

int isqrt(int n) {
  return floor(sqrt(n));
}

void eu064(char *ans) {
  int oddcount = 0;

  for (int n = 1; n <= 10000; n++) {
    int a0 = isqrt(n);
    if (a0*a0 == n) continue;
    int a = a0;
    int m = 0;
    int d = 1;
    int i;

    // sqrt(n) = a + 1/x
    // Solving for x,
    //   x = 1/(sqrt(n) - a)
    //     = (sqrt(n) + a) / (n - a^2)
    //     = b + (sqrt(n) + c) / (n-a^2)
    //     where
    for (i = 0; a != 2 * a0; i++) {
      int m1 = d * a - m;
      int d1 = (n - m1*m1) / d;
      int a1 = (a0 + m1) / d1;

      a = a1;
      m = m1;
      d = d1;
    }

    if (i % 2 == 1) {
      oddcount++;
    }
  }

  sprintf(ans, "%d", oddcount);
}
