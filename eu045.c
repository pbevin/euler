#include "euler.h"

/*
 * Next number after 40755 that is triangular, pentagonal and hexagonal.
 *
 * T(n+1) - T(n) = n+1
 * P(n+1) - P(n) = 3n+1
 * H(n+1) - H(n) = 4n+1
 */
void eu045(char *ans) {
  int a = 285, b = 165, c = 143;
  int ta = 40755, pb = ta, hc = ta;

  for (;;) {
    hc += 4*c+1;
    c++;

    while (pb < hc) {
      pb += 3*b+1;
      b++;
    }
    while (ta < hc) {
      ta += a+1;
      a++;
    }

    if (ta == pb && pb == hc) {
      sprintf(ans, "%d", ta);
      return;
    }
  }
}
