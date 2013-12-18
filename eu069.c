#include "euler.h"

static int primes[1000000];
static int nprimes;
static int cachedphi[1000000];

static int phi(int n) {
  int p;
  for (int i = 0; i < nprimes && ((p = primes[i]) < n); i++) {
    if (n % p == 0) {
      // If p and n/p are coprime, we can multiply them,
      // otherwise we have to cast out factors of p.
      if (n % (p*p) != 0) {
        return (cachedphi[n] = cachedphi[n / p] * cachedphi[p]);
      } else {
        int k = 2;
        int divisor = p*p;
        do {
          k++;
          divisor *= p;
        } while (n % divisor == 0);
        divisor /= p;

        // phi(p^k) = p^k-p^{k-1} and phi(n) = phi(n/p^k) * phi(p^k)
        int phi_p_k = divisor - divisor / p;

        return (cachedphi[n] = cachedphi[n / divisor] * phi_p_k);
      }
    }
  }

  // phi(p) = p-1 when p is prime
  return (cachedphi[n] = n-1);
}

static double n_over_phi_n(int n) {
  double d = n;
  d /= phi(n);
  return d;
}

void eu069(char *ans) {
  const int N = 1000000;
  /* const int N = 20; */

  double max = 0;
  int n_of_max = 0;

  nprimes = genprimes(primes, N);

  cachedphi[1] = 1;

  for (int n = 2; n < N; n++) {
    double v = n_over_phi_n(n);
    /* printf("%d: %d %g\n", n, phi(n), v); */
    if (v > max) {
      max = v;
      n_of_max = n;
    }
  }

  sprintf(ans, "%d", n_of_max);
}
