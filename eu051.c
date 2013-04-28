#include "euler.h"

/*
 * Prime number families: find the smallest prime
 * that is part of an 8 digit family, e.g.,
 * 56**3 (* in 0,1,3,4,6,7,9).
 *
 * This has to be a 3 digit group so that mod 3 remains
 * the same (otherwise the family can only be size 7).
 *
 * Also, the final digit has to be fixed, since primes
 * have to end in 1, 3, 7 or 9.
 *
 * I'm going to guess that it's a 6 digit group with 3
 * repeating digits.  If the fixed group is F (100..999)
 * and the repeating group is R (111, 222, 333, ..., 999)
 * then there are 10 ways of interpolating them:
 *   FFRRRF FRFRRF FRRFRF FRRRFF
 *   RFFRRF RFRFRF RFRRFF
 *   RRFFRF RRFRFF
 *   RRRFFF
 */

void upd51(int *min, char *sieve, int a, int b, int c, char *pat) {
  if (c != 1 && c != 3 && c != 7 && c != 9) return;

  int count = 0, m = INT_MAX;
  for (int r = 1; r < 10; r++) {
    int n = 0;
    for (int i = 0; pat[i]; i++) {
      int digit = 0;
      switch (pat[i]) {
      case 'a': digit = a; break;
      case 'b': digit = b; break;
      case 'c': digit = c; break;
      case 'r': digit = r; break;
      }
      n *= 10;
      n += digit;
    }
    if (!sieve[n]) {
      count++;
      if (n < m) {
        m = n;
      }
    }
  }
  if (count >= 8 && m < *min) {
    *min = m;
  }
}


void eu051(char *ans) {
  const int N = 1000000;
  char *sieve = malloc(N);
  gensieve(sieve, N);
  int min = N;
  for (int f = 100; f < 999; f++) {
    int a = f / 100;
    int b = (f / 10) % 10;
    int c = f % 10;

    upd51(&min, sieve, a, b, c, "abrrrc");
    upd51(&min, sieve, a, b, c, "arbrrc");
    upd51(&min, sieve, a, b, c, "arrbrc");
    upd51(&min, sieve, a, b, c, "arrrbc");
    upd51(&min, sieve, a, b, c, "rabrrc");
    upd51(&min, sieve, a, b, c, "rarbrc");
    upd51(&min, sieve, a, b, c, "rarrbc");
    upd51(&min, sieve, a, b, c, "rrabrc");
    upd51(&min, sieve, a, b, c, "rrarbc");
    upd51(&min, sieve, a, b, c, "rrrabc");
  }
  sprintf(ans, "%d", min);
  free(sieve);
}
