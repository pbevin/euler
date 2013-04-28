#include "euler.h"

void eu048(char *ans) {
  const int N = 1000;
  const long long int MOD = 10000000000L;
  long long sum = 0;

  for (int i = 1; i <= N; i++) {
    long long prod = 1;
    for (int j = 0; j < i; j++) {
      prod *= i;
      prod %= MOD;
    }
    sum += prod;
    sum %= MOD;
  }

  sprintf(ans, "%lld", sum);
}
