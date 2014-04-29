#include "euler.h"

#define N 1000000

/*
 * The number of distinct fractions with denominator less than N
 * is the sum of phi(n) from 2 to N inclusive.
 */
void
eu072(char *ans) {
  static int phi[N+1];

  genphi(phi, N+1);

  long long int sum = 0;
  for (int i = 2; i < N+1; i++) {
    sum += phi[i];
  }

  sprintf(ans, "%lld", sum);
}
