#include "euler.h"

/*
 * Find the longest sequence of primes under 1,000,000
 * whose sum is a prime.
 */
void eu050(char *ans) {
  const int N = 1000000;

  int *primes = malloc(N/2 * sizeof(int));
  int n = genprimes(primes, N);

  char *sieve = malloc(N);
  gensieve(sieve, N);

  int *sums = (int *)malloc(n * sizeof(int));
  memset(sums, 0, n * sizeof(int));
  int t = 0;

  for (int i = 0; i < n; i++) {
    t += primes[i];
    sums[i] = t;
  }

  int maxlen = 0;
  int maxsum = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n && sums[j]-sums[i] < N; j++) {
      int sum = sums[j] - sums[i];
      if (j - i > maxlen && sieve[sum] == 0) {
        maxsum = sum;
        maxlen = j - i;
      }
    }
  }
  sprintf(ans, "%d", maxsum);

  free(sums);
  free(primes);
  free(sieve);
}
