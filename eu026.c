#include "euler.h"

/*
 * Find the value of d < 1000 for which 1/d has the longest
 * recurring cycle in decimal.
 *
 * The length of the cycle is the smallest n for which
 *   10^n === 1 (mod d)
 * as long as d is relatively prime to 10.  (If not relatively
 * prime, then a smaller d has the same cycle length).
 */
int mulord(int b, int d) {
  int n = b % d;
  int iter = 1;

  while (n != 1) {
    n = (n * b) % d;
    iter++;
  }
  return iter;
}
void eu026(char *ans) {
  int d;
  int maxlen = 0;
  for (int i = 3; i < 1000; i++) {
    if (i % 2 != 0 && i % 5 != 0) {
      int len = mulord(10, i);
      if (len > maxlen) {
        d = i;
        maxlen = len;
      }
    }
  }

  sprintf(ans, "%d", d);
}
