#include "euler.h"

/* Count the divisors of n.  We use the trick that
 * divisors are symmetric: if d is a divisor, then
 * so is n/d, so we only have to count up to the
 * square root of n.
 */
int divisors(int n) {
  int count = 0, i;
  for (i = 1; i * i < n; i++) {
    if (n % i == 0) count += 2;
  }
  /* If n is a square, then sqrt(n) is a divisor
   * that has no pair. */
  if (i * i == n) count += 1;
  return count;
}

/* Add up the divisors of n, not counting n itself.
 * Same trick as divisors().
 */
int sumdivisors(int n) {
  int sum = 1, i;
  for (i = 2; i * i < n; i++) {
    if (n % i == 0) sum += i + n/i;
  }
  if (i * i == n) sum += i;
  return sum;
}

void eu012(char *ans) {
  int n = 0;

  for (int i = 1; ; i++) {
    int ndiv;
    n += i;
    ndiv = divisors(n);
    if (ndiv > 500) {
      sprintf(ans, "%d", n);
      return;
    }
  }
}
