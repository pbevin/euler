#include "euler.h"

/*
 * How many ways can you make 200 using coins
 * 1,2,5,10,20,50,100,200?
 *
 * Let a(i,x) be the number of ways of making up x using
 * only the first i denominations.
 *
 * Then a(1,x) = 1, and
 *   a(i+1,x) = a(i,x) + a(i+1,x-v(i)).
 * (e.g., to make up 13p using 1, 2 and 5, you can either
 * not use a 5 at all a(i,x) ways, or make 8p and add a 5.
 */
void eu031(char *ans) {
  const int N = 200;
  int coins[8] = { 1,2,5,10,20,50,100,200 };
  int a[N+1];

  for (int k = 0; k <= N; k++) a[k] = 1;

  for (int i = 1; i < 8; i++) {
    int v = coins[i];
    for (int k = v; k <= N; k++) {
      a[k] += a[k-v];
    }
  }

  sprintf(ans, "%d", a[N]);
}
