#include "euler.h"

void eu080(char *ans) {
  int sum = 0;
  mpz_t t, a, r, p;

  mpz_init(t); mpz_init(a); mpz_init(r); mpz_init(p);

  for (int n = 2; n < 100; n++) {
    int isqrt = sqrt(n);

    if (isqrt * isqrt == n) continue;

    mpz_set_ui(a, isqrt);
    mpz_set_ui(r, n - isqrt*isqrt);

    for (int i = 0; i < 99; i++) {
      mpz_mul_si(t, r, 100);
      int e;
      for (e = 0; e < 10; e++) {
        mpz_mul_ui(p, a, 20);
        mpz_add_ui(p, p, e);
        mpz_mul_ui(p, p, e);
        if (mpz_cmp(p, t) > 0) {
          break;
        }
      }
      e--;

      mpz_mul_ui(p, a, 20);
      mpz_add_ui(p, p, e);
      mpz_mul_ui(p, p, e);
      mpz_sub(r, t, p);
      mpz_mul_ui(a, a, 10);
      mpz_add_ui(a, a, e);
    }

    sum += digitsum(a);
  }

  sprintf(ans, "%d", sum);
}
