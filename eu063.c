#include "euler.h"

/*
 * How many nth powers are also n digit numbers?
 *
 * The maximum power we have to consider is 21, because
 * 9^22 is a 21 digit number and 10^22 is a 23 digit number;
 * for N>22, 9^N has fewer than N digits and 10^N has N+1.
 *
 * Since 9^21 > 2^64, we are going to have to use bignums.
 */

int numlen(mpz_t z) {
  static char buf[50];
  char *p = mpz_get_str(buf, 10, z);

  return strlen(p);
}

void eu063(char *ans) {
  int count = 0;
  mpz_t z;

  mpz_init(z);

  for (int n = 1; n < 22; n++) {
    int len = 0;
    for (int a = 1; len <= n; a++) {
      mpz_ui_pow_ui(z, a, n);
      len = numlen(z);
      if (len == n) {
        count++;
      }
    }
  }
  sprintf(ans, "%d", count);
}
