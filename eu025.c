#include "euler.h"

void eu025(char *ans) {
  const int N = 1000;
  int n = 2;
  char a1[N], a2[N], a3[N];

  memset(a1, 0, N);
  memset(a2, 0, N);
  a1[0] = 1;
  a2[0] = 1;

  for (;;) {
    n++;
    memcpy(a3, a1, N);
    add(a3, a2, N);
    if (a3[N-1]) {
      sprintf(ans, "%d", n);
      return;
    }
    memcpy(a1, a2, N);
    memcpy(a2, a3, N);
  }
}
