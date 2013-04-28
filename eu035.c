#include "euler.h"

/*
 * How many circular primes are there under a million?
 *
 * A circular prime is one where every rotation of the
 * digits is prime - e.g, 197->971->719.
 * We are given that there are 13 such primes under 100.
 *
 * Clearly we only need to consider numbers containing
 * digits 1,3,7 and 9: no rotation can be a multiple of
 * 2 or 5.
 */
int chkcirc(int lo, int hi, int len, char *sieve) {
  int count = 0;
  int m = 1;

  for (int i = 0; i < len-1; i++) {
    m *= 10;
  }

  for (int i = lo; i < hi; i += 2) {
    int is_circular_prime = 1;
    int n = i;
    for (int j = 0; j < len; j++) {
      if (sieve[n]) {
        is_circular_prime = 0;
        break;
      }
      int d = n % 10;
      n /= 10;
      n += m * d;
    }

    if (is_circular_prime) {
      count++;
    }
  }
  return count;
}

void eu035(char *ans) {
  int sum = 13;
  char *sieve = malloc(1000000);
  gensieve(sieve, 1000000);
  sum += chkcirc(111, 1000, 3, sieve);
  sum += chkcirc(1111, 10000, 4, sieve);
  sum += chkcirc(11111, 100000, 5, sieve);
  sum += chkcirc(111111, 1000000, 6, sieve);

  free(sieve);

  sprintf(ans, "%d", sum);
}
