#include "euler.h"

static int digfact[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

static int factsum(int n) {
  int t = 0;
  while (n > 0) {
    int d = n % 10;
    t += digfact[d];
    n /= 10;
  }
  return t;
}

#define N 1000000
#define LEN 60

void eu074(char *ans) {
  int count = 0;

  for (int i = 1; i < N; i++) {
    int chain[LEN+1];
    chain[0] = i;
    int n = 1, v = i;
    int done = 0;
    while (n <= LEN) {
      v = factsum(v);

      for (int j = 0; j < n-1; j++) {
        if (chain[j] == v) {
          done = 1;
          break;
        }
      }
      if (done) break;

      chain[n++] = v;
    }

    if (n == LEN) count++;
  }
  sprintf(ans, "%d", count);
}
