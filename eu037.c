#include "euler.h"

/*
 * Find all 11 primes that are also prime when
 * truncated left or right.
 *
 * The first digit can be 2,3,5,7, the last must be 3,7 or 9,
 * and the remainder can be 1,3,7,9.
 *
 * There isn't an obvious upper bound, but we can just keep
 * going until we find 11 of them.
 *
 * We generate the numbers by increasing a counter
 * and decoding it in kinda base 4: 1,3,7,9, 11,13,17,19,
 * 31,33,37,39, ... - actually reversed for convenience but
 * we're just enumerating so that's OK.  Since we actually
 * want to start with 11, we'll start with n=4.
 */
void eu037(char *ans) {
  int MAX = 1000000;
  int digits1[] = {2,3,5,7};
  int digits[] = {1,3,7,9};
  int count = 0, sum = 0;
  int n = 4;
  char *sieve = malloc(MAX);

  gensieve(sieve, MAX);

  while (count < 11) {
    int j = n, val, istrunc = 1;

    val = digits1[j % 4];
    j /= 4;

    while (j) {
      val *= 10;
      val += digits[j % 4];
      j /= 4;
    }
    if (val >= MAX) {
      fprintf(stderr, "Too high, count = %d\n", count);
      return;
    }

    /* find right-truncations */
    j = val;
    while (j > 0) {
      if (sieve[j]) {
        istrunc = 0;
        break;
      }
      j /= 10;
    }

    /* find left-truncations */
    char buf[30];
    sprintf(buf, "%d", val);
    for (char *p = buf; *p; p++) {
      int j = atoi(p);
      if (sieve[j]) {
        istrunc = 0;
        break;
      }
    }

    if (istrunc) {
      sum += val;
      count++;
    }

    n++;
  }

  free(sieve);

  sprintf(ans, "%d", sum);
}
