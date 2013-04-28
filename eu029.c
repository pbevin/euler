#include "euler.h"

/*
 * How many distinct values of a^b are there for
 * 2 <= a, b < 100 ?
 *
 * Well I'm not bloody calculating them all, that's
 * for sure.
 *
 * If we represent each a^b as prime factors, it'll
 * be easy: factorize a into a vector of prime factors,
 * multiply each one by b, and check if we've already
 * seen it.
 *
 * For example, 76 = 2^2 * 19, which we'll represent as
 *   [2,0,0,0,0,0,0,1]
 * and so 76^31 is
 *   [62,0,0,0,0,0,0,31]
 *
 * There are only 10,000 numbers to check, so we can
 * just keep them in an array.
 */
void eu029(char *ans) {
  int primes100[25] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97
  };

  int seen[10000][25];
  int nseen = 0;

  int factors[25];

  for (int a = 2; a <= 100; a++) {
    for (int i = 0; i < 25; i++) {
      int n = a;
      int p = primes100[i], k = 0; /* n has factor p^k */
      while (n % p == 0) {
        k++;
        n /= p;
      }
      factors[i] = k;
    }

    for (int b = 2; b <= 100; b++) {
      for (int i = 0; i < 25; i++) {
        seen[nseen][i] = factors[i] * b;
      }

      int isduplicate = 0;
      for (int j = 0; j < nseen; j++) {
        if (memcmp(seen[j], seen[nseen], sizeof(int[25])) == 0) {
          isduplicate = 1;
          break;
        }
      }
      if (!isduplicate) {
        nseen++;
      }
    }
  }
  sprintf(ans, "%d", nseen);
}

