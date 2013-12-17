#include "euler.h"

static int eterm(int n) {
  if (n == 0) {
    return 2;
  } else if (n % 3 == 2) {
    return 2 * (1 + n / 3);
  } else {
    return 1;
  }
}

void eu065(char *ans) {
  int N = 99;
  mpz_t n, d, r;

  mpz_init(n);
  mpz_init(d);
  mpz_init(r);

  mpz_set_ui(n, eterm(N));
  mpz_set_ui(d, 1);

  for (int i = N-1; i >= 0; i--) {
    mpz_swap(n, d);
    int t = eterm(i);
    mpz_addmul_ui(n, d, t);
    mpz_gcd(r, n, d);
    mpz_div(n, n, r);
    mpz_div(d, d, r);
    /* char bn[100], bd[100]; */
    /* mpz_get_str(bn, 10, n); */
    /* mpz_get_str(bd, 10, d); */
    /* printf("%d: %d -> %s/%s\n", i, t, bn, bd); */
  }

  sprintf(ans, "%d", digitsum(n));
}
