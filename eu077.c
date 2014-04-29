#include "euler.h"

#define N 5000
#define MAXPRIME (N*10)


void eu077(char *ans) {
  static char sieve[MAXPRIME+1];
  static int sum[N+1][N+1];

  gensieve(sieve, MAXPRIME+1);

  memset(sum, 0, sizeof(sum));

  // sum[i][j] is the number of ways of making i with numbers
  // less than or equal to j.
  //
  // sum[i][1] = i
  // sum[N][N] is the answer.

  for (int i = 2; i < N; i++) {
    sum[i][2] = 1;
    for (int j = 2; j < i; j++) {
      if (sieve[j]) {
        sum[i][j] = sum[i][j-1];
        continue;
      }
      int s;
      // We can make i from j + (i-j) as long as i-j
      // is made up of numbers less than j
      // There are sum[i-j][j] ways to do this.
      // The extra 1 comes from using j and i-j directly
      // as a two-sum. This is only possible if i-j is no
      // more than j AND IS A PRIME.

      if (i - j <= j && !sieve[i - j]) {
        s = 1;
      } else {
        s = 0;
      }
      sum[i][j] = sum[i][j-1] + sum[i-j][j] + s;
    }

    for (int j = i; j <= N; j++) {
      sum[i][j] = sum[i][i-1];
    }

    sum[i][i] = sum[i][i-1];
    if (sum[i][i] > N) {
      sprintf(ans, "%d", i);
      return;
    }
  }
}
