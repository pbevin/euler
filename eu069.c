#include "euler.h"

void eu069(char *ans) {
  const int N = 1000000;

  // INSIGHT: n/phi(n) is product(p/p-1) for all primes that divide n.
  // Repeated primes make no difference.
  //
  // So we just need to find the first product of distinct primes that
  // is less than 1,000,000.

  static int primes[50];
  genprimes(primes, 50);

  int product = 1;

  int i = 0;
  while (product < N) {
    product *= primes[i++];
  }
  product /= primes[i-1];

  sprintf(ans, "%d", product);
}
