#include "euler.h"

/*
 * Find the smallest positive integer, x, such that
 * 2x, 3x, 4x, 5x, and 6x, contain the same digits.
 */
void eu052(char *ans) {
  int x = 1;

  for (;;) {
    x++;
    int allsame = 1;
    for (int k = 3; k <= 6; k++) {
      if (!isperm(2*x, k*x)) {
        allsame = 0;
        break;
      }
    }
    if (allsame) {
      sprintf(ans, "%d", x);
      break;
    }
  }
}
