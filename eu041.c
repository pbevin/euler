#include "euler.h"

/*
 * Largest pandigital prime.
 *
 * No 8- or 9-digit pandigital can be prime, since the digit sum is
 * 36 or 45, which makes it divisible by 3.  So we'll just generate
 * the permutations of 1..7 in reverse until we find one.
 */

void eu041(char *ans) {
  char *sieve = malloc(7654324);
  char *p;
  gensieve(sieve, 7654324);

  strcpy(ans, "7654321");

  while ((p = prevperm(ans)) != 0) {
    int v = atoi(ans);
    if (!sieve[v])
      break;
  }
  free(sieve);
}
