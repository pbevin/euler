#include "euler.h"

/*
 * Smallest 4 consecutive numbers each to have 4 distinct prime factors.
 */
int countdpf(int n, int *primes, int nprimes, int *cache, int ncache) {
  for (int i = 0; i < nprimes; i++) {
    int p = primes[i];
    if (n % p == 0) {
      int m = n / p;
      while (m % p == 0) m /= p;
      return cache[n] = cache[m] + 1;
    }
  }
  abort();
}

void eu047(char *ans) {
  const int N = 200000;
  int *primes = malloc(N * sizeof(int));
  int nprimes = genprimes(primes, N);

  int *cache = malloc(N * sizeof(int));
  memset(cache, 0, N *sizeof(int));
  cache[1] = 0;

  for (int i = 2; i < N; i++) {
    if (countdpf(i, primes, nprimes, cache, N) >= 4 &&
        countdpf(i+1, primes, nprimes, cache, N) >= 4 &&
        countdpf(i+2, primes, nprimes, cache, N) >= 4 &&
        countdpf(i+3, primes, nprimes, cache, N) >= 4) {
      sprintf(ans, "%d", i);
      break;
    }
  }
  free(primes);
  free(cache);
}
