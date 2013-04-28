#include "euler.h"

int charcmp(const void *a, const void *b) {
  const char *aa = a;
  const char *bb = b;
  return *aa - *bb;
}

void digitsort(char *buf, int n) {
  sprintf(buf, "%d", n);
  qsort(buf, strlen(buf), 1, charcmp);
}

/*
 * Find the smallest positive integer, x, such that
 * 2x, 3x, 4x, 5x, and 6x, contain the same digits.
 */
void eu052(char *ans) {
  int x = 1;

  for (;;) {
    x++;
    int allsame = 1;
    char digits1[20];
    digitsort(digits1, 2*x);
    for (int k = 3; k <= 6; k++) {
      char digits2[20];
      digitsort(digits2, k*x);
      if (strcmp(digits1, digits2) != 0) {
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
