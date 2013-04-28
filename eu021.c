#include "euler.h"

/* Add up all amicable numbers under 10,000 */
void eu021(char *ans) {
  const int N = 10000;
  int ds[N];

  for (int i = 1; i < N; i++) {
    ds[i] = sumdivisors(i);
  }

  int sum = 0;
  for (int i = 1; i < N; i++) {
    if (ds[i] < N && i != ds[i] && ds[ds[i]] == i) {
      sum += i;
    }
  }

  sprintf(ans, "%d", sum);
}
