#include "euler.h"

void eu016(char *ans) {
  const int N = 1000;
  char num[N];
  int i, t;

  memset(num, 0, N);
  num[0] = 1;

  for (i = 0; i < N; i++) {
    add(num, num, N);
  }

  for (t = 0, i = 0; i < N; i++) {
    t += num[i];
  }

  sprintf(ans, "%d", t);
}
