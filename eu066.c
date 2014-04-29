#include "euler.h"

static int issquare(int n) {
  int sqrtn = sqrt(n);
  if (sqrtn * sqrtn == n)
    return 1;
  else
    return 0;
}

/*
 * http://en.wikipedia.org/wiki/Pell's_equation
 *
 * We find the continued fraction expansion of sqrt(d), and
 * expand out the convergents as h/k.  At some point, the
 * solution x=h, y=k will satisfy the equation and this is
 * guaranteed to be minimal in x.
 *
 * To find the continued fraction expansion of sqrt(d):
 *   http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 *
 * To find the convergents:
 *   http://www.proofwiki.org/wiki/Definition:Continued_Fraction/Numerators_and_Denominators
 * (our h, k are their p, q)
 */
static void minx(int d, mpz_t x) {
  int a0 = sqrt(d);
  int mn = 0, dn = 1, an = a0;
  int m1, d1, a1;

  mpz_t h, k;    // h_n, k_n
  mpz_t h1, k1;  // h_{n-1}, k_{n-1}
  mpz_t h2, k2;  // h_{n-2}, k_{n-2}
  mpz_t hsq, ksq; // h^2, k^2

  mpz_init(h); mpz_init(k);
  mpz_init(h1); mpz_init(k1);
  mpz_init(h2); mpz_init(k2);
  mpz_init(hsq); mpz_init(ksq);

  mpz_set_ui(h1, 1);
  mpz_set_ui(k1, 0);
  mpz_set_ui(h, a0);
  mpz_set_ui(k, 1);

  do {
    // Get the next a_n in the continued fraction
    m1 = dn * an - mn;
    d1 = (d - m1*m1) / dn;
    a1 = (a0 + m1) / d1;

    mn = m1;
    dn = d1;
    an = a1;

    // Get the next convergent
    mpz_set(h2, h1);
    mpz_set(k2, k1);
    mpz_set(h1, h);
    mpz_set(k1, k);
    mpz_mul_ui(h, h1, an); mpz_add(h, h, h2); // h_n = a_n*h_{n-1} + h_{n-2}
    mpz_mul_ui(k, k1, an); mpz_add(k, k, k2); // k_n = a_n*k_{n-1} + k_{n-2}

    // Check if h, k is a solution
    mpz_mul(hsq, h, h);
    mpz_mul(ksq, k, k);
    mpz_submul_ui(hsq, ksq, d);
  } while (mpz_cmp_ui(hsq, 1) != 0);

  mpz_set(x, h);

  mpz_clear(h); mpz_clear(k);
  mpz_clear(h1); mpz_clear(k1);
  mpz_clear(h2); mpz_clear(k2);
  mpz_clear(hsq); mpz_clear(ksq);
}

void eu066(char *ans) {
  const int N = 1000;
  int d_of_max = 0;
  mpz_t x, max;

  mpz_init(x);
  mpz_init(max);
  mpz_set_ui(max, 0);

  for (int d = 1; d < N; d++) {
    if (issquare(d)) continue;

    minx(d, x);

    if (mpz_cmp(x, max) > 0) {
      mpz_set(max, x);
      d_of_max = d;
    }
  }

  mpz_clear(x);
  mpz_clear(max);

  sprintf(ans, "%d", d_of_max);
}
