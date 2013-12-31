#include "euler.h"

#define N 300000
#define MOD 1000000


//
// Uses the recurrence relation from problem 76, but
// calculates over the field Z / Z_1000000.  Unlike in
// problem 76, the values P(n) are the actual values
// being asked for, since a single pile is a valid
// partition in this question.
//
void eu078(char *ans) {
  static int P[N+1];
  memset(P, 0, sizeof(P));

  P[0] = 1;
  P[1] = 1;

  for (int n = 2; n <= N; n++) {
    int sign = 1;
    int sum = 0;
    for (int k = 1; ; k++, sign = -sign) {
      int n1 = n - k * (3*k-1) / 2;
      int n2 = n - k * (3*k+1) / 2;

      if (n1 < 0) break;

      sum += P[n1] * sign;
      if (n2 >= 0) sum += P[n2] * sign;
    }

    sum %= MOD;
    if (sum < 0) sum += MOD;

    P[n] = sum;
    if (sum == 0) {
      sprintf(ans, "%d", n);
      return;
    }
  }
}
