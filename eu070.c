#include "euler.h"

#define N 10000000

/*
 * To minimize the ratio, we would like the answer to be a prime,
 * since this maximizes phi(n) = n-1.  But n-1 can't be a permutation
 * of n (only the last digit will change if n is prime)
 *
 * Next best guess is the product of a pair of primes close to sqrt(N)
 * since then phi(p)*phi(q) = (p-1)(q-1).
 *
 * So we'll search pairs of primes up to 2*sqrt(N) and see where that
 * gets us.
 */
void
eu070(char *ans) {
  int maxprime = 2 * sqrt(N);
  int *primes = malloc(maxprime * sizeof(int));
  int nprimes = genprimes(primes, maxprime);

  double min = 1000.0;
  int n_of_min = 0;

  for (int i = 0; i < nprimes; i++) {
    int p = primes[i];
    for (int j = 0; j < nprimes; j++) {
      int q = primes[j];
      int n = p * q;
      if (n > N) break;
      int phi = (p-1) * (q-1);

      if (isperm(n, phi)) {
        double ratio = (double)n / phi;

        if (ratio < min) {
          /* printf("%d*%d=%d %d %g\n", p, q, n, phi, ratio); */
          min = ratio;
          n_of_min = n;
        }
      }
    }
  }
  free(primes);

  sprintf(ans, "%d", n_of_min);
}
