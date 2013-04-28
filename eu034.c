#include "euler.h"

/* Find numbers that are the sum of the factorial
 * of their digits.
 *
 * The highest possible number is 9!*7 = 2,540,160.
 */
void eu034(char *ans) {
  int fact[10];
  int total = 0;

  fact[0] = 1;
  for (int i = 1, t=1; i < 10; i++) {
    t *= i;
    fact[i] = t;
  }

  for (int i = 10; i <= 2540160; i++) {
    int sum = 0;
    int n = i;

    while (n > 0) {
      int d = n % 10;
      n /= 10;
      sum += fact[d];
    }
    if (sum == i) {
       total += sum;
    }
  }
  sprintf(ans, "%d", total);
}
