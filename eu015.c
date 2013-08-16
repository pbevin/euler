#include "euler.h"

/*
 * The answer in general is (2n)choose(n).
 * In our case, it's (40! / 20!20!)
 * We can calculate it using Pascal's Triangle.
 */
void eu015(char *ans) {
  const int N = 20;
  const int HEIGHT = N*2+1;
  const int WIDTH = N*2+1;
  long long a[HEIGHT][WIDTH];

  memset(a, 0, sizeof(a));

  a[0][0] = 1;
  for (int i = 1; i < HEIGHT; i++) {
    a[i][0] = 1;
    for (int j = 1; j < i; j++) {
      a[i][j] = a[i-1][j-1] + a[i-1][j];
    }
    a[i][i] = 1;
  }
  sprintf(ans, "%lld", a[40][20]);
}
