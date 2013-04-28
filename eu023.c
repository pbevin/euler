#include "euler.h"

void eu023(char *ans) {
  int N = 28123;
  int abundant[N];
  char issum[N];
  int nabun = 0;

  memset(abundant, 0, sizeof(abundant));
  memset(issum, 0, sizeof(issum));

  for (int i = 2; i < N; i++) {
    if (sumdivisors(i) > i) {
      abundant[nabun++] = i;
    }
  }

  for (int i = 0; i < nabun; i++) {
    for (int j = 0; j <= i; j++) {
      int sum = abundant[i] + abundant[j];
      if (sum < N) {
        issum[sum] = 1;
      }
    }
  }

  int total = 0;
  for (int i = 1; i < N; i++) {
    if (!issum[i]) {
      total += i;
    }
  }

  sprintf(ans, "%d", total);
}

