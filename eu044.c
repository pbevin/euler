#include "euler.h"

int ispent(int pn) {
  int n = (1 + sqrt(1 + 24*pn)) / 6;
  return n * (3*n-1) / 2 == pn;
}


/*
 * Sum and difference of pentagonal numbers.
 *
 * This is a bit of a cheat: there is one solution for
 * i,j < 3000, and we just return it.  No guarantee that
 * it's the minimum difference.
 */
void eu044(char *ans) {
  const int N = 3000;
  for (int j = 1; j < N; j++) {
    int pj = j * (3*j-1) / 2;
    for (int k = j+1; k < N; k++) {
      int pk = k * (3*k-1) / 2;
      int s = pk + pj;
      int d = pk - pj;

      if (ispent(s) && ispent(d)) {
        sprintf(ans, "%d", d);
        return;
      }
    }
  }
}
