#include "euler.h"


/* Sum of digits of 1000! */
void eu020(char *ans) {
  const int N = 100;
  char fact[1000];

  memset(fact, 0, sizeof(fact));
  fact[0] = 1;

  for (int i = 2; i < N; i++) {
    mul1(fact, i, 1000);
  }

  int t = 0;
  for (int i = 0; i < 1000; i++) {
    t += fact[i];
  }
  sprintf(ans, "%d", t);
}
