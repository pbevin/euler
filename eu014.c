#include "euler.h"

int
collatz(long long n, int *a, long long int max) {
  static long long sequence[10000];
  int result;
  int i = 0;
  int c;

  for (;;) {
    sequence[i++] = n;
    if (n == 1) {
      result = 1;
      break;
    }
    if (n < max && a[n] > 0) {
      result = a[n];
      break;
    }

    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
  }

  // Fill in cache for numbers we saw
  c = result;
  while (--i >= 0) {
    long long int k = sequence[i];
    if (k < max) {
      a[k] = c;
    }
    c++;
  }

  return c - 1;
}

void eu014(char *ans) {
  const int N = 1000000;
  int *a = malloc(N * sizeof(int));
  int max = 0, nmax;

  memset(a, 0, N * sizeof(int));

  for (int i = 2; i < N; i++) {
    int count = collatz(i, a, N);
    if (count > max) {
      max = count;
      nmax = i;
    }
  }
  free(a);

  sprintf(ans, "%d", nmax);
}
