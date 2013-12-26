#include "euler.h"

#define N 10000000

void
eu070(char *ans) {
  static int phi[N];

  genphi(phi, N);

  double min = 1000.0;
  int i_of_min = 0;
  for (int i = 2; i < N; i++) {
    if (isperm(i, phi[i])) {
      double ratio = (double)i / phi[i];
      if (ratio < min) {
        /* printf("%d %d %g\n", i, phi[i], ratio); */
        min = ratio;
        i_of_min = i;
      }
    }
  }

  sprintf(ans, "%d", i_of_min);
}
