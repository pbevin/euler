#include "euler.h"

void eu010(char *ans) {
  const int N = 2000000;
  uint64_t sum = 0;
  char *sieve = malloc(N);

  gensieve(sieve, N);

  for (int i = 2; i < N; i++) {
    if (!sieve[i]) sum += i;
  }
  free(sieve);

  sprintf(ans, "%" PRIu64, sum);
}
