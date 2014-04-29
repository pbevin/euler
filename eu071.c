#include "euler.h"

void
eu071(char *ans) {
  const int N = 1000000;
  double max = 0;
  int num_of_max = 0;
  for (int d = 8; d < N; d++) {
    if (d % 7 == 0) continue;
    int n = d * 3 / 7;
    if (gcd(n, d) != 1) continue;
    double ratio = (double)n / d;
    if (ratio > max) {
      /* printf("%d %d %g\n", n, d, ratio); */
      max = ratio;
      num_of_max = n;
    }
  }

  sprintf(ans, "%d", num_of_max);
}
