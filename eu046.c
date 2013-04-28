#include "euler.h"

/*
 * Smallest odd composite that cannot be written as p+2n^2
 * (prime plus twice a square).
 */
void eu046(char *ans) {
  const int N = 10000;
  char sieve[N];
  char hits[N];

  gensieve(sieve, N);
  memset(hits, 0, N);

  for (int p = 2; p < N; p++) {
    if (sieve[p]) continue;
    for (int n = 0; p + 2*n*n < N; n++) {
      hits[p + 2*n*n] = 1;
    }
  }

  for (int i = 9; i < N; i += 2) {
    if (sieve[i] && hits[i] == 0) {
      sprintf(ans, "%d", i);
      return;
    }
  }
}
