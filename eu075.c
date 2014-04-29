#include "euler.h"

#define N 1500000

void eu075(char *ans) {
  static int counts[N];
  memset(counts, 0, sizeof(counts));

  // Euclid's formula says that if m > n, then
  //   x = m^2-n^2
  //   y = 2mn
  //   z = m^2+n^2
  // is a pythagorean triple, and furthermore, if m and n
  // are coprime with opposite parity, then this formula
  // generates all primitive pythagorean triples.
  for (int m = 1; m * m < N; m++) {
    for (int n = 1; n < m; n++) {
      if (n % 2 == m % 2) continue; // opposite parity
      if (gcd(m, n) != 1) continue; // coprime

      int x = m*m - n*n;
      int y = 2*m*n;
      int z = m*m + n*n;
      int len = x + y + z;

      if (len < N) {
        /* printf("  %d %d: %d %d %d => %d\n", m, n, x, y, z, len); */

        // Mark off this triple and all its multiples up to N
        for (int k = len; k < N; k += len) {
          counts[k]++;
        }
      } else {
        break;
      }
    }
  }

  int count = 0;
  for (int i = 0; i < N; i++) {
    if (counts[i] == 1)
      count++;
  }

  sprintf(ans, "%d", count);
}

