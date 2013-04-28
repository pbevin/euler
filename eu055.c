#include "euler.h"

void
strrev(char *s) {
  int len = strlen(s);
  char *p = s, *q = s + len - 1;
  while (p < q) {
    char t = *p;
    *p = *q;
    *q = t;
    p++; q--;
  }
}

void
reverse(mpz_t reversed, mpz_t a) {
  char *buf = mpz_get_str(NULL, 10, a);
  strrev(buf);
  mpz_set_str(reversed, buf, 10);
  free(buf);
}

void
eu055(char *ans) {
  int count = 0;
  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);

  for (int n = 0; n < 10000; n++) {
    int found = 0;
    mpz_set_si(a, n);
    reverse(b, a);
    for (int k = 0; k < 50; k++) {
      mpz_add(a, a, b);
      reverse(b, a);
      if (mpz_cmp(a, b) == 0) {
        found = 1;
        break;
      }
    }
    if (!found) {
      count++;
    }
  }
  sprintf(ans, "%d", count);

  mpz_clear(a);
  mpz_clear(b);
}
