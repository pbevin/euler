#include "euler.h"

/*
 * Find all numbers that can be written as the sum of the
 * fifth power of their digits.
 *
 * We only have to check up to 413343 = 9^5 * 6, since the
 * digit sum is less than the number for anything larger.
 */
void eu030(char *ans) {
  int fp[10] = { 0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049 };
  int t = 0;

  for (int n = 10; n < 413344; n++) {
    int digit5sum = 0;
    int v = n;
    while (v > 0) {
      int d = v % 10;
      v = v / 10;
      digit5sum += fp[d];
    }
    if (digit5sum == n) {
      t += n;
    }
  }

  sprintf(ans, "%d", t);
}
