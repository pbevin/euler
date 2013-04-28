#include "euler.h"

/*
 * Find all products that are a permutation of 1..9
 * e.g., 39 * 186 = 7254.
 */
void eu032(char *ans) {
  char buf[12], *s = buf;
  strcpy(s, "123456789");
  int len = strlen(s);
  int seen[1000];
  int nseen = 0;
  int t = 0;

  while (s) {
    for (int i = 1; i < len-1; i++) {
      for (int j = i+1; j < len; j++) {
        int a = subint(s, 0, i);
        int b = subint(s, i, j);
        int c = subint(s, j, len);

        if (a * b == c) {
          int seenit = 0;
          for (int k = 0; k < nseen; k++) {
            if (c == seen[k]) {
              seenit++;
              break;
            }
          }
          if (!seenit) {
            seen[nseen++] = c;
          }
        }
      }
    }
    s = nextperm(s);
  }

  for (int i = 0; i < nseen; i++) {
    t += seen[i];
  }

  sprintf(ans, "%d", t);
}
