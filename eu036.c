#include "euler.h"

int ispalindrome(char *a) {
  int i = 0, j = strlen(a) - 1;
  while (i < j) {
    if (a[i++] != a[j--])
      return 0;
  }
  return 1;
}

void base2(int n, char *a) {
  while (n) {
    *a++ = (n % 2 == 0) ? '0' : '1';
    n /= 2;
  }
  *a = 0;
}

/*
 * Sum of all numbers < 1,000,000 that are palindromic
 * in base 10 and base 2.
 */
void eu036(char *ans) {
  char buf[30];
  int t = 0;

  for (int i = 1; i < 1000000; i++) {
    sprintf(buf, "%d", i);
    if (ispalindrome(buf)) {
      base2(i, buf);
      if (ispalindrome(buf)) {
        t += i;
      }
    }
  }

  sprintf(ans, "%d", t);
}
