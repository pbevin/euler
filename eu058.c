#include "euler.h"

void
eu058(char *ans) {
  const int MAX = 700000000;
  int i, n = 1;
  //char *sieve = malloc(MAX);
  int primes = 0, nonprimes = 1;

  //gensieve(sieve, MAX);

  // Increment is 2,2,2,2, 4,4,4,4, 6,6,6,6, 8,8,8,8, ...
  for (i = 2; n < MAX; i += 2) {
    for (int j = 0; j < 4; j++) {
      if (isprime(n)) primes++;
      else nonprimes++;
      n += i;
    }
    // primes ratio is primes / (primes+nonprimes)
    // which is under 10% if 10 * primes / (primes+nonprimes) < 1
    if (primes * 10 < primes + nonprimes) {
      // Side length is increment plus one
      sprintf(ans, "%d", i+1);
      break;
    }
  }
  //free(sieve);
}
