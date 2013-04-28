#include "euler.h"

/* What number a+b+c under 1000 has the maximum integer
 * solutions to a^2+b^2=c^2 ?
 */

void eu039(char *ans) {
  int count[1001];

  memset(count, 0, sizeof(count));

  for (int c = 1; c < 1000; c++) {
    for (int b = 1; b <= c && b+c <= 1000; b++) {
      for (int a = 1; a <= b && a+b+c <= 1000; a++) {
        // Sides are a < b < c
        if (a*a + b*b == c*c) {
          count[a+b+c]++;
        }
      }
    }
  }

  int max = 0, a;
  for (int i = 0; i < 1000; i++) {
    if (count[i] > max) {
      max = count[i];
      a = i;
    }
  }
  sprintf(ans, "%d", a);
}
