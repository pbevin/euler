#include "euler.h"

static int primes[100000];
static int length;

static int prime_pair(int a, int b) {
  char string[50];
  int n;

  sprintf(string, "%d%d", primes[a], primes[b]);
  n = atoi(string);
  if (!is_prime(n)) return 0;

  sprintf(string, "%d%d", primes[b], primes[a]);
  n = atoi(string);
  if (!is_prime(n)) return 0;

  return 1;
}

void eu060(char *ans) {
  length = genprimes(primes, 10000);

  int a, b, c, d, e;

  for (a = 0; a <= length-5; a++) {
    for (b = a; b <= length-4; b++) {
      if (!prime_pair(a, b)) continue;
      for (c = b; c <= length-3; c++) {
        if (!prime_pair(a, c)) continue;
        if (!prime_pair(b, c)) continue;
        for (d = c; d <= length-2; d++) {
          if (!prime_pair(a, d)) continue;
          if (!prime_pair(b, d)) continue;
          if (!prime_pair(c, d)) continue;

          for (e = d; e <= length-1; e++) {
            if (!prime_pair(a, e)) continue;
            if (!prime_pair(b, e)) continue;
            if (!prime_pair(c, e)) continue;
            if (!prime_pair(d, e)) continue;
            sprintf(ans, "%d", primes[a] + primes[b] + primes[c] + primes[d] + primes[e]);
            return;
          }
        }
      }
    }
  }
}
