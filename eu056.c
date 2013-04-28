#include "euler.h"

void
eu056(char *ans) {
  int maxsum = 0;
  mpz_t z;  // z = a^b
  char buf[250];

  mpz_init(z);
  for (int a = 1; a < 100; a++) {
    mpz_set_si(z, 1);

    for (int b = 1; b < 100; b++) {
      mpz_mul_ui(z, z, a);

      char *p = mpz_get_str(buf, 10, z);
      int digitsum = 0;
      for (int i = 0; p[i]; i++) {
        digitsum += todigit(p[i]);
      }
      if (digitsum > maxsum) {
        maxsum = digitsum;
      }
    }
  }
  mpz_clear(z);

  sprintf(ans, "%d", maxsum);
}
