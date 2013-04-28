#include "euler.h"

/*
 * Find the best generator of primes g(n) = n^2+an+b where
 * |a| < 1000 and |b| < 1000.
 *
 * Clearly, b has to be at least 2, otherwise g(0) is not prime.
 *
 * Also, 1+a+b >= 2 (since g(1) is prime), so a >= 1-b.
 *
 * Also, g(b) is not prime, so the sequence can't be longer
 * than 1000, so we only have to consider primes up to
 * 2,001,000 (a^2+a^2+b).
 */
void eu027(char *ans) {
  const int MAXPRIME = 2001000;
  char *sieve = malloc(MAXPRIME);
  int max = 0;
  int max_ab;

  gensieve(sieve, MAXPRIME);

  for (int b = -999; b < 1000; b++) {
    for (int a = -999; a < 1000; a++) {
      int n = 0;
      while (n < b) {
        int f_n = n*n + a*n + b;
        if (f_n < 2 || f_n >= MAXPRIME || sieve[f_n]) {
          break;
        }
        n++;
      }

      /*
       * At this point, n is the minimum for which f_n is composite.
       * Subtracting 1 makes it the maximum for which f_n is prime.
       */
      n--;

      if (n > max) {
        max = n;
        max_ab = a * b;
      }
    }
  }
  free(sieve);

  sprintf(ans, "%d", max_ab);
}
