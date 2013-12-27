#include "euler.h"

#define N 12000

/*
 * For each denominator d, find the numerators that are relatively
 * prime that are between d/3 and d/2.
 */
void
eu073(char *ans) {
  int count = 0;
  for (int d = 2; d <= N; d++) {
    for (int n = d/3+1; 2*n < d; n++) {
      if (gcd(n, d) == 1) {
        count++;
      }
    }
  }

  sprintf(ans, "%d", count);
}
