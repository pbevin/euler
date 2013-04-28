#include "euler.h"

void
eu057(char *ans) {
  mpz_t a, b, c;
  int count = 0;

  mpz_init(a);
  mpz_init(b);
  mpz_init(c);

  mpz_set_si(a, 3);
  mpz_set_si(b, 2);

  for (int i = 0; i < 1000; i++) {
    // Let z_n = a/b
    // z_(n+1) = 1 + 1/(1 + z_n)
    // = 1 + 1/(1 + a/b)
    // = 1 + b/(b+a)
    // = (2b+a) / (b+a)
    //
    // so we set c=b+a, then a, b => b+c, c

    mpz_add(c, a, b);
    mpz_add(a, b, c);
    mpz_set(b, c);

    char buf[1000];
    mpz_get_str(buf, 10, a);
    int alen = strlen(buf);
    mpz_get_str(buf, 10, b);
    int blen = strlen(buf);
    if (alen > blen) {
      count++;
    }
  }

  sprintf(ans, "%d", count);
}
