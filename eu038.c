#include "euler.h"

int ispandigital(char *prod) {
  char seen[10];
  char *p = prod;
  memset(seen, 0, 10);
  while (*p) {
    int d = *p - '0';
    if (d == 0 || seen[d]) {
      return 0;
    }
    seen[d] = 1;
    p++;
  }
  return 1;
}

void eu038(char *ans) {
  int max = 0;
  for (int i = 0; i < 54321; i++) {
    char prod[20];
    int k = 1;
    int len;
    prod[0] = 0;
    while ((len = strlen(prod)) < 9) {
      sprintf(prod + len, "%d", i * k);
      k++;
    }
    if (len == 9 && ispandigital(prod)) {
      int n = atoi(prod);
      if (n > max) max = n;
    }
  }
  sprintf(ans, "%d", max);
}
