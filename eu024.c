#include "euler.h"

/* http://stackoverflow.com/a/362714 */
void genperm(char *ans, const char *xs, int len, const int perm, const int *fact) {
  if (len == 1) {
    *ans = xs[0];
    return;
  }

  char *buf = malloc(len);
  int p = (perm / fact[len - 1]) % len;
  *ans = xs[p];

  char *bp = buf;
  for (int i = 0; i < len; i++) {
    if (i != p) *bp++ = xs[i];
  }
  genperm(ans + 1, buf, len - 1, perm % fact[len-1], fact);
  free(buf);
}

void eu024(char *ans) {
  const int N = 10;
  const int perm = 1000000;
  int fact[N];

  for (int n = 1, i = 1; i < N; i++) {
    fact[i] = n;
    n *= i+1;
  }

  genperm(ans, "0123456789", 10, perm-1, fact);
}
