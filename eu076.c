#include "euler.h"

#define N 100


//
// Using Euler's generating function for a recurrence relation:
// see equation (11) on this page:
//   http://mathworld.wolfram.com/PartitionFunctionP.html
//
// We cache values in the P array so that P[n] is the partition
// number of n.  The question asks for the ways 2 or more numbers
// can sum to the value, so P() is off by one because it includes
// the degenerate sum n = n.
//
void eu076(char *ans) {
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

    P[n] = sum;
  }

  sprintf(ans, "%d", P[N] - 1);
}
